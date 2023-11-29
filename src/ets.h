#include <gtk/gtk.h>

enum {
	ID,
	Nom,
	Adresse,
	Region,
	Capacite,
	COLUMN
} ;


typedef struct {
    int ID;
    char Nom [30] ;
    char Adresse[30];
    char Region[30];
    int Capacite ;
}ETS ;

int verifierTypeUtilisateur (char login[], char password[]) ;
void add_ets(ETS entablissemet) ;
void display_ets(GtkTreeView  *list, char nomFIchier[]);
void delete_ets(ETS etablissement) ;
void viderETS(GtkTreeView *list) ;
void ETSTrieCapaciteCroiss(char nomFichier[]);
void ETSTrieCapaciteDecroiss(char nomFichier[]);
int ETSParRegion(char nomFichier[], char reg[]) ; 
ETS ChercherEts (char * nomFichier,  int ID  ) ;
int ModifierEts (char * nomFichier, ETS ets , int ID  ) ;
int SupprimerEts (int ID  );
void ETSTrieIDCroiss(char nomFichier[]); 
void ETSTrieIDDecroiss(char nomFichier[]);
int generateID(const char *filename) ;
void on_cell_ets_edited(GtkCellRendererText *cell, gchar *path_string, gchar *new_text, gpointer user_data);
void apply_style_textColor(GtkWidget *widget , const char *colorID) ;
void apply_style_bg(GtkWidget *widget , const char *colorID) ;
void apply_style_fg(GtkWidget *widget , const char *colorID) ;
void set_label_font(GtkLabel *label, const char *font_description) ;
