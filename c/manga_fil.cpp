#include <stdio.h>
#include <string.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#include "manga_fil.h"

int manga_filter(stream_t &ins, stream_t &outs){
#pragma HLS INTERFACE axis register both port=ins
#pragma HLS INTERFACE axis register both port=outs
#pragma HLS INTERFACE ap_ctrl_none port=return

	interface_t pix;
	interface_t out;

	unsigned int line_buf[2][WIDTH];
#pragma HLS array_partition variable=line_buf block factor=2 dim=1
#pragma HLS resource variable=line_buf core=RAM_2P

	int pix_mat[3][3];
#pragma HLS array_partition variable=pix_mat complete

	int sobel_fil_val, ternary_val, tmp, mix;

	Loop1 : do {	// user が 1になった時にフレームがスタートする
#pragma HLS LOOP_TRIPCOUNT min=1 max=1 avg=1
		ins >> pix;
	} while(pix.user == 0);

	Loop2 : for (int y=0; y<HEIGHT; y++){
		Loop3 : for (int x=0; x<WIDTH; x++){
#pragma HLS PIPELINE II=1
	        if (!(x==0 && y==0))	// 最初の入力はすでに入力されている
				ins >> pix;	// AXI4-Stream からの入力

			Loop4 : for (int k=0; k<3; k++){
				Loop5 : for (int m=0; m<2; m++){
#pragma HLS UNROLL
					pix_mat[k][m] = pix_mat[k][m+1];
				}
			}
			pix_mat[0][2] = line_buf[0][x];
			pix_mat[1][2] = line_buf[1][x];

			int y_val = rgb2y(pix.data);
			pix_mat[2][2] = y_val;

			line_buf[0][x] = line_buf[1][x];	// 行の入れ替え
			line_buf[1][x] = y_val;

			sobel_fil_val = sobel3(pix_mat[0][0], pix_mat[0][1], pix_mat[0][2],pix_mat[1][0], pix_mat[1][1], pix_mat[1][2],pix_mat[2][0], pix_mat[2][1], pix_mat[2][2],200);
//			sobel_fil_val = laplacian_fil(pix_mat[0][0], pix_mat[0][1], pix_mat[0][2],pix_mat[1][0], pix_mat[1][1], pix_mat[1][2],pix_mat[2][0], pix_mat[2][1], pix_mat[2][2]);
			if(y%3 == x%3) tmp = 255;
			else tmp = 0;
			ternary_val = ternary(y_val, tmp);
			mix = sobel_fil_val & ternary_val;
//			out.data = (ternary_val<<16)+(ternary_val<<8)+ternary_val; // RGB同じ値を入れる
//			out.data = (sobel_fil_val<<16)+(sobel_fil_val<<8)+sobel_fil_val;
			out.data = (mix << 16)+(mix<<8)+mix;
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

			outs << out;	// AXI4-Stream へ出力
		}
	}

	return 0;
}
