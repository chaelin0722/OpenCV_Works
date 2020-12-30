/*
 * Copyright (c) 2016-2019 Yoshihisa Nitta
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */
/* http://nw.tsuda.ac.jp/lec/kinect2/ */

#include <iostream>
#include <sstream>

#include "NtKinect.h"

using namespace std;

void doJob() {
  NtKinect kinect;
  while (1) {
    kinect.setRGB();
    kinect.setDepth();
    for (int y = 0; y < kinect.depthImage.rows; y++) {
      for (int x = 0; x < kinect.depthImage.cols; x++) {
	UINT16 d = kinect.depthImage.at<UINT16>(y, x);
	DepthSpacePoint dp; dp.X = x; dp.Y = y;
	ColorSpacePoint cp;
	HRESULT hr = kinect.coordinateMapper->MapDepthPointToColorSpace(dp, d, &cp);
	if (hr != S_OK) continue;
	if (d > 2000 || d < 500) {
	  int ax = (int)cp.X;
	  int ay = (int)cp.Y;
	  cv::rectangle(kinect.rgbImage, cv::Rect(ax - 2, ay - 2, 4, 4), cv::Scalar(255, 0, 0), 2);
	}
      }
    }
    cv::imshow("rbg near", kinect.rgbImage);
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
