
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

/*draw rectangle*/
/*
int main(int argc, char** argv)
{
	//--OpenCV 2.x 구현 --//
	Mat image(512, 512, CV_8UC3, Scalar(0, 255, 255)), result;
	rectangle(image, Point(100, 100), Point(400, 400), CV_RGB(255, 0, 0));
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);
	rectangle(image, Point(400 / 2, 100 / 2), Point(100 / 2, 400 / 2), CV_RGB(0, 0, 255));
	namedWindow("Drawing Graphics", CV_WINDOW_AUTOSIZE);
	imshow("Drawing Graphics", image);
	waitKey(0);// Wait for a keystroke in the window
	cvDestroyWindow("Drawing Graphics");
	return 0;
}

*/

int w = 512;// 생성 영상의 크기 설정
void MyLine(Mat img, Point start, Point end);
void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);
int main(int argc, char** argv)
{
	int k;
	//--OpenCV 2.x 구현 --//
	/// Windows names
	char atom_window[] = "Drawing 1: Atom";
	/// Create black empty images
	Mat atom_image = Mat::zeros(w, w, CV_8UC3);
	namedWindow(atom_window);

	//-- 메뉴 표시하기 ---//
	cout << "1 - 타원 그리기" << std::endl;
	cout << "2 - 채워진 원 그리고" << std::endl;
	cout << "3 - 사각형 그리기" << std::endl;
	cout << "4 - 라인 그리기" << std::endl;
	/// 1. Draw a simple atom:
	k = waitKey(0);
	if (k == 49) {
		/// 1.a. Creating ellipses
		MyEllipse(atom_image, 90);
		MyEllipse(atom_image, 0);
		MyEllipse(atom_image, 45);
		MyEllipse(atom_image, -45);
	}
	else if (k == 50) {
		/// 1.b. Creating circles
		MyFilledCircle(atom_image, Point(w / 2.0, w / 2.0));
	}
	else if (k == 51) {
		/// 2.b. Creating rectangles
		rectangle(atom_image, Point(0, 7 * w / 8.0), Point(w, w), Scalar(0, 255, 255),
			-1, 8);
	}
	else if (k == 52) {
		/// 2.c. Create a few lines
		MyLine(atom_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
		MyLine(atom_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
		MyLine(atom_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
		MyLine(atom_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
	}
	imshow(atom_window, atom_image);
	waitKey(0);// Wait for a keystroke in the window
	cvDestroyWindow("Drawing Graphics");
	return 0;
}
}
else if (k == 52) {
/// 2.c. Create a few lines
MyLine(atom_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
MyLine(atom_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
MyLine(atom_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
MyLine(atom_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
}
imshow(atom_window, atom_image);
waitKey(0);// Wait for a keystroke in the window
return 0;
}

void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img, start, end,
		Scalar(0, 0, 255),
		thickness,
		lineType);
}
void MyFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle(img, center, w / 6.0, Scalar(0, 0, 255), thickness, lineType);
}
void MyEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(img, Point(w / 2.0, w / 2.0), Size(w / 4.0, w / 16.0), angle, 0, 360,
		Scalar(255, 0, 0), thickness, lineType);
}