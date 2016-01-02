#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc,const char *argv[])
{
	int i,j,lvl=0,efp;
	char buf_c[1],lv[1];
	int fp,op,cp;	
	//FILE *fp,*op,*cp;
/*	if(argc!=3)
	{
		printf("Usage:<filename> <code>\nFilename:File to be encrypted\nCode    :1 for encoding using default key(Casual User)\n        :2 for specyfying the key(Advanced User)");
		getch();
		exit(0);
	}*/
	if((fp=open("text.c4",O_RDONLY))==-1)
	{
		printf("\nFILE READ ERROR NO SUCH FILE EXISTS\n");
		//getch();
		return 1;
	}
	if((cp=open("encode.c4",O_CREAT|O_WRONLY))==-1)
	{
		printf("\nFILE WRITE ERROR: NO FILE COULD BE CREATED\n");
		return 1;
	}
	if((op=open("index.c4",O_CREAT|O_WRONLY))==-1)
	{
		printf("\nFILE WRITE ERROR: NO FILE COULD BE CREATED\n");
		return 1;
	}
	while(read(fp,&buf_c[0],1)!=0)
	{
		lvl=buf_c[0]/26;
		lv[0]=lvl+97;
		buf_c[0]=(buf_c[0]%26);
		if(buf_c[0]==25)
			lv[0]+=1;
		if ((write(op,lv,1))==-1) printf("error");
		buf_c[0]+=98;
		write(cp,buf_c,1);
	}
close(cp);
close(op);
}
