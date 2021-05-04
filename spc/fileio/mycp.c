#include <stdio.h>

int main(int argc, char *argv[]){
	
	FILE *fp1, *fp2;
	// char input[100], output[100];
	// char s[100];
	int c;
	
	fp1 = fopen(argv[1], "r");
	if (fp1 == NULL)
	{
		printf("Failed to open file\n");
		return 1;
	}
	fp2 = fopen(argv[2], "w");
	
	while((c = fgetc(fp1)) != EOF)
	{
		putc(c, fp2);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	if (fclose(fp1) != 0)
	{
		printf("Failed to close file\n");
	}
	return 0;

}
