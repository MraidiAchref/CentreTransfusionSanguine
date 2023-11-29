#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <cairo.h>
#include "utilisateur.h"
#include <gtk/gtk.h>
#include "ets.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"



void
on_button_deconnecter_achref_ets_clicked(GtkWidget*graphic_object,gpointer user_data){
	GtkWidget *actualWindow = lookup_widget(graphic_object , "espaceAdmin");
	gtk_widget_destroy(actualWindow) ;
  	GtkWidget *windowAuthentification = create_windowAuthentification ();
  	gtk_widget_show (windowAuthentification);
}


void
on_button_retour_addEts_achref_clicked (GtkWidget *graphic_object ,gpointer user_data)
{
GtkWidget *actualWindow = lookup_widget(graphic_object , "admin_addEts_achref");
gtk_widget_destroy(actualWindow) ;
		GtkWidget *espaceAdmin ; 
		espaceAdmin= create_espaceAdmin();
		gtk_widget_show(espaceAdmin) ; 
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");	


}


void
on_button_retour_modifierEts_achref_clicked(GtkWidget *graphic_object ,gpointer user_data)
{
GtkWidget *actualWindow = lookup_widget(graphic_object , "Modifier_ETS_achref");

gtk_widget_destroy(actualWindow) ;
	
		GtkWidget *espaceAdmin ; 
		espaceAdmin= create_espaceAdmin();
		gtk_widget_show(espaceAdmin) ; 

		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;	
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
}


void
on_addButton_achref_ets_clicked(GtkWidget*graphic_button,gpointer user_data)
{
		
		GtkWidget *admin_addEts_achref;
		admin_addEts_achref = create_admin_addEts_achref ();


		char IDtoString[20]; 
		ETSTrieIDCroiss("ets.txt"); 
    		sprintf(IDtoString, "%d", generateID("ets.txt") );
		GtkWidget  *IDoutput  =lookup_widget(admin_addEts_achref,"IDoutput") ; 
		gtk_entry_set_text(GTK_ENTRY(IDoutput), IDtoString );

		  gtk_widget_show (admin_addEts_achref);




		GtkWidget *espaceAdmin  ; 
		espaceAdmin= lookup_widget(graphic_button,"espaceAdmin");
		gtk_widget_hide(espaceAdmin);




}


void
on_modifierButton_achref_ets_clicked (GtkWidget *graphic_button,gpointer user_data)
{
		GtkWidget *Modifier_ETS_achref;
		GtkWidget *espaceAdmin  ; 
		espaceAdmin= lookup_widget(graphic_button,"espaceAdmin");
		gtk_widget_hide(espaceAdmin);

		Modifier_ETS_achref = create_Modifier_ETS_achref ();
  		gtk_widget_show (Modifier_ETS_achref);
		
}


void
on_button_confirmer_addEts_achref_clicked (GtkWidget *objet, gpointer user_data)
{
	ETS etablissement ;

	GtkWidget *input2,*input3,*input4,*input5,*output1 ; 
	GtkWidget *admin_addEts_achref ; 
	int id , capacite ;
	char nom[30],adresse[30],region[30];

	admin_addEts_achref= lookup_widget(objet,"admin_addEts_achref");
	
	input2=lookup_widget(objet,"entry_nom_addEts_achref") ; 
	input3=lookup_widget(objet,"entry_adresse_addEts_achref") ; 
	input4=lookup_widget(objet,"combo_region_addEts_achref") ; 
	//gtk_combo_box_set_active(GTK_COMBO_BOX(input4),0);   // smart way
 	input5=lookup_widget(objet,"spinbutton_capacite_addEts_achref") ; 	
	output1 = lookup_widget(objet,"label_entryAdd_status_achref") ; 
	ETSTrieIDCroiss("ets.txt"); 
	id=generateID("ets.txt") ;   // auto generated 

	strcpy(nom , gtk_entry_get_text(GTK_ENTRY(input2)) ) ; 
	etablissement.ID = id;
	strcpy(etablissement.Nom , nom ) ; 
	strcpy(etablissement.Adresse , gtk_entry_get_text(GTK_ENTRY(input3)) ); 
	if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ){
		strcpy(etablissement.Region , gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) ) ; 
	}
	etablissement.Capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
	if (etablissement.ID == 0 || etablissement.Capacite == 0  || strcmp(etablissement.Nom ,"")== 0 || strcmp(etablissement.Adresse ,"")== 0 || gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL ) {	
		// contole ID
		if (etablissement.ID == 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ ID " );
		// controle capacite
		}else if (etablissement.ID != 0 && etablissement.Capacite == 0  && strcmp(etablissement.Nom ,"")!= 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Capacite " );
		//controle nom
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"")== 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir tous le champ Nom " );
		//controle adresse
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"")== 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Adresse " );
		//controle region
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"") != 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Region " );
		}else {

			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir tous les champs " );
		}
	}else {
	add_ets(etablissement) ; 
		
  		gtk_widget_destroy (admin_addEts_achref);
		GtkWidget *espaceAdmin ; 
		espaceAdmin= create_espaceAdmin();
		gtk_widget_show(espaceAdmin) ; 
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;	
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
 	}
}


void
on_button_confirm_triage_ets_clicked   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *espaceAdmin ; 
	espaceAdmin= lookup_widget(objet,"espaceAdmin");
	char region[30] ;
	GtkToggleButton *radiobutton_croiss_achref_ets= lookup_widget(objet,"radiobutton_croiss_achref_ets") ; 
	GtkToggleButton *radiobutton_decroiss_achref_ets= lookup_widget(objet,"radiobutton_decroiss_achref_ets") ; 
 /***/

	GtkToggleButton *radiobutton_parregioin_achref_ets= lookup_widget(objet,"radiobutton_parregioin_achref_ets") ;
	char typeTriage[30] ;
 			
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_parregioin_achref_ets))) {
	       GtkWidget *combobox_region_achref_ets =lookup_widget(objet,"combobox_region_achref_ets") ;
		if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_region_achref_ets)) != NULL ){

			strcpy(region , gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_region_achref_ets)) ) ; 
			ETSParRegion("ets.txt", region);
			GtkWidget *combobox_trier_achref_ets =lookup_widget(objet,"combobox_trier_achref_ets") ;

			if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_trier_achref_ets)) != NULL ){

				
				strcpy(typeTriage , gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_trier_achref_ets)) ) ; 

				if (strcmp(typeTriage,"Capacite")== 0 ) {
					if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_croiss_achref_ets))) {

						ETSTrieCapaciteCroiss("filtreParRegion.txt");
						
					}else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_decroiss_achref_ets))) {
						ETSTrieCapaciteDecroiss("filtreParRegion.txt");
					}
				}else if (strcmp(typeTriage,"ID")== 0 ) {
					if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_croiss_achref_ets))) {

						ETSTrieIDCroiss("filtreParRegion.txt");
						
					}else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_decroiss_achref_ets))) {
						ETSTrieIDDecroiss("filtreParRegion.txt");
					}	
				}

				GtkWidget *w1 ;
				w1= create_espaceAdmin();
				GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(w1, "treeviewETS_achref"));
				display_ets(treeview,"filtreParRegion.txt") ;
				    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
				    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
				gtk_widget_show(w1) ; 
				gtk_widget_hide(espaceAdmin);
						
			}else {
				GtkWidget *w1 ;
				w1= create_espaceAdmin();
				GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(w1, "treeviewETS_achref"));
				display_ets(treeview,"filtreParRegion.txt") ;
				    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
				    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
				gtk_widget_show(w1) ; 
				gtk_widget_hide(espaceAdmin);			
			}
		}
	}else {

		GtkWidget *combobox_trier_achref_ets =lookup_widget(objet,"combobox_trier_achref_ets") ;
		if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_trier_achref_ets)) != NULL ){
			strcpy(typeTriage , gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_trier_achref_ets)) ) ; 
			if (strcmp(typeTriage,"Capacite")== 0 ) {

				if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_croiss_achref_ets))) {

					ETSTrieCapaciteCroiss("ets.txt");
					
				}else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_decroiss_achref_ets))) {
					ETSTrieCapaciteDecroiss("ets.txt");
				}
			}else if (strcmp(typeTriage,"ID")== 0 ) {
				if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_croiss_achref_ets))) {

					ETSTrieIDCroiss("ets.txt");
					
				}else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_decroiss_achref_ets))) {
					ETSTrieIDDecroiss("ets.txt");
				}	
			}else {
				GtkWidget *w1 ;
				w1= create_espaceAdmin();
				GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(w1, "treeviewETS_achref"));
				display_ets(treeview,"ets.txt") ;
				    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
				    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
				gtk_widget_show(w1) ; 
				gtk_widget_hide(espaceAdmin);


			}



			/*if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_croiss_achref_ets))) {

				ETSTrieCapaciteCroiss("ets.txt");
				
			}else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_decroiss_achref_ets))) {
				ETSTrieCapaciteDecroiss("ets.txt");
			}*/


			GtkWidget *w1 ;
			w1= create_espaceAdmin();
			GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(w1, "treeviewETS_achref"));
			display_ets(treeview,"ets.txt") ;
			    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
			    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
			gtk_widget_show(w1) ; 
			gtk_widget_hide(espaceAdmin);
		}else {

			GtkWidget *w1 ;
			w1= create_espaceAdmin();
			GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(w1, "treeviewETS_achref"));
			display_ets(treeview,"ets.txt") ;
			    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
			    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
			gtk_widget_show(w1) ; 
			gtk_widget_hide(espaceAdmin);


		}
	}

	
		
	

}


void
on_button_OK_modifierEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data)
{	
	int ID ;
	GtkWidget *input2,*input22,*input3,*input33,*input4,*input44,*input5,*input55,*input6,*Modifier_ETS_achref ; 
	 
	input2=lookup_widget(objet,"entry_nom_modifierEts_achref") ; 
	input22=lookup_widget(objet,"label_nom_modifierEts_achref") ; 

	input3=lookup_widget(objet,"entry_adresse_modifierEts_achref") ; 
	input33=lookup_widget(objet,"label_adresse_modifierEts_achref") ; 

	input4=lookup_widget(objet,"combo_region_modifierEts_achref") ;
	input44=lookup_widget(objet,"label_region_modifierEts_achref") ;

	input5=lookup_widget(objet,"spinbutton_capacite_modifierEts_achref") ;
	input55=lookup_widget(objet,"label84") ;

	input6=lookup_widget(objet,"button_confirmer_modifierEts_achref") ;

	GtkWidget *statusLabel = lookup_widget(objet,"ets_search_result_achref");
	
	Modifier_ETS_achref= lookup_widget(objet,"Modifier_ETS_achref");
  	GtkWidget *input1 =lookup_widget(objet,"entry_Id_modifierEts_achref") ;
	ID = atoi(gtk_entry_get_text(GTK_ENTRY(input1))) ;
	if(ChercherEts("ets.txt",ID).ID == -1) {
		gtk_label_set_text(GTK_LABEL(statusLabel),"Etablissement non trouvee , Veilliez verifier l'id !") ;
	}else if(ChercherEts ("ets.txt",ID).ID != -1) {
		//setting visibility 
		gtk_label_set_text(GTK_LABEL(statusLabel),"Veilliez entrer vos modification ") ;
 		gtk_editable_set_editable(GTK_EDITABLE(input1), FALSE);
		gtk_widget_set_visible(input2, !gtk_widget_get_visible(input2));
		gtk_widget_set_visible(input22, !gtk_widget_get_visible(input22));
		gtk_widget_set_visible(input3, !gtk_widget_get_visible(input3));
		gtk_widget_set_visible(input33, !gtk_widget_get_visible(input33));
		gtk_widget_set_visible(input4, !gtk_widget_get_visible(input4));
		gtk_widget_set_visible(input44, !gtk_widget_get_visible(input44));
		gtk_widget_set_visible(input5, !gtk_widget_get_visible(input5));
		gtk_widget_set_visible(input55, !gtk_widget_get_visible(input55));
		gtk_widget_set_visible(input6, !gtk_widget_get_visible(input6));

		//set default text
		gtk_entry_set_text(GTK_ENTRY(input2),ChercherEts("ets.txt",ID).Nom );
		gtk_entry_set_text(GTK_ENTRY(input3),ChercherEts("ets.txt",ID).Adresse );
		//gtk_combo_box_set_active(GTK_COMBO_BOX(input4),ChercherEts("ets.txt",ID).Region );
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(input5),ChercherEts("ets.txt",ID).Capacite );


	}
}


void
on_button_confirmer_modifierEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	ETS etablissement ;
	GtkWidget *Modifier_ETS_achref= lookup_widget(objet,"Modifier_ETS_achref");
	GtkWidget *espaceAdmin = create_espaceAdmin ();

	GtkWidget *input1,*input2,*input3,*input4,*input5,*output1 ; 
	output1 = lookup_widget(objet,"ets_search_result_achref") ; 	

	input1 =lookup_widget(objet,"entry_Id_modifierEts_achref") ;
	input2=lookup_widget(objet,"entry_nom_modifierEts_achref") ; 
	input3=lookup_widget(objet,"entry_adresse_modifierEts_achref") ; 
	input4=lookup_widget(objet,"combo_region_modifierEts_achref") ;
	input5=lookup_widget(objet,"spinbutton_capacite_modifierEts_achref") ;
	
	etablissement.ID = atoi(gtk_entry_get_text(GTK_ENTRY(input1))) ;
	strcpy(etablissement.Nom , gtk_entry_get_text(GTK_ENTRY(input2)) ) ; 
	strcpy(etablissement.Adresse , gtk_entry_get_text(GTK_ENTRY(input3)) ); 
	if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ){
		strcpy(etablissement.Region , gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) ) ; 
	}
	etablissement.Capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
	
	
	if (etablissement.ID == 0 || etablissement.Capacite == 0  || strcmp(etablissement.Nom ,"")== 0 || strcmp(etablissement.Adresse ,"")== 0 || gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL ) {	
		// contole ID
		if (etablissement.ID == 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ ID " );
		// controle capacite
		}else if (etablissement.ID != 0 && etablissement.Capacite == 0  && strcmp(etablissement.Nom ,"")!= 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Capacite " );
		//controle nom
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"")== 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Nom " );
		//controle adresse
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"")== 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Adresse " );
		//controle region
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"") != 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL ) {	
			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir le champ Region " );
		}else {

			gtk_label_set_text(GTK_LABEL(output1),"Veillez remplir tous les champs " );
		}
	}else {
		ModifierEts ("ets.txt", etablissement, etablissement.ID  );
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));
		display_ets(treeview,"ets.txt") ;
		    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
		    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
		gtk_widget_show(espaceAdmin) ; 
		gtk_widget_hide(Modifier_ETS_achref);

	}
}


void
on_button_retour_deleteEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
		GtkWidget *DeleteEts_achref= lookup_widget(objet,"DeleteEts_achref");
		GtkWidget *espaceAdmin = create_espaceAdmin ();
		gtk_widget_show(espaceAdmin) ; 
        	GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));
		display_ets(treeview,"ets.txt") ;
		    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
		    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
		gtk_widget_hide(DeleteEts_achref);
		

}


void
on_button_confirmer_deleteEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	int id ;
	GtkWidget *input1 =lookup_widget(objet,"entry_deleteEts_id_achref") ;
	GtkWidget *output2=lookup_widget(objet,"label_deleteEts_status_achref") ;

	id = atoi(gtk_entry_get_text(GTK_ENTRY(input1))) ;
	if( ChercherEts("ets.txt",id).ID == -1) {
		gtk_label_set_text(GTK_LABEL(output2),"Etablissement non trouvee ") ;
	}else {
		SupprimerEts (id);
		GtkWidget *DeleteEts_achref= lookup_widget(objet,"DeleteEts_achref");
		GtkWidget *espaceAdmin = create_espaceAdmin ();
		gtk_widget_show(espaceAdmin) ;
        	GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));
		display_ets(treeview,"ets.txt") ;
		    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
		    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
 
		gtk_widget_hide(DeleteEts_achref);

	}

}


void
on_supprimerButton_achref_ets_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
		GtkWidget *DeleteEts_achref = create_DeleteEts_achref ();
		gtk_widget_show(DeleteEts_achref) ; 
		

}

static GtkWidget *calendar;
int choix_sexe[2] = {0}; 
int choix_role[3] = {0};  

void
on_button_Firas_Modifier_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *Firas_Modifier;
    GtkWidget *espaceAdmin;
    Firas_Modifier = create_Firas_Modifier();
    gtk_widget_show(Firas_Modifier);
    espaceAdmin = lookup_widget(GTK_WIDGET(button), "espaceAdmin");
    gtk_widget_hide(espaceAdmin);


}


void
on_button_Firas_Supprimer_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *Firas_Suppression;
    GtkWidget *espaceAdmin;
    Firas_Suppression = create_Firas_Suppression();
    gtk_widget_show(Firas_Suppression);
    espaceAdmin = lookup_widget(GTK_WIDGET(button), "espaceAdmin");
    gtk_widget_hide(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
}

    
void on_button_Firas_Chercher_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *espaceAdmin, *w1;

    w1 = lookup_widget(objet_graphique, "espaceAdmin");
    espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
    gtk_widget_hide(w1);
			GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
    GtkWidget *combobox_firas_Role = lookup_widget(objet_graphique, "combobox_firas_Role");
    GtkWidget *combobox_firas_sexe = lookup_widget(objet_graphique, "combobox_firas_sexe");

    char *selected_role = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_firas_Role));
    char *selected_sexe = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_firas_sexe));

    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    vider(treeview_Firas);

    if (selected_role != NULL && selected_sexe != NULL) {
        UserFilter("Utilisateur.txt", selected_role, selected_sexe);
        afficher_utilisateur(treeview_Firas, "filtered_users.txt");
    } else if (selected_role != NULL) {
        UserRole("Utilisateur.txt", selected_role);
        afficher_utilisateur(treeview_Firas, "Role_users.txt");
    } else if (selected_sexe != NULL) {
        UserSexe("Utilisateur.txt", selected_sexe);
        afficher_utilisateur(treeview_Firas, "Sexe_users.txt");
    } else {
        afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
    }
			GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
}

void on_button_Firas_Valider_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *entry_Firas_ID = lookup_widget(objet_graphique, "entry_Firas_ID");
    GtkWidget *entry_Firas_Nom = lookup_widget(objet_graphique, "entry_Firas_Nom");
    GtkWidget *entry_Firas_Prenom = lookup_widget(objet_graphique, "entry_Firas_Prenom");
    GtkWidget *entry_sabeh_Date = lookup_widget(objet_graphique, "entry_sabeh_Date");
    GtkWidget *entry_Firas_Pass = lookup_widget(objet_graphique, "entry_Firas_Pass");
    GtkWidget *entry_Firas_Confirm = lookup_widget(objet_graphique, "entry_Firas_Confirm");
    GtkWidget *label_error_firas = lookup_widget(objet_graphique, "label_error_firas");
    char confirm[20];

			GdkColor color;
    		gdk_color_parse("#FF0000", &color);  // Change #FF0000 to your desired color code
    		gtk_widget_modify_fg(label_error_firas, GTK_STATE_NORMAL, &color);


    if (strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_ID)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Nom)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Prenom)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Pass)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Confirm)), "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(label_error_firas), "Veuillez remplir tous les champs");
    }
    else
    {
        Utilisateur new_user;
        strcpy(new_user.ID, gtk_entry_get_text(GTK_ENTRY(entry_Firas_ID)));
        strcpy(new_user.Nom, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Nom)));
        strcpy(new_user.Prenom, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Prenom)));
        strcpy(new_user.Password, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Pass)));
        new_user.D = get_date_from_entry(GTK_ENTRY(entry_sabeh_Date));
        strcpy(new_user.Sexe, Sexe(choix_sexe));
        strcpy(new_user.Role, Role(choix_role));
        strcpy(confirm, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Confirm)));


        if (strcmp(new_user.Password, confirm) != 0)
        {
            gtk_label_set_text(GTK_LABEL(label_error_firas), "Erreur : Mot de passe non identique");
        }
        else
        {

            if (is_ID_exists(new_user.ID))
            {
                gtk_label_set_text(GTK_LABEL(label_error_firas), "Erreur : ID déjà existant");
            }
            else
            {
   
               ajouter(new_user);

     
                gtk_entry_set_text(GTK_ENTRY(entry_Firas_ID), "");
                gtk_entry_set_text(GTK_ENTRY(entry_Firas_Nom), "");
                gtk_entry_set_text(GTK_ENTRY(entry_Firas_Prenom), "");
                gtk_entry_set_text(GTK_ENTRY(entry_sabeh_Date), "");
                gtk_entry_set_text(GTK_ENTRY(entry_Firas_Pass), "");
                gtk_entry_set_text(GTK_ENTRY(entry_Firas_Confirm), "");


                GtkWidget *Firas_Ajout = lookup_widget(objet_graphique, "Firas_Ajout");
                gtk_widget_destroy(Firas_Ajout);

  
                GtkWidget *espaceAdmin = lookup_widget(objet_graphique, "espaceAdmin");
                gtk_widget_destroy(espaceAdmin);
                espaceAdmin = create_espaceAdmin();
                gtk_widget_show(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	        gtk_notebook_set_current_page(notebook, 1);

                GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
                afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
				GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
            }
        }
    }
}


void
on_button_Firas_Ajouter_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *Firas_Ajout;
    GtkWidget *espaceAdmin;
    Firas_Ajout = create_Firas_Ajout();
    gtk_widget_show(Firas_Ajout);
    espaceAdmin = lookup_widget(GTK_WIDGET(button), "espaceAdmin");
    gtk_widget_hide(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);

}


gboolean
on_entry1_focus_in_event (GtkWidget *widget,GdkEventFocus *event,gpointer user_data)
{
    	    GtkWidget *calendar = lookup_widget(GTK_WIDGET(widget), "calendar");

    	if (calendar != NULL) {
        	gtk_widget_show(calendar); 
   		 }

  
  		return FALSE;
}


void
on_calendar_day_selected (GtkCalendar *calendar,gpointer user_data)
{
    char *date_str;
    GtkWidget *entry_sabeh_Date = lookup_widget(GTK_WIDGET(calendar), "entry_sabeh_Date");
    int year, month, day;

    gtk_calendar_get_date(calendar, &day, &month, &year);

    date_str = g_strdup_printf("%02d-%02d-%04d", day, month + 1, year);

    gtk_entry_set_text(GTK_ENTRY(entry_sabeh_Date), date_str);
    g_free(date_str);
}



void on_button_Firas_SuppID_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
   GtkWidget *entry_Firas_SuppID = lookup_widget(objet_graphique, "entry_Firas_SuppID");
   GtkWidget *label_error_firas = lookup_widget(objet_graphique, "label_error_firas"); 
   
   char id[30];
   strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_Firas_SuppID)));
				  	 
		GdkColor color;
    		gdk_color_parse("#FF0000", &color);  // Change #FF0000 to your desired color code
    		gtk_widget_modify_fg(label_error_firas, GTK_STATE_NORMAL, &color);
   
    Utilisateur U;

   U = verifier(id);
   if (strcmp(U.ID,"-1")!=0)
   { 
	if(supprimer_utilisateur(id) == 1)	
		{        GtkWidget *Firas_Suppression = lookup_widget(objet_graphique, "Firas_Suppression");
    		       gtk_widget_destroy(Firas_Suppression);
		       GtkWidget *Succeed_Supp = create_Succeed_Supp();
   		       gtk_widget_show(Succeed_Supp);

		       g_timeout_add(3000, (GSourceFunc)gtk_widget_destroy, Succeed_Supp);
  		       GtkWidget *espaceAdmin = lookup_widget(objet_graphique, "espaceAdmin");
    		       gtk_widget_destroy(espaceAdmin);
  		       espaceAdmin = create_espaceAdmin();
   		       gtk_widget_show(espaceAdmin);
		        GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
			gtk_notebook_set_current_page(notebook, 1);
    		       GtkWidget *treeview_Firas=lookup_widget(espaceAdmin, "treeview_Firas");
    		       afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
		       GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		       display_ets(treeview,"ets.txt") ;
               }
   }else
     {
        gtk_label_set_text(GTK_LABEL(label_error_firas), "Erreur : Utilisateur non trouvé");
	
     }
}


void on_button_Fir_OK_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *entry_Fir_ID = lookup_widget(objet_graphique, "entry_Fir_ID");
    GtkWidget *entry_F_ID = lookup_widget(objet_graphique, "entry_F_ID");
    GtkWidget *label_F_ID = lookup_widget(objet_graphique, "label_F_ID");
    GtkWidget *entry_Fir_Nom = lookup_widget(objet_graphique, "entry_Fir_Nom");
    GtkWidget *entry_Fir_prenom = lookup_widget(objet_graphique, "entry_Fir_prenom");
    GtkWidget *label_Fir_Nom = lookup_widget(objet_graphique, "label_Fir_Nom");
    GtkWidget *label_Fir_prenom = lookup_widget(objet_graphique, "label_Fir_prenom");
    GtkWidget *label_Fir_Role = lookup_widget(objet_graphique, "label_Fir_Role");
    GtkWidget *label_Fir_Sexe = lookup_widget(objet_graphique, "label_Fir_Sexe");
    GtkWidget *label_Fir_DOB = lookup_widget(objet_graphique, "label_Fir_DOB");
    GtkWidget *combobox_Fir_Sexe = lookup_widget(objet_graphique, "combobox_Fir_Sexe");
    GtkWidget *combobox_Fir_Role = lookup_widget(objet_graphique, "combobox_Fir_Role");
    GtkWidget *entry_Fir_DOB = lookup_widget(objet_graphique, "entry_Fir_DOB");
    GtkWidget *entry_Fir_Pass = lookup_widget(objet_graphique, "entry_Fir_Pass");
    GtkWidget *entry_Fir_Confirm = lookup_widget(objet_graphique, "entry_Fir_Confirm");
    GtkWidget *label_Fir_Confirm = lookup_widget(objet_graphique, "label_Fir_Confirm");
    GtkWidget *label_Fir_pass = lookup_widget(objet_graphique, "label_Fir_pass");
    GtkWidget *button_Fir_Confirm = lookup_widget(objet_graphique, "button_Fir_Confirm");
    GtkWidget *label_firas_error_ID = lookup_widget(objet_graphique, "label_firas_error_ID");
    GtkToggleButton *togglebutton_Fir_Pass_Modif = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique, "togglebutton_Fir_Pass_Modif"));
    GtkToggleButton *togglebutton_Fir_Con_Modif = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique, "togglebutton_Fir_Con_Modif"));
    GtkImage *image = GTK_IMAGE(lookup_widget(objet_graphique, "image22"));
    GtkImage *image1 = GTK_IMAGE(lookup_widget(objet_graphique, "image23"));
	    GdkColor color;
    gdk_color_parse("#FF0000", &color);
    gtk_widget_modify_fg(label_firas_error_ID, GTK_STATE_NORMAL, &color);


    char entry_id[30];
    strcpy(entry_id, gtk_entry_get_text(GTK_ENTRY(entry_Fir_ID)));

    Utilisateur U;
    U = verifier(entry_id);

    if (strcmp(U.ID, "-1") != 0)
    {
        gtk_entry_set_text(GTK_ENTRY(entry_F_ID), U.ID);
        gtk_entry_set_text(GTK_ENTRY(entry_Fir_Nom), U.Nom);
        gtk_entry_set_text(GTK_ENTRY(entry_Fir_prenom), U.Prenom);
	gtk_entry_set_text(GTK_ENTRY(entry_Fir_Pass), U.Password);
        gtk_entry_set_text(GTK_ENTRY(entry_Fir_Confirm), "");
	char date[30];
	g_snprintf(date, sizeof(date), "%02d-%02d-%d", U.D.day, U.D.month, U.D.year);
	gtk_entry_set_text(GTK_ENTRY(entry_Fir_DOB), date);

        gtk_widget_show(GTK_WIDGET(button_Fir_Confirm));
        gtk_widget_show(GTK_WIDGET(label_F_ID));
        gtk_widget_show(GTK_WIDGET(entry_F_ID));
        gtk_widget_show(GTK_WIDGET(label_Fir_Nom));
        gtk_widget_show(GTK_WIDGET(entry_Fir_Nom));
        gtk_widget_show(GTK_WIDGET(label_Fir_prenom));
        gtk_widget_show(GTK_WIDGET(entry_Fir_prenom));
        gtk_widget_show(GTK_WIDGET(combobox_Fir_Sexe));
        gtk_widget_show(GTK_WIDGET(label_Fir_Sexe));
        gtk_widget_show(GTK_WIDGET(combobox_Fir_Role));
        gtk_widget_show(GTK_WIDGET(label_Fir_Role));
        gtk_widget_show(GTK_WIDGET(entry_Fir_DOB));
        gtk_widget_show(GTK_WIDGET(label_Fir_DOB));
        gtk_widget_show(GTK_WIDGET(entry_Fir_Pass));
        gtk_widget_show(GTK_WIDGET(label_Fir_pass));
        gtk_widget_show(GTK_WIDGET(label_Fir_Confirm));
        gtk_widget_show(GTK_WIDGET(entry_Fir_Confirm));
	gtk_widget_show(GTK_WIDGET(togglebutton_Fir_Pass_Modif));
	gtk_widget_show(GTK_WIDGET(togglebutton_Fir_Con_Modif));
	gtk_widget_show(GTK_WIDGET(image));
	gtk_widget_show(GTK_WIDGET(image1));


        gtk_editable_set_editable(GTK_EDITABLE(entry_Fir_ID), FALSE);
    }
    else
    {
	gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Erreur : Utilisateur non trouvé");
    }
}



void on_button_Fir_Confirm_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
        GtkWidget *entry_Fir_ID = lookup_widget(objet_graphique, "entry_Fir_ID");
    GtkWidget *entry_F_ID = lookup_widget(objet_graphique, "entry_F_ID");
    GtkWidget *entry_Fir_Nom = lookup_widget(objet_graphique, "entry_Fir_Nom");
    GtkWidget *entry_Fir_prenom = lookup_widget(objet_graphique, "entry_Fir_prenom");
    GtkWidget *combobox_Fir_Sexe = lookup_widget(objet_graphique, "combobox_Fir_Sexe");
    GtkWidget *combobox_Fir_Role = lookup_widget(objet_graphique, "combobox_Fir_Role");
    GtkWidget *entry_Fir_DOB = lookup_widget(objet_graphique, "entry_Fir_DOB");
    GtkWidget *entry_Fir_Pass = lookup_widget(objet_graphique, "entry_Fir_Pass");
    GtkWidget *entry_Fir_Confirm = lookup_widget(objet_graphique, "entry_Fir_Confirm");
    GtkWidget *label_firas_error_ID = lookup_widget(objet_graphique, "label_firas_error_ID");
		  	 GdkColor color;
    		gdk_color_parse("#FF0000", &color);  // Change #FF0000 to your desired color code
    		gtk_widget_modify_fg(label_firas_error_ID, GTK_STATE_NORMAL, &color);

    char entry_id[30];
    strcpy(entry_id, gtk_entry_get_text(GTK_ENTRY(entry_Fir_ID)));

    Utilisateur new_user;

    strncpy(new_user.ID, gtk_entry_get_text(GTK_ENTRY(entry_F_ID)), sizeof(new_user.ID) - 1);
    new_user.ID[sizeof(new_user.ID) - 1] = '\0'; 

    strncpy(new_user.Nom, gtk_entry_get_text(GTK_ENTRY(entry_Fir_Nom)), sizeof(new_user.Nom) - 1);
    new_user.Nom[sizeof(new_user.Nom) - 1] = '\0';

    strncpy(new_user.Prenom, gtk_entry_get_text(GTK_ENTRY(entry_Fir_prenom)), sizeof(new_user.Prenom) - 1);
    new_user.Prenom[sizeof(new_user.Prenom) - 1] = '\0';


    const gchar *selectedSexe = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_Fir_Sexe));
    if (selectedSexe != NULL) {
        strncpy(new_user.Sexe, selectedSexe, sizeof(new_user.Sexe) - 1);
        new_user.Sexe[sizeof(new_user.Sexe) - 1] = '\0';
    } else {
        gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Veuillez sélectionner un sexe");
        return; 
    }

    const gchar *selectedRole = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_Fir_Role));
    if (selectedRole != NULL) {
        strncpy(new_user.Role, selectedRole, sizeof(new_user.Role) - 1);
        new_user.Role[sizeof(new_user.Role) - 1] = '\0';
    } else {
        gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Veuillez sélectionner un rôle");
        return;
    }

    new_user.D = get_date_from_entry(GTK_ENTRY(entry_Fir_DOB));

    strncpy(new_user.Password, gtk_entry_get_text(GTK_ENTRY(entry_Fir_Pass)), sizeof(new_user.Password) - 1);
    new_user.Password[sizeof(new_user.Password) - 1] = '\0';

    char confirm[30];
    strncpy(confirm, gtk_entry_get_text(GTK_ENTRY(entry_Fir_Confirm)), sizeof(confirm) - 1);
    confirm[sizeof(confirm) - 1] = '\0';


    if (strlen(new_user.ID) == 0 || strlen(new_user.Role) == 0 || strlen(new_user.Nom) == 0 ||
        strlen(new_user.Prenom) == 0 || strlen(new_user.Sexe) == 0) {
        gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Veuillez remplir tous les champs");
        return;
    }


    if (strcmp(new_user.Password, confirm) == 0) {
        int result = modifier(entry_id, new_user);

        if (result == 1) {
            GtkWidget *Firas_Modifier = lookup_widget(objet_graphique, "Firas_Modifier");
            gtk_widget_destroy(Firas_Modifier);
            GtkWidget *espaceAdmin = lookup_widget(objet_graphique, "espaceAdmin");
            gtk_widget_destroy(espaceAdmin);
            espaceAdmin = create_espaceAdmin();
            gtk_widget_show(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
            GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
            afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
        } else {
            gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Erreur lors de la modification");
        }
    } else {
        gtk_label_set_text(GTK_LABEL(label_firas_error_ID), "Erreur : Mot de passe non identique");
    }
}



void
on_radiobutton_Firas_F_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
	     {         
		choix_sexe[0] = 0; 
        	choix_sexe[1] = 1; 
		}
}


void
on_radiobutton_Firas_H_toggled (GtkToggleButton *togglebutton,gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
	     {         
		choix_sexe[0] = 1; 
        	choix_sexe[1] = 0;
		}
}


void
on_button_Fir_Retour_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *Firas_Modifier = lookup_widget(GTK_WIDGET((GtkWidget*)button), "Firas_Modifier");
    gtk_widget_destroy(Firas_Modifier);

    GtkWidget *espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
			GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;

	
	
}


void
on_Fir_Retour_clicked (GtkButton *button, gpointer user_data)
{

    GtkWidget *Firas_Ajout = lookup_widget(GTK_WIDGET((GtkWidget*)button), "Firas_Ajout");
    gtk_widget_destroy(Firas_Ajout);

    GtkWidget *espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
	
}


void
on_checkbutton_Firas_Med_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {
    		choix_role[1] = 1;
	} else {
    		choix_role[1] = 0;
	}

}


void
on_checkbutton_Firas_Resp_toggled (GtkToggleButton *togglebutton,gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {
    		choix_role[2] = 1;
	} else {
    		choix_role[2] = 0;
	}

}


void
on_checkbutton_Firas_Inf_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {
    		choix_role[0] = 1;
	} else {
    		choix_role[0] = 0;
	}

}


gboolean
on_entry_Fir_DOB_focus_in_event (GtkWidget *widget,GdkEventFocus *event,gpointer user_data)
{
	 GtkWidget *calendar_Fir_2 = lookup_widget(GTK_WIDGET(widget), "calendar_Fir_2");

    	if (calendar_Fir_2 != NULL) {
        	gtk_widget_show(calendar_Fir_2); 
   		 }
  return FALSE;
}


void
on_calendar_Fir_2_day_selected  (GtkCalendar *calendar,gpointer user_data)
{
    char *date_str;
    GtkWidget *entry_Fir_DOB = lookup_widget(GTK_WIDGET(calendar), "entry_Fir_DOB");
    int year, month, day;

    gtk_calendar_get_date(calendar, &day, &month, &year);

    date_str = g_strdup_printf("%02d-%02d-%04d", day, month + 1, year);

    gtk_entry_set_text(GTK_ENTRY(entry_Fir_DOB), date_str);
    g_free(date_str);
}


void
on_button_Firas_Afficher_clicked (GtkWidget *objet_graphique,gpointer user_data)
{
 
    GtkWidget *espaceAdmin , *w1 ;
    
     w1 = lookup_widget(objet_graphique, "espaceAdmin");
     espaceAdmin = create_espaceAdmin();
     gtk_widget_show(espaceAdmin);
     gtk_widget_hide(w1);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);

    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    vider(treeview_Firas);    


        afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;


}


gboolean
on_drawingarea_Firas_button_press_event(GtkWidget *widget,GdkEventButton *event,gpointer user_data)
{
   
}



void
on_button_Firas_stat_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Firas_statistic;
    GtkWidget *espaceAdmin;
    Firas_statistic = create_Firas_statistic();
    gtk_widget_show(Firas_statistic);
    espaceAdmin = lookup_widget(GTK_WIDGET(button), "espaceAdmin");
    gtk_widget_hide(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
}



gboolean
on_treeview_Firas_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
 
     if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        // Right-click handling code

        // Get the tree view
        GtkTreeView *tree_view = GTK_TREE_VIEW(widget);

        // Get the path and column at the clicked position
        GtkTreePath *path;
        GtkTreeViewColumn *column;
        gint cell_x, cell_y;
	
        if (gtk_tree_view_get_path_at_pos(tree_view, event->x, event->y, &path, &column, &cell_x, &cell_y)) {

            GtkWidget *menu = gtk_menu_new();
            GtkWidget *item_edit = gtk_menu_item_new_with_label("Edit");
            GtkWidget *item_add = gtk_menu_item_new_with_label("Add");
	    g_signal_connect(item_add, "activate", G_CALLBACK(on_Add_activate), tree_view);
            GtkWidget *item_delete = gtk_menu_item_new_with_label("Delete");
	    g_signal_connect(item_delete, "activate", G_CALLBACK(on_Delete_activate), tree_view);


            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_edit);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_add);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_delete);

            gtk_widget_show_all(menu);

             gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, event->button, event->time);

            gtk_tree_path_free(path);

            return TRUE;
        }
    }

    return FALSE;

}

  void on_cell_edited(GtkCellRendererText *cell, gchar *path_string, gchar *new_text, gpointer user_data)
{
    
	
	GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    model = gtk_tree_view_get_model(treeview);

    // Convert the path string to a GtkTreeIter
    if (gtk_tree_model_get_iter_from_string(model, &iter, path_string)) {
        // Retrieve the column number directly from the cell renderer's property
       int column_number = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column-id"));
	
        // Update the model with the new text
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, column_number, new_text, -1);

 	// Save the changes to the file
        gchar *id, *nom, *prenom, *sexe, *role, *date, *password;
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, IDENTIFIANT, &id, NOM, &nom, PRENOM, &prenom,
                           SEXE, &sexe, ROLE, &role, DATE, &date, PASSWORD, &password, -1);
// Check if any of the required fields are empty
    if (strlen(id) == 0 || strlen(nom) == 0 || strlen(prenom) == 0 ||
        strlen(sexe) == 0 || strlen(role) == 0 || strlen(date) == 0 || strlen(password) == 0)
    {
        // Display an error message or handle the case where not all fields are filled
        g_free(id);
        g_free(nom);
        g_free(prenom);
        g_free(sexe);
        g_free(role);
        g_free(date);
        g_free(password);
        return;
    }

    // Check if the ID already exists
    else if (is_ID_exists(id)) {
	 // Modify the existing user

            // Assuming you have a Utilisateur structure
            Utilisateur nouv;
            strcpy(nouv.ID, id);
            strcpy(nouv.Nom, nom);
            strcpy(nouv.Prenom, prenom);
            strcpy(nouv.Sexe, sexe);
            strcpy(nouv.Role, role);

            // g_snprintf(date, sizeof(date), "%d-%02d-%02d", U.D.year, U.D.month, U.D.day);
            sscanf(date, "%02d-%02d-%d", &nouv.D.day, &nouv.D.month, &nouv.D.year);

            strcpy(nouv.Password, password);

            // Call the modifier function with the modified Utilisateur
            modifier(id, nouv);
 
    }else{

        // Assuming you have a Utilisateur structure
        		Utilisateur nouv;
        		strcpy(nouv.ID, id);
        		strcpy(nouv.Nom, nom);
        		strcpy(nouv.Prenom, prenom);
        		strcpy(nouv.Sexe, sexe);
        		strcpy(nouv.Role, role);

        //g_snprintf(date, sizeof(date), "%d-%02d-%02d", U.D.year, U.D.month, U.D.day);
			sscanf(date, "%02d-%02d-%d", &nouv.D.day, &nouv.D.month, &nouv.D.year);

        		strcpy(nouv.Password, password);

	
 	// Call the ajouter function with the new Utilisateur
        		ajouter(nouv);


        		g_free(id);
        		g_free(nom);
        		g_free(prenom);
        		g_free(sexe);
        		g_free(role);
        		g_free(date);
        		g_free(password);
    }
}
}


void
on_edit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_Delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
 GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);

    // Get the selected row
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Get the data from the row before removing it
        gchar *ID;

        gtk_tree_model_get(model, &iter, IDENTIFIANT, &ID, -1);

        // Remove the row from the model
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

        // Update the data file (Utilisateur.txt)
        int find = supprimer_utilisateur(ID);

        // Free the allocated memory
        g_free(ID);

        // Check if the ID was found in the file
        if (find) {
 		
        }
    }
}


void on_Add_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkTreeModel *model;
    GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));
        model = gtk_tree_view_get_model(tree_view);   

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, IDENTIFIANT, "", NOM, "", PRENOM, "", SEXE, "", ROLE, "", DATE, "", PASSWORD, "", -1);
  
    // Set the cursor to the newly added row
    gtk_tree_view_set_cursor(tree_view, gtk_tree_model_get_path(gtk_tree_view_get_model(tree_view), &iter), NULL, TRUE);
	
}



void
on_togglebutton1_toggled               (GtkWidget *togglebutton,
                                        gpointer         user_data)
{
    GtkImage *image = lookup_widget(togglebutton,"image7");
GtkWidget*Password = lookup_widget(togglebutton,"entry_Authentification_Password");
		GtkToggleButton *togglebutton1= lookup_widget(togglebutton,"togglebutton1");
    if (gtk_toggle_button_get_active(togglebutton1)) {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-open.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 1);
	
    } else {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-closed.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 0);

	
    }
}

void
on_togglebutton1_released              (GtkButton       *button,
                                        gpointer         user_data)
{

}




void
on_Authentification_buttonLogin_clicked
                                        (GtkWidget       *graphic_object,
                                        gpointer         user_data)
{
char userNameEntred[30] , passwordEntred[30];
  	GtkWidget *windowAdmin;
	  GtkWidget *actualwindow=lookup_widget(graphic_object,"windowAuthentification");
	GtkWidget *statusLabel = lookup_widget(graphic_object,"Authentification_labelStatus");
	GtkWidget *UserNameEntred = lookup_widget(graphic_object,"entry_Authentification_UserName");
	GtkWidget *PasswordEntred = lookup_widget(graphic_object,"entry_Authentification_Password");
	strcpy(userNameEntred,gtk_entry_get_text(GTK_ENTRY(UserNameEntred) )  ) ;
	strcpy(passwordEntred,gtk_entry_get_text(GTK_ENTRY(PasswordEntred) )  ) ;

	  	 GdkColor color;
    		gdk_color_parse("#FF0000", &color);  // Change #FF0000 to your desired color code
    		gtk_widget_modify_fg(statusLabel, GTK_STATE_NORMAL, &color);

	 
    /*gdk_color_parse("#FF0000", &color);  // Change #FF0000 to your desired color code
    gtk_widget_modify_bg(GTK_WIDGET(testbutton), GTK_STATE_NORMAL, &color);*/


  PangoFontDescription *font_desc = pango_font_description_from_string("Sans 18");  
    gtk_widget_modify_font(statusLabel, font_desc);
    pango_font_description_free(font_desc);
	GtkWidget *notRobot=lookup_widget(actualwindow,"notRobot_checkbutton");
	int checked_NotRobot = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(notRobot)) ;
	if (verifierTypeUtilisateur(userNameEntred, passwordEntred) == 0 && (checked_NotRobot) ) {
		gtk_label_set_text(GTK_LABEL(statusLabel),"Bienvenue") ;
		GtkWidget *actualWindow = lookup_widget(graphic_object , "windowAuthentification");
		gtk_widget_destroy(actualWindow) ;
		windowAdmin = create_espaceAdmin ();
  		gtk_widget_show (windowAdmin);

 		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(windowAdmin, "treeviewETS_achref"));
  		display_ets(treeview,"ets.txt") ;

    		GtkWidget *treeview_Firas=lookup_widget(windowAdmin, "treeview_Firas");
    		afficher_utilisateur(treeview_Firas,"Utilisateur.txt");


	}else if (verifierTypeUtilisateur(userNameEntred, passwordEntred) == 0 && (! checked_NotRobot) ){
 		gtk_label_set_text(GTK_LABEL(statusLabel),"Veillez verifiez que vous n'etes pas un robot ") ; 
	}else {
 		gtk_label_set_text(GTK_LABEL(statusLabel),"Utilisateur non valide ") ; 
	}
	

}


void
on_Refresh_button_achref_clicked       (GtkWidget       *graphic_object,
                                        gpointer         user_data)
{
		GtkWidget *actualWindow = lookup_widget(graphic_object , "espaceAdmin");
		GtkWidget *windowAdmin = create_espaceAdmin ();

  		gtk_widget_show (windowAdmin);		
		gtk_widget_destroy(actualWindow) ;


	        GtkWidget *treeview_Firas = lookup_widget(windowAdmin, "treeview_Firas");
    		vider(treeview_Firas);    
		afficher_utilisateur(treeview_Firas, "Utilisateur.txt");

		GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(windowAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;

}


/*******************/
gboolean
on_treeviewETS_achref_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
 
     if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        // Right-click handling code

        // Get the tree view
        GtkTreeView *tree_view = GTK_TREE_VIEW(widget);

        // Get the path and column at the clicked position
        GtkTreePath *path;
        GtkTreeViewColumn *column;
        gint cell_x, cell_y;
	
        if (gtk_tree_view_get_path_at_pos(tree_view, event->x, event->y, &path, &column, &cell_x, &cell_y)) {

            GtkWidget *menu = gtk_menu_new();
            GtkWidget *item_edit = gtk_menu_item_new_with_label("Edit");
            GtkWidget *item_add = gtk_menu_item_new_with_label("Add");
	    g_signal_connect(item_add, "activate", G_CALLBACK(on_AddETS_activate), tree_view);
            GtkWidget *item_delete = gtk_menu_item_new_with_label("Delete");
	    g_signal_connect(item_delete, "activate", G_CALLBACK(on_DeleteETS_activate), tree_view);


            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_edit);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_add);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_delete);

            gtk_widget_show_all(menu);

             gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, event->button, event->time);

            gtk_tree_path_free(path);

            return TRUE;
        }
    }

    return FALSE;

}  


void on_cell_ets_edited(GtkCellRendererText *cell, gchar *path_string, gchar *new_text, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    model = gtk_tree_view_get_model(treeview);

    // Convert the path string to a GtkTreeIter
    if (gtk_tree_model_get_iter_from_string(model, &iter, path_string)) {
        // Retrieve the column number directly from the cell renderer's property
        int column_number = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column-id"));

        // Convert the new text to an integer
        int new_capacite = atoi(new_text);

        // Assuming "Capacite" is the fourth column (index 3)
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, column_number, new_text, Capacite, new_capacite, -1);

        // Check if new_capacite is 0
        if (new_capacite == 0) {
            g_print("Error: Invalid Capacite value\n");
            // Handle the error or return from the function
            return;
        }

        gchar *nom, *adresse, *region;
	gint id ;

        // Assuming other columns are strings (replace with actual types if different)
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,ID,&id, Nom, &nom, Adresse, &adresse, Region, &region, -1);
	
// Check if any of the required fields are empty
    if ( strlen(nom) == 0 || strlen(adresse) == 0 ||
        strlen(region) == 0  || new_capacite == 0 )
    {
        // Display an error message or handle the case where not all fields are filled
        
        g_free(nom);
        g_free(adresse);
        g_free(region);
       
        return;
    }else {

    // Check if the ID already exists
    if (ChercherEts ("ets.txt", id ).ID != -1 ) {
	 // Modify the existing user

            // Assuming you have a Utilisateur structure
            ETS nouv;
            nouv.ID = id;
            strcpy(nouv.Nom, nom);
            strcpy(nouv.Adresse, adresse);
            strcpy(nouv.Region, region);
            nouv.Capacite = new_capacite ;


            // Call the modifier function with the modified ETS
            ModifierEts ("ets.txt", nouv,id ) ;
 
    }else{

        // Assuming you have a Utilisateur structure
        		ETS newETS;
			newETS.ID = id ;
        		strcpy(newETS.Nom, nom);
        		strcpy(newETS.Adresse, adresse);
        		strcpy(newETS.Region, region);
        		newETS.Capacite = new_capacite ;

        		add_ets(newETS) ; 

			
			g_free(nom);
			g_free(adresse);
			g_free(region);
			
    }
   }
}
}




void
on_editETS_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_DeleteETS_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
 GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);
	ETS newEts ;
    // Get the selected row
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Get the data from the row before removing it
	gint id , capacite ;
	gchar *nom,*adresse,*region ;

        gtk_tree_model_get(model, &iter,  ID,&id,  Nom,&nom,  Adresse ,&adresse,  Region , &region,  Capacite , &capacite, -1);
        // Remove the row from the model


	
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
	
        // Update 
	
	newEts.ID = id ;
	newEts.Capacite = capacite ;
	strcpy(newEts.Nom , nom ) ;
	strcpy(newEts.Adresse , adresse ) ;
	strcpy(newEts.Region , region ) ;
        delete_ets(newEts);
        

    }
}


void on_AddETS_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	 GtkTreeModel *model;
    GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));
    model = gtk_tree_view_get_model(tree_view);

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);

    int generatedID = generateID("ets.txt");
    gtk_list_store_set(store, &iter, ID, generatedID, Nom, "", Adresse, "", Region, "", Capacite, 0, -1);

    // Set the cursor to the newly added row
    gtk_tree_view_set_cursor(tree_view, gtk_tree_model_get_path(gtk_tree_view_get_model(tree_view), &iter), NULL, TRUE);
	
}




void
on_togglebutton_Fir_Pass_Ajout_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget *image = lookup_widget(togglebutton, "image28");
	GtkWidget *Password = lookup_widget(togglebutton, "entry_Firas_Pass");
	GtkWidget *togglebutton_Fir_Pass_Ajout = lookup_widget(togglebutton, "togglebutton_Fir_Pass_Ajout");

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton_Fir_Pass_Ajout))) {
	    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-open.png", NULL);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	    gtk_entry_set_visibility(GTK_ENTRY(Password), TRUE);
	} else {
	    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-closed.png", NULL);
	    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	    gtk_entry_set_visibility(GTK_ENTRY(Password), FALSE);
	}
}


void
on_togglebutton_Fir_Con_Ajout_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 	GtkImage *image = lookup_widget(togglebutton,"image29");
	GtkWidget*Password = lookup_widget(togglebutton,"entry_Firas_Confirm");
		GtkToggleButton *togglebutton_Fir_Con_Ajout= lookup_widget(togglebutton,"togglebutton_Fir_Con_Ajout");
    if (gtk_toggle_button_get_active(togglebutton_Fir_Con_Ajout)) {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-open.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 1);
    } else {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-closed.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 0);

    }
}


void
on_togglebutton_Fir_Pass_Modif_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkImage *image = lookup_widget(togglebutton,"image30");
	GtkWidget*Password = lookup_widget(togglebutton,"entry_Fir_Pass");
		GtkToggleButton *togglebutton_Fir_Pass_Modif= lookup_widget(togglebutton,"togglebutton_Fir_Pass_Modif");
    if (gtk_toggle_button_get_active(togglebutton_Fir_Pass_Modif)) {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-open.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 1);
    } else {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-closed.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 0);

    }
}


void
on_togglebutton_Fir_Con_Modif_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

 	GtkImage *image = lookup_widget(togglebutton,"image23");
	GtkWidget*Password = lookup_widget(togglebutton,"entry_Fir_Confirm");
		GtkToggleButton *togglebutton_Fir_Con_Modif= lookup_widget(togglebutton,"togglebutton_Fir_Con_Modif");
    if (gtk_toggle_button_get_active(togglebutton_Fir_Con_Modif)) {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-open.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 1);
    } else {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../pixmaps/eye-closed.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	gtk_entry_set_visibility(GTK_ENTRY(Password), 0);

    }
}


void
on_button_Retour_Supp_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Firas_Suppression = lookup_widget(GTK_WIDGET((GtkWidget*)button), "Firas_Suppression");
    gtk_widget_destroy(Firas_Suppression);

    GtkWidget *espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
		GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");
			GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
}


void
on_lum_button_admin_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

		GtkWidget* spin_contrast_admin = lookup_widget(objet_graphique,"spin_contrast_admin");
		GtkWidget *espaceAdmin= (lookup_widget(objet_graphique,"espaceAdmin") ) ;
			GtkWidget *notebook1= (lookup_widget(objet_graphique,"notebook1") ) ;
				
	

 int degre = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_contrast_admin));
  if (degre == 1 ) {
	apply_style_bg(espaceAdmin , "#1C1916") ;
	apply_style_bg(notebook1 , "#1C1916") ;
  }else if (degre ==  2) {
	apply_style_bg(espaceAdmin , "#4E4C4A") ;
	apply_style_bg(notebook1 , "#4E4C4A") ;

  }else if (degre == 3) {
	apply_style_bg(espaceAdmin , "#7F7C79") ;
	apply_style_bg(notebook1 , "#7F7C79") ;
  }else if (degre == 4){
	apply_style_bg(espaceAdmin , "#E0DEDC") ;
	apply_style_bg(notebook1 , "#E0DEDC") ;
  }else if (degre == 5){
	apply_style_bg(espaceAdmin , "#F3EEEA") ;
	apply_style_bg(notebook1 , "#F3EEEA") ;
  }

}

