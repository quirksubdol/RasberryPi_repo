#include <stdio.h>

int main(){
	
	FILE *fp;
	int c;
	
	fp = fopen("ASCII_file", "r");
	if (fp == NULL)
	{
		printf("Failed to open file\n");
		return 1;
	}
	while((c = fgetc(fp)) != EOF)
	{
		putc(c, stdout);
	}
	fclose(fp);
	if (fclose(fp) != 0)
	{
		printf("Failed to close file\n");
	}
	return 0;

}
