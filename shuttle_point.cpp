#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>


cv::Point p;

void mouse_callback(int event, int x, int y, int flags, void *userdata){
	bool *isClick = static_cast<bool *>(userdata);
	if (event == cv::EVENT_LBUTTONDOWN){
		*isClick = true;
		p.x = x;
		p.y = y;
	}
}


std::ofstream shuttle_csv("shuttle.csv");

int main(int argc, char** argv) {
	if (argc != 3){
		std::cout << "The number of arguments is incorrect." << std::endl;
		return 1;
	}
	int key = 0;
	bool delete_frame = false;
	bool flag = false;
	bool isClick = false;
	int count = 1;
	int interval = std::stoi(argv[2]);

	cv::namedWindow("Drawing point", cv::WINDOW_NORMAL);
	for (int i=0; i<std::stoi(argv[1]); i+=interval){
		if (flag == true){
			if (i > 2*interval){
				i -= 2*interval;
			} else {
				i = 0;
			}
			flag = false;
		}
		cv::Mat img = cv::imread("./frames/"+std::to_string(i)+".png", cv::IMREAD_COLOR);
		cv::setMouseCallback("Drawing point", mouse_callback, &isClick);
		while (1){
			if (isClick == true){
				cv::circle(img, p, 3, cv::Scalar(0, 0, 255), -1);
			}
			cv::putText(img, std::to_string(count), cv::Point(50, 100), cv::FONT_HERSHEY_DUPLEX, 2.0, CV_RGB(255, 0, 0), 2);
			cv::putText(img, std::to_string(i), cv::Point(50, 150), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
			cv::imshow("Drawing point", img);
			key = cv::waitKey(1);
			if (key == 'x'){
				delete_frame = true;
				break;
			}
			if (key == 'l'){
				count++;
			}
			else if (key == 'h'){
				count--;
			}
			if (key == 'k'){
				break;
			}
			else if (key == 'j'){
				flag = true;
				break;
			}
		}
		isClick = false;
		if (delete_frame == true){
			delete_frame = false;
			continue;
		}
		shuttle_csv << std::to_string(count) << ',' << std::to_string(i+1) << ',' << std::to_string(p.x) << ',' << std::to_string(p.y) << std::endl;
		cv::imwrite("./frames2/" + std::to_string(i)+".png", img);
	}
	return 0;
}
