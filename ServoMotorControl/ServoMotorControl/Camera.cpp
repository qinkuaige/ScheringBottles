#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	m_mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("memtest"));
	if (m_mutex == NULL)
	{
		m_mutex = CreateMutex(NULL, FALSE, TEXT("memtest"));
	}
}


Camera::~Camera()
{
}

int Camera::init()
{

	m_busMgr.GetNumOfCameras(&m_numCameras);
	m_busMgr.GetCameraFromIndex(1, &m_guid);
	m_cam.Connect(&m_guid);
	m_cam.GetCameraInfo(&m_camInfo);
	m_cam.StartCapture();
	return 0;
}

int  Camera::captureImages(int number)
{
	for (size_t i = 0; i < number; i++)
	{
		FlyCapture2::Image rawImage;
		FlyCapture2::Image  rgbImage;
		m_cam.RetrieveBuffer(&rawImage);//²¶»ñÖ¡  
		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);//Í¼Ïñ×ª»»
		Image* image = new Image;
		image->data = new unsigned char[rgbImage.GetDataSize()];
		sprintf((char*)image->data, "%s", rgbImage.GetData());
		image->width = rgbImage.GetCols();
		image->highly = rgbImage.GetRows();
		WaitForSingleObject(m_mutex, INFINITE); //¼ÏËø
		m_Image.push_back(image);
		ReleaseMutex(m_mutex); //½âËø
	}
	return 0;
}

CImage* Camera::get_image()
{
	WaitForSingleObject(m_mutex, INFINITE); //¼ÏËø
	if (m_Image.size() == 0)
	{
		return NULL;
	}
	Image* image = *(m_Image.begin());
	if (image == NULL)
	{
		return NULL;
	}
	
	CImage*  picture  = new CImage;
	picture->Create(image->width , image->highly , 32, CImage::createAlphaChannel);
	int  rr = 0, gg = 0, bb = 0;
	for (int y = 0; y < image->highly; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			unsigned char rgb = image->data[y*image->width + x];
			picture->SetPixel(x, y, RGB(rgb, rgb, rgb));
		}
	}
	m_Image.pop_front();
	ReleaseMutex(m_mutex); //½âËø
	return picture;

}


void Camera::Stretchimage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth)
{
	if (pImage->IsDIBSection())
	{
		// È¡µÃ pImage µÄ DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); 
		CBitmap *bitmap1 = pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);
		ResultImage->Create(StretchWidth, StretchHeight, bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		ResultImageDC->SetStretchBltMode(HALFTONE);
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL);
		StretchBlt(*ResultImageDC, 0, 0, StretchWidth, StretchHeight, *pImageDC1, 0, 0, pImage->GetWidth(), pImage->GetHeight(), SRCCOPY);
		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
}