#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
    cv::Mat img;
    img = cv::imread("/Users/kanta/Downloads/lena.png");
    
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    
    cv::imshow("title", img);
    cv::waitKey(0);
    
    return 0;
}

