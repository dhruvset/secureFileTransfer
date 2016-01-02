#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window,*win_ser_run;
GtkWidget *ip_label;
GtkWidget *ok_button,*cancel_button;
GtkWidget *hbox1;
GtkWidget *vbox;

void dialogbox(char *text)
{
win_ser_run=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,text);
		gtk_dialog_run(GTK_DIALOG(win_ser_run));
		gtk_widget_destroy(win_ser_run);
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
void closeApp (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}
void button_clicked ( GtkWidget *button, gpointer data)
{
	char ren[30],buff[20],fill[40];
	FILE *fp;

	

	if (system("./d")==-1)
		dialogbox("Error in Decryption");
	if (system("./o")==-1)
		dialogbox("Error in Output");
	
	fp=fopen("target_file","r");
	if(fp==NULL)
		printf("\nTarget_file file error\n");
	fgets(buff,20,fp);
	close(fp);
	
	system("xmessage -timeout 60 -file index.c4 -buttons index.c4 &");
	system("xmessage -timeout 60 -file code.c4 -buttons code.c4 &");
	

	sprintf(ren,"cp output.c4 %s",buff);
	system(ren);

	sprintf(fill,"xmessage -timeout 60 -file %s -buttons FILE &",buff);	
	system(fill);


	dialogbox("Decryption Successful");
	if(!dialogbox_q2("Do you want to delete the encrypted files"))
	{
		system("rm *c4 target_file");
	}
		
gtk_main_quit();
}
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Decryptor CLIENT X");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),150,150);

	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(closeApp),NULL);

	ip_label=gtk_label_new("This application decrypts the file");
	

	ok_button=gtk_button_new_with_label("Start decryption");
	cancel_button=gtk_button_new_with_label("Quit");

	g_signal_connect(GTK_OBJECT(ok_button),"clicked",GTK_SIGNAL_FUNC(button_clicked),NULL);
	g_signal_connect(GTK_OBJECT(cancel_button),"clicked",GTK_SIGNAL_FUNC(closeApp),NULL);
	hbox1=gtk_hbox_new(TRUE,5);
	
	
	vbox=gtk_vbox_new(FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox1),ip_label,TRUE,FALSE,5);
	
	
	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,2);
	

	gtk_box_pack_start(GTK_BOX(vbox),ok_button,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),cancel_button,FALSE,FALSE,2);

	gtk_container_add(GTK_CONTAINER(window),vbox);

	gtk_widget_show_all(window);
	gtk_main();
return 0;
}
