#include "fonction.h"

enum {
    CIN,
    NOM,
    PRENOM,
    ETS,
    TYPE_SANG,
    SEXE,
    JOUR,
    MOIS,
    ANNEE,
    COLUMNS,
};


//ajout 
int ajouter_emna(donneur D) {
    FILE *f = fopen("donneurs.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %d %s %d %d %d\n", D.cin, D.nom, D.prenom, D.sexe, D.ets, D.type_sang,D.d.jour,D.d.mois,D.d.annee);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}



void afficher_donneur(GtkTreeView *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	GtkTreeIter iter;

	GtkListStore *store;

	int cin;
	char nom[20];
	char prenom[20];	
	char sexe[20];
	int ets ;
        char type_sang[20];
        date_emna d ;
FILE *f;

	store=NULL;
	store=gtk_tree_view_get_model(liste);
if(store==NULL){

//cin
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("cin",renderer, "text",CIN, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//nom
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("nom",renderer, "text",NOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//prenom
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("prenom",renderer, "text",PRENOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//ETS
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("ets",renderer, "text",ETS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//type_de_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("type de sang",renderer, "text",TYPE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);


//sexe
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("sexe",renderer, "text",SEXE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//date_emna  
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("jour",renderer, "text",JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("mois",renderer, "text",MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("annee",renderer, "text",ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);


      store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);

        f = fopen("donneurs.txt", "r");
 
        if (f == NULL) {
g_print("errorr") ;
        return;
    } else {
g_print("in file !") ;
        while (fscanf(f, "%d %s %s %s %d %s %d %d %d\n", &cin, nom , prenom, sexe, &ets, type_sang, &d.jour, &d.mois, &d.annee) == 9) {
            gtk_list_store_append(store, &iter);
	
            gtk_list_store_set(store, &iter,CIN, cin, NOM, nom,PRENOM ,prenom,ETS,ets,TYPE_SANG,type_sang,SEXE,sexe, JOUR, d.jour,MOIS, d.mois, ANNEE, d.annee, -1);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}
}





//suppression
void supprimer_donneur(int cin1) {
    FILE *f = fopen("donneurs.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        donneur D; // Declare a local variable to hold data read from the file

        while (fscanf(f, "%d %s %s %s %d %s %d %d %d\n", &D.cin, D.nom, D.prenom, D.sexe, &D.ets, D.type_sang,&D.d.jour,&D.d.mois,&D.d.annee) != EOF) {
            if (D.cin != cin1) {
                fprintf(f2, "%d %s %s %s %d %s %d %d %d\n", D.cin, D.nom, D.prenom, D.sexe, D.ets, D.type_sang,D.d.jour,D.d.mois,D.d.annee);
            }
        }
        fclose(f);
        fclose(f2);
        remove("donneurs.txt");
        rename("nouv.txt", "donneurs.txt");
    }
}








// vider_emna le tableau apres suppression

void vider_emna(GtkWidget *liste)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;

GtkTreeIter iter;

 GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
        int cin;
	char nom[20];
	char prenom[20];	
	char sexe[20];
	int ets ;
        char type_sang[20];
        date_emna d ;

FILE* f;
	if(store==NULL){
//cin
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("cin",renderer, "text",CIN, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//nom
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("nom",renderer, "text",NOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//prenom
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("prenom",renderer, "text",PRENOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

//ETS
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("ets",renderer, "text",ETS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);


//type_de_sang
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("type de sang",renderer, "text",TYPE_SANG, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

//sexe
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("sexe",renderer, "text",SEXE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//date_emna  jour 
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("jour",renderer, "text",JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//mois
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("mois",renderer, "text",MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//annee
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("annee",renderer, "text",ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);
//

    store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,G_TYPE_INT);

gtk_list_store_append(store, &iter);
 gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));


}

}

int modifier_emna(int cin, donneur nouv) {
    int find = 0;
    donneur D;
    FILE *f = fopen("donneurs.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %s %s %s %d %s %d %d %d\n", &D.cin, D.nom, D.prenom, D.sexe, &D.ets, D.type_sang,&D.d.jour,&D.d.mois,&D.d.annee) != EOF) {
            if (D.cin == cin) {
                fprintf(f2, "%d %s %s %s %d %s %d %d %d\n", nouv.cin, nouv.nom, nouv.prenom, nouv.sexe, nouv.ets, nouv.type_sang,nouv.d.jour,nouv.d.mois,nouv.d.annee);
                find = 1;
            } else {
                fprintf(f2, "%d %s %s %s %d %s %d %d %d\n", D.cin, D.nom, D.prenom, D.sexe, D.ets, D.type_sang,D.d.jour,D.d.mois,D.d.annee);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove("donneurs.txt");
    rename("nouv.txt", "donneurs.txt");
    return find;
}




//chercher
int Chercher_donneur(const char *nomFichier, int cin) {
    FILE *f = fopen(nomFichier, "r");
	donneur D ;
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %s %d %s %d %d %d\n", &D.cin, D.nom, D.prenom, D.sexe, &D.ets, D.type_sang,&D.d.jour,&D.d.mois,&D.d.annee) == 9) {
            if (D.cin == cin) {
                fclose(f);
                return 1;
            }
        }
        fclose(f);
    }

    return 0;
}






// remis des Bd d'apres son cin
donneur retrieve_donneur_data(int cin) {
        donneur D;
	int find = 0;
    FILE *f = fopen("donneurs.txt", "r");

    if (f != NULL) {
        while (fscanf(f, "%d %19s %19s %19s %d %19s %d %d %d\n", 
                      &D.cin, D.nom, D.prenom, D.sexe, &D.ets, D.type_sang,
                      &D.d.jour, &D.d.mois, &D.d.annee) != EOF) {
            if (D.cin == cin) {
                find =1;
                break;
            }
        }
        fclose(f);
    }

    if (find ==0) {
   	  donneur d1;
  	  d1.cin = -1;
    	  return d1;
	} else 
	  { 
	     return D;
	}
}


int listeRDV(char nomFichier[],int ets, int jour, int mois, int annee) {
    int nombreRDVS = 0;
    date_emna d;
    donneur D ;
    FILE *f = fopen("RDV.txt", "r");
    FILE *f1 = fopen("recherche.txt", "w"); 
    int ID ,EtablissementINT,jourINT,moisINT,anneeINT ;
    char Etablissement[30] , heure[30] ,jourstr[30] ,moisstr[30] ,  anneestr[30] ; 
    if ((f!= NULL)&&(f1!= NULL)){
      while (fscanf(f, "%d %s %s %s %s %s \n", &ID, Etablissement,heure, jourstr,moisstr, anneestr) != EOF){
		EtablissementINT = atoi(Etablissement)  ; 
		jourINT = atoi(jourstr) ;
		moisINT = atoi(moisstr) ;
		anneeINT = atoi(anneestr) ;
            if (ets==EtablissementINT && jour== jourINT && mois== moisINT && annee== anneeINT){
                nombreRDVS++;

               fprintf(f1,"%d %d %d %d\n",EtablissementINT,jourINT,moisINT,anneeINT);
               

		 }              

    }

    fclose(f);
    fclose(f1);
	return nombreRDVS ;
    }

    else{  
      return nombreRDVS;
     }
}




int nbETS(char nomFichier[]) {
    int ets ;
    int nombreETS = 0;
	donneur D  ;
    FILE *f = fopen("RDV.txt", "r");
    int ID ,EtablissementINT,jourINT,moisINT,anneeINT ;
    char Etablissement[30] , heure[30] ,jourstr[30] ,moisstr[30] ,  anneestr[30] ; 
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %s %s %s \n", &ID, Etablissement,heure, jourstr,moisstr, anneestr) != EOF) {
           
		nombreETS++;
    }
}
    fclose(f);
    return nombreETS ;
    
    }




float moyRDV_ETS(char nomFichier[], int jour, int mois, int annee) {
    
    float moy ;
    float nb=0; 
    donneur D ;
    date_emna d ;

    int ID ,EtablissementINT,jourINT,moisINT,anneeINT ;
    char Etablissement[30] , heure[30] ,jourstr[30] ,moisstr[30] ,  anneestr[30] ; 

    FILE *f = fopen("RDV.txt", "r");

    if (f!= NULL) {
        
      while (fscanf(f, "%d %s %s %s %s %s \n", &ID, Etablissement,heure, jourstr,moisstr, anneestr) != EOF) {
		jourINT = atoi(jourstr) ;
		moisINT = atoi(moisstr) ;
		anneeINT = atoi(anneestr) ;
       if ((jour==jourINT)&&(mois==moisINT)&&(annee== anneeINT )){
          nb++;
           }

       }
    }
	g_print("%d" , nbETS("RDV.txt") ) ;
	moy = (nb/nbETS("RDV.txt")) * 100 ;
    fclose(f);

     return moy ;

    }





