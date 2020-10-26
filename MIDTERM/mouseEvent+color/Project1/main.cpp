#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;
void mouseEvent(int event, int x, int y, int flags, void* params);
// Ŭ���� �ȼ����� rgb �÷� �� max ���� 255 �Ҵ� 
int main(int argc, char** argv) {
	Mat image, result;

	image = imread(argv[1], 1); // 1 �̸� �÷� 0 �̸� ���
	
	//�ٸ� ����� Mat result = Mat::zeros(image.size(), image.type())

	namedWindow("original");

	setMouseCallback("original", mouseEvent, &image);

	imshow("original", image);

	
	result = image.clone();  // �̹����� ũ��, depth ���� ��� ���� �ϴ� ��

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
//threshold ���� ����ȭ �ϴ� ����� �Ʒ��� ����. 
/*
	//����ȭ �ϱ�
	int value = image.at<uchar>(x, y);

	if (value > th) {
		result.at<uchar>(x, y) = 255;
	}
	else {
		result.at<uchar>(x, y) = 0;
	}
	// �Ʒ��� ����! �������̵�
	result.at<Vec3b>(x, y)[0] = 255 - image.at<Vec3b>(x, y)[0];  //biue
	result.at<Vec3b>(x, y)[1] = 255 - image.at<Vec3b>(x, y)[1];  //green
	result.at<Vec3b>(x, y)[2] = 255 - image.at<Vec3b>(x, y)[2];   //red
	*/