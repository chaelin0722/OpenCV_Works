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
/*
int main(int argc, char** argv) {
	Mat image,result,result2, result3;
	image = imread(argv[1],1);

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

	//Gaussian Blur
	GaussianBlur(image, result2, Size(5, 5), 1.5);

	namedWindow("Gaussian filtered Image");
	imshow("Gaussian filtered Image", result2);

	//Gaussian Kernel
	Mat gauss = getGaussianKernel(9, 1.5, CV_32F);
	// Mat getGaussainKernel(int ksize, double sigma, int ktype=CV_64F)
	// 즉, 사이즈가 9이고 시그마가 1.5 인 커널을 생성
	// 커널이 9개가 생김! 범위가 9인것이다..!

	//DISPLAY kernel values
	Mat_ <float> ::const_iterator it = gauss.begin<float>();
	Mat_ <float> ::const_iterator itend = gauss.end<float>();
	cout << "[";
	for (; it!= itend; ++it) {
		cout << *it << " ";
	}
	cout << "]" << endl;

	waitKey(0);

	return 0;
}
*/

//noise 제거 실습
void salt(Mat& img, int n);
void saltPepper(Mat& img, int n);

int main(int argc, char** argv) {

	Mat image, result, dst, dst1;

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not open image" << endl;
		return -1;
	}
	//원본에 salt and pepper로 노이즈 추가해주기
	saltPepper(image, 30000);

	namedWindow("salt image");
	imshow("salt image", image);

	blur(image, result, Size(5, 5));
	namedWindow("blurred image");
	imshow("blurred image", result);
	
	//medianblur
	medianBlur(image, result, 5);
	namedWindow("Median filtered image");
	imshow("Median filtered image", result);
	
	waitKey(0);

	return 0;
}

void salt(Mat &img, int n) {
	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols; // 이미지 열크기 내에서 랜덤 수 생성, x좌표값
		int j = rand() % img.rows;  //이미지 행 크기 내에서 랜덤 수 생성, y좌표값

		if (img.channels() == 1) {  //grayscale image
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) {// color image
			img.at<Vec3b>(j, i)[0] = 255;
			img.at<Vec3b>(j, i)[1] = 255;
			img.at<Vec3b>(j, i)[2] = 255;
		}  // 모두 255 처리를 함으로써 하얀색 점만 찍히게 됨..
	}
}

void saltPepper(Mat& img, int n) {

	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;

		int salt_or_pepper = (rand() % 2) * 255; // 0또는 255값을 랜덤으로 줌,,!
		//(rand() % 2) => 0또는 1 즉, 0또는 255 값이 랜덤생성된다.
		if (img.channels() == 1) {  //grayscale image
			img.at<uchar>(j, i) = salt_or_pepper;
		}
		else if (img.channels() == 3) {// color image
			img.at<Vec3b>(j, i)[0] = salt_or_pepper;
			img.at<Vec3b>(j, i)[1] = salt_or_pepper;
			img.at<Vec3b>(j, i)[2] = salt_or_pepper;
		}  
	
	}//end for
}
