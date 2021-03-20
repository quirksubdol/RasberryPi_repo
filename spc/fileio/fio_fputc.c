#include <stdio.h>

int main(){
	
	FILE *fp;
	int c;
	
	fp = fopen("letters.txt", "w");
	for(c='a'; c<='z'; c++)
	{
		fputc(c, fp);
	}
	fclose(fp);
	return 0;

}
