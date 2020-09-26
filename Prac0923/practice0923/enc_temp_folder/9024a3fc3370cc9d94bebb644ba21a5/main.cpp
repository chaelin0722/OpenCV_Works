/*
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	//Mat image;
	//	image = imread(argv[1]);

	/*�÷� ��ȯ ����!! COLOR_ �� �����ܾ �ٲ㼭 �پ��� �÷��� �̹����� ��ȯ�غ���*/
	/*
	//image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	
	
	image = imread("../../../../images/beach.jpg", IMREAD_UNCHANGED);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// Create a new matrix to hold the gray image
	Mat result;
	// convert RGB image to gray
	cvtColor(image, result, COLOR_BGR2YCrCb);
	namedWindow("Display window");
	imshow("Display window", image);
	namedWindow("Result window");
	imshow("Result window", result);
	*/
	//���� ó�� 
	/*
	if (argc != 2)
	{
		cout << " Usage: Give an input image file name...!!!" << endl;
		return -1;
	}
	Mat image = imread(argv[1], 1);
	// �ش� �̹��� ���� �� ����
	if (!image.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	namedWindow("original", 1);
	imshow("original", image);
	Mat rgbChannels[3];
	split(image, rgbChannels);

	namedWindow("Blue", 1);
	imshow("Blue", rgbChannels[0]);

	namedWindow("Green", 1);
	imshow("Green", rgbChannels[1]);

	namedWindow("Red", 1);
	imshow("Red", rgbChannels[2]);

	// rbc ���� �� ������ 
	Mat g, fin_img;
	g = Mat:: zeros(Size(image.cols, image.rows), CV_8UC1);

	{	//Red channel!
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(rgbChannels[2]);
		/// Merge the three channels
		merge(channels, fin_img);
		namedWindow("R", 1);
		imshow("R", fin_img);
	}
	{
		// Green channel!
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(rgbChannels[1]);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("G", 1); imshow("G", fin_img);
	}
	{	// Blue channel!
		vector<Mat> channels;
		channels.push_back(rgbChannels[0]);
		channels.push_back(g);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("B", 1);
		imshow("B", fin_img);
	}
	
	//////////////////////////
	Mat bgr[3]; //destination array
	split(image, bgr);//split source //Note: OpenCV uses BGR color order

	//-- Show each color channel image
	namedWindow("Color Image");
	imshow("Color Image", image);
	namedWindow("Blue channel");
	namedWindow("Green channel");
	namedWindow("Red channel");
	imshow("Blue channel", bgr[0]);
	imshow("Green channel", bgr[1]);
	imshow("Red channel", bgr[2]);
	
	Mat dst;
	cvtColor(image, dst, COLOR_RGB2YCrCb);
	split(dst, bgr);//split source //Note: OpenCV uses YCrCb color order
	namedWindow("Y channel"); imshow("Y channel", bgr[0]);
	namedWindow("Cb channel"); imshow("Cb channel", bgr[1]);
	namedWindow("Cr channel"); imshow("Cr channel", bgr[2]);
	//-- Pixel processing Example with Y-component: bgr[0] plane
	Mat result;
	result = bgr[0].clone();
	int Thres = 128;
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			if (bgr[0].at<uchar>(i, j) > Thres) {
				result.at<uchar>(i, j) = 255;
			}
			else {
				result.at<uchar>(i, j) = 0;
			}
		}
	}
	namedWindow("Pixel Processing");
	imshow("Pixel Processing", result);


	Mat merged_img;
	//-- Mtehod 1 --//
	vector<Mat> channels;
	channels.push_back(bgr[0]);
	channels.push_back(bgr[1]);
	channels.push_back(bgr[2]);
	merge(channels, merged_img); 
	//-- Method 2 --//
	/*
	merge(bgr, 3, merged_img);
	namedWindow("Merged image", 1);
	imshow("Merged image", merged_img);

	*/
/*
	waitKey(0);
	return 0;
}
*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void colorReduceP(Mat& image, int div);
void colorReduceI(Mat& image, int div);
void colorReduceA(Mat& image, int div);

int main(int argc, char** argv)
{
	Mat image, result_ptr, result_itr, result_at;
	image = imread(argv[1]);

	//����ó��
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window");
	imshow("Display window", image);
	result_ptr = image.clone();
	colorReduceP(result_ptr, 64);
	colorReduceI(result_itr, 64);
	colorReduceA(result_at, 64);

	namedWindow("Processed pointer image");
	namedWindow("Processed iterator image");
	namedWindow("Processed at image");

	imshow("Processed pointer image", result_ptr);
	imshow("Processed iterator image", result_itr);
	imshow("Processed at image", result_at);

	waitKey(0);
	return 0;
}

// iterator�� ����
void colorReduceI(Mat& image, int div) {
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
	//��� ȭ�� ��ȸ�� //
	for (; it != itend; ++it) {
		//--- ����ȭ�� ó��---//
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}
// pointer�� ����
void colorReduceP(Mat& image, int div) {
	int nl = image.rows;//�ళ��
	int nc = image.cols * image.channels();//������ ������ ����
	for (int j = 0; j < nl; j++) {
		//-- j���� �ּ� (nc ����ŭ) �������� --//
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			//---�� ȭ�Ұ� ����--//
			data[i] = data[i] / div * div + div / 2;
		}
	}
}
void colorReduceA(Mat& image, int div) {
	int nl = image.rows;//�� ����
	int nc = image.cols; //�� ����
	//��� ȭ�� ��ȸ�� //
	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++) {
			//---��ȭ�� ó��--//
			image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(j, i)[0] / div * div + div / 2;
			image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(j, i)[1] / div * div + div / 2;
			image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(j, i)[2] / div * div + div / 2;
		}
	}
}