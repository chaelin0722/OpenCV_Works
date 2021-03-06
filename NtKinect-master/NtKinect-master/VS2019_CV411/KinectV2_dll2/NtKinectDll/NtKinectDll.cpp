﻿#include "pch.h"
#include "framework.h"
#include "NtKinectDll.h"

#define USE_FACE
#include "NtKinect.h"

using namespace std;

NTKINECTDLL_API void* getKinect(void) {
  NtKinect* kinect = new NtKinect;
  return static_cast<void*>(kinect);
}

NTKINECTDLL_API int faceDirection(void* ptr,float *dir) {
  NtKinect *kinect = static_cast<NtKinect*>(ptr);
  (*kinect).setRGB();
  (*kinect).setSkeleton();
  (*kinect).setFace();
  int scale = 4;
  cv::Mat img((*kinect).rgbImage);
  cv::resize(img,img,cv::Size(img.cols/scale,img.rows/scale),0,0);
  for (auto person: (*kinect).skeleton) {
    for (auto joint: person) {
      if (joint.TrackingState == TrackingState_NotTracked) continue;
      ColorSpacePoint cp;
      (*kinect).coordinateMapper->MapCameraPointToColorSpace(joint.Position,&cp);
      cv::rectangle(img, cv::Rect((int)cp.X/scale-2, (int)cp.Y/scale-2,4,4), cv::Scalar(0,0,255),2);
    }
  }
  for (auto r: (*kinect).faceRect) {
    cv::Rect r2(r.x/scale,r.y/scale,r.width/scale,r.height/scale);
    cv::rectangle(img, r2, cv::Scalar(255, 255, 0), 2);
  }
  cv::imshow("face",img);
  cv::waitKey(1);
  int idx=0;
  for (auto d: (*kinect).faceDirection) {
    dir[idx++] = d[0];
    dir[idx++] = d[1];
    dir[idx++] = d[2];
  }
  return (*kinect).faceDirection.size();
}
