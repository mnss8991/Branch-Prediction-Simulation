#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(int argc,char** argv)
{
	int num;
	if(argc != 2)
	{
		printf("Invalid");
		return 0;
	}
	FILE *inputfile=fopen(argv[1],"w+");
	if(inputfile == NULL)
	{
		printf("File has no contents");
		return 0;
	}
	int a, b;
	a=10000;
	while(a>0){ //PC:0b0100_0100//putting data into file that branch is taken
		b=50;
		fputs("T,",inputfile);
		while (b>0){ //PC: 0b0110_1100
			fputs("T,",inputfile);//putting data into file that branch is taken
			b=b-2;
		}
		if(b<=0)
		{
			fputs("NT,",inputfile); // code for branch is not taken
		}
		a=a-1;
	}
	fputs("NT",inputfile);
	fclose(inputfile);
	return 0;

}