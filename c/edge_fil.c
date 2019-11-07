#include "manga_fil.h"
#include <stdio.h>
#include <stdlib.h>

int edge_fil(int a0,int a1,int a2,int b0,int b1,int b2,int c0,int c1,int c2){
	int x, y, result;

	x =	-a0 * 1 - a1 * 2 - a2 * 1
		+c0 * 1 + c1 * 2 + c2 * 1;

	y = -a0 * 1 + a1 * 1
		-b0 * 2 + b2 * 2
		-c0 * 1 + c2 * 1;

	result = x + y;

	if(result > 255){
		result = 255;
	}else if(result < 0){
		result = 0;
	}

	return result;
}
