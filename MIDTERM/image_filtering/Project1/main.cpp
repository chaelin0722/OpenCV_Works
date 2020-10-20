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
/*
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
*/

//unsharp mask �̿� �ǽ�
/*
int main(int argc, char** argv) {
	Mat image, result, dst, dst1;

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not found" << endl;
		return -1;
	}

	namedWindow("Original image");
	imshow("Original image", image);

	Mat blurred;
	double sigma = 1;
	double threshold = 5;
	double amount = 1;
	GaussianBlur(image, blurred, Size(), sigma, sigma);
	Mat lowContrastMask = abs(image - blurred) < threshold;  //image ���� ���� ���� unsharp ����ũ�� ���������. 
	Mat sharpened = image * (1 + amount) + blurred * (-amount);

	image.copyTo(sharpened, lowContrastMask);

	namedWindow("Sharpened image");
	imshow("Sharpened image", sharpened);

	waitKey(0);
	return 0;
}
*/

//resampling �ǽ�
/*
int main(int argc, char** argv) {
	Mat src, dst, tmp;

	printf("\nZoom In-Out demo\n");
	printf("----------------\n");
	printf(" *[u]-> Zoom in\n");
	printf(" *[d]-> Zoom out\n");
	printf(" *[ESC] -> Close program\n\n");

	src = imread(argv[1]);
	if (!src.data) {
		cout << "no data!" << endl;
		return -1;
	}

	tmp = src;
	dst = tmp;

	namedWindow("Original image");
	imshow("Original image", src);

	while (true) {
		int c;
		c = waitKey(10);

		if ((char)c == 27) { break; }; //esc �Է½� ����
		if ((char)c == 'u') {
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			cout << "**Zoom In: Image x 2\n";
		}
		else if ((char)c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			cout << "**Zoom Out: Image / 2\n";
		}

		namedWindow("resampled Image");
		imshow("resampled Image", dst);
		tmp = dst;
	}
	waitKey(0);
	return 0;
}
*/

//filter2D �̿� �ǽ�
/*
int main(int argc, char** argv) {
	Mat image, result;
	image = imread(argv[1]);

	Mat kernel(3, 3, CV_32F, Scalar(0));

	//assign kernel values
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	
	
	//void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point
	//anchor = Point(-1, -1), double delta = 0, int borderType = BORDER_DEFAULT )
	filter2D(image, result, image.depth(), kernel);

	namedWindow("original image");
	imshow("original image", image);

	namedWindow("2D filtered image");
	imshow("2D filtered image", result);

	waitKey(0);

	return 0;
}
*/
//sobel ���͸� x�� y �Һ��� �ϰ� ���� ���ļ� �Һ��ϱ�~
/*
int main(int argc, char** argv) {
	Mat image, result;
	image = imread(argv[1], 0);
	if (!image.data) {
		cout << "no image!" << endl;
		return -1;
	}

	namedWindow("original image");
	imshow("original image", image);

	Mat sobelX;
	Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	namedWindow("sobel X image");
	imshow("sobel X image", sobelX);


	Mat sobelY;
	Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	namedWindow("sobel Y image");
	imshow("sobel Y image", sobelY);

	//compute norm of sobel
	Sobel(image, sobelX, CV_16S, 1, 0);
	Sobel(image, sobelY, CV_16S, 0, 1);

	Mat sobel;
	//compute L1 norm
	sobel = abs(sobelX) + abs(sobelY);

	double sobmin, sobmax;
	minMaxLoc(sobel, &sobmin, &sobmax);

	Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255. / sobmax, 255);
	namedWindow("Sobel Image");
	imshow("Sobel Image", sobelImage);

	Mat sobelThresholded;
	threshold(sobelImage, sobelThresholded, 240, 255, THRESH_BINARY);
	namedWindow("Binary Sobel Image(low)");
	imshow("Binary Sobel Image(low)", sobelThresholded);

	waitKey(0);
	return 0;
}
*/
//Laplacian �⺻����
int main(int argc, char** argv) {
	Mat src, src_gray, dst;

	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	src = imread(argv[1], 1);

	if (!src.data)	return -1;

	namedWindow("original image");
	imshow("original image", src);

	// remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0 ,BORDER_DEFAULT);

	namedWindow("gaussianblur_1");
	imshow("gaussianblur_1", src);
	//grayscale�� convert
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow("convert_2");
	imshow("convert_2", src_gray);

	//apply laplacian function
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	namedWindow("Laplacian Demo");
	imshow("Laplacian Demo", abs_dst);


	waitKey(0);
	return 0;
}
