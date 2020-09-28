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
	double t_ptr, t_itr, t_at;
	image = imread(argv[1]); 

	//예외처리
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window"); 
	imshow("Display window", image);
	result_ptr = image.clone();
	result_itr = image.clone();
	result_at = image.clone();
	// 포인터 함수 적용과 실행 시간 측정
	t_ptr = (double)getTickCount();
	colorReduceP(result_ptr, 64);
	t_ptr = ((double)getTickCount() - t_ptr) / getTickFrequency();
	// iterator 함수 적용과 실행시간 측정
	t_itr = (double)getTickCount();
	colorReduceI(result_itr, 64);
	t_itr = ((double)getTickCount() - t_itr) / getTickFrequency();

	// at 함수 적용과 실행시간 측정
	t_at = (double)getTickCount();
	colorReduceA(result_at, 64);
	t_at = ((double)getTickCount() - t_at) / getTickFrequency();


	cout << "POINTER TIME (ms) = " << t_ptr << endl;
	cout << "ITERATOR TIME (ms) = " << t_itr << endl;
	cout << "AT TIME (ms) = " << t_at << endl;

	namedWindow("Processed pointer image");
	namedWindow("Processed iterator image");
	namedWindow("Processed at image");

	imshow("Processed pointer image", result_ptr);
	imshow("Processed iterator image", result_itr);
	imshow("Processed at image", result_at);


	waitKey(0);
	return 0;
}

// iterator로 구현
void colorReduceI(Mat& image, int div) {
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
	//모든 화소 조회하면서 개별처리해줌 
	for (; it != itend; ++it) {
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}
// pointer로 구현
void colorReduceP(Mat& image, int div) {
	int nl = image.rows;//행개수
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			data[i] = data[i] / div * div + div / 2;
		}
	}
}
void colorReduceA(Mat& image, int div) {
	int nl = image.rows;
	int nc = image.cols; 
	//모든 화소 조회
	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++) {
			//각화소 처리
			image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(j, i)[0] / div * div + div / 2;
			image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(j, i)[1] / div * div + div / 2;
			image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(j, i)[2] / div * div + div / 2;
		}
	}
}