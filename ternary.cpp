int ternary(int pix, int tmp)
{
		int i;
		int result;
		const int thresholds[] = {86, 171};
		const int count = 2;
		const int band = 255 / count;

		for(i = 0 ; i < count ; ++i)
				if(pix < thresholds[i]) break;
		
		result = i * band;
		if(result == 254) return 255;
		else return result;
}
