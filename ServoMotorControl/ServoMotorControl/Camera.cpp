#include "stdafx.h"
#include "Camera.h"


Camera::Camera(UINT ID) :m_numCameras(0),m_ID(ID)
{
	m_mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("image"));
	if (m_mutex == NULL)
	{
		m_mutex = CreateMutex(NULL, FALSE, TEXT("image"));
	}
	m_Image.clear();
}


Camera::~Camera()
{

}

int Camera::init()
{

	m_busMgr.GetNumOfCameras(&m_numCameras);
	m_busMgr.GetCameraFromIndex(m_ID, &m_guid);
	m_cam.Connect(&m_guid);
	m_cam.GetCameraInfo(&m_camInfo);
	return 0;
}

int  Camera::captureImages(int number)
{
	m_cam.StartCapture(); 
	for (size_t i = 0; i < number; i++)
	{
		FlyCapture2::Image rawImage;
		FlyCapture2::Image  rgbImage;
		m_cam.RetrieveBuffer(&rawImage);//捕获帧  
		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_RGB8, &rgbImage);//图像转换
		Image* image = new Image;
		memset(image, 0, sizeof(image));
		image->data = new unsigned char[rgbImage.GetDataSize()];
		memset(image->data, 0, sizeof(image));
		sprintf((char*)image->data, "%s", rgbImage.GetData());
		image->width = rgbImage.GetCols();
		image->highly = rgbImage.GetRows();
		WaitForSingleObject(m_mutex, INFINITE); //加锁
		m_Image.push_back(image);
		ReleaseMutex(m_mutex); //解锁
	}
	m_cam.StopCapture();
	return 0;
}

CImage* Camera::get_image()
{
	WaitForSingleObject(m_mutex, INFINITE); //加锁
	if (m_Image.empty())
	{
		return NULL;
	}
	Image* image = *(m_Image.begin());
	if (image == NULL)
	{
		return NULL;
	}
	
	CImage*  picture = new CImage; 
	
	if (picture->IsNull())
	{
		picture->Create(image->width,image->highly, 8 * 1);

		//设置调色板
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		ColorTable = new RGBQUAD[MaxColors];

		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		picture->SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	{//灰度图像   
		UCHAR *pImg = (UCHAR *)picture->GetBits();
		int step = picture->GetPitch();
		for (int i = 0; i < image->highly; i++)
		{
			memcpy(pImg + step * i, image->data + image->width * i, image->width);
		}
	}
	m_Image.pop_front();
	ReleaseMutex(m_mutex);
	return picture;
}

