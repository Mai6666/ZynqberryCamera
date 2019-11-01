#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <iostream>
#include <fstream>
#include <ap_axi_sdata.h>

#include "manga_fil.h"
#include "bmp_header.h"

int main()
{
	using namespace std;

	stream_t ins;
	stream_t outs;

	interface_t pix;
	interface_t vals;

    BITMAPFILEHEADER bmpfhr;
    BITMAPINFOHEADER bmpihr;
    FILE *fbmpr, *fbmpw;
    int *rd_bmp, *tmp, *hw_lapd;
    int blue, green, red;

    // テンプレート画像読み込み
    if ((fbmpr = fopen("screen.bmp", "rb")) == NULL){
        fprintf(stderr, "Can't open test.bmp by binary read mode\n");
        exit(1);
    }

    fread(&bmpfhr.bfType, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfSize, sizeof(uint32_t), 1, fbmpr);
    fread(&bmpfhr.bfReserved1, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfReserved2, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfOffBits, sizeof(uint32_t), 1, fbmpr);
    fread(&bmpihr, sizeof(BITMAPINFOHEADER), 1, fbmpr);

    // 画像領域確保
    if ((tmp =(int *)malloc(sizeof(int) * (bmpihr.biWidth * bmpihr.biHeight))) == NULL){
        fprintf(stderr, "Can't allocate rd_bmp memory\n");
        exit(1);
    }

    for (int y=0; y<bmpihr.biHeight; y++){
        for (int x=0; x<bmpihr.biWidth; x++){
            blue = fgetc(fbmpr);
            green = fgetc(fbmpr);
            red = fgetc(fbmpr);
            rd_bmp[((bmpihr.biHeight-1)-y)*bmpihr.biWidth+x] = (blue & 0xff);
        }
    }
    fclose(fbmpr);

    // 画像読み込み
    if ((fbmpr = fopen("fox.bmp", "rb")) == NULL){
        fprintf(stderr, "Can't open test.bmp by binary read mode\n");
        exit(1);
    }

    fread(&bmpfhr.bfType, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfSize, sizeof(uint32_t), 1, fbmpr);
    fread(&bmpfhr.bfReserved1, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfReserved2, sizeof(uint16_t), 1, fbmpr);
    fread(&bmpfhr.bfOffBits, sizeof(uint32_t), 1, fbmpr);
    fread(&bmpihr, sizeof(BITMAPINFOHEADER), 1, fbmpr);

    // 画像領域確保
    if ((rd_bmp =(int *)malloc(sizeof(int) * (bmpihr.biWidth * bmpihr.biHeight))) == NULL){
        fprintf(stderr, "Can't allocate rd_bmp memory\n");
        exit(1);
    }
    if ((hw_lapd =(int *)malloc(sizeof(int) * (bmpihr.biWidth * bmpihr.biHeight))) == NULL){
        fprintf(stderr, "Can't allocate hw_lapd memory\n");
        exit(1);
    }

    for (int y=0; y<bmpihr.biHeight; y++){
        for (int x=0; x<bmpihr.biWidth; x++){
            blue = fgetc(fbmpr);
            green = fgetc(fbmpr);
            red = fgetc(fbmpr);
            rd_bmp[((bmpihr.biHeight-1)-y)*bmpihr.biWidth+x] = (blue & 0xff) | ((green & 0xff)<<8) | ((red & 0xff)<<16);
        }
    }
    fclose(fbmpr);

    for(int i=0; i<5; i++){
       	pix.user = 0;
     	pix.data = i;
    	ins << pix;
    }

    for(int j=0; j < bmpihr.biHeight; j++){
        for(int i=0; i < bmpihr.biWidth; i++){
        	pix.data = (ap_int<32>)rd_bmp[(j*bmpihr.biWidth)+i];

            if (j==0 && i==0)
            	pix.user = 1;
            else
            	pix.user = 0;

            if (i == bmpihr.biWidth-1)
                pix.last = 1;
            else
                pix.last = 0;

            ins << pix;
        }
    }

    // 画像処理回路
    manga_filter(ins, outs, tmp);

    // Streamから配列に
    cout << endl;
    cout << "outs" << endl;
    for(int j=0; j < bmpihr.biHeight; j++){
        for(int i=0; i < bmpihr.biWidth; i++){
        	outs >> vals;
            ap_int<32> val = vals.data;
            hw_lapd[(j*bmpihr.biWidth)+i] = (int)val;
        }
    }
    cout << "Success HW and SW results match" << endl;
    cout << endl;

//     画像出力
    if ((fbmpw=fopen("temp.bmp", "wb")) == NULL){
        fprintf(stderr, "Can't open temp_lap.bmp by binary write mode\n");
        exit(1);
    }

    fwrite(&bmpfhr.bfType, sizeof(uint16_t), 1, fbmpw);
    fwrite(&bmpfhr.bfSize, sizeof(uint32_t), 1, fbmpw);
    fwrite(&bmpfhr.bfReserved1, sizeof(uint16_t), 1, fbmpw);
    fwrite(&bmpfhr.bfReserved2, sizeof(uint16_t), 1, fbmpw);
    fwrite(&bmpfhr.bfOffBits, sizeof(uint32_t), 1, fbmpw);
    fwrite(&bmpihr, sizeof(BITMAPINFOHEADER), 1, fbmpw);


    for (int y=0; y<bmpihr.biHeight; y++){
        for (int x=0; x<bmpihr.biWidth; x++){
            blue = hw_lapd[((bmpihr.biHeight-1)-y)*bmpihr.biWidth+x] & 0xff;
            green = (hw_lapd[((bmpihr.biHeight-1)-y)*bmpihr.biWidth+x] >> 8) & 0xff;
            red = (hw_lapd[((bmpihr.biHeight-1)-y)*bmpihr.biWidth+x]>>16) & 0xff;

            fputc(blue, fbmpw);
            fputc(green, fbmpw);
            fputc(red, fbmpw);
        }
    }
    fclose(fbmpw);
    free(rd_bmp);
    free(hw_lapd);

    return 0;
}
