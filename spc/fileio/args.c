#include <stdio.h> 

int main(int argc, char *argv[])
{
	for(int i=1; i<=argc; i++)
	{
		printf("arg%d:%s\n", i, argv[i-1]);
	}
	return 0;
}
