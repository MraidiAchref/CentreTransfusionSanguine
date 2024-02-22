#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ets.h"
#include <ctype.h>
#include <gdk/gdk.h>



//add ets 

int verifierTypeUtilisateur (char login[], char password[]) {
	FILE* f ;
	char ID[30],Nom[30],Prenom[30],Sexe[30],Role[30],Password[30];
	int day,month, year,Role_int ;

	f=fopen("Utilisateur.txt","r") ; 
	if(f!=NULL) {
		while (fscanf(f,"%29[^,], %29[^,], %29[^,], %29[^,], %29[^,], %d-%d-%d, %29[^,],\n",ID,Nom,Prenom,Sexe,Role,&day,&month, &year,Password) != EOF) {			if ( strcmp(Role , "Responsable ETS" ) == 0){
				Role_int = 0 ;
			}else if ( strcmp(Role , "Infirmier" ) == 0){
				Role_int = 1 ;
			}else if ( strcmp(Role , "Medecin Biologiste" ) == 0){
				Role_int = 2 ;
			}else {
				Role_int = -1 ;
			}		
			
			if( ( strcmp(ID , login ) == 0 ) && ( strcmp(Password, password ) == 0 ) ) {
				fclose(f) ; 
				return Role_int ;
	
			}

		}
		fclose(f) ;
		return -1 ;
		
	}	



}

void add_ets(ETS entablissemet) {
	FILE *f;
	f=fopen("ets.txt","a+");
	if(f!=NULL){
		fprintf(f,"%d, %s, %s, %s, %d \n",entablissemet.ID ,entablissemet.Nom ,entablissemet.Adresse , entablissemet.Region , entablissemet.Capacite );
		fclose(f);
	}
}

void display_ets(GtkTreeView  *liste , char nomFIchier[]){
	GtkCellRenderer *renderer ; //cell displayer 
	GtkTreeViewColumn *column ; 	// columns visualisation 
	GtkTreeIter iter;  //iterateur
	GtkListStore *store ; // creation of a model with type list 
	int id;
	char nom [30] ;
	char adresse[30];
	char region[30];
	int capacite ;
	store=NULL ; 

	FILE *f ; 
	store=GTK_LIST_STORE(gtk_tree_view_get_model(liste) ) ;
	if (store==NULL){
		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" ID",renderer,"text",ID,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		//g_object_set(renderer, "editable", TRUE, NULL);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(ID));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);	

		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Nom",renderer,"text",Nom,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set(renderer, "editable", TRUE, NULL);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(Nom));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Adresse",renderer,"text",Adresse,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set(renderer, "editable", TRUE, NULL);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(Adresse));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Region",renderer,"text",Region,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set(renderer, "editable", TRUE, NULL);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(Region));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Capacite",renderer,"text",Capacite,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set(renderer, "editable", TRUE, NULL);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(Capacite));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);


		store=gtk_list_store_new (COLUMN, G_TYPE_INT, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT ) ;

		f= fopen(nomFIchier,"r");
		
		if(f==NULL) {
			return ;	
		}else {
			
			while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&id,nom,adresse,region,&capacite )== 5 ) {
				gtk_list_store_append(store,&iter);
				gtk_list_store_set(store,&iter,ID,id,Nom,nom,Adresse,adresse,Region,region,Capacite,capacite,-1);
				if (feof(f) ) break ;
			}
			fclose(f) ;
			gtk_tree_view_set_model(GTK_TREE_VIEW(liste) , GTK_TREE_MODEL(store)) ;
			//g_object_unref(store);
	
		}

		
	}


}


void delete_ets(ETS etablissement) {

	int ID;
	char Nom [30] ;
	char Adresse[30];
	char Region[30];
	int Capacite ;
	
	FILE *f,*g ;
	f=fopen("ets.txt", "r");
	g= fopen("dump.txt", "w");

	if(f == NULL || g== NULL ) {
		return;
	}else{
		while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
			if ( etablissement.ID != ID || strcmp(etablissement.Nom,Nom) != 0 || strcmp(etablissement.Adresse,Adresse) != 0 || strcmp(etablissement.Region,Region) != 0 || 	etablissement.Capacite != Capacite ) {
				fprintf(g,"%d, %s, %s, %s, %d \n",ID,Nom,Adresse,Region,Capacite )	;			
			}
		}
		fclose(f);
		fclose(g);
		remove("ets.txt");
		rename("dump.txt","ets.txt") ; 
		
	}


}

// empty the tree view
void viderETS(GtkTreeView *list) {

	GtkListStore *store ; // creation of a model with type list 
	int id;
	char nom [30] ;
	char adresse[30];
	char region[30];
	int capacite ;


	
	store=GTK_LIST_STORE(gtk_tree_view_get_model(list) ) ;
	if(store != NULL) {
		
		gtk_list_store_clear(store);
			
		
	}
		GtkTreeIter iter ;
		
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,ID,id,Nom,nom,Adresse,adresse,Region,region,Capacite,capacite,-1);

}


void ETSTrieCapaciteCroiss(char nomFichier[]){
	FILE * f1 =fopen(nomFichier , "r");
	FILE * f2 =fopen("trieParCapacite.txt" , "w");	
	ETS newEts ;
	int capaciteMax =0 ,i ;
	
	if (f1 != NULL  ) {
        	while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
		   	if (newEts.Capacite> capaciteMax) {
		       		capaciteMax = newEts.Capacite ; 
		    	if (feof(f1)) {break ;}
		    	}
        	}
    	}
	if (f1 != NULL  ) {
		
		for (i=0 ; i<capaciteMax+1 ; i++) {
			rewind(f1);
			while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
			   	if (newEts.Capacite == i) {
				fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
			    	if (feof(f1)) {break ;}
			    	}
			}
		}
    	}
        fclose(f1);
        fclose(f2);
	remove(nomFichier);
	rename("trieParCapacite.txt",nomFichier) ; 
	
		
}



void ETSTrieCapaciteDecroiss(char nomFichier[]){
	FILE * f1 =fopen(nomFichier , "r");
	FILE * f2 =fopen("trieParCapacite.txt" , "w");	
	ETS newEts ;
	int capaciteMax =0 ,i ;
	
	if (f1 != NULL  ) {
        	while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
		   	if (newEts.Capacite> capaciteMax) {
		       		capaciteMax = newEts.Capacite ; 
		    	if (feof(f1)) {break ;}
		    	}
        	}
    	}
	if (f1 != NULL  ) {
		
		for (i=capaciteMax ; i>-1 ; i--) {
			rewind(f1);
			while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
			   	if (newEts.Capacite == i) {
				fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
			    	if (feof(f1)) {break ;}
			    	}
			}
		}
    	}
        fclose(f1);
        fclose(f2);
	remove(nomFichier);
	rename("trieParCapacite.txt",nomFichier) ; 
	
		
}

int ETSParRegion(char nomFichier[], char reg[]){
	int nbre = 0 ;
	FILE * f1 =fopen(nomFichier , "r");
	FILE * f2 =fopen("filtreParRegion.txt" , "w");
    	ETS newEts ;
    	if (f1 != NULL  ) {
        	while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n" , &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
		   	if (strcmp(newEts.Region,reg) == 0 ) {
		       		nbre++;
				fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
		    	if (feof(f1)) {break ;}
		    	}
        	}
    	}
    fclose(f1);
    fclose(f2);

    return nbre ;

}

ETS ChercherEts (char * nomFichier,  int ID  ) {

    int found = 0 ;
    FILE * f1 =fopen(nomFichier , "r");
    ETS newEts ;
    if (f1 != NULL  ) {
        while( fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite) == 5 )  {

            if (newEts.ID == ID ) {
                found = 1 ;
		break ;

            
            }
	if (feof(f1)) {break ;}
        }
    }
    fclose(f1);
	if (found == 1 ) {
		return newEts ;	
	}else {
		newEts.ID=-1 ;	
		return newEts;
	}

    }

int ModifierEts (char * nomFichier, ETS ets , int ID  ) {

    int found = 0 ;
    FILE * f1 =fopen(nomFichier , "r");
    FILE * f2 = fopen("newFile.txt", "w") ;
    ETS newEts ;
    if (f1 != NULL && f2 != NULL ) {
        while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
            if (newEts.ID == ID ) {
                fprintf(f2,"%d, %s, %s, %s, %d \n",ets.ID ,ets.Nom ,ets.Adresse,ets.Region ,ets.Capacite) ;
                found = 1 ;
            }else {
                fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );

            }
            if (feof(f1)) {break ;}
        }
    }
    fclose(f1);
    fclose(f2);
    remove(nomFichier);
    rename("newFile.txt",nomFichier);
    return found ;

}

int SupprimerEts (int ID  ) {

    int found = 0 ;
    FILE * f = fopen("ets.txt" ,"r");
    FILE * f3 = fopen("newFile.txt","w") ;
    ETS newEts ;
    if (f != NULL && f3 != NULL ) {
        while( (fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
            if (newEts.ID == ID ) {
                found = 1 ;
            }else {
                fprintf(f3,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );

            }
            if (feof(f)) {break ;}
        }
    }
    fclose(f);
    fclose(f3);
    remove("ets.txt");
    rename("newFile.txt","ets.txt");

    return found ;

}


void ETSTrieIDCroiss(char nomFichier[]){
	FILE * f1 =fopen(nomFichier , "r");
	FILE * f2 =fopen("trieParCapacite.txt" , "w");	
	ETS newEts ;
	int IDMax =0 ,i ;
	
	if (f1 != NULL  ) {
        	while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
		   	if (newEts.ID> IDMax) {
		       		IDMax = newEts.ID ; 
		    	if (feof(f1)) {break ;}
		    	}
        	}
    	}
	if (f1 != NULL  ) {
		
		for (i=0 ; i<IDMax+1 ; i++) {
			rewind(f1);
			while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
			   	if (newEts.ID == i) {
				fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
			    	if (feof(f1)) {break ;}
			    	}
			}
		}
    	}
        fclose(f1);
        fclose(f2);
	remove(nomFichier);
	rename("trieParCapacite.txt",nomFichier) ; 
	
		
}


void ETSTrieIDDecroiss(char nomFichier[]){
	FILE * f1 =fopen(nomFichier , "r");
	FILE * f2 =fopen("trieParCapacite.txt" , "w");	
	ETS newEts ;
	int IDMax =0 ,i ;
	
	if (f1 != NULL  ) {
        	while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
		   	if (newEts.ID> IDMax) {
		       		IDMax = newEts.ID ; 
		    	if (feof(f1)) {break ;}
		    	}
        	}
    	}
	if (f1 != NULL  ) {
		
		for (i=IDMax ; i>-1 ; i--) {
			rewind(f1);
			while( (fscanf(f1,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
			   	if (newEts.ID == i) {
				fprintf(f2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
			    	if (feof(f1)) {break ;}
			    	}
			}
		}
    	}
        fclose(f1);
        fclose(f2);
	remove(nomFichier);
	rename("trieParCapacite.txt",nomFichier) ; 
	
		
}

int generateID(const char *filename) {
	ETS newEts ;
	int c , FirstID;
	FILE *file = fopen(filename, "r");

	FILE *file2 = fopen("ets.txt", "r");

	 fseek(file2, 0, SEEK_END); // Move to the end of the file

    	if (ftell(file2) == 0) {
        // The file is empty
        
	fclose(file2);
        return 1;
	}else 
	{
	rewind(file2);	
	int result = fscanf(file2, "%d, %29[^,], %29[^,], %29[^,], %d \n", &FirstID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite ) ;
		fclose(file2) ;
		if (FirstID  == 1 ) {
			FirstID ++ ;
			
			while ((c = fgetc(file)) != EOF && c != '\n');   // this is how i can skip the first line 
			while (fscanf(file, "%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite ) == 5) {
				if (FirstID < newEts.ID ) {
					fclose(file);
			  		return FirstID  ;
				
				} else {
				    FirstID++ ;
				}
		    	}
		    	fclose(file);
		    	return FirstID ;                                                                             
		}else {
			fclose(file);
			return 1 ;
		}
	}

}
void apply_style_bg(GtkWidget *widget , const char *colorID) {
  
    GdkColor color;
    gdk_color_parse(colorID, &color);
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
}
void apply_style_textColor(GtkWidget *widget , const char *colorID) {
   
        GdkColor color;
        gdk_color_parse(colorID , &color);
        gtk_widget_modify_text(widget, GTK_STATE_NORMAL, &color);
}
void apply_style_fg(GtkWidget *widget , const char *colorID) {
  
    GdkColor color;
    gdk_color_parse(colorID, &color);
    gtk_widget_modify_fg(widget, GTK_STATE_NORMAL, &color);
}
void set_label_font(GtkLabel *label, const char *font_description) {
    PangoFontDescription *font_desc = pango_font_description_from_string(font_description);
    gtk_widget_modify_font(GTK_WIDGET(label), font_desc);
    pango_font_description_free(font_desc);
}


int statETs( ) {
	int nbTOT = 0 , nb=0 ;

    FILE * f=fopen("statEts.txt","w");
    if (f!= NULL){

	nb = ETSParRegion("ets.txt", "Ariana") ;
	nbTOT += nb ;
        fprintf(f,"Ariana, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Ben Arous") ;
	nbTOT += nb ;
        fprintf(f,"Ben Arous, %d \n",  nb) ;

	nb = ETSParRegion("ets.txt", "Bizerte") ;
	nbTOT += nb ;
        fprintf(f,"Bizerte, %d \n",  nb) ;

	nb = ETSParRegion("ets.txt", "Gabès");
	nbTOT += nb ;
        fprintf(f,"Gabès, %d \n", nb ) ;



	nb = ETSParRegion("ets.txt", "Gafsa")  ;
	nbTOT += nb ;
        fprintf(f,"Gafsa, %d \n",nb ) ;

	nb = ETSParRegion("ets.txt", "Jendouba") ;
	nbTOT += nb ;
        fprintf(f,"Jendouba, %d \n", nb) ;

	nb = ETSParRegion("ets.txt", "Kairouan")  ;
	nbTOT += nb ;
        fprintf(f,"Kairouan, %d \n",nb ) ;

	nb =ETSParRegion("ets.txt", "Kasserine") ;
	nbTOT += nb ;
        fprintf(f,"Kasserine, %d \n",nb  ) ;

	nb = ETSParRegion("ets.txt", "Kebili") ;
	nbTOT += nb ;
        fprintf(f,"Kebili, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Kef") ;
	nbTOT += nb ;
        fprintf(f,"Kef, %d \n", nb  ) ;

	nb = ETSParRegion("ets.txt", "Mahdia") ;
	nbTOT += nb ;
        fprintf(f,"Mahdia, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Manouba")  ;
	nbTOT += nb ;
        fprintf(f,"Manouba, %d \n", nb) ;

	nb = ETSParRegion("ets.txt", "Medenine")  ;
	nbTOT += nb ;
        fprintf(f,"Medenine, %d \n",nb ) ;

	nb = ETSParRegion("ets.txt", "Monastir")  ;
	nbTOT += nb ;
        fprintf(f,"Monastir, %d \n",nb ) ;

	nb = ETSParRegion("ets.txt", "Nabeul") ;
	nbTOT += nb ;
        fprintf(f,"Nabeul, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Sfax") ;
	nbTOT += nb ;
        fprintf(f,"Sfax, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Sidi Bouzid") ;
	nbTOT += nb ;
        fprintf(f,"Sidi Bouzid, %d \n", nb  ) ;

	nb = ETSParRegion("ets.txt", "Siliana") ;
	nbTOT += nb ;
        fprintf(f,"Siliana, %d \n",  nb) ;

	nb = ETSParRegion("ets.txt", "Sousse")  ;
	nbTOT += nb ;
        fprintf(f,"Sousse, %d \n",nb ) ;

	nb = ETSParRegion("ets.txt", "Tataouine");
	nbTOT += nb ;
        fprintf(f,"Tataouine, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Tozeur") ;
	nbTOT += nb ;
        fprintf(f,"Tozeur, %d \n", nb ) ;

	nb = ETSParRegion("ets.txt", "Tunis (capital)")  ;
	nbTOT += nb ;
        fprintf(f,"Tunis (capital), %d \n", nb) ;

	nb = ETSParRegion("ets.txt", "Zaghouan")  ;
	nbTOT += nb ;
        fprintf(f,"Zaghouan, %d \n", nb) ;
        fclose(f) ;

        
    }
return nbTOT ;
}


void display_ets_Stat(GtkTreeView  *liste , char nomFIchier[]){
	GtkCellRenderer *renderer ; //cell displayer 
	GtkTreeViewColumn *column ; 	// columns visualisation 
	GtkTreeIter iter;  //iterateur
	GtkListStore *store ; // creation of a model with type list 
	int nbre , totalETS= 0;
	char region[30];
	store=NULL ; 
	
	FILE *f ; 
	store=GTK_LIST_STORE(gtk_tree_view_get_model(liste) ) ;
	if (store==NULL){
		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Region",renderer,"text",REGIONS,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(REGIONS));
		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);	

		renderer = gtk_cell_renderer_text_new() ;
		column = gtk_tree_view_column_new_with_attributes(" Nombre d'etablissement",renderer,"text",NBRE,NULL);
		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		g_object_set_data(G_OBJECT(renderer), "column-id", GINT_TO_POINTER(NBRE));
		

		g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_ets_edited), liste);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



		gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_AUTOSIZE);


		store=gtk_list_store_new (COLUM, G_TYPE_STRING ,G_TYPE_INT ) ;

		f= fopen(nomFIchier,"r");
		
		if(f==NULL) {
			return ;	
		}else {
			
			while(fscanf(f,"%29[^,], %d \n",region,&nbre )== 2 ) {
				totalETS++ ;
				gtk_list_store_append(store,&iter);
				gtk_list_store_set(store,&iter,REGIONS,region,NBRE,nbre,-1);
				if (feof(f) ) break ;
			}
			fclose(f) ;
			gtk_tree_view_set_model(GTK_TREE_VIEW(liste) , GTK_TREE_MODEL(store)) ;
			
			
		}
	
		
	}


}
void searcherETS(const char *fileName , const char *key ) {
	FILE *file = fopen(fileName, "r");
	FILE *file2 = fopen("searchResult.txt", "w");
	ETS newEts ;
	    char keyLower[30];
	    strcpy(keyLower, key);
	    for (int i = 0; i<strlen(key); i++) {
		keyLower[i] = tolower(keyLower[i]);
	    }

	char IDtostr[30] , capaciteTostr[30] ; 
	
	if (file != NULL  ) {
        	while( (fscanf(file,"%d, %29[^,], %29[^,], %29[^,], %d \n", &newEts.ID ,newEts.Nom ,newEts.Adresse,newEts.Region ,&newEts.Capacite )) == 5 )  {
			sprintf(IDtostr, "%d" , newEts.ID);
			sprintf(capaciteTostr, "%d" , newEts.Capacite);

			        char userFieldsLower[200];
				strcpy(userFieldsLower, IDtostr);
				strcat(userFieldsLower, newEts.Nom);
				strcat(userFieldsLower, newEts.Adresse);
				strcat(userFieldsLower, newEts.Region);
				strcat(userFieldsLower, capaciteTostr);
				for (int i = 0; i<strlen(userFieldsLower); i++) {
						userFieldsLower[i] = tolower(userFieldsLower[i]);
					    }
		   		if (strstr(userFieldsLower, keyLower) != NULL ) {
				fprintf(file2,"%d, %s, %s, %s, %d \n",newEts.ID ,newEts.Nom ,newEts.Adresse , newEts.Region , newEts.Capacite  );
		    	if (feof(file2)) {break ;}
				
		    	}
        	}
    	}
	fclose(file);
	fclose(file2);
	

}


