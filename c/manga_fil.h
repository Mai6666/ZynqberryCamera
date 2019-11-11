// 郢晁侭繝ｧ郢ｧ�ｽｪ郢晢ｽｩ郢ｧ�ｽ､郢晄じﾎ帷ｹ晢ｽｪ郢ｧ蜑�ｽｽ�ｽｿ邵ｺ�ｿｽ騾包ｽｨ
#include "hls_video.h"

#define HEIGHT 720
#define WIDTH 1280

typedef ap_axiu<32,1,1,1> interface_t;
typedef hls::stream<interface_t> stream_t;

int manga_filter(stream_t&, stream_t&);
int rgb2y(int);
int sobel3(int, int, int, int, int, int, int, int, int, int);
int laplacian_fil(int, int, int, int, int, int, int, int, int);
int ternary(int, int);

