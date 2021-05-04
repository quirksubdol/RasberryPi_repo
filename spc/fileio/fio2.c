#include <stdio.h>

int main(){
	
	FILE *fp;
	char s[100];
	
	fp = fopen("ASCII_file", "r");
	if (fp == NULL)
	{
		printf("Failed to open file\n");
		return 1;
	}
	while(fgets(s, 100, fp) != NULL)
	{
		printf("%s", s);
	}
	fclose(fp);
	if (fclose(fp) != 0)
	{
		printf("Failed to close file\n");
	}
	return 0;

}
