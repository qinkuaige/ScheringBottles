#pragma once
#include <FlyCapture2.h>
#include <opencv/cv.h>

class Camera
{
public:
	Camera();
	~Camera();

	int init(); //�����ʼ��
	int captureImages(CWnd* pWnd); //����ͼƬ
	void ShowMatImgToWnd(CWnd* pWnd, cv::Mat img);

private:
	FlyCapture2::BusManager m_busMgr; //�������
	unsigned int  m_numCameras; //����������ĸ���
	FlyCapture2::PGRGuid m_guid; //���GUID
	FlyCapture2::Camera m_cam; //��� 
	FlyCapture2::CameraInfo  m_camInfo; //�����Ϣ
};

