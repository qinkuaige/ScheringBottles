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

int  Camera::captureImages(CWnd* pWnd)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	FlyCapture2::Image rawImage;
	FlyCapture2::Image  rgbImage;
	m_cam.RetrieveBuffer(&rawImage);//����֡  
	rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);//ͼ��ת��
	unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows();

	cv::Mat image = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);
	ShowMatImgToWnd(pWnd, image);
	return 0;
}


void Camera::ShowMatImgToWnd(CWnd* pWnd, cv::Mat img)
{
	if (img.empty())
		return;

	CRect drect;
	pWnd->GetClientRect(&drect);    //(drect);  (&drect);  ���ַ�ʽ���ɣ���Ȼ	

	CClientDC dc(pWnd);
	HDC hDC = dc.GetSafeHdc();

	//�ڴ��е�ͼ�����ݿ�������Ļ��
	BYTE *bitBuffer = NULL;
	BITMAPINFO *bitMapinfo = NULL;

	int ichannels = img.channels();
	if (ichannels == 1)
	{
		bitBuffer = new BYTE[40 + 4 * 256];
	}
	else if (ichannels == 3)
	{
		bitBuffer = new BYTE[sizeof(BITMAPINFO)];
	}
	else
	{
		return;
	}


	if (bitBuffer == NULL)
	{
		return;
	}


	bitMapinfo = (BITMAPINFO *)bitBuffer;
	bitMapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitMapinfo->bmiHeader.biHeight = -img.rows;  //����߶�Ϊ���ģ�λͼ����ʼλ�������½ǡ�����߶�Ϊ������ʼλ�������Ͻǡ�
	bitMapinfo->bmiHeader.biWidth = img.cols;
	bitMapinfo->bmiHeader.biPlanes = 1;      // Ŀ���豸�ļ��𣬱���Ϊ1	
	bitMapinfo->bmiHeader.biBitCount = ichannels * 8;     // ÿ�����������λ����������1(˫ɫ), 4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ
	bitMapinfo->bmiHeader.biCompression = BI_RGB; //λͼѹ�����ͣ������� 0(��ѹ��), 1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ
	bitMapinfo->bmiHeader.biSizeImage = 0;      // λͼ�Ĵ�С�����ֽ�Ϊ��λ
	bitMapinfo->bmiHeader.biXPelsPerMeter = 0;	  // λͼˮƽ�ֱ��ʣ�ÿ��������
	bitMapinfo->bmiHeader.biYPelsPerMeter = 0;	  // λͼ��ֱ�ֱ��ʣ�ÿ��������
	bitMapinfo->bmiHeader.biClrUsed = 0;	  // λͼʵ��ʹ�õ���ɫ���е���ɫ��
	bitMapinfo->bmiHeader.biClrImportant = 0;	  // λͼ��ʾ��������Ҫ����ɫ��

	if (ichannels == 1)
	{
		for (int i = 0; i<256; i++)
		{	//��ɫ��ȡֵ��Χ (0-255)
			bitMapinfo->bmiColors[i].rgbBlue = bitMapinfo->bmiColors[i].rgbGreen = bitMapinfo->bmiColors[i].rgbRed = (BYTE)i;
		}

		bitMapinfo->bmiHeader.biClrUsed = 256;	  // λͼʵ��ʹ�õ���ɫ���е���ɫ��
	}
	SetStretchBltMode(hDC, COLORONCOLOR);


	StretchDIBits(hDC,
		0,
		0,
		drect.right,		//��ʾ���ڿ��
		drect.bottom,		//��ʾ���ڸ߶�
		0,
		0,
		img.cols,		   //ͼ����
		img.rows,		   //ͼ��߶�
		img.data,
		bitMapinfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);

	delete[]bitBuffer;

}