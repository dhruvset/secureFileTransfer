#include "stdio.h"
#include "string.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define SIZE 20
int main(int argc, char *argv[])
{
	int sfd,cfd,len;
	FILE *fd;
	char buff[SIZE];
		FILE *fp;
	struct sockaddr_in ser,c;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=8787;
	len=sizeof(ser);
	
	bind(sfd,(struct sockaddr *)&ser,len);
	listen(sfd,1);
	
len=sizeof(c);
		cfd=accept(sfd,(struct sockaddr*)&c,&len);
		
		system("ls  >list_ser");

		fp=fopen("list_ser","r");
		while(fgets(buff,20,fp)!=NULL)
			write(cfd,buff,20);

		write(cfd,"exit",20);
		close(fp);
return 0;
}
