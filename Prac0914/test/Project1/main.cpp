/*  화소 처리 예제 연습!*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//--OpenCV 2.x 구현 --//
	Mat image, result;
	//image = imread("Desert.bmp", IMREAD_COLOR); // Read the file
	char* imageName = argv[1];

	image = imread(imageName, IMREAD_COLOR);
	if (argc != 2 || !image.data) {
		printf("No image data \n");
		return -1;
	}
	result = image.clone();
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	//-- 1) pixel by pixel 반전 영상 생성 --//
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			result.at<Vec3b>(i, j)[0] = 255 - image.at<Vec3b>(i, j)[0];
			result.at<Vec3b>(i, j)[1] = 255 - image.at<Vec3b>(i, j)[1];
			result.at<Vec3b>(i, j)[2] = 255 - image.at<Vec3b>(i, j)[2];
		}
	}
	namedWindow("Processed image"); // Create a window for display.
	imshow("Processed image", result);// Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}