#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
/*
void mouseEvent(int event, int x, int y, int flags, void* param) {
	Mat* rgb = (Mat*) param;
	if (event == EVENT_LBUTTONDOWN) {
		printf("%d %d: %d, %d, %d\n", x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}

}

int main(int argc, char** argv) {

	Mat image, result;
	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	namedWindow("Display window");

	setMouseCallback("Display window", mouseEvent, &image);

	imshow("Display window", image);
	   	 
	waitKey(0);

	destroyWindow("Display window");
	destroyWindow("Processed image");
	return 0;
}

*/



/*
void my_mouse_callback(int event, int x, int y, int flags, void* params);
int main(int argc, char** argv) {
	
	//마우스 이벤트 구현하기
	int i, j, k;
	Mat image;
	image.create(500, 500, CV_8UC3);

	namedWindow("Main");

	// 500 X 500 검정 화면 만들기
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			for (k = 0; k < 3; k++) {
				Vec3b& intensity = image.at<Vec3b>(j, i); // 500x500 픽셀이미지생성
				intensity.val[k] = 255; //각 화소에 3개씩 아마 rgb에다가 0집어넣기 -> 검정화면
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
*/
/*

int main(int argc, char** argv) {
	Mat image(512, 512, CV_8UC3, Scalar(0, 255, 255)), result;

	rectangle(image, Point(100, 100), Point(400, 400), CV_RGB(255, 0, 0), -1);
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 0, 255), 2, 8, 1);
	line(image, Point(400, 100), Point(100, 400), Scalar(140, 0, 0), 1, 4, 2);
	line(image, Point(400, 100), Point(100, 400), Scalar(255, 0, 0), 1, 4, 3);
	rectangle(image, Point(400 / 2, 100 / 2), Point(100 / 2, 400 / 2), CV_RGB(0, 0, 255));
	rectangle(image, Point(400 / 4, 100 / 4), Point(100 / 4, 400 / 4), CV_RGB(0, 0, 255));
	rectangle(image, Point(400 / 8, 100 / 8), Point(100 / 8, 400 / 8), CV_RGB(255, 0, 0));
	namedWindow("Drawing Graphics");
	imshow("Drawing Graphics", image);

	waitKey(0);

	destroyWindow("Drawing Graphics");
	return 0;
}
*/
/*
int w = 512; //생성 영상 크기
void MyLine(Mat img, Point start, Point end);
void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);

int main(int argc, char** argv) {

	int k;
	char atom_window[] = "Drawing 1: Atom";
	
	Mat atom_image = Mat::zeros(w, w, CV_8UC3);
	namedWindow(atom_window);

	cout << "1 - draw ellipse" << endl;
	cout << "2 - filled circle" << endl;
	cout << "3 - draw rectangle" << endl;
	cout << "4 - draw line" << endl;

	k = waitKey(0);
	if (k == 49) {
		MyEllipse(atom_image, 90);
		MyEllipse(atom_image, 0);
		MyEllipse(atom_image, 45);
		MyEllipse(atom_image, -45);
	}
	else if (k == 50) {
		MyFilledCircle(atom_image, Point(w / 2.0, w / 2.0));
	}
	else if (k == 51) {
		rectangle(atom_image, Point(0, 7 * w / 8.0), Point(w, w), 
			Scalar(0, 255, 255), -1, 8);
	}
	else if (k == 52) {
		MyLine(atom_image, Point(0, 15 * w / 16.0), Point(w, 15 * w / 16.0));
		MyLine(atom_image, Point(w/4.0, 7 * w / 8.0), Point(w/4.0, w));
		MyLine(atom_image, Point(w / 2.0, 7 * w / 8.0), Point(w / 2.0, w));
		MyLine(atom_image, Point(3*w / 4.0, 7 * w / 8.0), Point(3*w / 4.0, w));
	}
	imshow(atom_window, atom_image);

	waitKey(0);
	destroyWindow(atom_window);
	return 0;
}

void MyLine(Mat img, Point start, Point end) {
	int thickness = 2;
	int lineType = 8;
	line(img, start, end, Scalar(0, 0, 255), thickness, lineType);
}
void MyFilledCircle(Mat img, Point center) {
	int thickness = -1;
	int lineType = 8;

	circle(img, center, w / 6.0, Scalar(0, 0, 255), thickness, lineType);
}
void MyEllipse(Mat img, double angle) {
	int thickness = 2;
	int lineType = 8;
	ellipse(img, Point(w / 2.0, w / 2.0), Size(w / 4.0, w / 16.0), angle, 0, 360, Scalar(255, 0, 0),
		thickness, lineType);
}
*/

Mat src, img, ROI;
Rect cropRect(0, 0, 0, 0);
Point P1(0, 0);
Point P2(0, 0);

const char* winName = "Crop Image";
bool clicked = false;
int i = 0;
char imgName[15];

void checkBoundary();
void onMouse(int event, int x, int y, int f, void*);
void showImage();

int main(int argc, char** argv) {

	cout << "click and drag for selection" << endl << endl;
	cout << "------> Press 's' to save" << endl << endl;
	cout << "------> Press '8' to move up" << endl;
	cout << "------> Press '2' to move down" << endl;
	cout << "------> Press '6' to move right" << endl;
	cout << "------> Press '4' to move left" << endl << endl;

	cout << "------> Press 'w' increas top" << endl;
	cout << "------> Press 'x' increas bottom" << endl;
	cout << "------> Press 'd' increas right" << endl;
	cout << "------> Press 'a' increas left" << endl << endl;

	cout << "------> Press 't' decrease top" << endl;
	cout << "------> Press 'b' decrease bottom" << endl;
	cout << "------> Press 'h' decrease right" << endl;
	cout << "------> Press 'f' decrease left" << endl << endl;

	cout << "------> Press 'r' to reset" << endl;
	cout << "------> Press 'Esc' to quit" << endl << endl;

	src = imread(argv[1], 1);

	namedWindow(winName);
	setMouseCallback(winName, onMouse, NULL);
	imshow(winName, src);

	while (1) {
		char c = waitKey();
		if (c == 's' && !ROI.empty()) {
			imwrite("croppedImg.jpg", ROI);
			cout << "saved" << imgName << endl;
		}
		if (c == '6') cropRect.x++;
		if (c == '4') cropRect.x--;
		if (c == '8') cropRect.y--;
		if (c == '2') cropRect.y++;

		if (c == 'w') { cropRect.y--; cropRect.height++; }
		if (c == 'd') cropRect.width++;
		if (c == 'x') cropRect.height++;
		if (c == 'a') { cropRect.x--; cropRect.width++; }
		if (c == 't') { cropRect.y++; cropRect.height--; }
		if (c == 'h') cropRect.width--;
		if (c == 'b') cropRect.height--;
		if (c == 'f') { cropRect.x++; cropRect.width--; }
		if (c == 27) break;
		if (c == 'r') {
			cropRect.x = 0; cropRect.y = 0;
			cropRect.width = 0; cropRect.height = 0;		}
		showImage();
	}

	return 0;
}
void onMouse(int event, int x, int y, int f, void*) {
	switch (event) {

		case EVENT_LBUTTONDOWN :
			clicked = true;
			P1.x = x;
			P1.y = y;
			P2.x = x;
			P2.y = y;
			break;

		case EVENT_LBUTTONUP : 
			P2.x = x;
			P2.y = y;
			clicked = false;
			break;

		case EVENT_MOUSEMOVE :
			if (clicked) {
				P2.x = x;
				P2.y = y;
			}
			break;

		default: break;

	}// end switch
	if (clicked) {
		if (P1.x > P2.x) {
			cropRect.x = P2.x;
			cropRect.width = P1.x - P2.x;
		}
		else {
			cropRect.x = P1.x;
			cropRect.width = P2.x - P1.x;
		}
		if (P1.y > P2.y) {
			cropRect.y = P2.y;
			cropRect.height = P1.y - P2.y;
		}
		else {
			cropRect.y = P1.y;
			cropRect.height = P2.y - P1.y;
		}
	}
	showImage();
}
void checkBoundary() {
	if (cropRect.width > img.cols - cropRect.x)
		cropRect.width = img.cols - cropRect.x;
	if (cropRect.height > img.rows - cropRect.y)
		cropRect.height = img.rows - cropRect.y;
	if (cropRect.x < 0)
		cropRect.x = 0;
	if (cropRect.y < 0)
		cropRect.height = 0;
}
void showImage() {
	img = src.clone();
	checkBoundary();
	namedWindow("cropped");
	if (cropRect.width > 0 && cropRect.height > 0) {
		ROI = src(cropRect);
		imshow("cropped", ROI);
	}
	rectangle(img, cropRect, Scalar(0, 255, 0), 1, 8, 0);
	imshow(winName, img);
}