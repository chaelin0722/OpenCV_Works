/*
	Filtering을 위한 다양한 API 존재
	- Blurring
	- Sharpening
	- 에지 검출 필터
	- 라플라시안 필터
	- 직접 디자인 가능한 filter2D 함수 등
*/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat image,result;
	image = imread(argv[1]);

	if (image.empty()) {
		cout << "image could not find" << endl;
		return -1;
	}
	// 원본
	namedWindow("Original Image");
	imshow("Original Image", image);

	//blured image
	blur(image, result, Size(5, 5));
	namedWindow("blurred Image");
	imshow("blurred Image", result);

	//Gaussian Kernel
	Mat gauss = getGaussianKernel(9, 1.5, CV_32F);
	// Mat getGaussainKernel(int ksize, double sigma, int ktype=CV_64F)

	//DISPLAY kernel values
	Mat_ <float> ::const_iterator it = gauss.begin<float>();
	Mat_ <float> ::const_iterator	itend = gauss.end<float>();
	cout << "[";
	for (; it!= itend; ++it) {
		cout << *it << " ";
	}
	cout << "]" << endl;



	return 0;
}