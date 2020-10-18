/*
	Filtering�� ���� �پ��� API ����
	- Blurring
	- Sharpening
	- ���� ���� ����
	- ���ö�þ� ����
	- ���� ������ ������ filter2D �Լ� ��
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
	// ����
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
	// ��, ����� 9�̰� �ñ׸��� 1.5 �� Ŀ���� ����
	// Ŀ���� 9���� ����! ������ 9�ΰ��̴�..!

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

//noise ���� �ǽ�
void salt(Mat& img, int n);
void saltPepper(Mat& img, int n);

int main(int argc, char** argv) {

	Mat image, result, dst, dst1;

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not open image" << endl;
		return -1;
	}
	//������ salt and pepper�� ������ �߰����ֱ�
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
		int i = rand() % img.cols; // �̹��� ��ũ�� ������ ���� �� ����, x��ǥ��
		int j = rand() % img.rows;  //�̹��� �� ũ�� ������ ���� �� ����, y��ǥ��

		if (img.channels() == 1) {  //grayscale image
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) {// color image
			img.at<Vec3b>(j, i)[0] = 255;
			img.at<Vec3b>(j, i)[1] = 255;
			img.at<Vec3b>(j, i)[2] = 255;
		}  // ��� 255 ó���� �����ν� �Ͼ�� ���� ������ ��..
	}
}

void saltPepper(Mat& img, int n) {

	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;

		int salt_or_pepper = (rand() % 2) * 255; // 0�Ǵ� 255���� �������� ��,,!
		//(rand() % 2) => 0�Ǵ� 1 ��, 0�Ǵ� 255 ���� ���������ȴ�.
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
