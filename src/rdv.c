#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rdv.h"
#define MAX_CAPACITY 5
#define MAX_CAPACITY_PER_DAY 5

RDV  rendezvous;
enum {
    ID_COL,
    Etablissement_COL,
    HEURE_COL,
    JOUR_COL,
    MOIS_COL,
    ANNEE_COL,
    COLUMNS
};


int add_rdv(RDV rendezvous) {
    FILE *f = fopen("RDV.txt", "a+");
    int current_capacity = 0;

    if (f != NULL) {
        fprintf(f, "%d %s %s %s %s %s \n", rendezvous.ID, rendezvous.Etablissement,
                rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee);
        fclose(f);

   
        current_capacity = get_capacity(rendezvous.Etablissement, rendezvous.date.jour);

 
        if (current_capacity != -1 && current_capacity <= MAX_CAPACITY_PER_DAY) {
            return current_capacity;
        } else {
     
            return -1;
        }
    }


    return 1;
}


 int get_capacity(const char *etablissement, const char *date) {
    FILE *f = fopen("RDV.txt", "r");
    if (f == NULL) {

        return -1;
    }

    int capacity = 0;
    RDV currentRdv;

    while (fscanf(f, "%d %29s %29s %s %s %s",
                  &currentRdv.ID, currentRdv.Etablissement,
                  currentRdv.heure, currentRdv.date.jour,
                  currentRdv.date.mois, currentRdv.date.annee) == 6) {
        if (strcmp(currentRdv.Etablissement, etablissement) == 0 &&
            strcmp(currentRdv.date.jour, date) == 0) 
 	  
{
            capacity++;
        }
    }

    fclose(f);


    if (capacity > MAX_CAPACITY_PER_DAY) {
        return -1;
    }


    return capacity;
}



void display_rdv(GtkWidget *liste, char nomFichier[])  {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    int ID;
    char Etablissement[30];
    char jour[30];
    char mois[30];
    char annee[30];
    char heure[30];

    FILE *f = fopen(nomFichier, "r");
    if (f == NULL) {
        g_print("Error: Could not open file %s for reading.\n", nomFichier);
        return;
    }

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));


    if (store != NULL) {
        gtk_list_store_clear(store);
    } else {

        store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

      
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("   ID    ", renderer, "text", 0, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("       Etablissement          ", renderer, "text", 1, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("   Heure   ", renderer, "text", 2, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("   Jour   ", renderer, "text", 3, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("   Mois   ", renderer, "text", 4, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("   Annee   ", renderer, "text", 5, NULL);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }


    while (fscanf(f, "%d %s %s %s %s %s\n", &ID, Etablissement, heure, jour, mois, annee) == 6) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, ID, 1, Etablissement, 2, heure, 3, jour, 4, mois, 5, annee, -1);
    }

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}


void Chercher_user(int ID) {
    RDV rendezvous;
    FILE *f1 = fopen("RDV.txt", "r");
    FILE *f2 = fopen("cherche.txt", "w");

    if (f1 != NULL && f2 != NULL) {
        while (fscanf(f1, "%d %s %s %s %s %s\n", &rendezvous.ID, rendezvous.Etablissement,
                      rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee) != EOF) {
            if (rendezvous.ID == ID) {
                
                fprintf(f2, "%d %s %s %s %s %s\n", rendezvous.ID, rendezvous.Etablissement,
                        rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee);
            }
        }
        fclose(f1);
        fclose(f2);
    }

    
}



int Chercher(char *nomFichier, int ID) {
    RDV rendezvous;
    int found = 0;
    FILE *f1 = fopen(nomFichier, "r");
    FILE *f2 = fopen("cherche.txt", "w");

    if (f1 != NULL && f2 != NULL) {
        while (fscanf(f1, "%d %s %s %s %s %s\n", &rendezvous.ID, rendezvous.Etablissement,
                      rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee) != EOF) {
            if (rendezvous.ID == ID) {
                found = 1;
                fprintf(f2, "%d %s %s %s %s %s\n", rendezvous.ID, rendezvous.Etablissement,
                        rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee);
            }
        }
        fclose(f1);
        fclose(f2);
    }

    return found;
}



void ModifierRDV(int ID,RDV newRdv) {
    FILE *f1 = fopen("RDV.txt", "r");
    FILE *f2 = fopen("newFile.txt", "w");
   

    if (f1 != NULL && f2 != NULL) {
        while (fscanf(f1,"%d %s %s %s %s %s \n", &rendezvous.ID, rendezvous.Etablissement,rendezvous.heure,rendezvous.date.jour,rendezvous.date.mois,rendezvous.date.annee) != EOF) {
            if (rendezvous.ID == ID) {
                fprintf(f2, "%d %s %s %s %s %s \n", rendezvous.ID, newRdv.Etablissement,newRdv.heure,newRdv.date.jour,newRdv.date.mois,newRdv.date.annee);
            } else {
                fprintf(f2, "%d %s %s %s %s %s \n", rendezvous.ID, rendezvous.Etablissement,rendezvous.heure,rendezvous.date.jour,rendezvous.date.mois,rendezvous.date.annee);
            }

  
    }

    fclose(f1);
    fclose(f2);
    remove("RDV.txt");
    rename("newFile.txt", "RDV.txt");
}}



int SupprimerRDV(int ID) {
    int found = 0;
    FILE *f = fopen("RDV.txt", "r");
    FILE *f3 = fopen("newFile.txt", "w");

    if (f != NULL && f3 != NULL) {
        while (fscanf(f, "%d %s %s %s %s %s \n", &rendezvous.ID, rendezvous.Etablissement,rendezvous.heure,rendezvous.date.jour,rendezvous.date.mois,rendezvous.date.annee) != EOF) {
            if (rendezvous.ID == ID) {
                found = 1;}
             else if (rendezvous.ID != ID)  {
                fprintf(f3, "%d %s %s %s %s %s \n", rendezvous.ID, rendezvous.Etablissement,rendezvous.heure,rendezvous.date.jour,rendezvous.date.mois,rendezvous.date.annee);
            }
           
        }
    }

    fclose(f);
    fclose(f3);
    remove("RDV.txt");
    rename("newFile.txt", "RDV.txt");

    return found;
}

void Chercher_user_by_etablissement(const char *etablissement) {
    RDV rendezvous;
    FILE *f1 = fopen("RDV.txt", "r");
    FILE *f2 = fopen("cherche.txt", "w");

    if (f1 != NULL && f2 != NULL) {
        while (fscanf(f1, "%d %s %s %s %s %s\n", &rendezvous.ID, rendezvous.Etablissement,
                      rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee) != EOF) {
            if (strcmp(rendezvous.Etablissement, etablissement) == 0) {
                fprintf(f2, "%d %s %s %s %s %s\n", rendezvous.ID, rendezvous.Etablissement,
                        rendezvous.heure, rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee);
            }
        }
        fclose(f1);
        fclose(f2);
    }
}




































