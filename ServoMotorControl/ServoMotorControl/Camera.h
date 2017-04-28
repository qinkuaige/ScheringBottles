#pragma once
#include <FlyCapture2.h>
#include <list>
using namespace std;

struct Image
{
	UINT width;
	UINT highly;
	unsigned  char* data; //����

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
	Camera();
	~Camera();

	int init(); //�����ʼ��
	int captureImages(int number);
	CImage* get_image();
	static void Stretchimage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth);
private:
	FlyCapture2::BusManager m_busMgr; //�������
	unsigned int  m_numCameras; //����������ĸ���
	FlyCapture2::PGRGuid m_guid; //���GUID
	FlyCapture2::Camera m_cam; //��� 
	FlyCapture2::CameraInfo  m_camInfo; //�����Ϣ
	list<Image*> m_Image; //��������ͼƬ
	HANDLE m_mutex; //�߳���
};

