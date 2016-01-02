#include <gtk/gtk.h>
#include "stdio.h"
#include "string.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define SIZE 20

GtkWidget *window,*win_ser_run;
GtkWidget *ip_label,*file_label;
GtkWidget *ok_button,*cancel_button;
GtkWidget *hbox1,*hbox2;
GtkWidget *vbox;
GtkWidget *ip_entry,*file_entry;

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
void sock_client(char const *ip)
{
	int sfd,len,result;
	char buff[SIZE],ch;
	FILE *fd,*list;
	struct sockaddr_in c;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	c.sin_family=AF_INET;
	c.sin_addr.s_addr=inet_addr(ip);
	c.sin_port=8787;
	len=sizeof(c);
	//dialogbox_q("Press OK when ready?");		
	result=connect(sfd,(struct sockaddr *)&c,len);
	if(result==-1)
	{
		printf("The connection cannot be established\nERROR\n");
		exit(1);
	}
	//dialogbox("The connection is being established\nList has been downloaded");
	
	fd=fopen("filez","w");
	do
	{
		read(sfd,&buff,20);
		if(strcmp(buff,"exit")==0)
			break;
		fprintf(fd,"%s",buff);
	}while(1);
	close(fd);
	system("xmessage -file filez -timeout 60 &");
}
void closeApp (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}
void button_clicked ( GtkWidget *button, gpointer data)
{
	int flag=0;
	const char *ip=gtk_entry_get_text(GTK_ENTRY(ip_entry ));
	//const char *pass=gtk_entry_get_text(GTK_ENTRY(file_entry));
	sock_client(ip);
	gtk_main_quit();
}
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Test Server");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),100,100);

	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(closeApp),NULL);

	ip_label=gtk_label_new("Server's IP");
	//file_label=gtk_label_new("Password");

	ip_entry=gtk_entry_new();
	//file_entry=gtk_entry_new();
	//gtk_entry_set_visibility(GTK_ENTRY(file_entry),FALSE);

	ok_button=gtk_button_new_with_label("Test");
	cancel_button=gtk_button_new_with_label("Exit");

	g_signal_connect(GTK_OBJECT(ok_button),"clicked",GTK_SIGNAL_FUNC(button_clicked),NULL);
	g_signal_connect(GTK_OBJECT(cancel_button),"clicked",GTK_SIGNAL_FUNC(closeApp),NULL);
	hbox1=gtk_hbox_new(TRUE,5);
	hbox2=gtk_hbox_new(TRUE,5);

	vbox=gtk_vbox_new(FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox1),ip_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox1),ip_entry,TRUE,FALSE,5);
	

	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,2);
	
	gtk_box_pack_start(GTK_BOX(hbox2),ok_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(hbox2),cancel_button,FALSE,FALSE,2);

	gtk_container_add(GTK_CONTAINER(window),vbox);

	gtk_widget_show_all(window);
	gtk_main();
return 0;
}
