#include "header.h"



/* mensagens */

void message_of_info (const gchar *message){
        GtkWidget               *dialog;

        /* create an error message dialog and display modally to the user */
        dialog = gtk_message_dialog_new (NULL,
                                         GTK_TYPE_DIALOG| GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_INFO,
                                         GTK_BUTTONS_OK,
                                         message);

        gtk_window_set_title (GTK_WINDOW (dialog), "Sucesso!");
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
}



void message_of_error (const gchar *message){
        GtkWidget               *dialog;

        /* create an error message dialog and display modally to the user */
        dialog = gtk_message_dialog_new (NULL,
                                         GTK_TYPE_DIALOG| GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_ERROR,
                                         GTK_BUTTONS_OK,
                                         message);

        gtk_window_set_title (GTK_WINDOW (dialog), "Erro No Sistema!");
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
}

void error_message (const gchar *message){

     GtkWidget               *dialog;

     dialog = gtk_message_dialog_new (NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     message);
    gtk_window_set_title (GTK_WINDOW (dialog), "Erro no Sistema!");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void question_message (const gchar *title, const gchar *message){
    gtk_label_set_text (interface->mensagem_tf, message);

    gtk_window_set_title (interface->true_or_false, title);
    show_widget(interface->true_or_false);
}
