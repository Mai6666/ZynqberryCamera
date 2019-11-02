// ライブラリの読み込み
#include <stdio.h>
#include <string.h>
#include <ap_int.h>
// VivadoHLSライブラリの読み込み
#include <hls_stream.h> // streamを使�?用
#include <ap_axi_sdata.h> // 小数点使�?用

#include "manga_fil.h"

void manga_filter(stream_t& stream_in, stream_t& stream_out, volatile int *tmp){
	interface_t pix;
	interface_t lap;

	// ラインバッファー
	unsigned int line_buf[2][WIDTH];
#pragma HLS array_partition variable=line_buf block factor=2 dim=1
#pragma HLS resource variable=line_buf core=RAM_2P

	// ウィンドウ
	int pix_mat[3][3];
#pragma HLS array_partition variable=pix_mat complete

	int lap_fil_val;
	int ter;

	// 画像データを�?つ
	Loop1 : do {
#pragma HLS LOOP_TRIPCOUNT min=1 max=1 avg=1
		stream_in >> pix;
	} while(pix.user == 0);

	// 画像�?��?
	Loop2 : for (int y=0; y<HEIGHT; y++){
		Loop3 : for (int x=0; x<WIDTH; x++){
#pragma HLS PIPELINE II=1
	        if (!(x==0 && y==0))
				stream_in >> pix;
	        lap = pix;

			Loop4 : for (int k=0; k<3; k++){
				Loop5 : for (int m=0; m<2; m++){
#pragma HLS UNROLL
					pix_mat[k][m] = pix_mat[k][m+1];
				}
			}
			pix_mat[0][2] = line_buf[0][x];
			pix_mat[1][2] = line_buf[1][x];

			// グレースケール�?
			int y_val = rgb2y(pix.data);
			pix_mat[2][2] = y_val;

			line_buf[0][x] = line_buf[1][x];
			line_buf[1][x] = y_val;

			// エ�?ジ検�?�
			lap_fil_val = edge_fil(	pix_mat[0][0], pix_mat[0][1], pix_mat[0][2],
										pix_mat[1][0], pix_mat[1][1], pix_mat[1][2],
										pix_mat[2][0], pix_mat[2][1], pix_mat[2][2]);

			//�?三�?��?
			ter = ternary(lap_fil_val, tmp[y*WIDTH+x]);

			lap.data = (ter<<16)+(ter<<8)+ter;

			if (x<2 || y<2)
				lap.data = 0;

			if (x==0 && y==0)
				lap.user = 1;
			else
				lap.user = 0;

			if (x == (WIDTH-1))
				lap.last = 1;
			else
				lap.last = 0;

			stream_out << lap;
		}
	}

}
