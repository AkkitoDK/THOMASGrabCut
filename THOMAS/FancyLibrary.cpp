#include "FancyLibrary.h"
#include <iostream>
#include "C:/Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/include/opencv2/opencv.hpp"
//#include "C:/Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/include/opencv2/imgproc.hpp"

using namespace std;
using namespace cv;
CascadeClassifier face_cascade;
int middlex;
int middley;
const unsigned int BORDER = 5;
const unsigned int BORDER2 = BORDER + BORDER;

extern "C"{
	cv::VideoCapture* cap;

	void Initialize()
	{
		face_cascade.load("C://Users/enest/OneDrive/Desktop/OpenCV-4.5.2/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml");
		cap = new cv::VideoCapture(0);
	}


	

	BYTE* ProcessFrame() {
		cv::Mat image;
	
		cv::Mat betterImage;

		(*cap) >> image;

		Mat fram2 = image.clone();

		// define bounding rectangle
		cv::Rect rectangle(40, 90, image.cols - 80, image.rows - 170);

		cv::Mat result1; // segmentation result (4 possible values)
		cv::Mat bgModel, fgModel; // the models (internally used)

		// GrabCut segmentation
		cv::grabCut(image,    // input image
			result1,   // segmentation result
			rectangle,// rectangle containing foreground
			bgModel, fgModel, // models
			1,        // number of iterations
			cv::GC_INIT_WITH_RECT); // use rectangle

		// Get the pixels marked as likely foreground
		cv::compare(result1, cv::GC_PR_FGD, result1, cv::CMP_EQ);
		// Generate output image
		cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
		//cv::Mat background(image.size(),CV_8UC3,cv::Scalar(255,255,255));
		image.copyTo(foreground, result1); // bg pixels not copied

		BYTE* result;

		

		//cv::flip(image, image, 0);

		cv::cvtColor(foreground, betterImage, COLOR_BGR2BGRA, 4);

		int size;
		size = betterImage.cols * betterImage.rows * 4;
		result = new BYTE[size];

		memcpy(result, betterImage.data, size);
		return result;
	}

	
	
	
	int Coordinates()
	{
		int combined;
		cv::Mat frame;
		cv::Mat frame_gray;
		cv::Mat oMatCrop;
		int Centerx;
		(*cap) >> frame;

		try {

			cv::cvtColor(frame, frame_gray, COLOR_BGR2GRAY, 4);

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
			//ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
			Mat faceROI = frame_gray(faces[i]);

			middlex = (faces[i].x + faces[i].width / 2);
			middley = (faces[i].y + faces[i].height / 2);
			
			string s1 = to_string(middlex);
			string s2 = to_string(middley);

			string s = s1 + s2;

			combined = stoi(s);
		}
		

		return combined;

	}
	

}


