#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

//Laplacian tutorial -> gray scale
/*
int main(int argc, char** argv) {

	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	src = imread(argv[1], 1);

	if (!src.data) {
		cout << "Could not found imaage" << endl;
		return -1;
	}

	namedWindow("Original image");
	imshow("Original image", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	//apply laplace function
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	
	// gaussian blur 처리 후 laplacian 처리 해줌

	namedWindow("Laplace Demo");
	imshow("Laplace Demo", abs_dst);

	waitKey(0);
	return 0;
}
*/

// laplacian 컬러 영상 그대로 연산 처리하기
int main(int argc, char** argv) {

	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	src = imread(argv[1], 1);

	if (!src.data) {
		cout << "Could not found imaage" << endl;
		return -1;
	}

	namedWindow("Original image");
	imshow("Original image", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	Mat abs_dst;
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	namedWindow("Laplace Color Demo");
	imshow("Laplace Color Demo", abs_dst);


	waitKey(0);
	return 0;
}