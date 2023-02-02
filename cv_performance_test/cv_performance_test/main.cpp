/*
* cv_performance_test/main.cpp
* Attempting to measure how fast we can
* perform computer vision operations adjacent
* to what is going to need to be done during flight.
* Author: Ethan Garnier
*/
#include <iostream>
#include "opencv2/opencv.hpp"

int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cout << "Unable to open camera capture" << std::endl;
		return -1;
	}

	for (;;)
	{
		// Where we store the frame
		cv::Mat frame;

		// Capture frame and store it in Mat
		cap >> frame;
		

		// DO PROCESSING HERE

		cv::imshow("frame capture", frame);

		// Wait 16 ms (roughly 60FPS)
		// before processing the next frame. If the user
		// presses a key then the program stops.
		if (cv::waitKey(16) >= 0) break;
	}

	return 0;
}