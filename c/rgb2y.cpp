#include "manga_fil.h"

int rgb2y(int pix){
  int R,G,B;
  int value;

   R =((pix >> 16) & 0xff);
   G =((pix >> 8) & 0xff);
   B =(pix  & 0xff);

  if(R==G && G==B){
    return R;
  }
  else{
    value = (0.299 * R + 0.587 * G + 0.144 * B);
    return value;
  }
}
