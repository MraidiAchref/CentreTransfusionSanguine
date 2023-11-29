#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "utilisateur.h"



char *Sexe(int choice[])
{
    if (choice[0] == 1 && choice[1] == 0)
    {
        return "Homme";
    }
    if (choice[0] == 0 && choice[1] == 1)
    {
        return "Femme";
    }
    return "Undefined";
}

char *Role(int choice[])
{
    if (choice[0] == 1)
    {
        return "Infirmier";
    }
    if (choice[1] == 1)
    {
        return "Medecin Biologiste";
    }
    if (choice[2] == 1)
    {
        return "Responsable ETS";
    }
    return "Undefined";
}


Date get_date_from_entry(GtkEntry *entry)
{
    Date date;
    const char *date_str = gtk_entry_get_text(GTK_ENTRY(entry));

    sscanf(date_str, "%02d-%02d-%d", &date.day, &date.month, &date.year);

    return date;
}


void ajouter(Utilisateur U)
{

    FILE *f = fopen("Utilisateur.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n", U.ID, U.Nom, U.Prenom, U.Sexe, U.Role, U.D.day, U.D.month, U.D.year, U.Password);
        fclose(f);
    }
}

void afficher_utilisateur(GtkWidget *liste, char nomFichier[] )
{
    Date D;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char nom[30];
    char prenom[30];
    char Date[30];
    char sexe[30];
    char role[30];
    char ID[30];
    char password[30];
    store = NULL;

    FILE *f;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL)
    {
	store = gtk_list_store_new(COLUMNS,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" ID", renderer, "text", IDENTIFIANT, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(IDENTIFIANT));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" nom", renderer, "text", NOM, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(NOM));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" prenom", renderer, "text", PRENOM, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(PRENOM));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" sexe", renderer, "text", SEXE, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(SEXE));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" role", renderer, "text", ROLE, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(ROLE));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Date de naissance", renderer, "text", DATE, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(DATE));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	g_object_set(renderer, "mode", GTK_CELL_RENDERER_MODE_EDITABLE, NULL);
	column = gtk_tree_view_column_new_with_attributes(" Mot de passe", renderer, "text", PASSWORD, NULL);
	g_object_set(renderer, "editable", TRUE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(PASSWORD));
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), liste);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	

	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	

        f = fopen(nomFichier, "r");

        if (f == NULL)
        {
            return;
        }
        else
        {
            while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n", ID, nom, prenom, sexe, role, &D.day, &D.month, &D.year, password ) != EOF)
            {
                g_snprintf(Date, sizeof(Date), "%02d-%02d-%04d", D.day, D.month, D.year);

                gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter,  IDENTIFIANT, ID, NOM, nom, PRENOM, prenom, SEXE, sexe, ROLE, role, DATE, Date, PASSWORD, password, -1);

            }
            fclose(f);
            gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
            g_object_unref(store);
        }
    }
}


Utilisateur verifier(char id[]) {
    FILE* f = fopen("Utilisateur.txt", "r");

    if (f == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        Utilisateur defaultUser;
        strcpy(defaultUser.ID, "-1");
        return defaultUser;
    }

    Utilisateur savedUser;
    int find = 0;

    while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",
                  savedUser.ID, savedUser.Nom, savedUser.Prenom, savedUser.Sexe, savedUser.Role,
                  &savedUser.D.day, &savedUser.D.month, &savedUser.D.year, savedUser.Password) != EOF) {
        if (strcmp(id, savedUser.ID) == 0) {
            find = 1;
            break;
        }
    }

    fclose(f);

    if (find == 0) {
        Utilisateur defaultUser;
        strcpy(defaultUser.ID, "-1");
        return defaultUser;
    } else {
        return savedUser;
    }
}

int supprimer_utilisateur( char id[]) {
    int find = 0;
    Utilisateur U;
    FILE *f = fopen("Utilisateur.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n", U.ID, U.Nom, U.Prenom, U.Sexe, U.Role, &U.D.day, &U.D.month, &U.D.year, U.Password) != EOF) {
            if (strcmp(U.ID, id) == 0)
                find = 1;
            else {
                fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n", U.ID, U.Nom, U.Prenom, U.Sexe, U.Role, U.D.day, U.D.month, U.D.year, U.Password);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove("Utilisateur.txt");
    rename("nouv.txt", "Utilisateur.txt");
    return find;
}


int modifier(char id[], Utilisateur nouv) {
    int find = 0;
    Utilisateur U;
    FILE *f = fopen("Utilisateur.txt", "r+");
	if (ferror(f)) {
    perror("Error reading from file");
	}
    FILE *f2 = fopen("nouv.txt", "w");
	if (f2 == NULL) {
    perror("Error opening new file");
	}
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n", U.ID, U.Nom, U.Prenom, U.Sexe, U.Role, &U.D.day, &U.D.month, &U.D.year, U.Password) != EOF) {
            if (strcmp(U.ID,id)==0) {
                fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n", nouv.ID, nouv.Nom, nouv.Prenom, nouv.Sexe, nouv.Role, nouv.D.day, nouv.D.month, nouv.D.year, nouv.Password);
                find = 1;
            } else {
                fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n", U.ID, U.Nom, U.Prenom, U.Sexe, U.Role, U.D.day, U.D.month, U.D.year, U.Password);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove("Utilisateur.txt");
    rename("nouv.txt", "Utilisateur.txt");
    return find;
}


void UserRole(char nomFichier[], char role[]) {
    FILE *f = fopen(nomFichier, "r");
    FILE *f2 = fopen("Role_users.txt", "w");

    if (f == NULL || f2 == NULL) {
        perror("Error opening file");
        return;
    }
	
    Utilisateur user;

    while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",
                  user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, &user.D.day, &user.D.month, &user.D.year, user.Password) != EOF) {

        if (strcmp(role, user.Role) == 0) {
            fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n",
                    user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, user.D.day, user.D.month, user.D.year, user.Password);
        }
    }

    fclose(f);
    fclose(f2);
}



void pourcentageUser(char nomFichier[], int *nbHomme, int *nbFemme) {
    FILE *f = fopen(nomFichier, "r");

    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    *nbHomme = 0;
    *nbFemme = 0;

    Utilisateur user;

    while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",
                  user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, &user.D.day, &user.D.month, &user.D.year, user.Password) != EOF) {
        if (strcmp(user.Sexe, "Homme") == 0) {
            (*nbHomme)++;
        } else if (strcmp(user.Sexe, "Femme") == 0) {
            (*nbFemme)++;
        }
    }

    fclose(f);
}

void vider(GtkWidget *liste) {
    char nom[30];
    char prenom[30];
    char Date[30];
    char sexe[30];
    char role[30];
    char ID[30];
    char password[30];
    GtkListStore *store;
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

   
       if (store != NULL) {
    		gtk_list_store_clear(store);
	}

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, IDENTIFIANT, ID, NOM, nom, PRENOM, prenom, SEXE, sexe, ROLE, role, DATE, Date, PASSWORD, password, -1);
}

void UserFilter(char nomFichier[], char role[], char sex[]) {
    FILE *f = fopen(nomFichier, "r");
    FILE *f2 = fopen("filtered_users.txt", "w");

    if (f == NULL || f2 == NULL) {
        perror("Error opening file");
        return;
    }

    Utilisateur user;

    while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",
                  user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, &user.D.day, &user.D.month, &user.D.year, user.Password) != EOF) {

        if (strcmp(role, user.Role) == 0 && strcmp(sex, user.Sexe) == 0) {
            fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n",
                    user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, user.D.day, user.D.month, user.D.year, user.Password);
        }
    }

    fclose(f);
    fclose(f2);
}
void UserSexe(char nomFichier[], char sexe[]) {

    FILE *f = fopen(nomFichier, "r");

    FILE *f2 = fopen("Sexe_users.txt", "w");

    if (f == NULL || f2 == NULL) {

        perror("Error opening file");

        return;

    }

    Utilisateur user;

    while (fscanf(f, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",

                  user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, &user.D.day, &user.D.month, &user.D.year, user.Password) != EOF) {

        if (strcmp(sexe, user.Sexe) == 0) {

            fprintf(f2, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n",

                    user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, user.D.day, user.D.month, user.D.year, user.Password);
        }
    }

    fclose(f);

    fclose(f2);
}

int is_ID_exists(const char *ID) {
    FILE *f = fopen("Utilisateur.txt", "r");
    if (f != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), f) != NULL) {
            char stored_ID[20];
            if (sscanf(line, "%19[^,],", stored_ID) == 1) {
                if (strcmp(ID, stored_ID) == 0) {
                    fclose(f);
                    return 1; 
                }
            }
        }
        fclose(f);
    }
	return 0;
}



void search_character(const char nomFichier[], const char *searchTerm) {
    FILE *inputFile = fopen(nomFichier, "r");
    FILE *outputFile = fopen("searchedUsers.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening file");
        return;
    }

    Utilisateur user;

    while (fscanf(inputFile, "%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",
                  user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, &user.D.day, &user.D.month, &user.D.year,
                  user.Password) != EOF) {

        char dateStr[20];
        snprintf(dateStr, sizeof(dateStr), "%d-%d-%d", user.D.day, user.D.month, user.D.year);

        if (strstr(user.ID, searchTerm) || strstr(user.Nom, searchTerm) || strstr(user.Prenom, searchTerm) ||
            strstr(user.Sexe, searchTerm) || strstr(user.Role, searchTerm) || strstr(user.Password, searchTerm) ||
            strstr(dateStr, searchTerm)) {
            fprintf(outputFile, "%s, %s, %s, %s, %s, %d-%d-%d, %s,\n",
                    user.ID, user.Nom, user.Prenom, user.Sexe, user.Role, user.D.day, user.D.month, user.D.year,
                    user.Password);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}






















