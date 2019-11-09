#include "manga_fil.h"
#include "hls_math.h"

int edge_fil(int a0,int a1,int a2,int b0,int b1,int b2,int c0,int c1,int c2, int th){
	double x, y;
	double result;

	x =	-a0 * 1 - a1 * 2 - a2 * 1
		+c0 * 1 + c1 * 2 + c2 * 1;

	y = -a0 * 1 + a2 * 1
		-b0 * 2 + b2 * 2
		-c0 * 1 + c2 * 1;

	//result = x + y;
	result = hls::sqrt(hls::pow(x,2)+hls::pow(y,2));

	if(result > th) result = 0;
	else result = 255;

	return result;
}
