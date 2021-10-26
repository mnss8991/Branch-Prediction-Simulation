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
	int a, b=5;
	a=0;
	while(a<10000){ //PC:0b0100_0100//putting data into file that branch is taken
	
			fputs("T,",inputfile);
			if (a%2==0){ //PC: 0b0110_1100//putting data into file that branch is taken
				fputs("T,",inputfile);
			}
			else
			{
				fputs("NT,",inputfile);//putting data into file that branch is not taken
			}
			a=a+1;
			if (b==0){
			}
	}
	fputs("NT",inputfile);
	fclose(inputfile);
	return 0;

}