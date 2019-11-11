#include "manga_fil.h"
#include "hls_opencv.h"

int main(){

	cv::Mat src = cv::imread("fox.bmp");
	cv::Mat dst = src;
	stream_t stream_in, stream_out;

	cvMat2AXIvideo(src, stream_in);
	manga_filter(stream_in, stream_out);
	AXIvideo2cvMat(stream_out, dst);

	//cv::cvtColor(dst,dst,CV_BGR2GRAY);
	cv::imwrite("tmp.bmp", dst);
	return 0;
}
