#include "fonctions.h"

enum {
    EID_DU_DON,
    EID_DONNEUR,
    ETYPE_DE_SANG,
    EID_ETS,
    EQUANTITE_SANG,
    EDATE_JOUR,
    EDATE_MOIS,
    EDATE_ANNEE,
    COLUMNS,
};

// ajouter_yas un don 
void ajouter_yas(don d) {
    FILE *file = fopen("don.txt", "r");
    if (file != NULL) {
        don temp;
        int unique = 0;
        while (fscanf(file, "%d %*d", &temp.id_du_don) != EOF) {
            if (temp.id_du_don == d.id_du_don) {
                unique = 1; // ID already exists
                break;
            }
        }
        fclose(file);

        if (unique != 0) {
            printf("ID already exists. Cannot add the record.\n");
            return;
        }
    }

    FILE *f = fopen("don.txt", "a+");
    if (f != NULL) {
        fprintf(f, "%d %d %s %d %d %d %d %d\n", d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
        fclose(f);
    }
}


//afficher un don 
void afficher_don(GtkWidget *liste,char nomFichier[]){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	GtkTreeIter iter;

	GtkListStore *store;

	int id_du_don;
	int id_donneur;
	char type_de_sang[100];
	int id_ETS;
	int quantite_sang;
	date_du_don date;
don d ;
FILE *f;

	GtkTreeModel *store_model = NULL;
	store_model = gtk_tree_view_get_model(liste);
if(store_model==NULL){

//id_du_don
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id du don",renderer, "text",EID_DU_DON, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//id_donneur
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id du donneur",renderer, "text",EID_DONNEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

//type_de_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("type de sang",renderer, "text",ETYPE_DE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//id_ETS
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id ETS",renderer, "text",EID_ETS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//quantite_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("quantite sang",renderer, "text",EQUANTITE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//date  
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("jour",renderer, "text",EDATE_JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("mois",renderer, "text",EDATE_MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("annee",renderer, "text",EDATE_ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

}


      store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,G_TYPE_INT);

    f = fopen(nomFichier, "r");
    if (f == NULL) {
        return;
    } else {
GHashTable *hash_table = g_hash_table_new(g_direct_hash, g_direct_equal);

	       while (fscanf(f, "%d %d %99s %d %d %d %d %d\n", &id_du_don, &id_donneur, type_de_sang, &id_ETS, &quantite_sang, &date.jour, &date.mois, &date.annee) == 8) {
		// Check if the id_du_don already exists in the hash table
		       	 if (!g_hash_table_contains(hash_table, GINT_TO_POINTER(id_du_don))) {
			    // If it doesn't exist, add it to the hash table and the GtkListStore
			    g_hash_table_insert(hash_table, GINT_TO_POINTER(id_du_don), GINT_TO_POINTER(id_du_don));

			    gtk_list_store_append(store, &iter);
			    gtk_list_store_set(store, &iter,
				               EID_DU_DON, id_du_don, EID_DONNEUR, id_donneur,
				               ETYPE_DE_SANG, type_de_sang, EID_ETS, id_ETS,
				               EQUANTITE_SANG, quantite_sang, EDATE_JOUR, date.jour,
				               EDATE_MOIS, date.mois, EDATE_ANNEE, date.annee, -1);
		      	  }
	    	}

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);

    // Destroy the hash table when done
    g_hash_table_destroy(hash_table);
	}

}


//supprimer
void supprimer_don(id_to_delete) {
// in callbacks
}

//modifier_yas 
int modifier_yas(int id_modifier, don nouveau) {
    int tr = 0;
    don d;

    FILE *f = fopen("don.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {
            if (d.id_du_don == id_modifier) {
                // Copy all values from nouveau except id_du_don
                fprintf(f2, "%d %d %s %d %d %d %d %d\n", d.id_du_don, nouveau.id_donneur,  nouveau.type_de_sang, nouveau.id_ETS, nouveau.quantite_sang, nouveau.date.jour, nouveau.date.mois, nouveau.date.annee);
                tr = 1;
            } else {
                // Copy unchanged data
                fprintf(f2, "%d %d %s %d %d %d %d %d\n",d.id_du_don, d.id_donneur,  d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove("don.txt");
    rename("nouv.txt", "don.txt");
    return tr;
}

// Function to retrieve data for a specific ID
don retrieve_don_data(int id_du_don) {
    don d;
    FILE *f = fopen("don.txt", "r");

    if (f != NULL) {
        while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {
            if (d.id_du_don == id_du_don ) {
                fclose(f);
                return d;
            }
        }
        fclose(f);
    }

    // If ID is not found or an error occurs
    d.id_du_don = -1; 
    return d;
}


// vider_yas tree view 

void vider_yas(GtkWidget *liste)
{

    GtkListStore *store;
 
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

   
       if (store != NULL) {
    		gtk_list_store_clear(store);
	}

 }
	

// quantity by type
int quantite_type( char type_sang[]){
	don d;
    	int totalQuantite = 0;
      FILE *f = fopen("don.txt", "r");

 if (f != NULL)
    {
             while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {
          
		if (strcmp(d.type_de_sang, type_sang) == 0){
        	    totalQuantite += d.quantite_sang;

        	}
        }
    }
    fclose(f);
     if (totalQuantite > 0) {
        return totalQuantite;
    } else {
        return -1; // bloood not found
    }
}

// sang rare 
void sang_rare(char *sangRare) {
    don d;
    int minQuantity = -1;
    int currentQuantity;
    char currentType[50]; // To store each blood type from the file

    sangRare[0] = '\0';
    FILE *f = fopen("don.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  currentType, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {
            currentQuantity = quantite_type(currentType);

            if (currentQuantity != -1 && (minQuantity == -1 || currentQuantity < minQuantity)) {
                minQuantity = currentQuantity;
                strcpy(sangRare, currentType);
            }
        }
        fclose(f);
    }
}

////////////////////////////
int isNumber(const char* str, int length) {
    // Check if string contains only digits and has the desired length
    if (strlen(str) == length) {
        for (int i = 0; i < length; ++i) {
            if (!isdigit(str[i])) {
                return 0; // Not a number
            }
        }
        return 1; // Is a number and has the desired length
    }
    return 0; // Not the desired length
}




//////////////////////////////

enum {
    E_BLOOD_TYPE = 0,
    E_QUANTITY,
    COLUMNS_2
};




 void vider_blood_quantities(GtkWidget *liste) {
  
    char bloodTypes[30];
    int quantity;
    GtkListStore *store;
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

   
       if (store != NULL) {
    		gtk_list_store_clear(store);
	}

   
}

//////////////:

   void blood_quantities_in_treeview(GtkTreeView *liste, int sortOrder) {
    

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	GtkTreeIter iter;

	GtkListStore *store;

 	GtkTreeModel *store_model = NULL;
	store_model = gtk_tree_view_get_model(liste);
if(store_model == NULL){

        // Create a new list store
        store = gtk_list_store_new(COLUMNS_2, G_TYPE_STRING, G_TYPE_INT);

        // Type de sang column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type de sang", renderer, "text", E_BLOOD_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // Quantité disponible column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Quantité disponible", renderer, "text", E_QUANTITY, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // Fetch blood types and quantities and add them to the list store
        char bloodTypes[50][50]; 
        int numBloodTypes = 0;

        // Create a hashtable (avoid repetition)
        GHashTable *addedBloodTypes = g_hash_table_new(g_str_hash, g_str_equal);

        FILE *f = fopen("don.txt", "r");
        if (f != NULL) {
            while (fscanf(f, "%*d %*d %49s %*d %*d %*d %*d %*d\n", bloodTypes[numBloodTypes]) == 1) {
                int quantity = quantite_type(bloodTypes[numBloodTypes]);
                if (quantity != -1) {
   printf("blood type: %s with quantity: %d\n", bloodTypes[numBloodTypes], quantity);
                    // Check if blood type is already added, if not, add it to the store
                    if (!g_hash_table_contains(addedBloodTypes, bloodTypes[numBloodTypes])) {
                        printf("blood type: %s with quantity: %d\n", bloodTypes[numBloodTypes], quantity);
                      
  gtk_list_store_append(store, &iter);
                        gtk_list_store_set(store, &iter, E_BLOOD_TYPE, bloodTypes[numBloodTypes], E_QUANTITY, quantity, -1);

                        // Add blood type to the set to mark it as added
                        g_hash_table_add(addedBloodTypes, g_strdup(bloodTypes[numBloodTypes]));
                    }
                    numBloodTypes++;
                }
            }
            fclose(f);
            g_hash_table_destroy(addedBloodTypes);

            // Sort the data based on the quantity column
            GtkTreeSortable *sortable = GTK_TREE_SORTABLE(store);
            if (sortOrder == 1) {
                gtk_tree_sortable_set_sort_column_id(sortable, E_QUANTITY, GTK_SORT_ASCENDING);
            } else {
                gtk_tree_sortable_set_sort_column_id(sortable, E_QUANTITY, GTK_SORT_DESCENDING);
            }

            // Set the model to the treeview
            gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
            g_object_unref(store);
        } else {
            printf("Error opening file\n");
        }
    }
}


//////////////////// filter home 

void ETSFilter(char nomFichier[], int id_ets) {
    FILE *f = fopen(nomFichier, "r");
    FILE *f2 = fopen("filtered_ETS.txt", "w");

    if (f == NULL || f2 == NULL) {
        perror("Error opening file filtered ets");
        return;
    }

    don d;
  while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {

        if ( id_ets == d.id_ETS ) {
            fprintf(f2, "%d %d %s %d %d %d %d %d\n", d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
        }
    }

    fclose(f);
    fclose(f2);
}


void BLOODFilter(char nomFichier[], char blood[]) {
    FILE *f = fopen(nomFichier, "r");
    FILE *f2 = fopen("filtered_blood.txt", "w");

    if (f == NULL || f2 == NULL) {
        perror("Error opening file filter blood");
        return;
    }

    don d;
  while (fscanf(f,"%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {

        if ( strcmp(blood, d.type_de_sang) == 0  ) {
            fprintf(f2,"%d %d %s %d %d %d %d %d\n", d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);


        }
    }

    fclose(f);
    fclose(f2);
}

void bothFilter(char nomFichier[], int id_ets, char blood[]) {
    FILE *f = fopen(nomFichier, "r");
    FILE *f4 = fopen("filtered.txt", "w");
don d;
    if (f == NULL || f4 == NULL) {
        perror("Error opening file both filter");
        return;
    }

  while (fscanf(f, "%d %d %s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {

        if (id_ets== d.id_ETS && strcmp(blood, d.type_de_sang) == 0 ) {
           fprintf(f4,"%d %d %s %d %d %d %d %d\n", d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
        }
    }

    fclose(f);
    fclose(f4);
}




void afficher_don_ets(GtkTreeView *liste, int ets_to_search) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store = NULL;

    FILE *f;
    don d;

    GtkTreeModel *store_model = gtk_tree_view_get_model(liste);
    if (store_model == NULL) {

//id_du_don
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id du don",renderer, "text",EID_DU_DON, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//id_donneur
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id du donneur",renderer, "text",EID_DONNEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

//type_de_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("type de sang",renderer, "text",ETYPE_DE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//id_ETS
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("id ETS",renderer, "text",EID_ETS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//quantite_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("quantite sang",renderer, "text",EQUANTITE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//date  
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("jour",renderer, "text",EDATE_JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("mois",renderer, "text",EDATE_MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("annee",renderer, "text",EDATE_ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

}
      store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,G_TYPE_INT);


  f = fopen("don.txt", "r");
    if (f == NULL) {
        return;
    } else {
        while (fscanf(f, "%d %d %99s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur, d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) == 8) {
            if (d.id_ETS == ets_to_search) {
                if (store == NULL) {
                    store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
                }

                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, EID_DU_DON, d.id_du_don, EID_DONNEUR, d.id_donneur,
                                   ETYPE_DE_SANG, d.type_de_sang, EID_ETS, d.id_ETS,
                                   EQUANTITE_SANG, d.quantite_sang, EDATE_JOUR, d.date.jour,
                                   EDATE_MOIS, d.date.mois, EDATE_ANNEE, d.date.annee, -1);
            }
        }
        fclose(f);

        if (store != NULL) {
            gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
            g_object_unref(store);
        }
    }
}
// search bar : 
void search_yass(const char nomFichier[], const char *searchTerm) {
    FILE *inputFile = fopen(nomFichier, "r");
    FILE *outputFile = fopen("searchedDon.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening file");
        return;
    }

    don d;

    char searchTermLower[30];
    strcpy(searchTermLower, searchTerm);
    for (int i = 0; searchTermLower[i]; i++) {
        searchTermLower[i] = tolower(searchTermLower[i]);
    }

    while (fscanf(inputFile, "%d %d %99s %d %d %d %d %d\n", &d.id_du_don, &d.id_donneur, d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {

        char dateStr[20];
        snprintf(dateStr, sizeof(dateStr), "%d-%d-%d", d.date.jour, d.date.mois, d.date.annee);

        char id[20], donneur[20], ets[20], qte[20];
        snprintf(id, sizeof(id), "%d", d.id_du_don);
        snprintf(donneur, sizeof(donneur), "%d", d.id_donneur);
        snprintf(ets, sizeof(ets), "%d", d.id_ETS);
        snprintf(qte, sizeof(qte), "%d", d.quantite_sang);

        char userFieldsLower[300];
        strcpy(userFieldsLower, d.type_de_sang);
        strcat(userFieldsLower, id);
        strcat(userFieldsLower, donneur);
        strcat(userFieldsLower, ets);
        strcat(userFieldsLower, qte);
        strcat(userFieldsLower, dateStr);

        for (int i = 0; userFieldsLower[i]; i++) {
            userFieldsLower[i] = tolower(userFieldsLower[i]);
        }

        if (strstr(userFieldsLower, searchTermLower) != NULL || strstr(dateStr, searchTermLower) != NULL) {
            fprintf(outputFile, "%d %d %s %d %d %d %d %d\n", d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

