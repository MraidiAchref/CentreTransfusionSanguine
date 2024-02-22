#include <gtk/gtk.h>

typedef struct {
    int jour;
    int mois;
    int annee;
} date_du_don;


typedef struct {
    int id_du_don;
    int id_donneur;
    char type_de_sang[100];
    int id_ETS;
    int quantite_sang;
    date_du_don date;
} don;
void afficher_don(GtkWidget *liste,char nomFichier[]);
//crud 
void ajouter_yas(don d);
void supprimer_don( int id_to_delete);
int modifier_yas(int id_modifier, don nouveau);
// retreive id ets from achref
int* readIDsFromFile();
don retrieve_don_data(int id_du_don);
// fnct 
void sang_rare(char *sangRare);
int quantite_type( char type_sang[]);
// treeview blood % qte 
void vider_blood_quantities(GtkWidget *liste);
void blood_quantities_in_treeview(GtkTreeView *liste, int sortOrder);

// validation 
int isNumber(const char* str, int length);

don chercher_don(int id_ets , GtkTreeView *yastreeview);

//void afficher_don_ets(GtkTreeView *liste, int ets_to_search);

// filter home 
void ETSFilter(char nomFichier[], int id_ets);
void BLOODFilter(char nomFichier[], char blood[]);
void bothFilter(char nomFichier[], int id_ets, char blood[]);
// chercher 
void search_yass(const char nomFichier[], const char *searchTerm);
