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
void closeApp (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}
void button_clicked ( GtkWidget *button, gpointer data)
{
	int flag=0;
	const char *name=gtk_entry_get_text(GTK_ENTRY(ip_entry ));
	const char *pass=gtk_entry_get_text(GTK_ENTRY(file_entry));
	FILE *fp;
	fp=fopen("user_detail","a");
	fprintf(fp," %s %s\n",name,pass);
	if(dialogbox_yesno("Do you want to add more?"))
		main();
	close(fp);	
	gtk_main_quit();
}
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"USER ENTRY");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),100,100);

	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(closeApp),NULL);

	ip_label=gtk_label_new("Username");
	file_label=gtk_label_new("Password");

	ip_entry=gtk_entry_new();
	file_entry=gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(file_entry),FALSE);

	ok_button=gtk_button_new_with_label("Add user");
	cancel_button=gtk_button_new_with_label("Exit");

	g_signal_connect(GTK_OBJECT(ok_button),"clicked",GTK_SIGNAL_FUNC(button_clicked),NULL);
	g_signal_connect(GTK_OBJECT(cancel_button),"clicked",GTK_SIGNAL_FUNC(closeApp),NULL);
	hbox1=gtk_hbox_new(TRUE,5);
	hbox2=gtk_hbox_new(TRUE,5);

	vbox=gtk_vbox_new(FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox1),ip_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox1),ip_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),file_entry,TRUE,FALSE,5);

	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(hbox1),ok_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(hbox2),cancel_button,FALSE,FALSE,2);

	gtk_container_add(GTK_CONTAINER(window),vbox);

	gtk_widget_show_all(window);
	gtk_main();
return 0;
}
