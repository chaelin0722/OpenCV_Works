#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;
void mouseEvent(int event, int x, int y, int flags, void* params);
// 클릭한 픽셀값의 rgb 컬러 중 max 값에 255 할당 
int main(int argc, char** argv) {
	Mat image, result;

	image = imread(argv[1], 1); // 1 이면 컬러 0 이면 흑백
	
	//다른 방법은 Mat result = Mat::zeros(image.size(), image.type())

	namedWindow("original");

	setMouseCallback("original", mouseEvent, &image);

	imshow("original", image);

	
	result = image.clone();  // 이미지의 크기, depth 등을 모두 같게 하는 것

	namedWindow("result");
	imshow("result", result);


	waitKey(0);
	destroyWindow("original");
	return 0;
}

void mouseEvent(int event, int x, int y, int flags, void* params) {
	Mat* rgb = (Mat*)params;
	
	if (event == EVENT_LBUTTONDOWN) {
		int r, g, b;
		b = (*rgb).at<Vec3b>(x, y)[0];
		g = (*rgb).at<Vec3b>(x, y)[1];
		r = (*rgb).at<Vec3b>(x, y)[2];

		if ((r > g) && (r > b)) {
			r = 255;
			b = 0;
			g = 0;
		}
		else if ((g > r) && (g > b)) {
			g = 255;
			r = 0;
			b = 0;

		}
		else if ((b > r) && (b > g)) {
			b = 255;
			r = 0;
			g = 0;
		}
		else if (r == b == g) {
			r = b = g = 0;
		}

		printf("x: %d, y: %d, r: %d, g: %d, b: %d\n", x, y,
			r,g, b);
	}
}
//threshold 없이 이진화 하는 방법은 아래와 같다. 
/*
	//이진화 하기
	int value = image.at<uchar>(x, y);

	if (value > th) {
		result.at<uchar>(x, y) = 255;
	}
	else {
		result.at<uchar>(x, y) = 0;
	}
	// 아래는 반전! 색반전이됨
	result.at<Vec3b>(x, y)[0] = 255 - image.at<Vec3b>(x, y)[0];  //biue
	result.at<Vec3b>(x, y)[1] = 255 - image.at<Vec3b>(x, y)[1];  //green
	result.at<Vec3b>(x, y)[2] = 255 - image.at<Vec3b>(x, y)[2];   //red
	*/