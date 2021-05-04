#include <stdio.h>

int main(int argc, char *argv[]){
	
	FILE *fp;
	char s[100];
	
	// we use argv[1] to read the second argument 
	// after the ./fio3 which is the first argument in the command line 
	fp = fopen(argv[1], "r");
	
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
