#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "rdv.h"
#include <cairo.h>
#include <math.h>
#include "utilisateur.h"
#include <gtk/gtk.h>
#include "ets.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonction.h"
#include "yassAjoutRegister.h"
#include "yassVerifLogin.h"
#include "fonctions.h"
#include <unistd.h>




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
			GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ ID");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
		// controle capacite
		}else if (etablissement.ID != 0 && etablissement.Capacite == 0  && strcmp(etablissement.Nom ,"")!= 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
			GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ capacite");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
		//controle nom
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"")== 0 && strcmp(etablissement.Adresse ,"")!= 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
						GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ nom");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
		//controle adresse
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"")== 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL ) {	
						GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ adresse");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
		//controle region
		}else if (etablissement.ID != 0 && etablissement.Capacite != 0  && strcmp(etablissement.Nom ,"") != 0 && strcmp(etablissement.Adresse ,"") != 0 && gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL ) {	
						GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ region");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
		}else {

						GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir  tous les champs");
				    gtk_dialog_run(GTK_DIALOG(dialog));
				    gtk_widget_destroy(dialog);
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
		GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Etablissement non trouvee, Veilliez verifier l'id !");
		    gtk_dialog_run(GTK_DIALOG(dialog));
		    gtk_widget_destroy(dialog);
	}else if(ChercherEts ("ets.txt",ID).ID != -1) {
		//setting visibility 
		GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Veuilliez entrer vos modifications ");
		    gtk_dialog_run(GTK_DIALOG(dialog));
		    gtk_widget_destroy(dialog);

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


void on_button_confirmer_modifierEts_achref_clicked(GtkWidget *objet, gpointer user_data)
{
    ETS etablissement;
    GtkWidget *Modifier_ETS_achref = lookup_widget(objet, "Modifier_ETS_achref");
    GtkWidget *espaceAdmin = create_espaceAdmin();

    GtkWidget *input1, *input2, *input3, *input4, *input5, *output1;
    output1 = lookup_widget(objet, "ets_search_result_achref");

    input1 = lookup_widget(objet, "entry_Id_modifierEts_achref");
    input2 = lookup_widget(objet, "entry_nom_modifierEts_achref");
    input3 = lookup_widget(objet, "entry_adresse_modifierEts_achref");
    input4 = lookup_widget(objet, "combo_region_modifierEts_achref");
    input5 = lookup_widget(objet, "spinbutton_capacite_modifierEts_achref");

    etablissement.ID = atoi(gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(etablissement.Nom, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(etablissement.Adresse, gtk_entry_get_text(GTK_ENTRY(input3)));
    if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) != NULL)
    {
        strcpy(etablissement.Region, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
    }
    etablissement.Capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));

    // Check if any of the required fields are empty
    if (etablissement.ID == 0)
    {
	GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Veuillez remplir le champ ID");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
        return;
    }

    if (etablissement.Capacite == 0)
    {
	GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Veuillez remplir le champ Capacite");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
        return;
    }

    if (strcmp(etablissement.Nom, "") == 0)
    {
	GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                 "Veuillez remplir le champ Nom");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
        return;
    }

    if (strcmp(etablissement.Adresse, "") == 0)
    {
	GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
						"Veuillez remplir le champ Adresse");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
        return;
    }

    if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) == NULL)
    {
	GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                                "Veuillez remplir le champ Region" );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
        return;
    }

    // All fields are filled, proceed with modification
    ModifierEts("ets.txt", etablissement, etablissement.ID);
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));
    display_ets(treeview, "ets.txt");
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
    gtk_widget_show(espaceAdmin);
    gtk_widget_hide(Modifier_ETS_achref);
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

void on_button_confirmer_deleteEts_achref_clicked(GtkWidget *objet, gpointer user_data)
{
    int id;
    GtkWidget *input1 = lookup_widget(objet, "entry_deleteEts_id_achref");
    id = atoi(gtk_entry_get_text(GTK_ENTRY(input1)));

    if (ChercherEts("ets.txt", id).ID == -1)
    {
        GtkWidget *error_dialog = gtk_message_dialog_new(NULL,
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Etablissement non trouvé");
        gtk_window_set_title(GTK_WINDOW(error_dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
    else
    {
        GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_QUESTION,
                                                           GTK_BUTTONS_OK_CANCEL,
                                                           "Voulez-vous vraiment supprimer cet établissement ?");
        gtk_window_set_title(GTK_WINDOW(confirm_dialog), "Confirmation");

        gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
        gtk_widget_destroy(confirm_dialog);

        if (response == GTK_RESPONSE_OK)
        {
            // Delete the ETS
            SupprimerEts(id);

            GtkWidget *success_dialog = gtk_message_dialog_new(NULL,
                                                              GTK_DIALOG_MODAL,
                                                              GTK_MESSAGE_INFO,
                                                              GTK_BUTTONS_OK,
                                                              "Etablissement supprimé avec succès");
            gtk_window_set_title(GTK_WINDOW(success_dialog), "Succès");
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
            GtkWidget *espaceAdmin = create_espaceAdmin();
            gtk_widget_show(espaceAdmin);
            GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));
            display_ets(treeview, "ets.txt");

            GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
            afficher_utilisateur(treeview_Firas, "Utilisateur.txt");
            GtkWidget *DeleteEts_achref = lookup_widget(objet, "DeleteEts_achref");
            gtk_widget_hide(DeleteEts_achref);
        }
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

    char confirm[20];

    if  (strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_ID)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Nom)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Prenom)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Pass)), "") == 0 ||
        strcmp(gtk_entry_get_text(GTK_ENTRY(entry_Firas_Confirm)), "") == 0 || (choix_role[0]!=1 && choix_role[1]!=1 && choix_role[2]!=1) ||(choix_sexe[0]!=1 && choix_sexe[1]!=1))
    {
        // Show an error dialog
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Veuillez remplir tous les champs!");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else
    {
      if ( (choix_role[0]==1 && choix_role[1]==1) ||(choix_role[1]==1 && choix_role[2]==1 ) ||(choix_role[0]==1 && choix_role[2]==1) || (choix_role[0]==1 &&      choix_role[1]==1 && choix_role[2]==1 ) ) {
	    
	    // Show an error dialog for not selecting a role
	    GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
		                                            GTK_DIALOG_MODAL,
		                                            GTK_MESSAGE_ERROR,
		                                            GTK_BUTTONS_OK,
		                                            "Veuillez choisir un rôle!");

	    gtk_dialog_run(GTK_DIALOG(errorDialog));
	    gtk_widget_destroy(errorDialog);
	    return;  
	}

        Utilisateur new_user;
        strcpy(new_user.ID, gtk_entry_get_text(GTK_ENTRY(entry_Firas_ID)));
        strcpy(new_user.Nom, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Nom)));
        strcpy(new_user.Prenom, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Prenom)));
        strcpy(new_user.Password, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Pass)));
        new_user.D = get_date_from_entry(GTK_ENTRY(entry_sabeh_Date));
        strcpy(new_user.Sexe, Sexe(choix_sexe));
        strcpy(new_user.Role, Role(choix_role));
        strcpy(confirm, gtk_entry_get_text(GTK_ENTRY(entry_Firas_Confirm)));

        // Check if ID is a number using atoi
        if (atoi(new_user.ID) == 0)
        {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : ID doit être un nombre");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
        }
        else
        {
            if (strcmp(new_user.Password, confirm) != 0)
            {
                // Show an error dialog
                GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                                GTK_DIALOG_MODAL,
                                                                GTK_MESSAGE_ERROR,
                                                                GTK_BUTTONS_OK,
                                                                "Erreur : Mot de passe non identique");

                gtk_dialog_run(GTK_DIALOG(errorDialog));
                gtk_widget_destroy(errorDialog);
            }
            else
            {
                if (is_ID_exists(new_user.ID))
                {
                    // Show an error dialog
                    GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                                    GTK_DIALOG_MODAL,
                                                                    GTK_MESSAGE_ERROR,
                                                                    GTK_BUTTONS_OK,
                                                                    "Erreur : ID déjà existant");

                    gtk_dialog_run(GTK_DIALOG(errorDialog));
                    gtk_widget_destroy(errorDialog);
                }
                else
                {
                    // Show confirmation dialog
                    GtkWidget *confirmationDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                                         GTK_DIALOG_MODAL,
                                                                         GTK_MESSAGE_QUESTION,
                                                                         GTK_BUTTONS_YES_NO,
                                                                         "Confirmez-vous l'ajout de l'utilisateur ?");

                    gint result = gtk_dialog_run(GTK_DIALOG(confirmationDialog));

                    // Handle user response
                    if (result == GTK_RESPONSE_YES)
                    {
                        ajouter(new_user);

                        // Clear entry fields
                        gtk_entry_set_text(GTK_ENTRY(entry_Firas_ID), "");
                        gtk_entry_set_text(GTK_ENTRY(entry_Firas_Nom), "");
                        gtk_entry_set_text(GTK_ENTRY(entry_Firas_Prenom), "");
                        gtk_entry_set_text(GTK_ENTRY(entry_sabeh_Date), "");
                        gtk_entry_set_text(GTK_ENTRY(entry_Firas_Pass), "");
                        gtk_entry_set_text(GTK_ENTRY(entry_Firas_Confirm), "");

                        // Show a success dialog
                        GtkWidget *successDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                                         GTK_DIALOG_MODAL,
                                                                         GTK_MESSAGE_INFO,
                                                                         GTK_BUTTONS_OK,
                                                                         "Utilisateur ajouté avec succès!");

                        gtk_dialog_run(GTK_DIALOG(successDialog));
                        gtk_widget_destroy(successDialog);

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

                    gtk_widget_destroy(confirmationDialog);
                }
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

    date_str = g_strdup_printf("%02d-%02d-%04d", year, month + 1, day);

    gtk_entry_set_text(GTK_ENTRY(entry_sabeh_Date), date_str);
    g_free(date_str);
}



void on_button_Firas_SuppID_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *entry_Firas_SuppID = lookup_widget(objet_graphique, "entry_Firas_SuppID");

    char id[30];
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_Firas_SuppID)));


    Utilisateur U;

    U = verifier(id);
    if (strcmp(U.ID, "-1") != 0)
    {
        // Ask for confirmation
        GtkWidget *confirmDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_QUESTION,
                                                          GTK_BUTTONS_YES_NO,
                                                          "Voulez-vous vraiment supprimer cet utilisateur ?");
        int result = gtk_dialog_run(GTK_DIALOG(confirmDialog));
        gtk_widget_destroy(confirmDialog);

        if (result == GTK_RESPONSE_YES)
        {
            if (supprimer_utilisateur(id) == 1)
            {
                // Show a success dialog
                GtkWidget *successDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                                 GTK_DIALOG_MODAL,
                                                                 GTK_MESSAGE_INFO,
                                                                 GTK_BUTTONS_OK,
                                                                 "Utilisateur supprimé avec succès!");

                gtk_dialog_run(GTK_DIALOG(successDialog));
                gtk_widget_destroy(successDialog);

                       GtkWidget *Firas_Suppression = lookup_widget(objet_graphique, "Firas_Suppression");
    		       gtk_widget_destroy(Firas_Suppression);

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
        }
    }
    else
    {

        // Show an error dialog for user not found
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Utilisateur non trouvé");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
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
    GtkToggleButton *togglebutton_Fir_Pass_Modif = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique, "togglebutton_Fir_Pass_Modif"));
    GtkToggleButton *togglebutton_Fir_Con_Modif = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique, "togglebutton_Fir_Con_Modif"));
    GtkImage *image = GTK_IMAGE(lookup_widget(objet_graphique, "image22"));
    GtkImage *image1 = GTK_IMAGE(lookup_widget(objet_graphique, "image23"));


    char entry_id[30];
    strcpy(entry_id, gtk_entry_get_text(GTK_ENTRY(entry_Fir_ID)));

    Utilisateur U;
    U = verifier(entry_id);

    if (strcmp(U.ID, "-1") != 0)
    {
        // Create a confirmation dialog
        GtkWidget *confirmDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_QUESTION,
                                                          GTK_BUTTONS_OK_CANCEL,
                                                          "Êtes-vous sûr de vouloir modifier cet utilisateur ?");
        gtk_window_set_title(GTK_WINDOW(confirmDialog), "Confirmation");

        gint result = gtk_dialog_run(GTK_DIALOG(confirmDialog));

        if (result == GTK_RESPONSE_OK)
        {
            // User clicked OK, proceed with modification

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
        }
        else
        {
            
            gtk_widget_destroy(confirmDialog);
            return;
        }

        gtk_widget_destroy(confirmDialog);
    }
    else
    {

        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Error: User not found");
        gtk_window_set_title(GTK_WINDOW(errorDialog), "Error");

        gint result = gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
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
    gdk_color_parse("#FF0000", &color);
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
        // Show an error dialog
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Veuillez sélectionner un sexe!");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    const gchar *selectedRole = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_Fir_Role));
    if (selectedRole != NULL) {
        strncpy(new_user.Role, selectedRole, sizeof(new_user.Role) - 1);
        new_user.Role[sizeof(new_user.Role) - 1] = '\0';
    } else {
        // Show an error dialog
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Veuillez sélectionner un rôle!");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
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
        // Show an error dialog
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Veuillez remplir tous les champs!");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    if (strcmp(new_user.Password, confirm) == 0) {
        int result = modifier(entry_id, new_user);

        if (result == 1) {
            // Show a success dialog
            GtkWidget *successDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                              GTK_DIALOG_MODAL,
                                                              GTK_MESSAGE_INFO,
                                                              GTK_BUTTONS_OK,
                                                              "Utilisateur modifié avec succès!");

            gtk_dialog_run(GTK_DIALOG(successDialog));
            gtk_widget_destroy(successDialog);

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
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur lors de la modification");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
        }
    } else {
        // Show an error dialog
        GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Mot de passe non identique");

        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
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

    date_str = g_strdup_printf("%02d-%02d-%04d", year, month + 1, day);

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





gboolean
on_treeview_Firas_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
 
     if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        GtkTreeView *tree_view = GTK_TREE_VIEW(widget);

        // Get the path and column at the clicked position
        GtkTreePath *path;
        GtkTreeViewColumn *column;
        gint cell_x, cell_y;

        if (gtk_tree_view_get_path_at_pos(tree_view, event->x, event->y, &path, &column, &cell_x, &cell_y)) {
            GtkWidget *menu = gtk_menu_new();

            // Edit item
            GtkWidget *item_edit = gtk_menu_item_new_with_label("Edit");
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_edit);

            // Add item
            GtkWidget *item_add = gtk_menu_item_new_with_label("Add");
            g_signal_connect(item_add, "activate", G_CALLBACK(on_Add_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_add);

            // Delete item
            GtkWidget *item_delete = gtk_menu_item_new_with_label("Delete");
            g_signal_connect(item_delete, "activate", G_CALLBACK(on_Delete_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_delete);

            // Copy item
            GtkWidget *item_copy = gtk_menu_item_new_with_label("Copy");
            g_signal_connect(item_copy, "activate", G_CALLBACK(on_Copy_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_copy);

            // Paste item
            GtkWidget *item_paste = gtk_menu_item_new_with_label("Paste");
            g_signal_connect(item_paste, "activate", G_CALLBACK(on_Paste_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_paste);

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

	// Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Veuillez remplir tous les champs!");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
        return;
    }

    // Check if the ID already exists
    else if (is_ID_exists(id)) {
	 // Modify the existing user
           if (atoi(id) == 0)
        {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : ID doit être un nombre");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }

	if ((strcmp(sexe,"Homme") != 0 )&& (strcmp(sexe,"Femme") != 0))
        {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : Il faut taper Homme or Femme");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }

	if((strcmp(role,"Medecin Biologiste") != 0) && (strcmp(role,"Infirmier") != 0 )&& (strcmp(role,"Responsable ETS") !=0))
          {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : Il faut taper Medecin Biologiste ou Infirmier ou Responsable ETS ");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }
        
	
            // Assuming you have a Utilisateur structure
            Utilisateur nouv;
            strcpy(nouv.ID, id);
            strcpy(nouv.Nom, nom);
            strcpy(nouv.Prenom, prenom);
            strcpy(nouv.Sexe, sexe);
            strcpy(nouv.Role, role);

            
            sscanf(date, "%02d-%02d-%d", &nouv.D.day, &nouv.D.month, &nouv.D.year);

            strcpy(nouv.Password, password);

		// Show a confirmation dialog
		GtkWidget *confirmationDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
				                                     GTK_DIALOG_MODAL,
				                                     GTK_MESSAGE_QUESTION,
				                                     GTK_BUTTONS_OK_CANCEL,
				                                     "Confirmez-vous la modification de l'utilisateur ?");

		gint result = gtk_dialog_run(GTK_DIALOG(confirmationDialog));

		// Handle user response
		if (result == GTK_RESPONSE_OK) {
		    // Call the modifier function with the modified Utilisateur
		    modifier(id, nouv);

		    // Show a success editing dialog
		    GtkWidget *successEditDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
				                                          GTK_DIALOG_MODAL,
				                                          GTK_MESSAGE_INFO,
				                                          GTK_BUTTONS_OK,
				                                          "Utilisateur modifié avec succès!");

		    gtk_dialog_run(GTK_DIALOG(successEditDialog));
		    gtk_widget_destroy(successEditDialog);
		}

		gtk_widget_destroy(confirmationDialog);
 
    } else{

	  if (atoi(id) == 0)
        {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : ID doit être un nombre");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }

	if ((strcmp(sexe,"Homme") != 0) && (strcmp(sexe,"Femme") != 0))
        {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : Il faut taper Homme or Femme");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }

	if((strcmp(role,"Medecin Biologiste") != 0) && (strcmp(role,"Infirmier") != 0) && (strcmp(role,"Responsable ETS") !=0))
          {
            // Show an error dialog
            GtkWidget *errorDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_OK,
                                                            "Erreur : Il faut taper Medecin Biologiste ou Infirmier ou Responsable ETS ");

            gtk_dialog_run(GTK_DIALOG(errorDialog));
            gtk_widget_destroy(errorDialog);
		return;
        }

        // Assuming you have a Utilisateur structure
        		Utilisateur nouv;
        		strcpy(nouv.ID, id);
        		strcpy(nouv.Nom, nom);
        		strcpy(nouv.Prenom, prenom);
        		strcpy(nouv.Sexe, sexe);
        		strcpy(nouv.Role, role);

        //g_snprintf(date, sizeof(date), "%d-%02d-%02d", U.D.year, U.D.month, U.D.day);
			sscanf(date, "%d-%d-%d", &nouv.D.year, &nouv.D.month, &nouv.D.day);

        		strcpy(nouv.Password, password);

	
 	// Call the ajouter function with the new Utilisateur
        		ajouter(nouv);
		
			 // Show a success adding dialog
            GtkWidget *successAddDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                                 GTK_DIALOG_MODAL,
                                                                 GTK_MESSAGE_INFO,
                                                                 GTK_BUTTONS_OK,
                                                                 "Utilisateur ajouté avec succès!");

            gtk_dialog_run(GTK_DIALOG(successAddDialog));
            gtk_widget_destroy(successAddDialog);


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


void on_Delete_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);

    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gchar *ID;

        gtk_tree_model_get(model, &iter, IDENTIFIANT, &ID, -1);

        GtkWidget *confirmationDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(tree_view))),
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_QUESTION,
                                                               GTK_BUTTONS_YES_NO,
                                                               "Voulez-vous vraiment supprimer cet utilisateur ?");

        // Run the dialog and act based on the response
        switch (gtk_dialog_run(GTK_DIALOG(confirmationDialog)))
        {
        case GTK_RESPONSE_YES:
            gtk_widget_destroy(confirmationDialog);

            // Remove the selected row from the model
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Call the function to delete the user
            int find = supprimer_utilisateur(ID);

            g_free(ID);

            if (find)
            {
                // Handle successful deletion
                GtkWidget *successDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(tree_view))),
                                                                  GTK_DIALOG_MODAL,
                                                                  GTK_MESSAGE_INFO,
                                                                  GTK_BUTTONS_OK,
                                                                  "Utilisateur supprimé avec succès!");

                // Run the success dialog
                gtk_dialog_run(GTK_DIALOG(successDialog));

                // Destroy the success dialog after the user clicks OK
                gtk_widget_destroy(successDialog);
            }
            break;

        case GTK_RESPONSE_NO:
            gtk_widget_destroy(confirmationDialog);
            break;
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


	}else if (verifierTypeUtilisateur(userNameEntred, passwordEntred) == 1 && ( checked_NotRobot) ){
 		  GtkWidget *Espace_Infirmier = create_Espace_Infirmier();
  
		  GtkWidget *actualWindow = lookup_widget(graphic_object , "windowAuthentification");
		  gtk_widget_destroy(actualWindow) ;
		  gtk_widget_show (Espace_Infirmier);

	}else if (verifierTypeUtilisateur(userNameEntred, passwordEntred) == 2 && ( checked_NotRobot) ){
		GtkWidget *yasmine_home_window = create_yasmine_home_window();
		
		GtkWidget *actualWindow = lookup_widget(graphic_object , "windowAuthentification");
		gtk_widget_destroy(actualWindow) ;

		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
		gtk_widget_show (yasmine_home_window);

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

		            // Copy item
            GtkWidget *item_copy = gtk_menu_item_new_with_label("Copy");
            g_signal_connect(item_copy, "activate", G_CALLBACK(on_copyETS_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_copy);

            // Paste item
            GtkWidget *item_paste = gtk_menu_item_new_with_label("Paste");
            g_signal_connect(item_paste, "activate", G_CALLBACK(on_PasteETS_activate), tree_view);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_paste);


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

/*
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
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,ID, &id, Nom, &nom, Adresse, &adresse, Region, &region, -1);
	
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
*/
void on_cell_ets_edited(GtkCellRendererText *cell, gchar *path_string, gchar *new_text, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    model = gtk_tree_view_get_model(treeview);

    // Convert the path string to a GtkTreeIter
    if (gtk_tree_model_get_iter_from_string(model, &iter, path_string))
    {
        // Retrieve the column number directly from the cell renderer's property
        int column_number = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column-id"));

        // Convert the new text to an integer
        int new_capacite = atoi(new_text);

        // Assuming "Capacite" is the fourth column (index 3)
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, column_number, new_text, Capacite, new_capacite, -1);

        // Check if new_capacite is 0
        if (new_capacite == 0)
        {
            g_print("Error: Invalid Capacite value\n");
            // Display an error dialog
            GtkWidget *error_dialog = gtk_message_dialog_new(NULL,
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Invalid Capacite value");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
            // Handle the error or return from the function
            return;
        }

         gchar *nom, *adresse, *region;
         gint id;

        // Assuming other columns are strings (replace with actual types if different)
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, ID, &id, Nom, &nom, Adresse, &adresse, Region, &region, -1);

        // Check if any of the required fields are empty
        if (strlen(nom) == 0 || strlen(adresse) == 0 ||
            strlen(region) == 0 || new_capacite == 0)
        {
            // Display an error dialog
            GtkWidget *error_dialog = gtk_message_dialog_new(NULL,
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Please fill in all fields");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);

            g_free(nom);
            g_free(adresse);
            g_free(region);

            return;
        }
        else
        {

            // Check if the ID already exists
            if (ChercherEts("ets.txt", id).ID != -1)
            {
                // Display a confirmation dialog
                GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
                                                                   GTK_DIALOG_MODAL,
                                                                   GTK_MESSAGE_QUESTION,
                                                                   GTK_BUTTONS_OK_CANCEL,
                                                                   "Are you sure you want to modify this item?");
                gtk_window_set_title(GTK_WINDOW(confirm_dialog), "Confirmation");

                gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
                gtk_widget_destroy(confirm_dialog);

                // Modify the existing ETS if confirmed
                if (response == GTK_RESPONSE_OK)
                {
                    // Assuming you have an ETS structure
                    ETS nouv;
                    nouv.ID = id;
                    strcpy(nouv.Nom, nom);
                    strcpy(nouv.Adresse, adresse);
                    strcpy(nouv.Region, region);
                    nouv.Capacite = new_capacite;

                    // Call the modifier function with the modified ETS
                    ModifierEts("ets.txt", nouv, id);
                }
            }
            else
            {

                // Display a confirmation dialog
                GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
                                                                   GTK_DIALOG_MODAL,
                                                                   GTK_MESSAGE_QUESTION,
                                                                   GTK_BUTTONS_OK_CANCEL,
                                                                   "Are you sure you want to add this item?");
                gtk_window_set_title(GTK_WINDOW(confirm_dialog), "Confirmation");

                gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
                gtk_widget_destroy(confirm_dialog);

                // Add the new ETS if confirmed
                if (response == GTK_RESPONSE_OK)
                {
                    // Assuming you have an ETS structure
                    ETS newETS;
                    newETS.ID = id;
                    strcpy(newETS.Nom, nom);
                    strcpy(newETS.Adresse, adresse);
                    strcpy(newETS.Region, region);
                    newETS.Capacite = new_capacite;

                    add_ets(newETS);
                }

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


void on_DeleteETS_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkTreeView *tree_view = GTK_TREE_VIEW(user_data);
    ETS newEts;

    // Get the selected row
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        // Get the data from the row before removing it
        gint id, capacite;
        gchar *nom, *adresse, *region;

        gtk_tree_model_get(model, &iter, ID, &id, Nom, &nom, Adresse, &adresse, Region, &region, Capacite, &capacite, -1);

        // Create a confirmation dialog
        GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_QUESTION,
                                                           GTK_BUTTONS_OK_CANCEL,
                                                           "Are you sure you want to delete the selected item?");
        gtk_window_set_title(GTK_WINDOW(confirm_dialog), "Confirmation");

        // Run the dialog and check the response
        gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
        gtk_widget_destroy(confirm_dialog);

        if (response == GTK_RESPONSE_OK)
        {
            // Remove the row from the model
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Update
            newEts.ID = id;
            newEts.Capacite = capacite;
            strcpy(newEts.Nom, nom);
            strcpy(newEts.Adresse, adresse);
            strcpy(newEts.Region, region);
            delete_ets(newEts);

            // Display a successful deletion dialog
            GtkWidget *success_dialog = gtk_message_dialog_new(NULL,
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_INFO,
                                                               GTK_BUTTONS_OK,
                                                               "Deletion successful!");
            gtk_window_set_title(GTK_WINDOW(success_dialog), "Success");
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        }
 
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
	ETSTrieIDCroiss("ets.txt") ; 
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


void
on_button_search_firas_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *espaceAdmin, *w1;

    w1 = lookup_widget(objet_graphique, "espaceAdmin");
    espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
    gtk_widget_hide(w1);
			GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 1);

    GtkWidget *entry_search_firas = lookup_widget(objet_graphique, "entry_search_firas");

    const char *selected = gtk_entry_get_text(GTK_ENTRY(entry_search_firas));

    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    vider(treeview_Firas);

	search_character("Utilisateur.txt",selected);
	afficher_utilisateur(treeview_Firas,"searchedUsers.txt");
}

int currentMode = 0;

gboolean
on_drawingarea_Firas_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{

    cairo_t *cr = gdk_cairo_create(widget->window);

    int nbHomme, nbFemme, totalUsers, nbMedecine, nbInfimier, nbResponsable;
    const char *title;
    const char *legend1, *legend2, *legend3;

    if (currentMode == 0) {
        pourcentageUser("Utilisateur.txt", &nbHomme, &nbFemme);
        totalUsers = nbHomme + nbFemme;
        title = "Gender Distribution";
        legend1 = "Homme";
        legend2 = "Femme";
        legend3 = NULL;  
    } else {
        countUsersByRole("Utilisateur.txt", &nbMedecine, &nbInfimier, &nbResponsable);
        totalUsers = nbMedecine + nbInfimier + nbResponsable;
        title = "Role Distribution";
        legend1 = "Med";
        legend2 = "Inf";
        legend3 = "Res";
    }

    int width = gdk_window_get_width(widget->window);
    int height = gdk_window_get_height(widget->window);

    int barWidth = 50;
    int barGap = 30; 
    int maxBarHeight = height - 80; // Adjusted to make space for axis labels and title

    // Draw Y-axis
    cairo_set_source_rgb(cr, 0, 0, 0); // Black
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, 60, 30); // Adjusted starting point for Y-axis
    cairo_line_to(cr, 60, height - 50); // Adjusted end point for Y-axis
    cairo_stroke(cr);

    // Draw X-axis
    cairo_move_to(cr, 60, height - 50);
    cairo_line_to(cr, width - 20, height - 50);
    cairo_stroke(cr);

    // Axis labels
    cairo_set_source_rgb(cr, 0, 0, 0); // Black
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD); // Bold text
    cairo_set_font_size(cr, 12);

    // X-axis label
    const char *xAxisLabel;
    if (currentMode == 0) {
        xAxisLabel = "Gender";
    } else {
        xAxisLabel = "Role";
    }
    cairo_move_to(cr, (width - 20) / 2, height - 30);
    cairo_show_text(cr, xAxisLabel);

    // Y-axis label
    cairo_rotate(cr, -M_PI_2); // Rotate the context for vertical text
    cairo_move_to(cr, -height / 2, 40); // Adjusted coordinates for Y-axis label
    cairo_show_text(cr, "Percentage");
    cairo_rotate(cr, M_PI_2); // Rotate back to normal

    // Title
    cairo_set_source_rgb(cr, 0, 1, 0); // Green
    cairo_move_to(cr, (width - 20) / 2 - 100, 20); // Adjusted coordinates for title
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 16);
    cairo_show_text(cr, title);

    // Underline for the title
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr, (width - 20) / 2 - 100, 25);
    cairo_line_to(cr, (width - 20) / 2 + 80, 25);
    cairo_stroke(cr);

    // Draw grid lines
    cairo_set_source_rgba(cr, 0.8, 0.8, 0.8, 0.5); // Light gray, semi-transparent
    cairo_set_line_width(cr, 0.5);

    // Horizontal grid lines
    for (int i = 20; i <= maxBarHeight; i += 20) {
        cairo_move_to(cr, 60, height - 50 - i);
        cairo_line_to(cr, width - 20, height - 50 - i);
    }

    // Vertical grid lines
    for (int i = 60; i <= width - 20; i += barWidth + barGap) {
        cairo_move_to(cr, i, height - 50);
        cairo_line_to(cr, i, 30);
    }

    cairo_stroke(cr);

    // Calculate bar heights
    int barHeightHomme = 0;
    int barHeightFemme = 0;
    int barHeightResponsable = 0;

    // Check for zero division
    if (totalUsers != 0) {
        barHeightHomme = -(currentMode == 0 ? nbHomme : nbMedecine) * maxBarHeight / totalUsers;
        barHeightFemme = -(currentMode == 0 ? nbFemme : nbInfimier) * maxBarHeight / totalUsers;

        if (currentMode == 1) {
            barHeightResponsable = -nbResponsable * maxBarHeight / totalUsers;
        }
    }

    // Draw bars based on the current mode
    // Blue for Homme or Medecine
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_rectangle(cr, (width - (barWidth + barGap) * 2) / 2, height - 50, barWidth, barHeightHomme);
    cairo_fill(cr);

    // Display percentage on top of the "Homme" or "Medecine" bar
    if (totalUsers != 0) {
           cairo_set_source_rgb(cr, 0, 0, 1); // Blue
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD); // Bold text
    cairo_set_font_size(cr, 10);
    cairo_move_to(cr, (width - (barWidth + barGap) * 2) / 2 + barWidth / 2 - 10, height - 50 - (currentMode == 0 ? nbHomme : nbMedecine) * maxBarHeight / totalUsers - 5);
    cairo_show_text(cr, g_strdup_printf("%d%%", (currentMode == 0 ? nbHomme : nbMedecine) * 100 / totalUsers));
	}

    // Red for Femme or Infimier
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, (width - (barWidth + barGap) * 2) / 2 + barWidth + barGap, height - 50, barWidth, barHeightFemme);
    cairo_fill(cr);

    // Display percentage on top of the "Femme" or "Infimier" bar
    if (totalUsers != 0) {
       cairo_set_source_rgb(cr, 1, 0, 0); // Red
    cairo_set_font_size(cr, 10);
    cairo_move_to(cr, (width - (barWidth + barGap) * 2) / 2 + barWidth + barGap + barWidth / 2 - 10, height - 50 - (currentMode == 0 ? nbFemme : nbInfimier) * maxBarHeight / totalUsers - 5);
    cairo_show_text(cr, g_strdup_printf("%d%%", (currentMode == 0 ? nbFemme : nbInfimier) * 100 / totalUsers));
    }

    if (currentMode == 1) {
        // Yellow for Responsable
        cairo_set_source_rgb(cr, 1, 1, 0); // Yellow
        cairo_rectangle(cr, (width - (barWidth + barGap) * 2) / 2 + 2 * (barWidth + barGap), height - 50, barWidth, barHeightResponsable);
        cairo_fill(cr);

        // Display percentage on top of the "Responsable" bar
        if (totalUsers != 0) {
            cairo_set_source_rgb(cr, 1, 1, 0); // Yellow
        cairo_set_font_size(cr, 10);
        cairo_move_to(cr, (width - (barWidth + barGap) * 2) / 2 + 2 * (barWidth + barGap) + barWidth / 2 - 10, height - 50 - nbResponsable * maxBarHeight / totalUsers - 5);
        cairo_show_text(cr, g_strdup_printf("%d%%", nbResponsable * 100 / totalUsers));
        }
    }

    // Total number of users
    cairo_set_source_rgb(cr, 0, 0, 0); // Black
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD); // Bold text
    cairo_set_font_size(cr, 12);
    cairo_move_to(cr, width - 20 - 100, height / 2); // Adjusted coordinates for total users
    cairo_show_text(cr, g_strdup_printf("Total Users: %d", totalUsers));

    // Add numbering to the Y-axis
    for (int i = 0; i <= 100; i += 20) {
        cairo_move_to(cr, 50, height - 50 - (i * maxBarHeight) / 100);
        cairo_show_text(cr, g_strdup_printf("%d%%", i));
    }

    // Draw legends based on the current mode
    // Legend for "Homme" or "Medecine"
    cairo_set_source_rgb(cr, 0, 0, 1); // Blue
    cairo_rectangle(cr, width - 80, 30, 15, 15);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0, 0, 0); // Black
    cairo_move_to(cr, width - 60, 40);
    cairo_show_text(cr, legend1);

    // Legend for "Femme" or "Infimier"
    cairo_set_source_rgb(cr, 1, 0, 0); // Red
    cairo_rectangle(cr, width - 80, 50, 15, 15);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0, 0, 0); // Black
    cairo_move_to(cr, width - 60, 60);
    cairo_show_text(cr, legend2);

    if (currentMode == 1) {
        // Legend for "Responsable"
        cairo_set_source_rgb(cr, 1, 1, 0); // Green
        cairo_rectangle(cr, width - 80, 70, 15, 15);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 0, 0, 0); // Black
        cairo_move_to(cr, width - 60, 80);
        cairo_show_text(cr, legend3);
    }

    cairo_destroy(cr);
    return FALSE;
}


void
on_togglebutton_Firas_clicked  (GtkWidget *objet_graphique,gpointer user_data)
{
      GtkDrawingArea *drawingarea_Firas = GTK_DRAWING_AREA(user_data);
    GtkToggleButton *togglebutton_Firas = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique, "togglebutton_Firas"));
   
        currentMode = (currentMode + 1) % 2;

    GtkWidget *espaceAdmin, *w1;

	w1 = lookup_widget(objet_graphique, "espaceAdmin");
	espaceAdmin = create_espaceAdmin();
	gtk_widget_show(espaceAdmin);
	gtk_widget_hide(w1);

       
        GtkNotebook *notebook1 = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook1, 2);
	GtkNotebook *notebook2 = lookup_widget(espaceAdmin, "notebook2");
	gtk_notebook_set_current_page(notebook2, 0); 
	GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(espaceAdmin, "treeviewETS_achref"));	
		display_ets(treeview,"ets.txt") ;
    GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
    afficher_utilisateur(treeview_Firas,"Utilisateur.txt");	
}





gboolean
on_fixed_stat_ets_proximity_in_event   (GtkWidget       *widget,
                                        GdkEventProximity *event,
                                        gpointer         user_data)
{
	
  return FALSE;
}







gboolean
on_label_stat_achref_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
g_print("in stat") ; 
int totalETS =statETs( );
GtkTreeView *treeviewStats = GTK_TREE_VIEW(lookup_widget(widget, "treeviewStatEts"));	
		
 display_ets_Stat(treeviewStats , "statEts.txt") ;
char nbTOstr[10] ;
sprintf(nbTOstr , "%d",totalETS) ;
GtkWidget *label = lookup_widget(widget, "label_totalNB_container");
gtk_label_set_text(GTK_LABEL(label), nbTOstr);
  return FALSE;
}


void
on_buttonSearchEts_clicked             (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *espaceAdmin, *w1;

    w1 = lookup_widget(button, "espaceAdmin");
    espaceAdmin = create_espaceAdmin();
    gtk_widget_show(espaceAdmin);
    gtk_widget_hide(w1);
			GtkNotebook *notebook = lookup_widget(espaceAdmin, "notebook1");
	gtk_notebook_set_current_page(notebook, 0);

    GtkWidget *entrySearchBoxEts = lookup_widget(button, "entrySearchBoxEts");

    const char *selected = gtk_entry_get_text(GTK_ENTRY(entrySearchBoxEts));

    GtkWidget *treeviewETS_achref = lookup_widget(espaceAdmin, "treeviewETS_achref");
	searcherETS("ets.txt",selected);
	display_ets(treeviewETS_achref,"searchResult.txt") ;

	GtkWidget *treeview_Firas = lookup_widget(espaceAdmin, "treeview_Firas");
        afficher_utilisateur(treeview_Firas,"Utilisateur.txt");

}

GtkTreeIter copyIter;
void
on_Copy_activate (GtkMenuItem *menuitem, gpointer user_data)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
     GtkTreeModel *model;
    GtkTreeSelection *selection;
    GList *rows, *current;
    
    // Assuming 'treeview' is a globally defined GtkWidget pointer to your GtkTreeView
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (gtk_tree_selection_count_selected_rows(selection) > 0) {
        rows = gtk_tree_selection_get_selected_rows(selection, &model);

        // For simplicity, we'll consider only the first selected row
        GtkTreePath *path = (GtkTreePath *)rows->data;

        gtk_tree_model_get_iter(model, &copyIter, path);

        // Free the list of selected rows
        g_list_free_full(rows, (GDestroyNotify)gtk_tree_path_free);
    }
}


void
on_Paste_activate (GtkMenuItem *menuitem, gpointer user_data)
{
GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    GtkTreeModel *model;
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    // Check if there's copied data
    if (gtk_tree_model_iter_n_children(model, NULL) > 0)
    {
        // Append a new row
        gtk_list_store_append(store, &iter);

        // Get the copied data and set it in the new row
        gchar *ID, *nom, *prenom, *sexe, *role, *date, *password;
        gtk_tree_model_get(model, &copyIter, IDENTIFIANT, &ID, NOM, &nom, PRENOM, &prenom, SEXE, &sexe, ROLE, &role, DATE, &date, PASSWORD, &password, -1);

        // Make copies of the strings using g_strdup
        ID = g_strdup(ID);
        nom = g_strdup(nom);
        prenom = g_strdup(prenom);
        sexe = g_strdup(sexe);
        role = g_strdup(role);
        date = g_strdup(date);
        password = g_strdup(password);

        gtk_list_store_set(store, &iter, IDENTIFIANT, ID, NOM, nom, PRENOM, prenom, SEXE, sexe, ROLE, role, DATE, date, PASSWORD, password, -1);

        // Free the copied data
        g_free(nom);
        g_free(prenom);
        g_free(sexe);
        g_free(role);
        g_free(date);
        g_free(password);
    }
}

GtkTreeIter copyIterETS;

void
on_copyETS_activate (GtkMenuItem *menuitem, gpointer user_data)
{ 
     GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
     GtkTreeModel *model;
    GtkTreeSelection *selection;
    GList *rows, *current;
    
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (gtk_tree_selection_count_selected_rows(selection) > 0) {
        rows = gtk_tree_selection_get_selected_rows(selection, &model);

        // For simplicity, we'll consider only the first selected row
        GtkTreePath *path = (GtkTreePath *)rows->data;

        gtk_tree_model_get_iter(model, &copyIterETS, path);

        // Free the list of selected rows
        g_list_free_full(rows, (GDestroyNotify)gtk_tree_path_free);
    }
}


void
on_PasteETS_activate  (GtkMenuItem *menuitem, gpointer  user_data)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    GtkTreeModel *model;
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    // Check if there's copied data
    if (gtk_tree_model_iter_n_children(model, NULL) > 0)
    {
        // Append a new row
        gtk_list_store_append(store, &iter);

        // Get the copied data and set it in the new row
         int id , capacite ;
	gchar *nom,*adresse,*region ;
	
        gtk_tree_model_get(model, &copyIterETS,  ID,&id,  Nom,&nom,  Adresse ,&adresse,  Region , &region,  Capacite , &capacite, -1);

        // Make copies of the strings using g_strdup
	ETSTrieIDCroiss("ets.txt") ; 
    	int generatedID = generateID("ets.txt");
        nom = g_strdup(nom);
        adresse = g_strdup(adresse);
        region = g_strdup(region);

        gtk_list_store_set(store, &iter,  ID,generatedID,  Nom,nom,  Adresse ,adresse,  Region , region,  Capacite , capacite, -1);

        // Free the copied data
        g_free(nom);
        g_free(adresse);
        g_free(region);

    }
}

/*********GHAZI *********/ 
char choix[20];
void
on_button2_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_D_ajout_de_RDV = create_Interface_D_ajout_de_RDV ();

int ID , Capacite ;
char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;
GtkWidget *combobox = lookup_widget(Interface_D_ajout_de_RDV, "comboboxentry3_ghazi");
FILE *f = fopen("ets.txt" , "r" ) ;
if (f != NULL ) {
while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
sprintf(IDstr , "%d" , ID ) ;
 gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
}

}

 gtk_widget_show (Interface_D_ajout_de_RDV);
GtkWidget * Interface_De_la_page_Dacceuil = lookup_widget(button,"Interface_De_la_page_Dacceuil");
  gtk_widget_destroy (Interface_De_la_page_Dacceuil);
}


void
on_button3_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_De_La_Modification = create_Interface_De_La_Modification ();
int ID , Capacite ;
char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;
GtkWidget *combobox = lookup_widget(Interface_De_La_Modification, "comboboxentry55_ghazi");
FILE *f = fopen("ets.txt" , "r" ) ;
if (f != NULL ) {
while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
sprintf(IDstr , "%d" , ID ) ;
 gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
}

}

 gtk_widget_show (Interface_De_La_Modification);
GtkWidget * Interface_De_la_page_Dacceuil = lookup_widget(button,"Interface_De_la_page_Dacceuil");
  gtk_widget_destroy (Interface_De_la_page_Dacceuil);
}


void
on_button4_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_De_Suppression_De_RDV = create_Interface_De_Suppression_De_RDV ();
 gtk_widget_show (Interface_De_Suppression_De_RDV);
GtkWidget * Interface_De_la_page_Dacceuil = lookup_widget(button,"Interface_De_la_page_Dacceuil");
  gtk_widget_destroy (Interface_De_la_page_Dacceuil);
}

// mdf avec succes 
void
on_button16_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
 gtk_widget_show (Interface_De_la_page_Dacceuil);
GtkWidget * MDF_Avec_SUCESS = lookup_widget(button,"MDF_Avec_SUCESS");
  gtk_widget_destroy (MDF_Avec_SUCESS);
}


void
on_button7_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
 gtk_widget_show (Interface_De_la_page_Dacceuil);
GtkWidget * Interface_D_ajout_de_RDV = lookup_widget(button,"Interface_D_ajout_de_RDV");
  gtk_widget_destroy (Interface_D_ajout_de_RDV);
}



void on_button6_ghazi_clicked(GtkButton *button, gpointer user_data) {
    int tr;
    RDV rendezvous;
    GtkWidget *input1 = lookup_widget(button, "entry8");
    GtkWidget *input2 = lookup_widget(button, "comboboxentry3_ghazi");
    GtkWidget *input3 = lookup_widget(button, "combobox1_ghazi");
    GtkWidget *input4 = lookup_widget(button, "combobox2_ghazi");
    GtkWidget *input5 = lookup_widget(button, "spinbutton1");
    GtkWidget *input6 = lookup_widget(button, "comboboxentry2_ghazi");
    GtkWidget *output7 = lookup_widget(button, "label112");

    char *id_str = gtk_entry_get_text(GTK_ENTRY(input1));

    if (strlen(id_str) != 8 || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)) ||
        !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input6)) || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)) ||
        !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)) || !gtk_entry_get_text(GTK_ENTRY(input5))) {

        if (strlen(id_str) != 8) {
            gtk_label_set_text(GTK_LABEL(output7), "ID invalide. Doit contenir exactement 8 chiffres.");
        } else {
            gtk_label_set_text(GTK_LABEL(output7), "Veuillez remplir tous les champs s'il vous plaît !");
        }

        return;
    }

    rendezvous.ID = atoi(id_str);
    strcpy(rendezvous.Etablissement, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)));
    strcpy(rendezvous.heure, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input6)));
    strcpy(rendezvous.date.jour, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
    strcpy(rendezvous.date.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
    strcpy(rendezvous.date.annee, gtk_entry_get_text(GTK_ENTRY(input5)));

    // Check capacity before adding the appointment
    tr = get_capacity(rendezvous.Etablissement, rendezvous.date.jour);

    if (tr == -1) {
        gtk_label_set_text(GTK_LABEL(output7), "La capacité pour cet établissement à cette date est pleine. Choisissez une autre date !");
        return;
    } else {
        // Capacity is available, proceed to add the appointment
        tr = add_rdv(rendezvous);

        if (tr > 0) {
            GtkWidget *Interface_De_la_Confirmation_De_RDV = create_Interface_De_la_Confirmation_De_RDV();
            gtk_widget_show(Interface_De_la_Confirmation_De_RDV);
        } else {
            gtk_label_set_text(GTK_LABEL(output7), "Erreur lors de l'ajout du rendez-vous. Veuillez réessayer.");
        }
    }
}






void
on_button8_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget * Interface_De_la_Confirmation_De_RDV = lookup_widget(button,"Interface_De_la_Confirmation_De_RDV");
  gtk_widget_destroy (Interface_De_la_Confirmation_De_RDV);
}



void
on_button10_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}

 gtk_widget_show (Interface_De_la_page_Dacceuil);
GtkWidget * Interface_De_La_Modification = lookup_widget(button,"Interface_De_La_Modification");
  gtk_widget_destroy (Interface_De_La_Modification);
}


void on_button9_ghazi_clicked(GtkButton *button, gpointer user_data) {
    int ID;
    RDV new;
    GtkWidget *input1 = lookup_widget(button, "entry11");
    GtkWidget *input2 = lookup_widget(button, "combobox4");
    GtkWidget *input3 = lookup_widget(button, "combobox99_ghazi");
    GtkWidget *input4 = lookup_widget(button, "spinbutton2");
    GtkWidget *input5 = lookup_widget(button, "comboboxentry40_ghazi");
    GtkWidget *input6 = lookup_widget(button, "comboboxentry55_ghazi");
    GtkWidget *input55 = lookup_widget(button, "label95_ghazi");


    if (!gtk_entry_get_text(GTK_ENTRY(input1)) || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input6)) ||
        !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input5)) || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)) ||
        !gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)) || !gtk_entry_get_text(GTK_ENTRY(input4))) {


        gtk_label_set_text(GTK_LABEL(input55), "Veuillez remplir tous les champs s'il vous plais !");
        return;
    }

    ID = atoi(gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(new.Etablissement, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input6)));
    strcpy(new.heure, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input5)));
    strcpy(new.date.jour, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)));
    strcpy(new.date.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
    strcpy(new.date.annee, gtk_entry_get_text(GTK_ENTRY(input4)));
    ModifierRDV(ID, new);

    GtkWidget *MDF_Avec_SUCESS = create_MDF_Avec_SUCESS();
    gtk_widget_show(MDF_Avec_SUCESS);
    GtkWidget *Interface_De_La_Modification = lookup_widget(button, "Interface_De_La_Modification");
    gtk_widget_destroy(Interface_De_La_Modification);
}





void on_button17_clicked(GtkButton *button, gpointer user_data) {
    int ID;
    GtkWidget *input2, *input22, *input3, *input33, *input4, *input44, *input55, *output1000, *output1001, *output1002;

    input2 = lookup_widget(button, "entry11");
    input22 = lookup_widget(button, "combobox4");
    input3 = lookup_widget(button, "combobox99_ghazi");
    input33 = lookup_widget(button, "spinbutton2");
    input4 = lookup_widget(button, "comboboxentry40_ghazi");
    input44 = lookup_widget(button, "comboboxentry55_ghazi");
    input55 = lookup_widget(button, "label95_ghazi");
    output1000 = lookup_widget(button, "label_mdf1");
    output1001 = lookup_widget(button, "label_mdf2");
    output1002 = lookup_widget(button, "label_mdf3");

    char *id_str = gtk_entry_get_text(GTK_ENTRY(input2));

    if (strlen(id_str) != 8) {
        gtk_label_set_text(GTK_LABEL(input55), "ID invalide. Doit contenir exactement 8 chiffres.");
        return;
    }

    ID = atoi(id_str);

    if (Chercher("RDV.txt", ID) == 0) {
        gtk_label_set_text(GTK_LABEL(input55), "Rendez-vous non trouvé. Veuillez vérifier l'ID, s'il vous plaît !");
    } else if (Chercher("RDV.txt", ID) == 1) {
   
        gtk_label_set_text(GTK_LABEL(input55), "Veuillez entrer vos modifications.");
        gtk_editable_set_editable(GTK_EDITABLE(input2), FALSE);
        gtk_widget_set_visible(input22, TRUE);
        gtk_widget_set_visible(input3, TRUE);
        gtk_widget_set_visible(input33, TRUE);
        gtk_widget_set_visible(input4, TRUE);
        gtk_widget_set_visible(input44, TRUE);
        gtk_widget_set_visible(input55, TRUE);
        gtk_widget_set_visible(output1000, TRUE);
        gtk_widget_set_visible(output1001, TRUE);
        gtk_widget_set_visible(output1002, TRUE);
    }
}



void on_button11_ghazi_clicked(GtkButton *button, gpointer user_data) {
  /*  if (choix[7] == 1) {
        int tr;
        RDV rendezvous;

        GtkWidget *input2 = lookup_widget(button, "entry8");
        GtkWidget *input22 = lookup_widget(button, "comboboxentry3_ghazi");
        GtkWidget *input3 = lookup_widget(button, "combobox1_ghazi");
        GtkWidget *input33 = lookup_widget(button, "combobox2_ghazi");
        GtkWidget *input4 = lookup_widget(button, "spinbutton1");
        GtkWidget *input44 = lookup_widget(button, "comboboxentry2_ghazi");

       
        if (!GTK_IS_ENTRY(input2)) {
            g_print("Error: 'input2' is not a GTK entry widget.\n");
            return;
        }

        rendezvous.ID = atoi(gtk_entry_get_text(GTK_ENTRY(input2)));
        strcpy(rendezvous.Etablissement, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input22)));
        strcpy(rendezvous.heure, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
        strcpy(rendezvous.date.jour, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input33)));
        strcpy(rendezvous.date.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
        strcpy(rendezvous.date.annee, gtk_entry_get_text(GTK_ENTRY(input44)));

        tr = add_rdv(rendezvous);
        if (tr == 1) {

            RDV newRdv = {rendezvous.ID, rendezvous.Etablissement, rendezvous.heure,
                          {rendezvous.date.jour, rendezvous.date.mois, rendezvous.date.annee}};
            ModifierRDV(rendezvous.ID, newRdv);

            GtkWidget *Interface_De_La_Confirmation_De_La_Modification_De_RDV = lookup_widget(button, "Interface_De_La_Confirmation_De_La_Modification_De_RDV");
            gtk_widget_destroy(Interface_De_La_Confirmation_De_La_Modification_De_RDV);

            GtkWidget *MDF_Avec_SUCESS = create_MDF_Avec_SUCESS();
            gtk_widget_show(MDF_Avec_SUCESS);
        }
    }

    if (choix[5] == 1) {
        GtkWidget *Interface_De_La_Confirmation_De_La_Modification_De_RDV =
            lookup_widget(button, "Interface_De_La_Confirmation_De_La_Modification_De_RDV");
        gtk_widget_destroy(Interface_De_La_Confirmation_De_La_Modification_De_RDV);

        GtkWidget *Interface_De_La_Modification = create_Interface_De_La_Modification();
        gtk_widget_show(Interface_De_La_Modification);
    }*/
}



void
on_button14_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
 gtk_widget_show (Interface_De_la_page_Dacceuil);
GtkWidget * Interface_De_Suppression_De_RDV = lookup_widget(button,"Interface_De_Suppression_De_RDV");
  gtk_widget_destroy (Interface_De_Suppression_De_RDV);
}


void on_button12_ghazi_clicked(GtkButton *button, gpointer user_data) {
    int id_supp, tb;
    GtkWidget *out = lookup_widget(button, "out10_ghazi");
    GtkWidget *input1 = lookup_widget(button, "entry12_ghazi");

    char *id_str = gtk_entry_get_text(GTK_ENTRY(input1));


    if (strlen(id_str) != 8) {
        gtk_label_set_text(GTK_LABEL(out), "ID invalide. Doit contenir exactement 8 chiffres.");
        return;
    }

    id_supp = atoi(id_str);

    if (choix[2] == 1) {
      
        tb = SupprimerRDV(id_supp);

        if (tb == 1 && choix[2] == 1) {
            gtk_label_set_text(GTK_LABEL(out), "Le Rendez-Vous a été Supprimé Avec Succès");

GtkWidget *Interface_De_Confirmation_De_Suppression_Des_RDV = create_Interface_De_Confirmation_De_Suppression_Des_RDV ();
 gtk_widget_show (Interface_De_Confirmation_De_Suppression_Des_RDV);
GtkWidget * Interface_De_Suppression_De_RDV = lookup_widget(button,"Interface_De_Suppression_De_RDV");
  gtk_widget_destroy (Interface_De_Suppression_De_RDV);


        } else if (tb == 0) {
            gtk_label_set_text(GTK_LABEL(out), "ID non trouvé");
        } 
    } else if (choix[2] == 0) {
        gtk_label_set_text(GTK_LABEL(out), "Choisissez confirmer, s'il vous plaît");
    }
}


void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget * Interface_De_Confirmation_De_Suppression_Des_RDV = lookup_widget(button,"Interface_De_Confirmation_De_Suppression_Des_RDV");
  gtk_widget_destroy (Interface_De_Confirmation_De_Suppression_Des_RDV);
 GtkWidget *Interface_De_Suppression_De_RDV= create_Interface_De_Suppression_De_RDV();
 gtk_widget_show (Interface_De_Suppression_De_RDV);
}

void
on_button_affiche_ghazi_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview113;
 GtkWidget *Interface_De_la_page_Dacceuil =  lookup_widget(button, "Interface_De_la_page_Dacceuil");
 gtk_widget_destroy(Interface_De_la_page_Dacceuil);
 Interface_De_la_page_Dacceuil= create_Interface_De_la_page_Dacceuil();
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
 gtk_widget_show (Interface_De_la_page_Dacceuil);
 treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
 display_rdv(treeview113,"RDV.txt");



}


void
on_treeview111_columns_changed         (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}

void
on_treeview112_columns_changed         (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}

void
on_button00_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data)


{
 GtkWidget *Interface_De_la_page_Dacceuil =  lookup_widget(button, "Interface_De_la_page_Dacceuil");
 gtk_widget_destroy(Interface_De_la_page_Dacceuil);
 GtkWidget *Interface_D_affichage_RDV= create_Interface_D_affichage_RDV();

 gtk_widget_show (Interface_D_affichage_RDV);



}





void on_button_chercher_clicked(GtkButton *button, gpointer user_data) {
 char id_str[10];
int ID;
  GtkWidget *input9 = lookup_widget(button, "entry9");
   strcpy(id_str,gtk_entry_get_text(GTK_ENTRY(input9)));
    if (strlen(id_str) != 8) {
        g_print("ID invalide. Doit contenir exactement 8 chiffres. \n");
        return;
    }

    ID = atoi(id_str);
    Chercher_user(ID);

    GtkWidget *treeview112;
    GtkWidget *Interface_D_affichage_RDV = lookup_widget(button, "Interface_D_affichage_RDV");
    gtk_widget_destroy(Interface_D_affichage_RDV);
    Interface_D_affichage_RDV = create_Interface_D_affichage_RDV();
    gtk_widget_show(Interface_D_affichage_RDV);
    treeview112 = lookup_widget(Interface_D_affichage_RDV, "treeview112");


  
    display_rdv(GTK_TREE_VIEW(treeview112), "cherche.txt");
    remove("cherche.txt");
}


void
on_button19_help_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

 GtkWidget *Interface_De_la_page_Dacceuil =  lookup_widget(button, "Interface_De_la_page_Dacceuil");
 gtk_widget_destroy(Interface_De_la_page_Dacceuil);
  GtkWidget *Interface_Help = create_Interface_Help ();
  gtk_widget_show (Interface_Help);


}


void
on_button18_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_Help =  lookup_widget(button, "Interface_Help");
 gtk_widget_destroy(Interface_Help);
 GtkWidget * Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
  gtk_widget_show (Interface_De_la_page_Dacceuil);
}


void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_D_affichage_RDV =  lookup_widget(button, "Interface_D_affichage_RDV");
 gtk_widget_destroy(Interface_D_affichage_RDV);
  GtkWidget *Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
  gtk_widget_show (Interface_De_la_page_Dacceuil);
}


void
on_button99_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_De_la_page_Dacceuil =  lookup_widget(button, "Interface_De_la_page_Dacceuil");
 gtk_widget_destroy(Interface_De_la_page_Dacceuil);
 GtkWidget * Interface_De_Deconnection_ = create_Interface_De_Deconnection_ ();
  gtk_widget_show (Interface_De_Deconnection_);
}


void
on_button17_ghazi_rdv_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *out = lookup_widget(button, "label113");

if (choix[9] == 1)
{
gtk_main_quit();
}
if (choix[9] == 0)
{
gtk_label_set_text(GTK_LABEL(out),"Clicker Sur Deconnecter S'il Vous Plais !");
}
}

void
on_checkbutton2_deconnecter_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)


{
if (gtk_toggle_button_get_active(togglebutton))
choix[9] = 1;
else
choix[9] = 0;

}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)

{

if (gtk_toggle_button_get_active(togglebutton))
choix[2] = 1;
else
choix[2] = 0;
}



//no
void
on_radiobutton2_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
choix[5] = 1;
else
choix[5] = 0;
}

//yes
void
on_radiobutton1_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
choix[7] = 1;
else
choix[7] = 0;
}


void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_De_Deconnection_ =  lookup_widget(button, "Interface_De_Deconnection_");
 gtk_widget_destroy(Interface_De_Deconnection_);
 GtkWidget * Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
  gtk_widget_show (Interface_De_la_page_Dacceuil);
}


void on_button20_clicked(GtkButton *button, gpointer user_data) {
    char etablissement_str[100];  
    GtkWidget *combobox_entry = lookup_widget(button, "comboboxentry1");
    GtkWidget *treeview112;

    char *active_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_entry));
  
    strcpy(etablissement_str, active_text);
    g_free(active_text);

    Chercher_user_by_etablissement(etablissement_str); 

    GtkWidget *Interface_De_la_page_Dacceuil = lookup_widget(button, "Interface_De_la_page_Dacceuil");
    gtk_widget_destroy(Interface_De_la_page_Dacceuil);
    Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil();
    gtk_widget_show(Interface_De_la_page_Dacceuil);
    treeview112 = lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");

    display_rdv(GTK_TREE_VIEW(treeview112), "cherche.txt");
    remove("cherche.txt");
}


void
on_button25_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_Help =  lookup_widget(button, "Interface_Help");
 gtk_widget_destroy(Interface_Help);
 GtkWidget * Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
  gtk_widget_show (Interface_De_la_page_Dacceuil);
}


void
on_button23_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_Help =  lookup_widget(button, "Interface_Help");
 gtk_widget_destroy(Interface_Help);
 GtkWidget * Interface_De_Suppression_De_RDV = create_Interface_De_Suppression_De_RDV ();
  gtk_widget_show (Interface_De_Suppression_De_RDV);
}


void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Interface_Help =  lookup_widget(button, "Interface_Help");
 gtk_widget_destroy(Interface_Help);
 GtkWidget * Interface_D_ajout_de_RDV = create_Interface_D_ajout_de_RDV ();
  gtk_widget_show (Interface_D_ajout_de_RDV);
}


void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{/*
GtkWidget *Interface_Help =  lookup_widget(button, "Interface_Help");
 gtk_widget_destroy(Interface_Help);
 GtkWidget * Interface_De_La_Modification = Interface_De_La_Modification ();
  gtk_widget_show (Interface_De_La_Modification);*/
}



/****** EMNA **********/ 
// Interface affichage
void on_ajouter_emna_clicked                (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *ajout;
    GtkWidget *affichage;
	int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;
    affichage = lookup_widget(objet_graphique, "affichage");
    gtk_widget_hide(affichage);
    ajout = create_ajout();
	GtkWidget *combobox = lookup_widget(ajout, "combobox_etablissement");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}	
    gtk_widget_show(ajout);
}

void on_supprimer_emna_clicked              (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *affichage;
    GtkWidget *suppression;

    affichage = lookup_widget(objet_graphique, "affichage");
    gtk_widget_hide(affichage);
    suppression = create_suppression();
    gtk_widget_show(suppression);
}

void on_modifier_emna_clicked               (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *affichage;
    GtkWidget *modifier;

    affichage = lookup_widget(objet_graphique, "affichage");
    gtk_widget_hide(affichage);
    modifier = create_modifier();

	int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;
	GtkWidget *combobox = lookup_widget(modifier, "combobox_etablissement_mod");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}
    gtk_widget_show(modifier);
}






// Interface d'ajout
void on_retour_bekri_clicked                (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *affichage;
    GtkWidget *ajout;

    ajout = lookup_widget(objet_graphique, "ajout");
    gtk_widget_hide(ajout);
    affichage = create_affichage();
    GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
  afficher_donneur(treeviewEmna) ; 
    gtk_widget_show(affichage);
}

void on_valider_bekri_clicked               (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *cin;
    GtkWidget *nom;
    GtkWidget *prenom;
    GtkWidget *radiobutton_homme_bekri;
    GtkWidget *radiobutton_femme_bekri;
    GtkWidget *combobox_type_sang;
    GtkWidget *combobox_etablissement;
    GtkWidget *jour;
    GtkWidget *mois;
    GtkWidget *annee;
    GtkWidget *affichage;
    GtkWidget *ajout;
    GtkWidget* label_dialogue;



label_dialogue = lookup_widget(objet_graphique, "label_dialogue");    


donneur D;

cin= lookup_widget(objet_graphique, "cin_bekri");
D.cin= atoi(gtk_entry_get_text(GTK_ENTRY(cin)) ) ;
if(D.cin==0){
   gtk_label_set_text(GTK_LABEL(label_dialogue), "donner un Numero de Carte Identite");
   return;
}
     
nom= lookup_widget(objet_graphique, "nom_bekri");
strcpy(D.nom,gtk_entry_get_text(GTK_ENTRY(nom)) ) ;

prenom= lookup_widget(objet_graphique, "prenom_bekri");
strcpy(D.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)) ) ;

int choix=0 ;
radiobutton_homme_bekri = lookup_widget(objet_graphique, "radiobutton_homme_bekri" ) ;
if  (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (radiobutton_homme_bekri) ))
{
 	choix=1 ;
}
if (choix == 1 ) 
{
	strcpy(D.sexe,"homme") ; 
}
else
 {
	strcpy(D.sexe,"femme") ; 
}

combobox_type_sang= lookup_widget(objet_graphique, "combobox_type_sang");
char ets[30];


combobox_etablissement= lookup_widget(objet_graphique, "combobox_etablissement");
const char *selectedtype = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_type_sang));
    if (selectedtype != NULL) {
        strncpy(D.type_sang, selectedtype, sizeof(D.type_sang) - 1);
       D.type_sang[sizeof(D.type_sang) - 1] = '\0';}
   else{
      gtk_label_set_text(GTK_LABEL(label_dialogue), "remplissez toutes les cases");
      return ;
}
const char *selectedets = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_etablissement));
    if (selectedets != NULL) {
        strncpy(ets, selectedtype, sizeof(ets) - 1);
	D.ets =atoi(ets);
   } 
    else{
gtk_label_set_text(GTK_LABEL(label_dialogue), "remplissez toutes les cases");
return;
}



GtkWidget *spinbutton_jour_bekri = lookup_widget(objet_graphique, "spinbutton_jour_bekri");
D.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour_bekri));

GtkWidget *spinbutton_mois_bekri = lookup_widget(objet_graphique, "spinbutton_mois_bekri");
D.d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois_bekri));

GtkWidget *spinbutton_annee_bekri =lookup_widget(objet_graphique, "spinbutton_annee_bekri");
D.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee_bekri));

GtkWidget *checkbutton_verif_emna = lookup_widget(objet_graphique, "checkbutton_verif_emna");
    if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_verif_emna))) {
      
gtk_label_set_text(GTK_LABEL(label_dialogue), "Veuillez cocher la confirmation");
return;
}
ajouter_emna(D) ; 
  affichage = create_affichage ();
  GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
  afficher_donneur(treeviewEmna) ; 
  gtk_widget_show (affichage);
   ajout = lookup_widget(objet_graphique, "ajout");
    gtk_widget_hide(ajout);
    // Assurez-vous d'utiliser les fonctions appropriées pour libérer la mémoire
    // g_free(cin);
    // g_free(nom);
    // g_free(prenom);
    // g_free(sexe);
    // g_free(etablissement);
    // g_free(type_sang);
    // g_free(jour);
    // g_free(mois);
    // g_free(annee);
}






// Interface modifier

void on_retour_emnabek_clicked             (GtkWidget       *objet_graphique,gpointer         user_data)
{

GtkWidget *affichage;
GtkWidget *modifier;
  
    
affichage = create_affichage();
GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
afficher_donneur(treeviewEmna) ; 
gtk_widget_show(affichage);
modifier = lookup_widget(objet_graphique, "modifier");
gtk_widget_hide(modifier);
  
}
  


void on_cherchez_emnabek_clicked (GtkWidget  *objet_graphique, gpointer  user_data)
{

//cin
GtkWidget *emnabek_cin= lookup_widget(objet_graphique, "emnabek_cin"); 
GtkWidget *cin_emnabek = lookup_widget(objet_graphique, "cin_emnabek"); 



//nom
GtkWidget *emnabek_nom = lookup_widget(objet_graphique, "emnabek_nom"); 
GtkWidget *nom_emnabek= lookup_widget(objet_graphique, "nom_emnabek"); 



//prenom
GtkWidget *emnabek_prenom = lookup_widget(objet_graphique, "emnabek_prenom"); 
GtkWidget *prenom_emnabek= lookup_widget(objet_graphique, "prenom_emnabek"); 



//type de sang 
GtkWidget *emnabek_type_sang= lookup_widget(objet_graphique,"emnabek_type_sang");
GtkWidget *combobox_type_sang_mod= lookup_widget(objet_graphique,"combobox_type_sang_mod"); 



//ets
GtkWidget *emnabek_etablissement = lookup_widget(objet_graphique,"emnabek_etablissement");
GtkWidget *combobox_etablissement_mod= lookup_widget(objet_graphique,"combobox_etablissement_mod"); 



//sexe
GtkWidget *radiobutton_homme_emnabek = lookup_widget(objet_graphique, "radiobutton_homme_emnabek" ) ;
GtkWidget *radiobutton_femme_emnabek = lookup_widget(objet_graphique, "radiobutton_femme_emnabek" ) ;
GtkWidget *emnabek_sexe = lookup_widget(objet_graphique, "emnabek_sexe" ) ;
 
//date_emna
GtkWidget *spinbutton_jour_emnabek =lookup_widget(objet_graphique,"spinbutton_jour_emnabek");
GtkWidget *spinbutton_mois_emnabek =lookup_widget(objet_graphique,"spinbutton_mois_emnabek"); 
GtkWidget *spinbutton_annee_emnabek=lookup_widget(objet_graphique,"spinbutton_annee_emnabek"); 
GtkWidget *emnabek_date_naissance=lookup_widget(objet_graphique,"emnabek_date_naissance"); 
GtkWidget *valider_emnabek =lookup_widget(objet_graphique,"valider_emnabek"); 


    GtkWidget *label_resultat_recherche = lookup_widget(objet_graphique, "label_resultat_recherche");

// CIN
    donneur D;
    char id[30];
       strcpy(id , gtk_entry_get_text(GTK_ENTRY(cin_emnabek)));
	int entry_id ;
	entry_id = atoi(id);     

     D = retrieve_donneur_data(entry_id);

    if (D.cin != 0) {
	char ID[30];
	sprintf(ID,"%d",D.cin); 
        gtk_entry_set_text(GTK_ENTRY(cin_emnabek), ID);
        // Assuming D.cin, D.nom, D.prenom are strings, update accordingly
        gtk_entry_set_text(GTK_ENTRY(nom_emnabek), D.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom_emnabek), D.prenom);

        // Toggle visibility of widgets based on design
        gtk_widget_set_visible(emnabek_nom, TRUE);
        gtk_widget_set_visible(nom_emnabek, TRUE);
        gtk_widget_set_visible(emnabek_prenom, TRUE);
        gtk_widget_set_visible(prenom_emnabek, TRUE);
        gtk_widget_set_visible(emnabek_type_sang, TRUE);
        gtk_widget_set_visible(combobox_type_sang_mod, TRUE);
        gtk_widget_set_visible(emnabek_etablissement, TRUE);
        gtk_widget_set_visible(combobox_etablissement_mod, TRUE);
        gtk_widget_set_visible(emnabek_sexe, TRUE);
        gtk_widget_set_visible(radiobutton_homme_emnabek, TRUE);
        gtk_widget_set_visible(radiobutton_femme_emnabek, TRUE);
        gtk_widget_set_visible(emnabek_date_naissance, TRUE);
        gtk_widget_set_visible(spinbutton_jour_emnabek, TRUE);
        gtk_widget_set_visible(spinbutton_mois_emnabek, TRUE);
        gtk_widget_set_visible(spinbutton_annee_emnabek, TRUE);
        gtk_widget_set_visible(valider_emnabek, TRUE);
    } else {
        // Display an error message if the user is not found
        gtk_label_set_text(GTK_LABEL(label_resultat_recherche), "Error: User not found");
    }
}



void on_valider_modification_clicked       (GtkWidget       *objet_graphique ,gpointer        user_data)
{

int modified;
GtkWidget* cin_emnabek;
GtkWidget* nom_emnabek; 
GtkWidget* prenom_emnabek; 
GtkWidget* combobox_type_sang_mod; 
GtkWidget* combobox_etablissement_mod;
GtkWidget* radiobutton_homme_emnabek;
GtkWidget* radiobutton_femme_emnabek;
GtkWidget* spinbutton_jour_emnabek; 
GtkWidget* spinbutton_mois_emnabek;
GtkWidget* spinbutton_annee_emnabek; 
GtkWidget* affichage;
GtkWidget* cin;
GtkWidget* nom;
GtkWidget* label_resultat_recherche;


label_resultat_recherche = lookup_widget(objet_graphique, "label_resultat_recherche"); 


//id donneur 
cin_emnabek = lookup_widget(objet_graphique, "cin_emnabek"); 

//nom
nom_emnabek= lookup_widget(objet_graphique, "nom_emnabek"); 

//prenom 
prenom_emnabek= lookup_widget(objet_graphique, "prenom_emnabek"); 

//type de sang 
combobox_type_sang_mod= lookup_widget(objet_graphique,"combobox_type_sang_mod"); 

//ets
combobox_etablissement_mod= lookup_widget(objet_graphique,"combobox_etablissement_mod"); 

//sexe
radiobutton_homme_emnabek = lookup_widget(objet_graphique, "radiobutton_homme_emnabek" ) ;
radiobutton_femme_emnabek = lookup_widget(objet_graphique, "radiobutton_femme_emnabek" ) ;
 
//date_emna
spinbutton_jour_emnabek =lookup_widget(objet_graphique,"spinbutton_jour_emnabek");
spinbutton_mois_emnabek =lookup_widget(objet_graphique,"spinbutton_mois_emnabek"); 
spinbutton_annee_emnabek=lookup_widget(objet_graphique,"spinbutton_annee_emnabek"); 

date_emna d;
donneur nouv; 
char ets[30];


cin = atoi(gtk_entry_get_text(GTK_ENTRY(cin_emnabek)));
g_print("%d" , cin ) ; 
nouv.cin = atoi(gtk_entry_get_text(GTK_ENTRY(cin_emnabek)));
g_print("%d" , nouv.cin ) ; 
strcpy(nouv.nom,gtk_entry_get_text(GTK_ENTRY(nom_emnabek)));
g_print("%s" , nouv.nom ) ; 
strcpy(nouv.prenom,gtk_entry_get_text(GTK_ENTRY(prenom_emnabek)));
g_print("%s" , nouv.prenom ) ; 
//combobox 

if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_type_sang_mod)) != NULL ){
strcpy(nouv.type_sang ,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_type_sang_mod)) ) ;
} else {
strcpy(nouv.type_sang ,"" ) ;
}
if (gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_etablissement_mod)) != NULL ){
strcpy( ets ,  gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_etablissement_mod))  ) ;
} else {
strcpy(ets ,"" ) ;
}
/*
const char *selectedtype = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_type_sang_mod));
    if (selectedtype != NULL) {
        strncpy(nouv.type_sang, selectedtype, sizeof(nouv.type_sang) - 1);
       nouv.type_sang[sizeof(nouv.type_sang) - 1] = '\0';}
   else{
      gtk_label_set_text(GTK_LABEL(label_resultat_recherche), "remplissez toutes les cases");
      return ;
}
const char *selectedets = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_etablissement_mod));
    if (selectedets != NULL) {
        strncpy(nouv.ets, selectedtype, sizeof(nouv.ets) - 1);
   } 
    else{
gtk_label_set_text(GTK_LABEL(label_resultat_recherche), "remplissez toutes les cases");
return;
}*/


nouv.ets =atoi(ets);

int choix=0 ;
radiobutton_homme_emnabek = lookup_widget(objet_graphique, "radiobutton_homme_emnabek" ) ;
if  (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (radiobutton_homme_emnabek) ))
{
 	choix=1 ;
}
if (choix == 1 ) 
{
	strcpy(nouv.sexe,"homme") ; 
}
else
 {
	strcpy(nouv.sexe,"femme") ; 
}

//spin btn 
nouv.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour_emnabek)) ;
nouv.d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois_emnabek)) ; 
nouv.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee_emnabek)); 

if ( (strcmp(nouv.type_sang ,"" ) != 0 )  && (strcmp(ets ,"" ) != 0  )   ) {
modified =modifier_emna(cin,  nouv);
GtkTreeView *treeview1; 
GtkWidget *modif= lookup_widget(objet_graphique, "modifier"); 
gtk_widget_hide(modif); 
affichage= create_affichage();
gtk_widget_show(affichage); 
treeview1 = lookup_widget(affichage, "treeview1");
afficher_donneur(treeview1); 
 }
 else
 {
 gtk_label_set_text(GTK_LABEL(label_resultat_recherche), "modificatuon not aboutis");


}
}
	




 








//interface suppression
void on_retour_suppression_clicked          (GtkWidget       *objet_graphique ,gpointer        user_data)
{
    GtkWidget *affichage;
    GtkWidget *suppression;

    suppression = lookup_widget(objet_graphique, "suppression");
    gtk_widget_hide(suppression);
    affichage = create_affichage();
    GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
  afficher_donneur(treeviewEmna) ; 
    gtk_widget_show(affichage);

}




void on_supprimerr_suppression_clicked      (GtkWidget       *objet_graphique ,gpointer        user_data)
{ 
GtkWidget *CIN;
GtkWidget *cin_supprimer;
GtkWidget *window;

donneur D;
char id[20];
 int cin ;
cin_supprimer = lookup_widget(objet_graphique, "cin_supprimer");
cin = atoi( gtk_entry_get_text(GTK_ENTRY(cin_supprimer) )  );
//D.cin = atoi(id);
//cin=atoi(gtk_entry_get_text(GTK_ENTRY(cin_supprimer)));
//donneur Trouve;
if (Chercher_donneur("donneurs.txt", cin)) {
supprimer_donneur(cin);

}else {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, " veuillez vérifier votre numeroCarteCin !");
        gtk_dialog_run(GTK_DIALOG(dialog)); 
        gtk_widget_destroy(dialog);
	}
}




void on_listeRDV_emna_clicked               (GtkWidget       *objet_graphique ,gpointer         user_data)
{
 GtkWidget *stat1;
 GtkWidget *affichage;

    affichage = lookup_widget(objet_graphique, "affichage");
    gtk_widget_hide(affichage);
    stat1 = create_stat1();
    gtk_widget_show(stat1);
}


void on_moyRDV_emna_clicked                 (GtkWidget       *objet_graphique, gpointer         user_data)
{ 
GtkWidget *stat2;
GtkWidget *affichage;

affichage = lookup_widget(objet_graphique, "affichage");
gtk_widget_hide(affichage);
stat2 = create_stat2();
gtk_widget_show(stat2);

}


void on_retour_stat1_clicked                (GtkWidget       *objet_graphique, gpointer         user_data)
{
GtkWidget *affichage;
GtkWidget *stat1;
  
    
affichage = create_affichage();
GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
afficher_donneur(treeviewEmna) ; 
gtk_widget_show(affichage);
stat1 = lookup_widget(objet_graphique, "stat1");
gtk_widget_hide(stat1);
}


void on_retour_stat2_clicked                (GtkWidget       *objet_graphique, gpointer         user_data)
{
GtkWidget *affichage;
GtkWidget *stat2;
  
    
affichage = create_affichage();
GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
afficher_donneur(treeviewEmna) ; 
gtk_widget_show(affichage);
stat2 = lookup_widget(objet_graphique, "stat2");
gtk_widget_hide(stat2);

}


void
on_radiobutton_femme_emnabek_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_homme_emnabek_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_femme_bekri_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_homme_bekri_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void on_affiche_sta1_clicked                (GtkWidget       *objet_graphique, gpointer         user_data)
{
GtkWidget *spinbutton_jour_stat1 =lookup_widget(objet_graphique,"spinbutton_jour_stat1");
GtkWidget *spinbutton_mois_stat1 =lookup_widget(objet_graphique,"spinbutton_mois_stat1"); 
GtkWidget *spinbutton_annee_stat1=lookup_widget(objet_graphique,"spinbutton_annee_stat1"); 
GtkWidget *label_affiche_stat1=lookup_widget(objet_graphique,"label_affiche_stat1"); 
GtkWidget *ets_stat1=lookup_widget(objet_graphique,"ets_stat1"); 
date_emna d;
donneur D;
D.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour_stat1)) ;
D.d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois_stat1)) ; 
D.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee_stat1)); 
g_print("%d" ,D.d.jour ) ;
g_print("%d" ,D.d.mois ) ;
g_print("%d" ,D.d.annee  ) ;



///jiben el ets
int ets;
ets = atoi(gtk_entry_get_text(GTK_ENTRY(ets_stat1)));
g_print("%d" ,ets  ) ;

int x;
x=listeRDV("RDV.txt", ets, D.d.jour, D.d.mois, D.d.annee);
char nbreRDV[30];
sprintf (nbreRDV ,"%d", x);
gtk_label_set_text(GTK_LABEL(label_affiche_stat1), nbreRDV);


}


void on_affiche_stat2_clicked               (GtkWidget       *objet_graphique, gpointer         user_data)
{
GtkWidget *spinbutton_jour_stat2 =lookup_widget(objet_graphique,"spinbutton_jour_stat2");
GtkWidget *spinbutton_mois_stat2 =lookup_widget(objet_graphique,"spinbutton_mois_stat2"); 
GtkWidget *spinbutton_annee_stat2=lookup_widget(objet_graphique,"spinbutton_annee_stat2"); 
GtkWidget *label_affiche_moyRDV=lookup_widget(objet_graphique,"label_affiche_moyRDV");
donneur D; 
date_emna d;

D.d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour_stat2)) ;
D.d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois_stat2)) ; 
D.d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee_stat2)); 
float moy;
moy=moyRDV_ETS("donneurs.txt", D.d.jour, D.d.mois, D.d.annee);
char moyenne[20];
sprintf (moyenne ,"%.2f",moy);
strcat(moyenne , " %") ; 
gtk_label_set_text(GTK_LABEL(label_affiche_moyRDV),moyenne);
}


 /*********** YASSMINE ****/ 

void delay(int seconds) {
    sleep(seconds);
}

//register
void on_yasmine_register_button_clicked(GtkWidget *objet_graphique, gpointer user_data){
  
GtkWidget *yasmine_login_window;

GtkWidget* yasmine_register_entryNom;
GtkWidget* yasmine_register_entryPrenom;
GtkWidget* yasmine_register_entryUsername;
GtkWidget* yasmine_register_entryPassword;
GtkWidget* yasmine_register_entryRole;

char nom[50];
char prenom[50];
char username[50];
char password[50];
int role;

yasmine_register_entryNom = lookup_widget(objet_graphique, "yasmine_register_entryNom");
yasmine_register_entryPrenom = lookup_widget(objet_graphique, "yasmine_register_entryPrenom");
yasmine_register_entryUsername = lookup_widget(objet_graphique, "yasmine_register_entryUsername");
yasmine_register_entryPassword = lookup_widget(objet_graphique, "yasmine_register_entryPassword");
yasmine_register_entryRole = lookup_widget(objet_graphique, "yasmine_register_entryRole");

strcpy(nom,gtk_entry_get_text(GTK_ENTRY(yasmine_register_entryNom)));
strcpy(prenom,gtk_entry_get_text(GTK_ENTRY(yasmine_register_entryPrenom)));
strcpy(username,gtk_entry_get_text(GTK_ENTRY(yasmine_register_entryUsername)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(yasmine_register_entryPassword)));

role = atoi(gtk_entry_get_text(GTK_ENTRY(yasmine_register_entryRole)) ) ;

	yassAjoutRegister(nom, prenom, username, password, role);

}


//login
void on_yasmine_login_button_clicked (GtkWidget *objet_graphique, gpointer user_data) {
  
    GtkWidget *yasmine_welcome_window;

  GtkWidget *yasmine_login_entryUsername;
    GtkWidget *yasmine_login_entryPassword;
    GtkWidget *yasmine_login_label_error;

    char usernameLogin[50];
    char passwordLogin[50];

    yasmine_login_entryUsername = lookup_widget(objet_graphique, "yasmine_login_entryUsername");
    yasmine_login_entryPassword = lookup_widget(objet_graphique, "yasmine_login_entryPassword");
    yasmine_login_label_error = lookup_widget(objet_graphique, "yasmine_login_label_error");

    strcpy(usernameLogin, gtk_entry_get_text(GTK_ENTRY(yasmine_login_entryUsername)) );
    strcpy(passwordLogin, gtk_entry_get_text(GTK_ENTRY(yasmine_login_entryPassword)) );


}
//
void
on_yasmine_home_navbar_viewAll_clicked  (GtkWidget *objet_graphique,  gpointer         user_data)
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////::


int order = 1;


void
on_yasmine_qte_type_tri_decroissant_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{ 

    if (gtk_toggle_button_get_active(togglebutton)) {
        order = 0;
        printf("decroissant %d\n", order);

	}
}
void
on_yasmine_qte_type_tri_croissant_toggled(GtkToggleButton *togglebutton, gpointer  user_data)
{


  if (gtk_toggle_button_get_active(togglebutton)) {
        order = 1;
        printf("croissant %d\n", order);

	}
}

// from home to qte dispo 
void on_yasmine_home_navbar_qtdispo_clicked (GtkWidget *objet_graphique,  gpointer         user_data)
{


 GtkWidget *yasmine_home_window;
GtkWidget *yasmine_quantite_type_window;
GtkTreeView *yasmine_quantite_type_treeView;

    yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
    yasmine_quantite_type_treeView = GTK_TREE_VIEW(lookup_widget(objet_graphique, "yasmine_treeview"));

    gtk_widget_hide(yasmine_home_window);
    yasmine_quantite_type_window = create_yasmine_quantite_type_window();
    gtk_widget_show(yasmine_quantite_type_window);


blood_quantities_in_treeview(yasmine_quantite_type_treeView, order);
	
}



// actualiser treeeview qte type
void
on_yasmine_qte_type_btn_actualiser_clicked (GtkWidget *objet, gpointer user_data)
{

  GtkWidget *yasmine_qte_type_tri_decroissant = lookup_widget(objet, "yasmine_qte_type_tri_decroissant");
  GtkWidget *yasmine_qte_type_tri_croissant = lookup_widget(objet, "yasmine_qte_type_tri_croissant");
  //GtkTreeView *yasmine_quantite_type_treeView = GTK_TREE_VIEW(lookup_widget(objet, "yasmine_quantite_type_treeView"));

  // Clear the tree view
//vider_blood_quantities(yasmine_quantite_type_treeView);
 GtkWidget *yasmine_quantite_type_window , *w1 ;
    
     w1 = lookup_widget(objet, "yasmine_quantite_type_window");
     yasmine_quantite_type_window = create_yasmine_quantite_type_window();
     gtk_widget_show(yasmine_quantite_type_window);
     gtk_widget_hide(w1);

    GtkWidget *yasmine_quantite_type_treeView = lookup_widget(yasmine_quantite_type_window, "yasmine_quantite_type_treeView");
  // Populate the tree view with data
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(yasmine_qte_type_tri_decroissant))){
		
		blood_quantities_in_treeview(yasmine_quantite_type_treeView, 0);
 } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(yasmine_qte_type_tri_croissant))){

		blood_quantities_in_treeview(yasmine_quantite_type_treeView, 1);}
printf("actualiser \n");
}

// type le plus rare
void on_yasmine_home_navbar_typerare_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    char sangRare[20];
    char msg[100]; 
    GtkWidget *yasmine_sang_plusRare_label;
    GtkWidget *yasmine_home_window;
    GtkWidget *yasmine_sang_plusRare_window;

    yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
    gtk_widget_hide(yasmine_home_window);
    yasmine_sang_plusRare_window = create_yasmine_sang_plusRare_window();
    gtk_widget_show(yasmine_sang_plusRare_window);

    sang_rare(sangRare);

    int quantity = quantite_type(sangRare); // Fetch quantity for the rarest blood type

    yasmine_sang_plusRare_label = lookup_widget(yasmine_sang_plusRare_window, "yasmine_sang_plusRare_label");

    sprintf(msg, "le sang le plus rare est : %s et sa quantité est = %d mL", sangRare, quantity);

    gtk_label_set_text(GTK_LABEL(yasmine_sang_plusRare_label), msg);
}




// from home to ajout window
void
on_yasmine_home_ajouter_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data)
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_ajout_window;
yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
gtk_widget_hide(yasmine_home_window);
yasmine_ajout_window= create_yasmine_ajout_window();


	int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;


	int cin;
int ets;
char nom[20];
char prenom[20];char sexe[20] ;char type_sang[20] ; char donneur[20];int jour ; int mois ; int annee ; 

	GtkWidget *combobox = lookup_widget(yasmine_ajout_window, "yasmine_ajout_comboBox_Ets");
	GtkWidget *combo_donneur = lookup_widget(yasmine_ajout_window, "yasmine_ajout_id_donneur");
	FILE *f = fopen("ets.txt" , "r" ) ;

	if (f != NULL ) {
		while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ;
		 gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
		}

	}

//emna
FILE *f2 = fopen("donneurs.txt", "r");
	if (f2 != NULL ) {
		while (fscanf(f2, "%d %s %s %s %d %s %d %d %d\n", &cin, nom, prenom, sexe, &ets, type_sang,&jour,&mois,&annee) != EOF) {
		sprintf(donneur, "%d" , cin ) ;
		gtk_combo_box_append_text ( GTK_COMBO_BOX (combo_donneur ) , donneur ) ;
			}
	}

gtk_widget_show(yasmine_ajout_window);

}

// from home to update window
void
on_yasmine_home_modifier_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data)
                                     
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_update_window;
yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
gtk_widget_hide(yasmine_home_window);
yasmine_update_window= create_yasmine_update_window();


	int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;
//emna 

	int cin;
int ets;
char nom[20];
char prenom[20];char sexe[20] ;char type_sang[20] ; char donneur[20];int jour ; int mois ; int annee ; 

	GtkWidget *combobox = lookup_widget(yasmine_update_window, "yasmine_update_comboBox_ets");
	GtkWidget *combo_donneur = lookup_widget(yasmine_update_window, "yasmine_update_id_donneur");
	FILE *f = fopen("ets.txt" , "r" ) ;

	if (f != NULL ) {
		while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ;
		 gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
		}

	}

//emna
FILE *f2 = fopen("donneurs.txt", "r");
	if (f2 != NULL ) {
		while (fscanf(f2, "%d %s %s %s %d %s %d %d %d\n", &cin, nom, prenom, sexe, &ets, type_sang,&jour,&mois,&annee) != EOF) {
		sprintf(donneur, "%d" , cin ) ;
		gtk_combo_box_append_text ( GTK_COMBO_BOX (combo_donneur ) , donneur ) ;
			}
	}

gtk_widget_show(yasmine_update_window);
}

// from home to delete window
void
on_yasmine_home_supprimer_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data)
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_delete_window;

yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
gtk_widget_hide(yasmine_home_window);
yasmine_delete_window= create_yasmine_delete_window();
gtk_widget_show(yasmine_delete_window);
}



// delete
void on_yasmine_delete_button_clicked(GtkWidget *objet, gpointer user_data) {
    GtkWidget *yasmine_delete_id_exist;
    GtkWidget *yasmine_delete_entryId;

    yasmine_delete_entryId = lookup_widget(objet, "yasmine_delete_entryId");
    yasmine_delete_id_exist = lookup_widget(objet, "yasmine_delete_id_exist");

    gchar *id_str = gtk_entry_get_text(GTK_ENTRY(yasmine_delete_entryId));
    // Check if the input is empty
    if (strlen(id_str) == 0) {
        gtk_label_set_text(GTK_LABEL(yasmine_delete_id_exist), "ID field is empty!");
        return;
    }
    int id_to_delete = atoi(id_str);

    int trv = 0;
    don d;
    FILE *f = fopen("don.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %d %s %d %d %d %d %d\n",&d.id_du_don, &d.id_donneur,  d.type_de_sang, &d.id_ETS, &d.quantite_sang, &d.date.jour, &d.date.mois, &d.date.annee) != EOF) {
            if (d.id_du_don == id_to_delete) {
                trv = 1;
            } else {
                fprintf(f2, "%d %d %s %d %d %d %d %d\n",d.id_du_don, d.id_donneur,  d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
            }
        }

        fclose(f);
        fclose(f2);
        remove("don.txt");
        rename("nouv.txt", "don.txt");
    }

    if (trv != 1) {
        // ID not found
        gtk_label_set_text(GTK_LABEL(yasmine_delete_id_exist), "ID not found!");
        return; // Stop further execution
    }else {
	 gtk_label_set_text(GTK_LABEL(yasmine_delete_id_exist), "don deleted with success !");

	}

    // Refresh the treeview after deletion
    GtkWidget *yasmine_treeview = lookup_widget(objet, "yasmine_treeview");
    afficher_don(yasmine_treeview, "dont.txt" );
}






void on_yasmine_update_chercherBTN_clicked(GtkWidget *objet, gpointer user_data) {

//label msg for id existance
 GtkWidget *yasmine_update_label_id_exist = lookup_widget(objet, "yasmine_update_label_id_exist");  
//id don
GtkWidget *yasmine_update_label_Nom= lookup_widget(objet, "yasmine_update_label_Nom");
 GtkWidget *yasmine_update_Id_don = lookup_widget(objet, "yasmine_update_Id_don");
//id donneur
GtkWidget *yasmine_update_label_id_donneur = lookup_widget(objet, "yasmine_update_label_id_donneur");
 GtkWidget *yasmine_update_id_donneur = lookup_widget(objet, "yasmine_update_id_donneur");
//type de sang 
 GtkWidget *yasmine_update_label_typeSang= lookup_widget(objet,"yasmine_update_label_typeSang");

 GtkWidget *yasmine_update_comboBox_typeSang= lookup_widget(objet,"yasmine_update_comboBox_typeSang");
//ets
GtkWidget *yasmine_update_label_ETS = lookup_widget(objet,"yasmine_update_label_ETS");
 GtkWidget *yasmine_update_comboBox_ets= lookup_widget(objet,"yasmine_update_comboBox_ets");
//qte
 GtkWidget *yasmine_update_label_qt =lookup_widget(objet,"yasmine_update_label_qt");
 GtkWidget *yasmine_update_entry_spinbutton_qte= lookup_widget(objet,"yasmine_update_entry_spinbutton_qte");
//date
 GtkWidget *yasmine_update_label_date =lookup_widget(objet,"yasmine_update_label_date");

 GtkWidget * yasmine_update_label_jour =lookup_widget(objet,"yasmine_update_label_jour");
 GtkWidget *yasmine_update_jour_spinBtn=lookup_widget(objet,"yasmine_update_jour_spinBtn");

 GtkWidget * yasmine_update_label_mois=lookup_widget(objet,"yasmine_update_label_mois");
 GtkWidget *yasmine_update_mois_spinBtn= lookup_widget(objet,"yasmine_update_mois_spinBtn");

 GtkWidget * yasmine_update_label_annee=lookup_widget(objet,"yasmine_update_label_annee");
 GtkWidget *yasmine_update_annee_spinBtn= lookup_widget(objet,"yasmine_update_annee_spinBtn");

   // btn update 
GtkWidget * yasmine_update_button =lookup_widget(objet,"yasmine_update_button");

 // Check if ID exists in my data
 const gchar *id_str = gtk_entry_get_text(GTK_ENTRY(yasmine_update_Id_don));
if (strlen(id_str) == 0 || retrieve_don_data(atoi(id_str)).id_du_don == -1) {
    gtk_label_set_text(GTK_LABEL(yasmine_update_label_id_exist), 
                       strlen(id_str) == 0 ? "ID field is empty!" : "ID not found!");
    return;
}

// show hidden widgets
gtk_widget_show(yasmine_update_id_donneur);
gtk_widget_show(yasmine_update_label_id_donneur);
//type sang 
gtk_widget_show(yasmine_update_label_typeSang);
gtk_widget_show(yasmine_update_comboBox_typeSang);
//ets
gtk_widget_show(yasmine_update_label_ETS);
gtk_widget_show(yasmine_update_comboBox_ets);
//qte
gtk_widget_show(yasmine_update_label_qt);
gtk_widget_show(yasmine_update_entry_spinbutton_qte);
//date
gtk_widget_show(yasmine_update_label_date);
//jour
gtk_widget_show(yasmine_update_label_jour);
gtk_widget_show(yasmine_update_jour_spinBtn);
//mois
gtk_widget_show(yasmine_update_label_mois);
gtk_widget_show(yasmine_update_mois_spinBtn);
//annee
gtk_widget_show(yasmine_update_label_annee);
gtk_widget_show(yasmine_update_annee_spinBtn);
//btn 
gtk_widget_show(yasmine_update_button);

  // If ID exists, populate UI fields with retrieved data
int id_to_update = atoi(id_str);
don retrieved_data = retrieve_don_data(id_to_update);
const gchar *types_of_blood[] = {"A+", "A-", "B+", "B-","O+","O-" ,NULL};
int id_ets[] = {1,2, 3,4,5,6,7,8,9,10,11,-1};

// retrive data from combobox typde de sang 
int index = 0;
while (types_of_blood[index] != NULL) {
    if (strcmp(types_of_blood[index], retrieved_data.type_de_sang) == 0) {
        gtk_combo_box_set_active(yasmine_update_comboBox_typeSang, index);
        break;
    }
    index++;
}
// retrive data from combobox ets
int i = 0;
while (id_ets[i] != -1) {
    if (id_ets[i] == retrieved_data.id_ETS) {
        gtk_combo_box_set_active(yasmine_update_comboBox_ets, i);
        break;
    }
    i++;
}

//retrieved data from spin btn 

gtk_spin_button_set_value(GTK_SPIN_BUTTON(yasmine_update_entry_spinbutton_qte), retrieved_data.quantite_sang);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(yasmine_update_jour_spinBtn), retrieved_data.date.jour);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(yasmine_update_mois_spinBtn), retrieved_data.date.mois);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(yasmine_update_annee_spinBtn), retrieved_data.date.annee);


}



// update
void on_yasmine_update_button_clicked  (GtkWidget *objet, gpointer user_data){
int modified;
GtkWidget* yasmine_update_window;


GtkWidget* yasmine_update_id_donneur;
GtkWidget* yasmine_update_Id_don;

GtkWidget* yasmine_update_comboBox_typeSang;
GtkWidget* yasmine_update_comboBox_ets;
GtkWidget* yasmine_update_entry_spinbutton_qte;
GtkWidget* yasmine_update_jour_spinBtn;
GtkWidget* yasmine_update_mois_spinBtn;
GtkWidget* yasmine_update_annee_spinBtn;

yasmine_update_Id_don = lookup_widget(objet, "yasmine_update_Id_don");

//combobox
yasmine_update_id_donneur= lookup_widget(objet,"yasmine_update_id_donneur");
yasmine_update_comboBox_typeSang= lookup_widget(objet,"yasmine_update_comboBox_typeSang");
yasmine_update_comboBox_ets= lookup_widget(objet,"yasmine_update_comboBox_ets");
//spin btn
yasmine_update_entry_spinbutton_qte= lookup_widget(objet,"yasmine_update_entry_spinbutton_qte");
yasmine_update_jour_spinBtn= lookup_widget(objet,"yasmine_update_jour_spinBtn");
yasmine_update_mois_spinBtn= lookup_widget(objet,"yasmine_update_mois_spinBtn");
yasmine_update_annee_spinBtn= lookup_widget(objet,"yasmine_update_annee_spinBtn");


   don nouveau;
nouveau.id_du_don = atoi(gtk_entry_get_text(GTK_ENTRY(yasmine_update_Id_don)));


//combobox
strcpy(nouveau.type_de_sang ,gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_update_comboBox_typeSang)));
nouveau.id_ETS = atoi(gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_update_comboBox_ets)) ) ;
nouveau.id_donneur = atoi(gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_update_id_donneur)));
//spin btn
nouveau.quantite_sang = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_update_jour_spinBtn)) ;
nouveau.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_update_jour_spinBtn))  ;
nouveau.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_update_mois_spinBtn)) ;
nouveau.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_update_annee_spinBtn));


 modified = modifier_yas(nouveau.id_du_don, nouveau);
    printf("Modifier function called\n");
    if (modified != 1) {

        printf("ID snot found!");
    } else {
        printf("Modification successful\n");
    }

GtkWidget *yasmine_home_window;

 GtkTreeView *yastreeview;

yasmine_update_window= lookup_widget(objet, "yasmine_update_window");
gtk_widget_hide(yasmine_update_window);

yasmine_home_window= create_yasmine_home_window();
gtk_widget_show(yasmine_home_window);

   yastreeview = lookup_widget(objet, "yasmine_treeview");
   afficher_don(yastreeview, "don.txt");

}


// ajout 
void on_yasmine_ajout_button_clicked(GtkWidget* objet, gpointer user_data) {
    GtkWidget *yasmine_ajout_id_don = lookup_widget(objet, "yasmine_ajout_id_don");
    GtkWidget *yasmine_ajout_id_donneur = lookup_widget(objet, "yasmine_ajout_id_donneur");
    GtkWidget *yasmine_ajout_comboBox_typeSang = lookup_widget(objet, "yasmine_ajout_comboBox_typeSang");
    GtkWidget *yasmine_ajout_comboBox_Ets = lookup_widget(objet, "yasmine_ajout_comboBox_Ets");
    GtkWidget *yasmine_ajout_entry_spinbutton_qte = lookup_widget(objet, "yasmine_ajout_entry_spinbutton_qte");
    GtkWidget *yasmine_ajout_jour_spinBtn = lookup_widget(objet, "yasmine_ajout_jour_spinBtn");
    GtkWidget *yasmine_ajout_mois_spinBtn = lookup_widget(objet, "yasmine_ajout_mois_spinBtn");
    GtkWidget *yasmine_ajout_annee_spinBtn = lookup_widget(objet, "yasmine_ajout_annee_spinBtn");

    don d;
    GtkWidget *yasmine_ajout_label_id_exist = lookup_widget(objet, "yasmine_ajout_label_id_exist");

    char qte_char[20];

    // Check for empty input fields
    const gchar *id_don_text = gtk_entry_get_text(GTK_ENTRY(yasmine_ajout_id_don));
    const gchar *id_donneur_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_ajout_id_donneur));
    const gchar *type_sang_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_ajout_comboBox_typeSang));
    const gchar *ets_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_ajout_comboBox_Ets));

    d.quantite_sang = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_ajout_entry_spinbutton_qte));
    sprintf(qte_char, "%d", d.quantite_sang);

    if (strlen(id_don_text) == 0 || strlen(id_donneur_text) == 0 || strlen(ets_text) == 0 ||
        strlen(type_sang_text) == 0 || strlen(qte_char) == 0) {
        gtk_widget_show(yasmine_ajout_label_id_exist);

        if (strlen(id_don_text) == 0 || strlen(id_don_text) != 4) {
            gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "La longueur de l'iD du don doit être de 4 chiffres et non vide !");
        } else if (strlen(id_donneur_text) == 0) {
            gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "L'ID du donneur est vide");
        } else if (strlen(type_sang_text) == 0) {
            gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "Type de sang est vide!");
        } else if (strlen(ets_text) == 0) {
            gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "ID ETS est vide !");
        } else if (strlen(qte_char) == 0) {
            gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "quantité du sang est vide!");
        }

        return;
    }

int x ;
// Get values from widgets
x = isNumber(id_don_text, 2);
if (x != 1) {
    gtk_widget_show(yasmine_ajout_label_id_exist);
    gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), "ID du don must be a number of len 2!");
    return;
}
d.id_du_don = atoi(id_don_text);
x = isNumber(id_donneur_text, 4);
//combobox
d.id_donneur = atoi(id_donneur_text);
strcpy(d.type_de_sang ,type_sang_text); 
d.id_ETS = atoi(ets_text);
// spin btn
    d.quantite_sang = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_ajout_entry_spinbutton_qte));
    d.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_ajout_jour_spinBtn));
    d.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_ajout_mois_spinBtn));
    d.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(yasmine_ajout_annee_spinBtn));


 FILE *f = fopen("don.txt", "r");
if (f != NULL) {
    don temp;
    int unique = 1;
    while (fscanf(f, "%d %d %s %d %d %d %d %d",
                  &temp.id_du_don, &temp.id_donneur, temp.type_de_sang, &temp.id_ETS,
                  &temp.quantite_sang, &temp.date.jour, &temp.date.mois, &temp.date.annee) == 8) {
        if (temp.id_du_don == d.id_du_don) {
            unique = 0; // ID already exists
            break;
        }
    }
    fclose(f);

    if (unique == 0) {
      GtkWidget *yasmine_ajout_label_id_exist = lookup_widget(objet, "yasmine_ajout_label_id_exist");
gtk_widget_show(yasmine_ajout_label_id_exist);
gtk_label_set_text(GTK_LABEL(yasmine_ajout_label_id_exist), " id du don exists ! try again !");
         
        return; 
    }
}



    f = fopen("don.txt", "a+");
    if (f != NULL) {
        fprintf(f, "%d %d %s %d %d %d %d %d\n",d.id_du_don, d.id_donneur, d.type_de_sang, d.id_ETS, d.quantite_sang, d.date.jour, d.date.mois, d.date.annee);
        fclose(f);
}

 // Hide the current window and show the home window
    GtkWidget *yasmine_ajout_window = lookup_widget(objet, "yasmine_ajout_window");
    gtk_widget_hide(yasmine_ajout_window);
 
    GtkWidget *yasmine_home_window = create_yasmine_home_window();

    gtk_widget_show(yasmine_home_window);

     GtkTreeView *yastreeview = GTK_TREE_VIEW(lookup_widget(objet, "yasmine_treeview"));

    // Clear the existing data in the tree view
    //vider_yas(yastreeview);

    // Refresh the tree view with updated data
    afficher_don(yastreeview , "don.txt");


}

//actualiser
void on_yasmine_home_actualiser_button_clicked (GtkWidget     *objet, gpointer   user_data)
{
GtkWidget *yasmine_home_window, *w1;

    w1 = lookup_widget(objet, "yasmine_home_window");
    yasmine_home_window = create_yasmine_home_window();
    gtk_widget_show(yasmine_home_window);
    gtk_widget_hide(w1);

   

    GtkWidget *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    vider_yas(yasmine_treeview);

  
        afficher_don(yasmine_treeview, "don.txt" );
   

}

// from delete to home
void
on_yasmine_delete_retourBtn_clicked    (GtkWidget     *objet, gpointer         user_data)
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_delete_window;

yasmine_delete_window = lookup_widget(objet, "yasmine_delete_window");
gtk_widget_hide(yasmine_delete_window);
yasmine_home_window= create_yasmine_home_window();
		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
gtk_widget_show(yasmine_home_window);
}




// from update to home
void
on_yasmine_update_return_btn_clicked   (GtkWidget     *objet, gpointer         user_data)
{

GtkWidget *yasmine_home_window;
GtkWidget *yasmine_update_window;

yasmine_update_window = lookup_widget(objet, "yasmine_update_window");
gtk_widget_hide(yasmine_update_window);
yasmine_home_window= create_yasmine_home_window();
		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
gtk_widget_show(yasmine_home_window);
}


// from ajout window to home
void
on_yasmine_ajout_return_home_clicked  (GtkWidget*   objet, gpointer   user_data)
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_ajout_window;

yasmine_ajout_window = lookup_widget(objet, "yasmine_ajout_window");
gtk_widget_hide(yasmine_ajout_window);
yasmine_home_window= create_yasmine_home_window();
		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
gtk_widget_show(yasmine_home_window);
}

// from sang plus rare to home 
void on_yasmine_sang_plusRare_retour_btn_clicked  (GtkWidget*   objet, gpointer   user_data)                
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_sang_plusRare_window;

yasmine_sang_plusRare_window = lookup_widget(objet, "yasmine_sang_plusRare_window");
gtk_widget_hide(yasmine_sang_plusRare_window);
yasmine_home_window= create_yasmine_home_window();
		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
gtk_widget_show(yasmine_home_window);
}

// from delete confirm to delete
void
on_yasmine_delete_retour_btn_clicked  (GtkWidget*   objet, gpointer   user_data)         
{
GtkWidget *yasmine_delete_confirm_window;
GtkWidget *yasmine_delete_window;

yasmine_delete_confirm_window = lookup_widget(objet, "yasmine_delete_confirm_window");
gtk_widget_hide(yasmine_delete_confirm_window);
yasmine_delete_window= create_yasmine_delete_window();
gtk_widget_show(yasmine_delete_window);
}


// from qte type retour to  home 
void on_yasmine_quantite_type_retourBtn_clicked (GtkWidget*   objet, gpointer   user_data) 
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_quantite_type_window;

yasmine_quantite_type_window = lookup_widget(objet, "yasmine_quantite_type_window");
gtk_widget_hide(yasmine_quantite_type_window);
yasmine_home_window= create_yasmine_home_window();
		  GtkTreeView *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    		afficher_don(yasmine_treeview, "don.txt" );
gtk_widget_show(yasmine_home_window);

}

// ets show input  home filter
void
on_yasmine_home_filtre_ETS_BTN_clicked (GtkWidget*   objet,gpointer         user_data)
{
GtkWidget *yasmine_home_window;
GtkWidget *yasmine_home_filtre_idETScombox = lookup_widget(objet, "yasmine_home_filtre_idETScombox");

yasmine_home_window = lookup_widget(objet, "yasmine_home_window");
 

	int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

FILE *f = fopen("ets.txt" , "r" ) ;

if (f != NULL ) {
		while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ;
		 gtk_combo_box_append_text ( GTK_COMBO_BOX (yasmine_home_filtre_idETScombox ) , IDstr ) ;
		}

	}


gtk_widget_show(yasmine_home_filtre_idETScombox); 


}

// ets show input home filter
void
on_yasmine_home_filtre_TS_BTN_clicked  (GtkWidget*   objet, gpointer         user_data)
{
 GtkWidget *yasmine_home_filtre_typesang_combox  = lookup_widget(objet, "yasmine_home_filtre_typesang_combox");
gtk_widget_show(yasmine_home_filtre_typesang_combox);
}

// filtre home 
void on_yasmine_home_filtre_validerBtn_clicked(GtkWidget *objet, gpointer user_data) {

GtkWidget *yasmine_home_window, *w1;

    w1 = lookup_widget(objet, "yasmine_home_window");
    yasmine_home_window = create_yasmine_home_window();
    gtk_widget_show(yasmine_home_window);
    gtk_widget_hide(w1);

    GtkWidget *yasmine_home_filtre_idETScombox = lookup_widget(objet, "yasmine_home_filtre_idETScombox");
    GtkWidget *yasmine_home_filtre_typesang_combox = lookup_widget(objet, "yasmine_home_filtre_typesang_combox");

    char *selected_ets = gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_home_filtre_idETScombox));
    char *selected_blood = gtk_combo_box_get_active_text(GTK_COMBO_BOX(yasmine_home_filtre_typesang_combox));
    int ets_to_find; 

    GtkWidget *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");
    vider_yas(yasmine_treeview);

    if (selected_ets != NULL && selected_blood != NULL) {
       ets_to_find= atoi(selected_ets);
        bothFilter("don.txt", ets_to_find, selected_blood);
	afficher_don(yasmine_treeview, "filtered.txt" );

    } else if (selected_ets != NULL) {
        ets_to_find= atoi(selected_ets);
        ETSFilter("don.txt", ets_to_find);
        afficher_don(yasmine_treeview, "filtered_ETS.txt" );
    } else if (selected_blood != NULL) {
       BLOODFilter("don.txt", selected_blood);
       afficher_don(yasmine_treeview, "filtered_blood.txt" );
    } else {
        afficher_don(yasmine_treeview, "don.txt" );
    }


}








void
on_button_Gestion_Donneurr_clicked     (GtkWidget   *objet, gpointer         user_data)
{
                  GtkWidget *affichage = create_affichage ();
  
		  GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
		  afficher_donneur(treeviewEmna) ; 

		   GtkWidget *Espace_Infirmier = lookup_widget(objet , "Espace_Infirmier");
		  gtk_widget_destroy(Espace_Infirmier) ;
		  gtk_widget_show (affichage);
}


void
on_button_gestion_Rdv_clicked          (GtkWidget   *objet, gpointer         user_data)
{
	         GtkWidget *Interface_De_la_page_Dacceuil  = create_Interface_De_la_page_Dacceuil ();
 
		   GtkWidget *Espace_Infirmier = lookup_widget(objet , "Espace_Infirmier");
		  gtk_widget_destroy(Espace_Infirmier) ;
		 GtkWidget *treeview113= lookup_widget(Interface_De_la_page_Dacceuil, "treeview113");
		 display_rdv(treeview113,"RDV.txt");
		int ID , Capacite ;
	char Nom[30] , Adresse[30] , Region[30] , IDstr[30] ;

	GtkWidget *combobox = lookup_widget(Interface_De_la_page_Dacceuil, "comboboxentry1");
	FILE *f = fopen("ets.txt" , "r" ) ; 
	if (f != NULL ) {
	while(fscanf(f,"%d, %29[^,], %29[^,], %29[^,], %d \n",&ID,Nom,Adresse,Region,&Capacite ) != EOF ) {
		sprintf(IDstr , "%d" , ID ) ; 
	  gtk_combo_box_append_text ( GTK_COMBO_BOX (combobox ) , IDstr ) ;
	}

	}

		  gtk_widget_show (Interface_De_la_page_Dacceuil );
}


void
on_button_Deconnexion_clicked   (GtkWidget   *objet, gpointer         user_data)
{
	GtkWidget *Espace_Infirmier = lookup_widget(objet , "Espace_Infirmier");
	gtk_widget_destroy(Espace_Infirmier) ;
  	GtkWidget *windowAuthentification = create_windowAuthentification ();
  	gtk_widget_show (windowAuthentification);
}


void
on_button_Retour_Gestion_clicked   (GtkWidget   *objet, gpointer         user_data)
{
	          GtkWidget *Espace_Infirmier = create_Espace_Infirmier ();
  

		   GtkWidget *affichage = lookup_widget(objet , "affichage");
		  gtk_widget_destroy(affichage) ;
		  gtk_widget_show (Espace_Infirmier);
}


void
on_button_retour_rdddv_clicked   (GtkWidget   *objet, gpointer         user_data)
{
			         GtkWidget *Espace_Infirmier  = create_Espace_Infirmier();
 
		   GtkWidget *Interface_De_la_page_Dacceuil = lookup_widget(objet , "Interface_De_la_page_Dacceuil");
		  gtk_widget_destroy(Interface_De_la_page_Dacceuil) ;
		  gtk_widget_show (Espace_Infirmier );
}


void
on_quit_All_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_main_quit();
}


void
on_button_Disconnect_yass_clicked      (GtkWidget   *objet, gpointer         user_data)
{
		
	GtkWidget *yasmine_home_window = lookup_widget(objet , "yasmine_home_window");
	gtk_widget_destroy(yasmine_home_window) ;
  	GtkWidget *windowAuthentification = create_windowAuthentification ();
  	gtk_widget_show (windowAuthentification);


}

///////////////////////////////////
void
on_button_search_yass_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    	GtkWidget *yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");
	GtkWidget *yasmine_treeview = lookup_widget(yasmine_home_window, "yasmine_treeview");

    yasmine_home_window = lookup_widget(objet_graphique, "yasmine_home_window");		

    GtkWidget *entry_search_yass = lookup_widget(objet_graphique, "entry_search_yass");

    const char *selected = gtk_entry_get_text(GTK_ENTRY(entry_search_yass));

  
   vider_yas(yasmine_treeview);

	search_yass("don.txt",selected);
	afficher_don(yasmine_treeview,"searchedDon.txt");
}





void
on_ghazi_chercher_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_search_emna_buttonn_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


gboolean
on_Authentification_buttonLogin_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *Authentification_buttonLogin= (lookup_widget(widget,"Authentification_buttonLogin") ) ;
	apply_style_bg(Authentification_buttonLogin , "#E2A36D") ;
  return FALSE;
}


gboolean
on_label_bienvenueAdmin_expose_event   (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label_bienvenueAdmin") ) ;
  GdkColor color;
    gdk_color_parse("#C7B342", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Georgia 20 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);

  return FALSE;
}


gboolean
on_label141_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label141") ) ;
  GdkColor color;
    gdk_color_parse("#C7B342", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Georgia 20 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);

  return FALSE;
}


gboolean
on_comboboxentry1_expose_event         (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{


  return FALSE;
}


gboolean
on_label_bienvenue_expose_event        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label_bienvenue") ) ;
  GdkColor color;
    gdk_color_parse("#C7B342", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Georgia 20 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);
  return FALSE;
}


gboolean
on_label133_medd_focus                 (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label133_medd") ) ;
  GdkColor color;
    gdk_color_parse("#C7B342", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Georgia 20 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);

  return FALSE;
}


gboolean
on_label_Welcome_expose_event          (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label_Welcome") ) ;
  GdkColor color;
    gdk_color_parse("#C7B342", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Georgia 20 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);

  return FALSE;
}


gboolean
on_label_Authentification_UserName_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label_Authentification_UserName") ) ;
  GdkColor color;
    gdk_color_parse("#A2C742", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Roboto-Bold 16 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);
	
  return FALSE;
}


gboolean
on_label_Authentification_Password_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GtkWidget *label133= (lookup_widget(widget,"label_Authentification_Password") ) ;
  GdkColor color;
    gdk_color_parse("#A2C742", &color);
    gtk_widget_modify_fg(label133, GTK_STATE_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("Roboto-Bold 16 ");
    gtk_widget_modify_font(GTK_WIDGET(label133), font_desc);
    pango_font_description_free(font_desc);

  return FALSE;
}

