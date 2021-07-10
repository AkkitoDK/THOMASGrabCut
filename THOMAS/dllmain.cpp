#include "framework.h"
#include "Header.h"
#include <iostream>
#include "C:/Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/include/opencv2/opencv.hpp"
#include "C:/Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/include/opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;
CascadeClassifier face_cascade;
int* middle;


namespace UsingOpenCV
{
	cv::VideoCapture* cap;

	void Functions::Initialize()
	{
		face_cascade.load("C://Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml");
		cap = new cv::VideoCapture(0);
	}


	

	BYTE* Functions::ProcessFrame() {
		cv::Mat image;
	
		cv::Mat betterImage;
		

		BYTE* result;

		(*cap) >> image;

		cv::flip(image, image, 0);

		cv::cvtColor(image, betterImage, COLOR_BGR2BGRA, 4);

		result = new BYTE[image.cols * image.rows * 4];

		memcpy(result, betterImage.data, betterImage.cols * image.rows * 4);
		return result;
	}


	int* Functions::Coordinates()
	{

		cv::Mat frame;
		cv::Mat frame_gray;
		cv::Mat oMatCrop;
		int* Centerx;

		try {

			cv::cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

		}
		catch (cv::Exception& e)
		{
			const char* err_msg = e.what();
			std::cout << "exception caught: " << err_msg << std::endl;
		}

		cv::equalizeHist(frame_gray, frame_gray);

		//-- Detect faces
		std::vector<Rect> faces;
		face_cascade.detectMultiScale(frame_gray, faces);
		for (size_t i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
			Mat faceROI = frame_gray(faces[i]);

			Centerx = new int(faces[i].x + faces[i].width / 2);
			middle = Centerx;

		}

		return middle;

	}
	

}


