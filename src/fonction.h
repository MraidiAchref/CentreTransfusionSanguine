#include <gtk/gtk.h>
typedef struct
{
	int jour;
        int mois;
        int annee;
}date_emna;

typedef struct
{
	int cin;
	char nom[20];
	char prenom[20];	
	char sexe[20];
	int ets ;
        char type_sang[20];
        date_emna d ;
}donneur;


int ajouter_emna(donneur D);
void afficher_donneur(GtkTreeView *liste);
int modifier_emna(int cin, donneur nouv);
void supprimer_donneur(int cin1);
void vider_emna(GtkWidget *liste);
int Chercher_donneur(const char *nomFichier, int cin);
donneur retrieve_donneur_data(int cin);
int nbETS(char nomFichier[]) ;
float moyRDV_ETS(char nomFichier[], int jour, int mois, int annee);
int listeRDV(char nomFichier[],  int ets, int jour, int mois, int annee);
