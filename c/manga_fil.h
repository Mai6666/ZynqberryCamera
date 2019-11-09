// 繝薙ョ繧ｪ繝ｩ繧､繝悶Λ繝ｪ繧剃ｽｿ縺�逕ｨ
#include "hls_video.h"

#define HEIGHT 720
#define WIDTH 1280

typedef ap_axiu<32,1,1,1> interface_t;
typedef hls::stream<interface_t> stream_t;

void manga_filter(stream_t&, stream_t&, volatile int *);
int rgb2y(int);
int edge_fil(int, int, int, int, int, int, int, int, int, int);
int ternary(int, int);

