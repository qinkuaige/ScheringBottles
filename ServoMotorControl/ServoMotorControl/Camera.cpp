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

	return 0;
}
