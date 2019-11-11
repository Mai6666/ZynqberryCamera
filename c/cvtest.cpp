#include "manga_fil.h"
#include "hls_opencv.h"

int main(){

	cv::Mat src = cv::imread("lena.png");
	cv::Mat screen = cv::imread("screen.bmp");
	cv::Mat dst = src;
	stream_t stream_in, stream_out;
	interface_t pix, out;

	int line_buf[2][WIDTH];
	int pix_mat[3][3];
	int edg;

	cvMat2AXIvideo(src, stream_in);
	for(int y=0; y<src.cols; y++){
		for(int x=0; x<src.rows; x++){
			stream_in >> pix;
			out = pix;
			Loop4 : for (int k=0; k<3; k++){
				Loop5 : for (int m=0; m<2; m++){
#pragma HLS UNROLL
					pix_mat[k][m] = pix_mat[k][m+1];
				}
			}
			pix_mat[0][2] = line_buf[0][x];
			pix_mat[1][2] = line_buf[1][x];

			pix_mat[2][2] = pix.data;

			line_buf[0][x] = line_buf[1][x];	// 行の入れ替え
			line_buf[1][x] = pix.data;

			// 自分の実装した関数以外をコメントアウトしてください
			//out.data = rgb2y(pix.data);
			out.data = edge_fil(pix_mat[0][0], pix_mat[0][1], pix_mat[0][2],pix_mat[1][0], pix_mat[1][1], pix_mat[1][2],pix_mat[2][0], pix_mat[2][1], pix_mat[2][2], 200);
			//out.data = ternary(pix.data, screen.data[y*src.rows+x]);
			stream_out << out;
		}
	}
	AXIvideo2cvMat(stream_out, dst);

	cv::imwrite("tmp.bmp", dst);
}
