#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int defk[3][3]={17,17,5,21,18,21,2,2,19},usrk[3][3],key[3][3];
	int i,j,efp,tmp[3],lvl[3],tmp1;
	char buf_c[3],tochr,lv[1],buffer[3];
	int buf_out[3]={0,0,0};
	int fp,cfp;
	//FILE *fp,*cfp;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			key[i][j]=defk[i][j];
	if((fp=open("encode.c4",O_RDONLY))==-1)
		printf("\nFILE READ ERROR NO SUCH FILE EXISTS\n");
	if((cfp=open("code.c4",O_CREAT|O_WRONLY))==-1)
		printf("\nFILE WRITE ERROR :FILE COULD NOT BE CREATED\n");
	while(read(fp,&buf_c,3)!=0)
	{
		  /*read(fp,&buf_c[0],1);
		  read(fp,&buf_c[1],1);
		  read(fp,&buf_c[2],1);
		  */
		  tmp[0]=buf_c[0]-97;
		  tmp[1]=buf_c[1]-97;
		  tmp[2]=buf_c[2]-97;
		  for(i=0;i<3;i++)
		  	for(j=0;j<3;j++)
				buf_out[i]=buf_out[i]+(tmp[j]*key[i][j]);
		  for(i=0;i<=2;i++)
		  {
			tmp1=(buf_out[i]%26);
			//printf("%d",tmp1);
			lv[0]=tmp1+97;
			//printf("%c",lv[0]);			
			//tochr=tmp1;
			if(write(cfp,lv,1)==-1) printf("error");
			//write(cfp,tochr,1);
		  }
		  buf_out[0]=0;
		  buf_out[1]=0;
		  buf_out[2]=0;
	}
}
