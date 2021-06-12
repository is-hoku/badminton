#include <iostream>
#include <opencv2/opencv.hpp>
#include <cvui.h>
#include <string>
#define CVUI_IMPLEMENTATION


int main(int argc, char** argv) {
	if (argc != 2){
		std::cout << "The number of arguments is incorrect." << std::endl;
		return 1;
	}
	cv::VideoCapture cap;
	cap.open(argv[1]);
	if (!cap.isOpened()){
		std::cout << "Cannot open " << argv[1] << "!" << std::endl;
		return 1;
	}
	
	for (int count = 2; count < cap.get(cv::CAP_PROP_FRAME_COUNT)-2; count++){
		cv::Mat frame;
		if (!cap.read(frame)){
			std::cout << "Failed to extract a frame." << std::endl;
		}
		std::string path = "frames/" + std::to_string(count) + ".png";
		cv::imwrite(path, frame);
	}

	cvui::init("drawing points");
	
	return 0;
}
