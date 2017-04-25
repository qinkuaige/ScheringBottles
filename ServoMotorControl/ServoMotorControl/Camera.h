#pragma once
#include <FlyCapture2.h>

class Camera
{
public:
	Camera();
	~Camera();

	int init(); //�����ʼ��
private:
	FlyCapture2::BusManager m_busMgr; //�������
	unsigned int  m_numCameras; //����������ĸ���
	FlyCapture2::PGRGuid m_guid; //���GUID
	FlyCapture2::Camera m_cam; //��� 
	FlyCapture2::CameraInfo  m_camInfo; //�����Ϣ
};

