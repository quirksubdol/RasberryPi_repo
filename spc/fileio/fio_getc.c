#include <stdio.h>

int main(){
	
	FILE *fp;
	int c;
	
	fp = fopen("letters.txt", "r");
	while((c = fgetc(fp)) != EOF)
	{
		putc(c, stdout);
	}
	fclose(fp);
	return 0;

}
