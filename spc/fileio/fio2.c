#include <stdio.h>

int main(){
	
	FILE *fp;
	char s[100];
	
	fp = fopen("ASCII_file", "r");
	while(fgets(s, 100, fp) != NULL)
	{
		printf("%s", s);
	}
	fclose(fp);
	return 0;

}
