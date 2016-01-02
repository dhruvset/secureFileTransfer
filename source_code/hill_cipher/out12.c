#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>
int main()
{
	char txt[1],lvl[1],out[1];
	int a;
	int fp,ip,op;
	//FILE fp,ip,op;
	if((fp=open("./code1.c4",O_RDONLY))==-1)
		printf("\nFILE READ ERROR :FILE NOT PRESENT\n");
	if((ip=open("./index.c4",O_RDONLY))==-1)
		printf("\nFILE READ ERROR :FILE NOT PRESENT\n");
	if((op=open("./output.c4",O_WRONLY|O_CREAT))==-1)
		printf("\nFILE WRITE ERROR :FILE COULD NOT BE CREATED\n");
	while(read(ip,lvl,1)!=0)
	{
		//fscanf(fp,"%c",&txt[0]);
		//fscanf(ip,"%c",&lvl[0]);
		read(fp,&txt,1);

		
		txt[0]-=97;
		if(txt[0]==26)
			lvl[0]+=1;
		
		lvl[0]-=97;		
			
		a=(lvl[0]*26);
		//fprintf(op,"%c",((a+txt[0])-1));
		
		out[0]=((a+txt[0])-1);
		write(op,out,1);
	}
}




