/*MOUSE EVENT 구현하기 - BUTTON*/
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
void my_mouse_callback(int event, int x, int y, int flags, void* param); // 함수 선언
int main(int argc, char** argv)
{
	//--- 마우스 이벤트 구현 ---//
	int i, j, k;
	Mat image;
	image.create(500, 500, CV_8UC3);
	namedWindow("Main");
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			for (k = 0; k < 3; k++) {
				Vec3b& intensity = image.at<Vec3b>(j, i);
				intensity.val[k] = 0;
			}
		}
	}
	setMouseCallback("Main", my_mouse_callback, &image);
	imshow("Main", image);
	waitKey(0); // Wait for anu user’s key stroke….!!!!!
	return 0;
}
//--- 마우스 이벤트 구현함 --//
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	int thickness = -1;
	int lineType = 8;
	if (event == EVENT_LBUTTONDOWN) {
		cout << "Left button has been clicked (" << x << "," << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN) {
		cout << "Right button has been clicked (" << x << "," << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE) {
		cout << "Mouse has been moved (" << x << "," << y << ")" << endl;
	}
}