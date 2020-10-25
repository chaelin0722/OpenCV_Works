#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

void my_mouse_callback(int event, int x, int y, int flags, void* params);

int main(int argc, char** argv) {
	
	//���콺 �̺�Ʈ �����ϱ�
	int i, j, k;
	Mat image;
	image.create(500, 500, CV_8UC3);

	namedWindow("Main");

	// 500 X 500 ���� ȭ�� �����
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			for (k = 0; k < 3; k++) {
				Vec3b& intensity = image.at<Vec3b>(j, i); // 500x500 �ȼ��̹�������
				intensity.val[k] = 0; //�� ȭ�ҿ� 3���� �Ƹ� rgb���ٰ� 0����ֱ� -> ����ȭ��
			}
		}

	} // end for
	setMouseCallback("Main", my_mouse_callback, &image);
	imshow("Main", image);

	waitKey(0);
	return 0;
}

void my_mouse_callback(int event, int x, int y, int flags, void* params) {
	
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