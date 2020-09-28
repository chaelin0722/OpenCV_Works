
// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS 

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

//--- 히스토그램 관련 클래스 구현 --//
class Histogram1D {
private:
	int histSize[1]; // 히스토그램 빈도수
	float hranges[2]; // 히스토그램 최소/최대 화소값
	const float* ranges[1];
	int channels[1]; // 1채널만 사용
public:
	Histogram1D() { // 1차원 히스토그램을 위한 인자 준비
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}
	// 1차원 히스토그램 계산
	MatND getHistogram(const Mat& image) {
		MatND hist;
		// 이미지의 히스토그램 계산
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		// 인자 값 : 이미지, 단일영상, 대상채널, 마스크 사용안함, 결과히스토그램,
		// 1차원 히스토그램, 빈도수, 화소값 범위
		return hist;
	}
	// 히스토그램을 위한 바 그래프 사용
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image); // 히스토그램 계산
		double maxVal = 0; // 최대 빈도수
		double minVal = 0; // 최소 빈도수
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		// 히스토그램을 출력하기 위한 영상
		Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
		// nbins의 90%를 최대점으로 설정
		int hpt = static_cast<int>(0.9 * histSize[0]);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int> (binVal * hpt / maxVal);
			// 두 점간의 거리를 그림
			line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImg;
	}
};

int main(int argc, char** argv)
{
	Mat image, dst;
	/// Load image
	image = imread(argv[1], 0); // Read the file as grayscale image

	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window");
	imshow("Display window", image);
	Histogram1D h; // 히스토그램을 위한 객체
	MatND histo = h.getHistogram(image); // 히스토그램 계산
	for (int i = 0; i < 256; i++) // 히스토그램의 빈도를 조회
		cout << "Value" << i << "=" << histo.at<float>(i) << std::endl;
	// 히스토그램을 영상으로 띄우기
	namedWindow("Histogram");
	imshow("Histogram", h.getHistogramImage(image));
	//영상을 두 그룹으로 나누는 부분을 경계값으로 처리해 확인
	Mat thresholdedImage; // 경계값으로 이진 영상 생성
	threshold(image, thresholdedImage, 60, 255, THRESH_BINARY);
	// 영상을 경계화 하기 위해 히스토그램의 높은 봉우리(60) 방향으로 증가하기 직전인 최소값으로 정함
	namedWindow("Binary Image");
	imshow("Binary Image", thresholdedImage);
	waitKey(0);	return 0;}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
