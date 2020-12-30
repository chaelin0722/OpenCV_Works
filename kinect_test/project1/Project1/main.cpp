
#include <iostream>
#include <sstream>

#include "NtKinect.h"

using namespace std;

void doJob() {
	NtKinect kinect;
	while (1) {
		kinect.setDepth(false);
		cv::imshow("depth", kinect.depthImage);
		auto key = cv::waitKey(1);
		if (key == 'q') break;
	}
	cv::destroyAllWindows();
}

int main(int argc, char** argv) {
	try {
		doJob();
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		string s;
		cin >> s;
	}
	return 0;
}


/*
#pragma once

#include <windows.h>
#include "Kinect.h"
#pragma comment (lib, "kinect20.lib")

#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>
using namespace std;



// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface*& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

HRESULT get_colour_frame(Mat& frame_content, INT& frame_width, INT& frame_height, IKinectSensor* m_pKinectSensor)
{
	HRESULT hr;

	IColorFrameReader* m_pFrameReader = NULL;
	IColorFrameSource* pFrameSource = NULL;

	hr = m_pKinectSensor->get_ColorFrameSource(&pFrameSource);

	if (FAILED(hr))
	{
		cout << "get_ColorFrameSource error" << endl;
		return hr;
	}

	hr = pFrameSource->OpenReader(&m_pFrameReader);

	if (FAILED(hr))
	{
		cout << "OpenReader error" << endl;
		return hr;
	}

	SafeRelease(pFrameSource);

	IColorFrame* pFrame = NULL;
	hr = m_pFrameReader->AcquireLatestFrame(&pFrame);

	if (FAILED(hr))
	{
		cout << "AcquireLatestFrame error" << endl;
		return hr;
	}

	IFrameDescription* pDescription = NULL;
	hr = pFrame->get_FrameDescription(&pDescription);

	if (FAILED(hr))
	{
		cout << "get_FrameDescription error" << endl;
		return hr;
	}

	hr = pDescription->get_Width(&frame_width);

	if (FAILED(hr))
	{
		cout << "get_Width error" << endl;
		return hr;
	}

	hr = pDescription->get_Height(&frame_height);

	if (FAILED(hr))
	{
		cout << "get_Height error" << endl;
		return hr;
	}

	SafeRelease(pDescription);

	UINT nBufferSize = 0; // Number of bytes in pBuffer
	BYTE* pBuffer = NULL;
	hr = pFrame->AccessRawUnderlyingBuffer(&nBufferSize, &pBuffer);

	if (FAILED(hr))
	{
		cout << "AccessRawUnderlyingBuffer error" << endl;
		return hr;
	}

	// check out convertTo member function
	//cvtColor(in, out, CV_BGRA2BGR);
	frame_content = Mat(frame_height, frame_width, CV_8UC4, pBuffer).clone();

	cvtColor(frame_content, frame_content, COLOR_RGBA2BGR);

	SafeRelease(pFrame);
	SafeRelease(m_pFrameReader);

	return S_OK;
}

HRESULT get_depth_frame(Mat& frame_content, INT& frame_width, INT& frame_height, IKinectSensor* m_pKinectSensor)
{
	HRESULT hr;

	IDepthFrameReader* m_pFrameReader = NULL;
	IDepthFrameSource* pFrameSource = NULL;

	hr = m_pKinectSensor->get_DepthFrameSource(&pFrameSource);

	if (FAILED(hr))
	{
		cout << "get_DepthFrameSource error" << endl;
		return hr;
	}

	hr = pFrameSource->OpenReader(&m_pFrameReader);

	if (FAILED(hr))
	{
		cout << "OpenReader error" << endl;
		return hr;
	}

	SafeRelease(pFrameSource);

	IDepthFrame* pFrame = NULL;
	hr = m_pFrameReader->AcquireLatestFrame(&pFrame);

	if (FAILED(hr))
	{
		cout << "AcquireLatestFrame error" << endl;
		return hr;
	}

	IFrameDescription* pDescription = NULL;
	hr = pFrame->get_FrameDescription(&pDescription);

	if (FAILED(hr))
	{
		cout << "get_FrameDescription error" << endl;
		return hr;
	}

	hr = pDescription->get_Width(&frame_width);

	if (FAILED(hr))
	{
		cout << "get_Width error" << endl;
		return hr;
	}

	hr = pDescription->get_Height(&frame_height);

	if (FAILED(hr))
	{
		cout << "get_Height error" << endl;
		return hr;
	}

	SafeRelease(pDescription);

	UINT nBufferSize = 0; // Number of bytes in pBuffer
	UINT16* pBuffer = NULL;
	hr = pFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);

	if (FAILED(hr))
	{
		cout << "AccessUnderlyingBuffer error" << endl;
		return hr;
	}

	frame_content = Mat(frame_height, frame_width, CV_16UC1, pBuffer).clone();

	//Mat byte_frame_content(frame_height, frame_width, CV_8UC3);

	//for (int j = 0; j < frame_content.rows; j++)
	//{
	//	for (int i = 0; i < frame_content.cols; i++)
	//	{
	//		UINT16 a = frame_content.at<UINT16>(j, i);

	//		BYTE hi = (a >> 8) & 0xff;
	//		BYTE low = (a >> 0) & 0xff;
	//		byte_frame_content.at<Vec3b>(j, i)[0] = hi;
	//		byte_frame_content.at<Vec3b>(j, i)[1] = low;
	//		byte_frame_content.at<Vec3b>(j, i)[2] = 0;
	//	}
	//}

	//frame_content = byte_frame_content.clone();

	Mat float_frame_content(frame_height, frame_width, CV_32FC1);

	for (int j = 0; j < frame_content.rows; j++)
		for (int i = 0; i < frame_content.cols; i++)
			float_frame_content.at<float>(j, i) = frame_content.at<UINT16>(j, i) / 65535.0f;

	frame_content = float_frame_content.clone();

	SafeRelease(pFrame);
	SafeRelease(m_pFrameReader);

	return S_OK;
}

HRESULT get_infrared_frame(Mat& frame_content, INT& frame_width, INT& frame_height, IKinectSensor* m_pKinectSensor)
{
	HRESULT hr;

	IInfraredFrameReader* m_pFrameReader = NULL;
	IInfraredFrameSource* pFrameSource = NULL;

	hr = m_pKinectSensor->get_InfraredFrameSource(&pFrameSource);

	if (FAILED(hr))
	{
		cout << "get_InfraredFrameSource error" << endl;
		return hr;
	}

	hr = pFrameSource->OpenReader(&m_pFrameReader);

	if (FAILED(hr))
	{
		cout << "OpenReader error" << endl;
		return hr;
	}

	SafeRelease(pFrameSource);

	IInfraredFrame* pFrame = NULL;
	hr = m_pFrameReader->AcquireLatestFrame(&pFrame);

	if (FAILED(hr))
	{
		cout << "AcquireLatestFrame error" << endl;
		return hr;
	}

	IFrameDescription* pDescription = NULL;
	hr = pFrame->get_FrameDescription(&pDescription);

	if (FAILED(hr))
	{
		cout << "get_FrameDescription error" << endl;
		return hr;
	}

	hr = pDescription->get_Width(&frame_width);

	if (FAILED(hr))
	{
		cout << "get_Width error" << endl;
		return hr;
	}

	hr = pDescription->get_Height(&frame_height);

	if (FAILED(hr))
	{
		cout << "get_Height error" << endl;
		return hr;
	}

	SafeRelease(pDescription);

	UINT nBufferSize = 0; // Number of bytes in pBuffer
	UINT16* pBuffer = NULL;
	hr = pFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);

	if (FAILED(hr))
	{
		cout << "AccessUnderlyingBuffer error" << endl;
		return hr;
	}

	frame_content = Mat(frame_height, frame_width, CV_16UC1, pBuffer).clone();

	//Mat byte_frame_content(frame_height, frame_width, CV_8UC3);

	//for (int j = 0; j < frame_content.rows; j++)
	//{
	//	for (int i = 0; i < frame_content.cols; i++)
	//	{
	//		UINT16 a = frame_content.at<UINT16>(j, i);

	//		BYTE hi = (a >> 8) & 0xff;
	//		BYTE low = (a >> 0) & 0xff;
	//		byte_frame_content.at<Vec3b>(j, i)[0] = hi;
	//		byte_frame_content.at<Vec3b>(j, i)[1] = low;
	//		byte_frame_content.at<Vec3b>(j, i)[2] = 0;
	//	}
	//}

	//frame_content = byte_frame_content.clone();

	Mat float_frame_content(frame_height, frame_width, CV_32FC1);

	for (int j = 0; j < frame_content.rows; j++)
		for (int i = 0; i < frame_content.cols; i++)
			float_frame_content.at<float>(j, i) = frame_content.at<UINT16>(j, i) / 65535.0f;

	frame_content = float_frame_content.clone();

	SafeRelease(pFrame);
	SafeRelease(m_pFrameReader);

	return S_OK;
}

*/


/*
// Standard Library
#include <iostream>

// OpenCV Header
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// Kinect for Windows SDK Header
#include <Kinect.h>
PublicAdditionalLibraries.Add("'filepath'\Kinect20.lib")

using namespace std;

int main(int argc, char** argv)
{
	// 1a. Get default Sensor
	cout << "Try to get default sensor" << endl;
	IKinectSensor* pSensor = nullptr;
	if (GetDefaultKinectSensor(&pSensor) != S_OK)
	{
		cerr << "Get Sensor failed" << endl;
		return -1;
	}

	// 1b. Open sensor
	cout << "Try to open sensor" << endl;
	if (pSensor->Open() != S_OK)
	{
		cerr << "Can't open sensor" << endl;
		return -1;
	}

	// 2a. Get frame source
	cout << "Try to get color source" << endl;
	IColorFrameSource* pFrameSource = nullptr;
	if (pSensor->get_ColorFrameSource(&pFrameSource) != S_OK)
	{
		cerr << "Can't get color frame source" << endl;
		return -1;
	}

	// 2b. Get frame description
	cout << "get color frame description" << endl;
	int		iWidth = 0;
	int		iHeight = 0;
	IFrameDescription* pFrameDescription = nullptr;
	if (pFrameSource->get_FrameDescription(&pFrameDescription) == S_OK)
	{
		pFrameDescription->get_Width(&iWidth);
		pFrameDescription->get_Height(&iHeight);
	}
	pFrameDescription->Release();
	pFrameDescription = nullptr;

	// 3a. get frame reader
	cout << "Try to get color frame reader" << endl;
	IColorFrameReader* pFrameReader = nullptr;
	if (pFrameSource->OpenReader(&pFrameReader) != S_OK)
	{
		cerr << "Can't get color frame reader" << endl;
		return -1;
	}

	// 2c. release Frame source
	cout << "Release frame source" << endl;
	pFrameSource->Release();
	pFrameSource = nullptr;

	// Prepare OpenCV data
	cv::Mat	mImg(iHeight, iWidth, CV_8UC4);
	UINT uBufferSize = iHeight * iWidth * 4 * sizeof(BYTE);
	cv::namedWindow("Color Map");

	// Enter main loop
	while (true)
	{
		// 4a. Get last frame
		IColorFrame* pFrame = nullptr;
		if (pFrameReader->AcquireLatestFrame(&pFrame) == S_OK)
		{
			// 4c. Copy to OpenCV image
			if (pFrame->CopyConvertedFrameDataToArray(uBufferSize, mImg.data, ColorImageFormat_Bgra) == S_OK)
			{
				cv::imshow("Color Map", mImg);
			}
			else
			{
				cerr << "Data copy error" << endl;
			}

			// 4e. release frame
			pFrame->Release();
		}

		// 4f. check keyboard input
		if (cv::waitKey(30) == VK_ESCAPE) {
			break;
		}
	}

	// 3b. release frame reader
	cout << "Release frame reader" << endl;
	pFrameReader->Release();
	pFrameReader = nullptr;

	// 1c. Close Sensor
	cout << "close sensor" << endl;
	pSensor->Close();

	// 1d. Release Sensor
	cout << "Release sensor" << endl;
	pSensor->Release();
	pSensor = nullptr;

	return 0;
}

*/