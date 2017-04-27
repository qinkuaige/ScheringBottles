#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
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
		m_cam.RetrieveBuffer(&rawImage);//捕获帧  
		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);//图像转换
		Image* image = new Image;
		image->data = new unsigned char[rgbImage.GetReceivedDataSize()];
		sprintf((char*)image->data, "%s", rgbImage.GetData());
		image->width = rgbImage.GetCols();
		image->highly = rgbImage.GetRows();
		m_Image.push_back(image);
	}
	return 0;
}

CImage* Camera::get_image()
{
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
	return picture;

}


void Camera::Stretchimage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth)
{
	if (pImage->IsDIBSection())
	{
		// 取得 pImage 的 DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image 因為有自己的 DC, 所以必須使用 FromHandle 取得對應的 DC



		CBitmap *bitmap1 = pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);
		ResultImage->Create(StretchWidth, StretchHeight, bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		ResultImageDC->SetStretchBltMode(HALFTONE); // 使用最高品質的方式
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL); // 調整 Brush 的起點
		StretchBlt(*ResultImageDC, 0, 0, StretchWidth, StretchHeight, *pImageDC1, 0, 0, pImage->GetWidth(), pImage->GetHeight(), SRCCOPY);
		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
}