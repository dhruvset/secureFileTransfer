#include<stdio.h>
#include<string.h>
#include<stdlib.h>#include<fcntl.h>
#include<ctype.h>
int main()
{
	int defik[3][3]={4,9,15,15,17,6,24,0,17},key[3][3];
	int i,j,efp,toint[3],tmp[3];
	char buf_c[3],buf_tmp[3],tochr[1];
	int buf_out[3]={0,0,0};
	int fp,cfp;
	//FILE *fp,*cfp;
	//clrscr();
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			key[i][j]=defik[i][j];
	if((fp=open("./code.c4",O_RDONLY))==-1)
		printf("\nFILE READ ERROR :NO CODED FILE EXISTS\n");
	if((cfp=open("./code1.c4",O_CREAT|O_WRONLY))==-1)
		printf("\nFILE WRITE ERROR :FILE COULD NOT BE CREATED\n");
	while(read(fp,&buf_tmp,3)!=0)
	{
			/*
		  fscanf(fp,"%c",&buf_tmp[0]);
		  fscanf(fp,"%c",&buf_tmp[1]);
		  fscanf(fp,"%c",&buf_tmp[2]);
		 */ 
		toint[0]=buf_tmp[0]-97;
		  toint[1]=buf_tmp[1]-97;
		  toint[2]=buf_tmp[2]-97;
		  for(i=0;i<3;i++)
		  {
			for(j=0;j<3;j++)
			{
				buf_out[i]=buf_out[i]+(toint[j]*key[i][j]);
			}
		  }
		  for(i=0;i<3;i++)
		  {
			buf_out[i]=buf_out[i]%26;
			//fprintf(cfp,"%c",buf_out[i]);
			tochr[0]=buf_out[i]+97;
			write(cfp,tochr,1);
		  }
		  buf_out[0]=0;
		  buf_out[1]=0;
		  buf_out[2]=0;
	}
}
