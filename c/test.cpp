#include "manga_fil.h"
#include "hls_opencv.h"

int main(){

	cv::Mat src = cv::imread("lena.png");
	cv::Mat tmp = cv::imread("screen.bmp");
	cv::Mat dst = src;
	stream_t stream_in, stream_out;

	int screen[WIDTH*HEIGHT];

	for(int y=0; y<HEIGHT; y++){
		for(int x=0; x<WIDTH; x++){
			screen[WIDTH*y+x] = tmp.data[WIDTH*y+x];
		}
	}
	cvMat2AXIvideo(src, stream_in);
	manga_filter(stream_in, stream_out, screen);
	AXIvideo2cvMat(stream_out, dst);

	cv::cvtColor(dst,dst,CV_BGR2GRAY);
	cv::imwrite("tmp.bmp", dst);
}
