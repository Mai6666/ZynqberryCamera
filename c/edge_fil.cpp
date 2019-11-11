#include "manga_fil.h"
#include "hls_math.h"
#include "ap_fixed.h"

int sobel3(int a0,int a1,int a2,int b0,int b1,int b2,int c0,int c1,int c2, int th){
	ap_fixed<32,20> x, y;
	ap_fixed<32,20> t, r;
//	double x, y;
//	double t, r;
	int result;

	x =	-a0 * 1 - a1 * 2 - a2 * 1
		+c0 * 1 + c1 * 2 + c2 * 1;

	y = -a0 * 1 + a2 * 1
		-b0 * 2 + b2 * 2
		-c0 * 1 + c2 * 1;

	//result = x + y;
	//std::cout << x << " " << y << std::endl;
	t = x*x+y*y;
	//std::cout << "t " << t << std::endl;
	r = hls::sqrt(t);
	//std::cout << "r " << r << std::endl;

	if(r > th) result = 0;
	else result = 255;

	return result;
}

//int laplacian_fil(int x0y0, int x1y0, int x2y0, int x0y1, int x1y1, int x2y1, int x0y2, int x1y2, int x2y2)
//{
//	int y;
//
//	y = -x0y0 -x1y0 -x2y0 -x0y1 +8*x1y1 -x2y1 -x0y2 -x1y2 -x2y2;
//	if (y<0)
//		y = 0;
//	else if (y>255)
//		y = 255;
//    return(255-y);
//}
