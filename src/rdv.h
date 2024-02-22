#ifndef ETS_H
#define ETS_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ctype.h>
#include <gdk/gdk.h>

typedef struct {
    char jour[50];
    char mois[50];
    char annee[50];
} Date_gh;

typedef struct {
    int ID;
    char Etablissement[30];
    char heure[30];
    Date_gh date;
} RDV;

int Chercher(char *nomFichier, int ID);
int add_rdv(RDV rendezvous);
void ModifierRDV(int ID, RDV newRdv);
void display_rdv(GtkWidget *liste, char nomFichier[]);
void Chercher_user(int ID);
int SupprimerRDV(int ID);
void Chercher_user_by_etablissement(const char *etablissement);
int get_capacity(const char *etablissement, const char *date);

#endif

