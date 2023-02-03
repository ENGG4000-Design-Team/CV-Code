/*
* cv_performance_test/main.cpp
* Attempting to measure how fast we can
* perform computer vision operations adjacent
* to what is going to need to be done during flight.
* Author: Ethan Garnier
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include "opencv2/opencv.hpp"

// Ideas:
// 1. Use minMaxLoc
// 2. Use threshold
void find_brightest_spot(cv::Mat &img, int radius)
{
	if (img.empty()) return;

	// Clone and convert the image to grayscale
	cv::Mat proccImg = img.clone();
	cv::cvtColor(img, proccImg, cv::COLOR_BGR2GRAY);

	// Apply a Gaussian Blur to perform high frequency filtering
	cv::Size blurSize = cv::Size(radius, radius);
	cv::GaussianBlur(img, proccImg, blurSize, 0);

	// We must split the image into a single channel array
	cv::Mat channels[3];
	cv::split(proccImg, channels);

	// Determine the maximum in the image
	cv::Point maxLoc;
	cv::minMaxLoc(channels[0], NULL, NULL, NULL, &maxLoc);

	// Draw a circle around the brightest location
	cv::circle(img, maxLoc, radius * 10, cv::Scalar(255, 0, 0, 0));

	// Draw a line from the center of the image to the brightest spot
	cv::Point imgCenter = cv::Point(img.cols / 2, img.rows / 2);
	cv::line(img, imgCenter, maxLoc, cv::Scalar(255, 0, 0, 0));

	// Calculate the distance from the brightest spot to center of the image
	double dist = cv::norm(maxLoc - imgCenter);
	std::cout << "Distance from center to brightest spot: " << dist << std::endl;
}

int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cout << "Unable to open camera capture" << std::endl;
		return -1;
	}

	std::vector<double> durations;

	for (;;)
	{
		// Begin timing of image processing
		auto start = std::chrono::high_resolution_clock::now();

		// Where we store the frame
		cv::Mat frame;

		// Capture frame and store it in Mat
		cap >> frame;
		
		// DO PROCESSING HERE
		find_brightest_spot(frame, 5);

		// Stop timing and store results
		auto stop = std::chrono::high_resolution_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		durations.push_back(std::chrono::duration<double>(d).count());

		cv::imshow("frame capture", frame);

		// Wait 16 ms (roughly 60FPS)
		// before processing the next frame. If the user
		// presses a key then the program stops.
		if (cv::waitKey(16) >= 0) break;
	}

	// Print average processing time
	if (!durations.empty())
		std::cout << "Average processing time: " << (std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size()) * 1000.0 << "ms" << std::endl;

	return 0;
}