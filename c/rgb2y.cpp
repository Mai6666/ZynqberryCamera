#include "manga_fil.h"
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char byte;
typedef unsigned char ubyte;

int rgb2y(int pix){
  ubyte R,G,B;
  int value;

   R =(ubyte)((pix >> 16) & 0xff);
   G =(ubyte)((pix >> 8) & 0xff);
   B =(ubyte)(pix  & 0xff);
    
  if(R==G && G==B){
    return R;
  }
  else{
    byte value = (byte)(0.299 * R + 0.587 * G + 0.144 * B);
    return value;
  }
}
