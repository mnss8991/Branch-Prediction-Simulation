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
	int a, b, m;
	m=10000;
	while(m>0){ //PC:0b0100_0100//putting data into file that branch is taken
			a = m%2;
			fputs("T,",inputfile);
			if (a==2) {//PC: 0b0110_1100//putting data into file that branch is taken
				a=0;
				fputs("T,",inputfile);
			}
			else
			{
				fputs("NT,",inputfile);//putting data into file that branch is not taken
			}
			b=(int) m/2;
			if (b==2) {//PC: 0b0111_0100//putting data into file that branch is taken
				b=0;
				fputs("T,",inputfile);
			}
			else
			{
				fputs("NT,",inputfile);//putting data into file that branch is not taken
			}
			if (a!=b){//PC: 0b1000_1000
				m=m-2;
				fputs("T,",inputfile);//putting data into file that branch is taken
			}
			else
			{
				fputs("NT,",inputfile);//putting data into file that branch is not taken
			}
			m=m-1;
		}
		fputs("NT",inputfile);//putting data into file that branch is not taken
	fclose(inputfile);
	return 0;

}