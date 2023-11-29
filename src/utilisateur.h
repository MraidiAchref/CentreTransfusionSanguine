#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>

enum
{
    IDENTIFIANT,
    NOM,
    PRENOM,
    SEXE,
    ROLE,
    DATE,
    PASSWORD,
    COLUMNS
};


typedef struct
{
    int day ;
    int month ;
    int year;
}Date;

typedef struct
{
    char Nom[20];
    char Prenom[20];
    char Sexe[30];
    char Role[30];
    char ID[30];
    char Password[30];
    Date D;
} Utilisateur;


void ajouter( Utilisateur );
int modifier(char id[], Utilisateur nouv);
void afficher_utilisateur(GtkWidget *liste, char nomFicher[] );
int supprimer_utilisateur( char id[]);
Utilisateur verifier( char id[]);
char* Sexe(int choice[]);
char* Role(int choice[]);
Date get_date_from_entry(GtkEntry *entry);
void UserRole(char nomFichier[], char role[]);
void pourcentageUser(char nomFichier[], int *nbHomme, int *nbFemme);
void vider(GtkWidget *liste );
void UserFilter(char nomFichier[], char role[], char sex[]);
void UserSexe(char nomFichier[], char sexe[]);
int is_ID_exists(const char *ID);
void on_cell_edited(GtkCellRendererText *renderer, gchar *path_string, gchar *new_text, gpointer user_data) ;
Date parse_date(const gchar *date_str);
void date_to_string(const Date *date, char *date_str);




#endif // POINT_H_INCLUDED
