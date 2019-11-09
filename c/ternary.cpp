int ternary(int pix, int tmp){
	int th1=60, th2=150;
	int out;

	if(pix < th1) out = 0;
	else if(pix > th2) out = 255;
	else out = tmp;

	return out;
}
