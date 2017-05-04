#pragma once
#include <FlyCapture2.h>
#include <list>
using namespace std;

struct Image
{
	UINT width;
	UINT highly;
	unsigned  char* data; //像素

	Image() :width(0), highly(0), data(NULL)
	{

	}
	~Image()
	{
		if (this->data != NULL)
		{
			delete[] data;
			data = NULL;
		}
	}
};

class Camera
{
public:
	Camera(UINT ID = 0);
	~Camera();

	int init(); //相机初始化
	int captureImages(int number);
	CImage* get_image();
	
private:
	FlyCapture2::BusManager m_busMgr; //相机总线
	UINT  m_numCameras; //总线上相机的个数
	UINT  m_ID; //相机ID 
	FlyCapture2::PGRGuid m_guid; //相机GUID
	FlyCapture2::Camera m_cam; //相机 
	FlyCapture2::CameraInfo  m_camInfo; //相机信息
	list<Image*> m_Image; //相机拍摄的图片
	HANDLE m_mutex; //线程锁
};

