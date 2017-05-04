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
	
	CImage*  picture  = new CImage;
	//picture->Create(image->width, image->highly, 32 ,Cmage::createAlphaChannel);
	picture->CreateEx(image->width, image->highly, 32, 0);
	auto x_pixel = image->width * 3; //每行像素点拆分为 R G B 
	for (int y = 0; y < image->highly; y++)
	{
		auto y_pixel = y * x_pixel; //第y行第一个像素点
		for (int x = 0; x < image->width; x++)
		{
			auto current_pixel = x * 3;
			
			picture->SetPixelRGB(x, y, image->data[y_pixel + current_pixel], image->data[y_pixel + current_pixel + 1], current_pixel + 2);
		}
	}
	m_Image.pop_front();
	ReleaseMutex(m_mutex); //解锁
	return picture;
}

