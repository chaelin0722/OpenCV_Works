#define _CRT_SECURE_NO_WARNINGS 

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
calcHist();
//--- ������׷� ���� Ŭ���� ���� --//
class Histogram1D {
private:
	int histSize[1]; // ������׷� �󵵼�
	float hranges[2]; // ������׷� �ּ�/�ִ� ȭ�Ұ�
	const float* ranges[1];
	int channels[1]; // 1ä�θ� ���
public:
	Histogram1D() { // 1���� ������׷��� ���� ���� �غ�
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}
	// 1���� ������׷� ���
	MatND getHistogram(const Mat& image) {
		MatND hist;
		// �̹����� ������׷� ���
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		// ���� �� : �̹���, ���Ͽ���, ���ä��, ����ũ ������, ���������׷�,
		// 1���� ������׷�, �󵵼�, ȭ�Ұ� ����
		return hist;
	}
	// ������׷��� ���� �� �׷��� ���
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image); // ������׷� ���
		double maxVal = 0; // �ִ� �󵵼�
		double minVal = 0; // �ּ� �󵵼�
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		// ������׷��� ����ϱ� ���� ����
		Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
		// nbins�� 90%�� �ִ������� ����
		int hpt = static_cast<int>(0.9 * histSize[0]);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int> (binVal * hpt / maxVal);
			// �� ������ �Ÿ��� �׸�
			line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImg;
	}
};

int main(int argc, char** argv)
{
	Mat image, dst;
	/// Load image
	image = imread("../../../../images/test.jpg",0); // Read the file as grayscale image

	if (image.empty()) { 
		cout << "�̹��� ����!" << std::endl;
		return -1;
	}

	namedWindow("Display window"); 
	imshow("Display window", image);
	Histogram1D h; // ������׷��� ���� ��ü
	MatND histo = h.getHistogram(image); // ������׷� ���
	for (int i = 0; i < 256; i++) // ������׷��� �󵵸� ��ȸ
		cout << "Value" << i << "=" << histo.at<float>(i) << endl;
	// ������׷��� �������� ����
	namedWindow("Histogram");
	imshow("Histogram", h.getHistogramImage(image));
	//������ �� �׷����� ������ �κ��� ��谪���� ó���� Ȯ��
	Mat thresholdedImage; // ��谪���� ���� ���� ����
	threshold(image, thresholdedImage, 60, 255, THRESH_BINARY);
	// ������ ���ȭ �ϱ� ���� ������׷��� ���� ���츮(60) �������� �����ϱ� ������ �ּҰ����� ����
	namedWindow("Binary Image");
	imshow("Binary Image", thresholdedImage);
	waitKey(0);	return 0;}/*class Histogram1D {
private:
	int histSize[1]; // ������׷� �󵵼�
	float hranges[2]; // ������׷� �ּ�/�ִ� ȭ�Ұ�
	const float* ranges[1];
	int channels[1]; // 1ä�θ� ���
public:
	Histogram1D() { // 1���� ������׷��� ���� ���� �غ�
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}
	// 1���� ������׷� ���
	MatND getHistogram(const Mat& image) {
		MatND hist;
		// �̹����� ������׷� ���
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		// ���� �� : �̹���, ���Ͽ���, ���ä��, ����ũ ������, ���������׷�,
		// 1���� ������׷�, �󵵼�, ȭ�Ұ� ����
		return hist;
	}	// Equalizes the source image.
	MatND equalize(const cv::Mat& image) {
		Mat result;
		equalizeHist(image, result);
		return result;
	}
};

int main(int argc, char** argv)
{
	Mat image, dst;
	image = imread(argv[1], 0); 

	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Histogram1D h; // ������׷��� ���� ��ü
		// Equalize the image
	MatND eqHist = h.equalize(image);
	// Show the result
	namedWindow("Equalized Image");
	imshow("Equalized Image", eqHist);
	// Show the new histogram
	namedWindow("Equalized Histogram");
	imshow("Equalized Histogram",
		h.getHistogramImage(eqHist));
	waitKey(0);
	return 0;
}
*/