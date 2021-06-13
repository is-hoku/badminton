#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <string>


cv::Point p;

void mouse_callback(int event, int x, int y, int flags, void *userdata){
	bool *isClick = static_cast<bool *>(userdata);
	if (event == cv::EVENT_LBUTTONDOWN){
		*isClick = true;
		p.x = x;
		p.y = y;
	}
}


int main(int argc, char** argv) {
	int key = 0;
	bool flag = false;
	bool isClick = false;
	cv::namedWindow("Drawing point", cv::WINDOW_AUTOSIZE);
	for (int i=0; i<10; i++){
		if (flag == true){
			if (i > 2){
				i -= 2;
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
			cv::imshow("Drawing point", img);
			key = cv::waitKey(1);
			if (key == 'k'){
				break;
			}
			else if (key == 'j'){
				flag = true;
				break;
			}
		}
		isClick = false;
		cv::imwrite(std::to_string(i)+".png", img);
	}
	
	return 0;
}
