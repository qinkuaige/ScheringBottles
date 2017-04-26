#pragma once
#include <FlyCapture2.h>
#include <opencv/cv.h>

class Camera
{
public:
	Camera();
	~Camera();

	int init(); //相机初始化
	int captureImages(CWnd* pWnd); //捕获图片
	void ShowMatImgToWnd(CWnd* pWnd, cv::Mat img);

private:
	FlyCapture2::BusManager m_busMgr; //相机总线
	unsigned int  m_numCameras; //总线上相机的个数
	FlyCapture2::PGRGuid m_guid; //相机GUID
	FlyCapture2::Camera m_cam; //相机 
	FlyCapture2::CameraInfo  m_camInfo; //相机信息
};

