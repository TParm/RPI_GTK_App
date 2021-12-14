/*gcc `pkg-config --cflags --libs gtk+-2.0` gtkgui.c -o GTK_start -lPJ_RPI*/
// gcc `pkg-config --cflags --libs gtk+-2.0` gtkgui.c -o GTK_start -lwiringPi
// -lwiringPi
#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wiringPi.h>

// Global variables
char ledOn[20] = "Led on";
char ledOff[20] = "Led off";
char ledslblRecover[20] = "Leds status: Off";

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

// Inputs for 2 buttons
// GPIO 18
void buttonPressed1(GtkWidget *wid, gpointer ptr)
{
    if (digitalRead(18))
    {
        gtk_label_set_text(GTK_LABEL(ptr), "button(18) is pressed");
        delay(50);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(ptr), "Button(18) is not pressed");
        delay(50);
    }
}

// GPIO23
void buttonPressed2(GtkWidget *wid, gpointer ptr)
{
    if (digitalRead(23))
    {
        gtk_label_set_text(GTK_LABEL(ptr), "Button(23) is pressed!");
        delay(50);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(ptr), "Button(23) is not pressed");
        delay(50);
    }
}

// Outpus for 2 leds
// GPIO 17
void toggleLed1(GtkWidget *wid, gpointer ptr) // GREEN LED in my case
{
    gtk_label_set_text(GTK_LABEL(ptr), ledOn);
    while (gtk_events_pending())
        gtk_main_iteration();
    digitalWrite(17, HIGH);
    delay(500);
    sleep(2);

    gtk_label_set_text(GTK_LABEL(ptr), ledOff);
    while (gtk_events_pending())
        gtk_main_iteration();
    digitalWrite(17, LOW);
    delay(500);
    sleep(2);
    gtk_label_set_text(GTK_LABEL(ptr), ledslblRecover);
}

// GPIO27
void toggleLed2(GtkWidget *wid, gpointer ptr) //// LED in my case
{
    gtk_label_set_text(GTK_LABEL(ptr), ledOn);
    while (gtk_events_pending())
        gtk_main_iteration();
    digitalWrite(27, HIGH);
    delay(500);
    sleep(2);

    gtk_label_set_text(GTK_LABEL(ptr), ledOff);
    while (gtk_events_pending())
        gtk_main_iteration();
    digitalWrite(27, LOW);
    delay(500);
    sleep(2);
    gtk_label_set_text(GTK_LABEL(ptr), ledslblRecover);
}

int main(int argc, char *argv[])
{
    // Setup GPIO's
    wiringPiSetupGpio();
    // Outputs leds
    pinMode(17, OUTPUT);
    pinMode(27, OUTPUT);

    // Inputs button
    pinMode(18, INPUT);
    pinMode(23, INPUT);
    pullUpDnControl(18, PUD_DOWN);
    pullUpDnControl(23, PUD_DOWN);

    gtk_init(&argc, &argv);
    // Window
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Table
    GtkWidget *tblMain = gtk_table_new(4, 4, TRUE); // tabel //0-4
    // buttons
    GtkWidget *btnExit = gtk_button_new_with_label("Exit");
    GtkWidget *btnGpio17 = gtk_button_new_with_label("17");
    GtkWidget *btnGpio27 = gtk_button_new_with_label("27");
    GtkWidget *btnToggle = gtk_button_new_with_label("toggle");
    GtkWidget *btnInputs = gtk_button_new_with_label("Show inputs");

    // labels
    GtkWidget *lblTitle = gtk_label_new("GTK input/output app");
    GtkWidget *lblLedStatus = gtk_label_new("Leds status: Off");
    GtkWidget *lblSubTitle = gtk_label_new("Choose a output gpio:");
    GtkWidget *lblBtnStatus1 = gtk_label_new("Button 1 status");
    GtkWidget *lblBtnStatus2 = gtk_label_new("Button 2 status"); // Button 2 status
    GtkWidget *lblInputStatus = gtk_label_new("input status:");

    GtkWidget *input = gtk_entry_new();

    // events
    g_signal_connect(btnExit, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(btnGpio17, "clicked", G_CALLBACK(toggleLed1), lblLedStatus);
    g_signal_connect(btnGpio27, "clicked", G_CALLBACK(toggleLed2), lblLedStatus);
    g_signal_connect(btnInputs, "clicked", G_CALLBACK(buttonPressed1), lblBtnStatus1);
    g_signal_connect(btnInputs, "clicked", G_CALLBACK(buttonPressed2), lblBtnStatus2);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    // widgets toevoegen aan tabel
    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblTitle, 1, 9, 0, 1); // 1ste nummer < 2de nummer, 3de nummer < 4de nummer (eerste 2 zijn de breedte, laatste 2 zijn de hoogte)
    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblLedStatus, 1, 9, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), btnGpio17, 1, 5, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), btnGpio27, 5, 9, 2, 3);

    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblSubTitle, 1, 9, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), input, 1, 7, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), btnToggle, 7, 9, 4, 5);

    gtk_table_attach_defaults(GTK_TABLE(tblMain), btnInputs, 1, 9, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblInputStatus, 1, 9, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblBtnStatus1, 0, 5, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), lblBtnStatus2, 5, 10, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(tblMain), btnExit, 10, 10, 10, 11);

    // box toevoegen aan window
    gtk_container_add(GTK_CONTAINER(win), tblMain);

    gtk_widget_show_all(win);

    gtk_main();
}