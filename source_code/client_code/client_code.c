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
GtkWidget *ip_label,*file_label,*port_label,*desti_label,*name_label,*pass_label;
GtkWidget *ok_button,*cancel_button,*test_button;
GtkWidget *hbox1,*hbox2,*hbox3,*hbox4,*hbox5,*hbox6;
GtkWidget *vbox;
GtkWidget *ip_entry,*file_entry,*port_entry,*desti_entry,*name_entry,*pass_entry;

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
void test_func (GtkWidget *window, gpointer data)
{
	system("./test_conn &");
}
void closeApp (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}
void button_clicked ( GtkWidget *button, gpointer data)
{
	int flag=0;
	FILE *desti_file;
	const char *ip=gtk_entry_get_text(GTK_ENTRY(ip_entry ));
	const char *port=gtk_entry_get_text(GTK_ENTRY(port_entry));
	const char *file=gtk_entry_get_text(GTK_ENTRY(file_entry));
	const char *desti=gtk_entry_get_text(GTK_ENTRY(desti_entry));
	const char *name=gtk_entry_get_text(GTK_ENTRY(name_entry));
	const char *pass=gtk_entry_get_text(GTK_ENTRY(pass_entry));

	desti_file=fopen("target_file","w");
	fprintf(desti_file,"%s",desti);
	close(desti_file);
	flag=socket_by_me(ip,port,file,desti,name,pass);

	if(flag)
		dialogbox("The operation FAILED");
	else
		dialogbox("The operation is Successful");
	
	system("./key &");
	
	gtk_main_quit();
}
int socket_by_me(char const *ip,char const *port,char const *file,char const *desti,char const *name,char const *pass)
{
	int sfd,len,result;
	char buff[SIZE],ch;
	FILE *fd,*list;
	struct sockaddr_in c;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	c.sin_family=AF_INET;
	c.sin_addr.s_addr=inet_addr(ip);
	c.sin_port=atoi(port);
	len=sizeof(c);
	dialogbox_q("Press OK when ready?");		
	result=connect(sfd,(struct sockaddr *)&c,len);
	if(result==-1)
	{
		dialogbox_q("The connection cannot be established\nERROR\n");
		return 1;
	}
	dialogbox("The connection is being established\nList has been downloaded");
	write(sfd,name,20);
	write(sfd,pass,20);
	fd=fopen("filez","w");
	do
	{
		read(sfd,&buff,20);
		if(strcmp(buff,"exit")==0)
			break;
		fprintf(fd,"%s",buff);
	}while(1);
	close(fd);
	
	/*reading the index.c4 file */
	
	fd=fopen("index.c4","w");
	write(sfd,file,20);
		
	do
	{
		read(sfd,&buff,20);
		if(strcmp(buff,"exit")==0)
			break;
		fprintf(fd,"%s",buff);
	}while(1);
	close(fd);
	/*reading the encode.c4 file */
	fd=fopen("code.c4","w");
	strcpy(buff,"code.c4");
	write(sfd,buff,20);

	do
	{
		read(sfd,&buff,20);
		if(strcmp(buff,"exit")==0)
			break;
		fprintf(fd,"%s",buff);
	}while(1);
	
	close(fd);
close(sfd);
return 0;
}
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"DOWNLOAD TERMINAL");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),125,125);

	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(closeApp),NULL);

	ip_label=gtk_label_new("Server's IP");
	file_label=gtk_label_new("Download File");
	port_label=gtk_label_new("Socket's Port");
	desti_label=gtk_label_new("Destination filename");
	name_label=gtk_label_new("Username");
	pass_label=gtk_label_new("Password");

	ip_entry=gtk_entry_new();
	file_entry=gtk_entry_new();
	port_entry=gtk_entry_new();
	desti_entry=gtk_entry_new();
	name_entry=gtk_entry_new();
	pass_entry=gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(pass_entry),FALSE);

	ok_button=gtk_button_new_with_label("Search for Server");
	cancel_button=gtk_button_new_with_label("Quit");
	test_button=gtk_button_new_with_label("Test Server");

	g_signal_connect(GTK_OBJECT(ok_button),"clicked",GTK_SIGNAL_FUNC(button_clicked),NULL);
	g_signal_connect(GTK_OBJECT(cancel_button),"clicked",GTK_SIGNAL_FUNC(closeApp),NULL);
	g_signal_connect(GTK_OBJECT(test_button),"clicked",GTK_SIGNAL_FUNC(test_func),NULL);

	hbox1=gtk_hbox_new(TRUE,5);
	hbox2=gtk_hbox_new(TRUE,5);
	hbox3=gtk_hbox_new(TRUE,5);
	hbox4=gtk_hbox_new(TRUE,5);
		hbox5=gtk_hbox_new(TRUE,5);
		hbox6=gtk_hbox_new(TRUE,5);
	
	vbox=gtk_vbox_new(FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox1),ip_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox1),ip_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox3),port_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox3),port_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox4),desti_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox4),desti_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox5),name_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox5),name_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox6),pass_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox6),pass_entry,TRUE,FALSE,5);

	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox3,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox4,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox5,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox6,FALSE,FALSE,2);


	gtk_box_pack_start(GTK_BOX(vbox),test_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),cancel_button,FALSE,FALSE,2);

	gtk_container_add(GTK_CONTAINER(window),vbox);

	gtk_widget_show_all(window);
	gtk_main();
return 0;
}
