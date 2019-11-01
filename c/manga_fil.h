// ビデオライブラリを使う用
#include "hls_video.h"

#define height 720
#define width 1280

typedef ap_axis<32,1,1,1> interface_t;
typedef hls::stream<interface_t> stream_t;

void manga_filter(stream_t&, stream_t&, volatile int *);
int rgb2y(int);
int edge_fil(int, int, int, int, int, int, int, int, int);
int ternary(int, int );

