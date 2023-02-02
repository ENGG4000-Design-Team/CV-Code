/*
* cv_performance_test/main.cpp
* Attempting to measure how fast we can
* perform computer vision operations adjacent
* to what is going to need to be done during flight.
* Author: Ethan Garnier
*/
#include <iostream>
#include <chrono>
#include "opencv2/opencv.hpp"

void find_brightest_spot(cv::Mat oldImg, cv::Mat& newImg)
{
	cv::GaussianBlur(oldImg, newImg, cv::Size(5, 5), 0);
}

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
		// Begin timing of image processing
		auto start = std::chrono::high_resolution_clock::now();

		// Where we store the frame
		cv::Mat frame;

		// Capture frame and store it in Mat
		cap >> frame;
		

		// DO PROCESSING HERE
		cv::Mat processedImg;
		find_brightest_spot(frame, processedImg);

		cv::imshow("frame capture", processedImg);

		
		// Stop timing and print result
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "Processing Time: " << duration.count() << std::endl;

		// Wait 16 ms (roughly 60FPS)
		// before processing the next frame. If the user
		// presses a key then the program stops.
		if (cv::waitKey(16) >= 0) break;
	}

	return 0;
}