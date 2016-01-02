#include <gtk/gtk.h>
#include "stdio.h"
#include "string.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define SIZE 20

GtkWidget *window,*win_ser_run,*win_ser_can;
GtkWidget *ip_label,*file_label;
GtkWidget *ok_button,*cancel_button,*add_user;
GtkWidget *hbox1,*hbox2;
GtkWidget *vbox;
GtkWidget *ip_entry,*file_entry;

void dialogbox(char *text)
{
win_ser_run=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,text);
		gtk_dialog_run(GTK_DIALOG(win_ser_run));
		gtk_widget_destroy(win_ser_run);
}
void dialogbox_q(char *text)
{
win_ser_run=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,text);
		gtk_dialog_run(GTK_DIALOG(win_ser_run));
		gtk_widget_destroy(win_ser_run);
		//gtk_main_quit();
}
int dialogbox_q2(char *text)
{
int res=0;
win_ser_run=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK_CANCEL,text);
		res=gtk_dialog_run(GTK_DIALOG(win_ser_run));
		gtk_widget_destroy(win_ser_run);
		switch(res)
		{
		case GTK_RESPONSE_OK:	//dialogbox("ok");
					return 0;
		case GTK_RESPONSE_CANCEL:	
					//dialogbox("cancel");
					return 1;
		}
}
int dialogbox_yesno(char *text)
{
int res=0;
win_ser_run=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,text);
		res=gtk_dialog_run(GTK_DIALOG(win_ser_run));
		gtk_widget_destroy(win_ser_run);
		switch(res)
		{
		case GTK_RESPONSE_YES:	//dialogbox("ok");
					return 1;
		case GTK_RESPONSE_NO:	
					//dialogbox("cancel");
					return 0;
		}
}
int verify(char *name,char *pass)
{
	FILE *fp;
	char buff[20];
	fp=fopen("user_detail","r");
	while(!feof(fp))
	{
		if(fscanf(fp,"%s",buff))
		{
			if(strcmp(name,buff)==0)
			{
				if(fscanf(fp,"%s",buff))
					if(strcmp(pass,buff)==0)
						return 1;
			}
		}
	}
return 0;
}	
int socket_by_me(char const *ip,char const *port)
{
	int sfd,cfd,len;
	FILE *fd;
	struct sockaddr_in ser,c;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(ip);
	ser.sin_port=atoi(port);
	len=sizeof(ser);
	
	bind(sfd,(struct sockaddr *)&ser,len);
	listen(sfd,1);
	//dialogbox("The Server is up and running, waiting for request!!\nShall we start?");
x:
	while(1)
	{
		char buff[SIZE],name[20],pass[20],file_buff[30];
		int i;
		FILE *fp;
		len=sizeof(c);
		//log=fopen("LOGS_SERVER","a");
		
		//printf("\nServer is waiting");
		cfd=accept(sfd,(struct sockaddr*)&c,&len);
		
		read(cfd,&buff,20);
		strcpy(name,buff);
		
		read(cfd,&buff,20);
		strcpy(pass,buff);
		//sprintf(log,"xmessage -timeout 5 \"\nUSERNAME %s trying to logon \"",name);
		//system(log);
		if(!verify(name,pass))
		{
			dialogbox("The User is not Authentic");
		//	sprintf(log,"\nUSERNAME %s logon failed",name);
			goto x;
		}
		//sprintf(log,"\nUSERNAME %s Successfully logon",name);
		//dialogbox("Access Granted");
		system("ls  >list_ser");

		fp=fopen("list_ser","r");
		while(fgets(buff,20,fp)!=NULL)
			write(cfd,buff,20);

		write(cfd,"exit",20);
		close(fp);
		
		/*reading the file passed*/
		read(cfd,&buff,20);
		sprintf(file_buff,"cp %s text.c4",buff);

		system("xmessage -timeout 60 -buttons FILE_REQUESTED -file text.c4 &");
		if(system(file_buff)==-1)
			printf("eeeeee");

		//sprintf(log,"\nFile requested %s",buff);
		if(system("./in")==-1)
			dialogbox("sdfsdfsdf");
		system("./h");
		system("xmessage -file index.c4 -timeout 60 -buttons encode.c4 &");
		/*sending the index file*/
		fp=fopen("index.c4","r");

		while(fgets(buff,20,fp)!=NULL)
			write(cfd,buff,20);
		write(cfd,"exit",20);
		close(fp);
		/*sending the code file*/
		fp=fopen("code.c4","r");
		while(fgets(buff,20,fp)!=NULL)
			write(cfd,buff,20);
		write(cfd,"exit",20);
		close(fp);
		//sprintf(log,"\nFile download successful\n");
		//system("xmessage -timeout 20 -file LOGS_SERVER &");
		/*if(dialogbox_yesno("Want to stop the server?"))
		{
			if(!dialogbox_q2("Delete the temporary files?"))
				system("rm *c4");
		exit(0);
		}*/
		sleep(1);
		system("rm *c4 &");
	}
close(cfd);
close(sfd);
return 0;
}
void add_user_func (GtkWidget *window, gpointer data)
{
	system("./add_user &");
}
void closeApp (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}
void button_clicked ( GtkWidget *button, gpointer data)
{
	int flag=0;
	char fill[30];
	const char *ip=gtk_entry_get_text(GTK_ENTRY(ip_entry ));
	const char *port=gtk_entry_get_text(GTK_ENTRY(file_entry));
	
	sprintf(fill,"./test_ser %s &",ip);
	system(fill);
	flag=socket_by_me(ip,port);
	
	if(flag)
		dialogbox("The operation FAILED");
	else
		dialogbox("The operation is Successful");
	gtk_main_quit();
}
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"FILE SERVER");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),200,200);

	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(closeApp),NULL);

	ip_label=gtk_label_new("Server IP");
	file_label=gtk_label_new("Service Port");

	ip_entry=gtk_entry_new();
	file_entry=gtk_entry_new();

	ok_button=gtk_button_new_with_label("Initiate Server");
	add_user=gtk_button_new_with_label("Add User(s)");
	cancel_button=gtk_button_new_with_label("Quit");

	g_signal_connect(GTK_OBJECT(ok_button),"clicked",GTK_SIGNAL_FUNC(button_clicked),NULL);
	g_signal_connect(GTK_OBJECT(cancel_button),"clicked",GTK_SIGNAL_FUNC(closeApp),NULL);
	g_signal_connect(GTK_OBJECT(add_user),"clicked",GTK_SIGNAL_FUNC(add_user_func),NULL);
	hbox1=gtk_hbox_new(TRUE,5);
	hbox2=gtk_hbox_new(TRUE,5);

	vbox=gtk_vbox_new(FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox1),ip_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox1),ip_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_entry,TRUE,FALSE,5);

	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),cancel_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),add_user,FALSE,FALSE,2);


	gtk_container_add(GTK_CONTAINER(window),vbox);

	gtk_widget_show_all(window);
	gtk_main();
return 0;
}
