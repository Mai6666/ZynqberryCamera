#include "manga_fil.h"

void manga_filter(stream_t &stream_in, stream_t &stream_out, volatile int *screen){
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both port=screen
#pragma HLS INTERFACE axis register both port=stream_out
#pragma HLS INTERFACE axis register both port=stream_in

	interface_t pix, out;

	int line_buf[2][WIDTH];
#pragma HLS array_partition variable=line_buf block factor=2 dim=1
#pragma HLS resource variable=line_buf core=RAM_2P

	int pix_mat[3][3];
#pragma HLS array_partition variable=pix_mat complete

	int edg;

	Loop1 : do {	// user が 1になった時にフレームがスタートする
#pragma HLS LOOP_TRIPCOUNT min=1 max=1 avg=1
		stream_in >> pix;
	} while(pix.user == 0);

	for(int y=0; y<HEIGHT; y++){
		for(int x=0; x<WIDTH; x++){
#pragma pipeline
			if (!(x==0 && y==0)) stream_in >> pix;

			pix.data = rgb2y(pix.data);
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

			edg = edge_fil(pix_mat[0][0], pix_mat[0][1], pix_mat[0][2],pix_mat[1][0], pix_mat[1][1], pix_mat[1][2],pix_mat[2][0], pix_mat[2][1], pix_mat[2][2], 200);
			out.data = edg & ternary(pix.data, screen[y*WIDTH+x]);


			if (x<2 || y<2) // 最初の2行とその他の行の最初の2列は無効データなので0とする
				out.data = 0;

			if (x==0 && y==0) // 最初のデータでは、TUSERをアサートする
				out.user = 1;
			else
				out.user = 0;

			if (x == (WIDTH-1))	// 行の最後で TLAST をアサートする
				out.last = 1;
			else
				out.last = 0;

			stream_out << out;
		}
	}

}
