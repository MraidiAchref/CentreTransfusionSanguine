#include <gtk/gtk.h>


void
on_button_Firas_Modifier_clicked (GtkButton *button,gpointer user_data);

void
on_button_Firas_Supprimer_clicked (GtkButton *button,gpointer user_data);

void
on_button_Firas_Chercher_clicked (GtkWidget *objet_graphique,gpointer user_data);

void
on_button_Firas_Ajouter_clicked (GtkButton *button,gpointer user_data);

void
on_button_Firas_Valider_clicked (GtkWidget *objet_graphique,gpointer user_data);

gboolean
on_entry1_focus_in_event (GtkWidget *widget,GdkEventFocus *event,gpointer user_data);

void
on_calendar_day_selected (GtkCalendar *calendar, gpointer user_data);

void
on_button_Firas_SuppID_clicked (GtkWidget *objet_graphique, gpointer user_data);


void
on_button_Fir_OK_clicked (GtkWidget *objet_graphique,gpointer user_data);

void
on_button_Fir_Confirm_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_radiobutton_Firas_F_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_radiobutton_Firas_H_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_radiobutton_Firas_Oui_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_radiobutton_Firas_Non_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_button_Fir_Retour_clicked (GtkButton *button,gpointer user_data);

void
on_Fir_Retour_clicked (GtkButton *button,gpointer user_data);

void
on_checkbutton_Firas_Med_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_checkbutton_Firas_Resp_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_checkbutton_Firas_Inf_toggled (GtkToggleButton *togglebutton,gpointer user_data);

gboolean
on_entry_Fir_DOB_focus_in_event (GtkWidget *widget,GdkEventFocus *event,gpointer user_data);

void
on_calendar_Fir_2_day_selected (GtkCalendar *calendar,gpointer user_data);

void
on_button_Firas_Afficher_clicked (GtkWidget *objet_graphique,gpointer user_data);

gboolean
on_drawingarea_Firas_button_press_event(GtkWidget *widget,GdkEventButton *event,gpointer user_data);



void
on_button_Firas_stat_clicked           (GtkButton       *button,
                                        gpointer         user_data);



void
on_treeview_Firas_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

gboolean
on_treeview_Firas_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_treeview_Firas_move_cursor          (GtkTreeView     *treeview,
                                        GtkMovementStep  step,
                                        gint             count,
                                        gpointer         user_data);

void
on_treeview_Firas_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

gboolean on_treeview_Firas_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

gboolean
on_treeview_Firas_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_edit_clicked                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Delete_clicked                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Add_clicked                         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_edit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Add_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button_deconnecter_achref_ets_clicked(GtkWidget*graphic_object,gpointer user_data);

void
on_button_retour_addEts_achref_clicked (GtkWidget *graphic_object ,gpointer user_data);


void
on_button_retour_modifierEts_achref_clicked(GtkWidget *graphic_object ,gpointer user_data);

void
on_addButton_achref_ets_clicked (GtkWidget*graphic_button,gpointer user_data);

void
on_modifierButton_achref_ets_clicked(GtkWidget*graphic_button,gpointer user_data) ;

void
on_button_confirmer_addEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_confirm_triage_ets_clicked   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_OK_modifierEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_confirmer_modifierEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_retour_deleteEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_confirmer_deleteEts_achref_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_supprimerButton_achref_ets_clicked  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_togglebutton1_toggled               (GtkWidget *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton1_released              (GtkButton       *button,
                                        gpointer         user_data);


void
on_Authentification_buttonLogin_clicked
                                        (GtkWidget       *graphic_object,
                                        gpointer         user_data);

void
on_Refresh_button_achref_clicked       (GtkWidget       *graphic_object,
                                        gpointer         user_data);

gboolean
on_treeviewETS_achref_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
void on_AddETS_activate(GtkMenuItem *menuitem, gpointer user_data);
void
on_DeleteETS_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_editETS_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_treeviewETS_achref_button_press_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);



void
on_togglebutton_Fir_Pass_Ajout_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton_Fir_Con_Ajout_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton_Fir_Pass_Modif_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton_Fir_Con_Modif_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_Retour_Supp_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_lum_button_admin_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_search_firas_clicked (GtkWidget *objet_graphique, gpointer user_data);

gboolean
on_drawingarea_Firas_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_togglebutton_Firas_clicked  (GtkWidget *objet_graphique,gpointer user_data);
gboolean
on_fixed_stat_ets_proximity_in_event   (GtkWidget       *widget,
                                        GdkEventProximity *event,
                                        gpointer         user_data);



void
on_notebook2_switch_page               (GtkWidget     *notebook,
                                        GtkNotebookPage *page,
                                        guint            page_num,
                                        gpointer         user_data);


gboolean
on_label_stat_achref_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_buttonSearchEts_clicked             (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Copy_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Paste_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
void
on_PasteETS_activate  (GtkMenuItem *menuitem, gpointer  user_data);
void
on_copyETS_activate (GtkMenuItem *menuitem, gpointer user_data);

void
on_button25_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button23_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data);


//******GHAZI ******/ 

void
on_button2_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button3_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button4_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button16_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button7_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button6_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button8_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9_ghazi_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button17_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button11_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button14_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button12_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_affiche_ghazi_clicked        (GtkButton       *button,
                                        gpointer         user_data);


void
on_treeview111_columns_changed         (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button14_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button00_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_chercher_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_button19_help_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button18_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button99_ghazi_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton1_rester_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2_deconnecter_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button17_ghazi_rdv_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton2_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton1_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton2_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton1_ghazi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button25_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button23_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data);


/******** EMNA ******/ 

void on_ajouter_emna_clicked                (GtkWidget       *objet_graphique ,gpointer        user_data);

void on_supprimer_emna_clicked              (GtkWidget       *objet_graphique ,gpointer        user_data);

void on_modifier_emna_clicked               (GtkWidget       *objet_graphique ,gpointer        user_data);




void on_retour_bekri_clicked                (GtkWidget       *objet_graphique ,gpointer        user_data);
void on_valider_bekri_clicked               (GtkWidget       *objet_graphique ,gpointer        user_data);




void on_retour_emnabek_clicked              (GtkWidget       *objet_graphique ,gpointer        user_data);
void on_valider_modification_clicked        (GtkWidget       *objet_graphique ,gpointer        user_data);
void on_cherchez_emnabek_clicked            (GtkWidget       *objet_graphique  ,gpointer         user_data);



void on_supprimerr_suppression_clicked      (GtkWidget       *objet_graphique ,gpointer        user_data);
void on_retour_suppression_clicked          (GtkWidget       *objet_graphique ,gpointer        user_data);






void on_listeRDV_emna_clicked               (GtkWidget       *objet_graphique ,gpointer         user_data);

void on_moyRDV_emna_clicked                 (GtkWidget       *objet_graphique, gpointer         user_data);




void on_retour_stat1_clicked                (GtkWidget       *objet_graphique, gpointer         user_data);

void on_retour_stat2_clicked                (GtkWidget       *objet_graphique, gpointer         user_data);



void on_affiche_sta1_clicked                (GtkWidget       *objet_graphique, gpointer         user_data);
void on_affiche_stat2_clicked               (GtkWidget       *objet_graphique, gpointer         user_data);





void
on_radiobutton_femme_emnabek_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_homme_emnabek_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_femme_bekri_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_homme_bekri_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


/*** YASSMINE ***/ 



void on_yasmine_register_button_clicked(GtkWidget *objet_graphique, gpointer user_data);

void on_yasmine_login_button_clicked(GtkWidget *objet_graphique, gpointer user_data);
////////////////////////////////////////////////////////////////////////////////////////////////::
void
on_yasmine_home_navbar_viewAll_clicked  (GtkWidget *objet_graphique,  gpointer   user_data);

void on_yasmine_home_navbar_qtdispo_clicked  (GtkWidget *objet_graphique,  gpointer   user_data);
// from home to type plus rare 
void on_yasmine_home_navbar_typerare_clicked (GtkWidget *objet_graphique,  gpointer   user_data);

void on_yasmine_home_ajouter_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data);

void on_yasmine_home_modifier_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data);

void
on_yasmine_home_supprimer_button_clicked (GtkWidget *objet_graphique,  gpointer   user_data);
                                       
void
on_yasmine_ajout_confirm_yes_radioBtn_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_yasmine_ajout_confirm_non_radioBtn_clicked
                                        (GtkButton       *button,
                                       gpointer         user_data);
//chercher btn before update 
void on_yasmine_update_chercherBTN_clicked  (GtkWidget     *objet, gpointer         user_data);

//update
void
on_yasmine_update_button_clicked       (GtkWidget *objet, gpointer user_data);

//delete 
void on_yasmine_delete_button_clicked   (GtkWidget     *objet, gpointer   user_data);

void
on_yasmine_delete_checkbutton_non_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_yasmine_update_confirm_checkbtn_oui_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
//hneeeeee
void
on_yasmine_treeview_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void on_yasmine_home_retour_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_yasmine_ajout_button_clicked        (GtkWidget*   objet, gpointer   user_data);

void
on_yasmine_ajout_button_afficher_clicked  (GtkWidget*   objet, gpointer user_data);

void on_yasmine_home_actualiser_button_clicked (GtkWidget     *objet, gpointer   user_data);

void on_yasmine_delete_retourBtn_clicked    (GtkWidget     *objet, gpointer         user_data);



void
on_yasmine_update_return_btn_clicked    (GtkWidget     *objet, gpointer         user_data);

void
on_yasmine_ajout_confirm_btn_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_yasmine_delete_confirm_btn_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_yasmine_update_confirm_btn_activate (GtkButton       *button,
                                        gpointer         user_data);
// from ajout window to home
void  on_yasmine_ajout_return_home_clicked  (GtkWidget*   objet, gpointer   user_data);

// from sang plus rare to home
void on_yasmine_sang_plusRare_retour_btn_clicked  (GtkWidget*   objet, gpointer   user_data);
// from delete confirm to home
void on_yasmine_delete_retour_btn_clicked  (GtkWidget*   objet, gpointer   user_data) ;

// trier btn qte type 
void
on_yasmine_quantite_type_validerTri_clicked (GtkWidget*   objet, gpointer   user_data) ;
// retour from qte type to home 
void
on_yasmine_quantite_type_retourBtn_clicked (GtkWidget*   objet, gpointer   user_data) ;

void
on_yasmine_qte_type_btn_actualiser_clicked  (GtkWidget*   objet, gpointer   user_data) ;
                                     

void
on_yasmine_qte_type_tri_decroissant_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_yasmine_qte_type_tri_croissant_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_yasmine_home_filtre_ETS_BTN_clicked  (GtkWidget*   objet,gpointer         user_data);

void
on_yasmine_home_filtre_TS_BTN_clicked  (GtkWidget*   objet,gpointer         user_data);

void
on_yasmine_home_filtre_validerBtn_clicked (GtkWidget*   objet, gpointer         user_data);



void
on_button_Gestion_Donneurr_clicked  (GtkWidget   *objet, gpointer         user_data);

void
on_button_gestion_Rdv_clicked  (GtkWidget   *objet, gpointer         user_data);

void
on_button_Deconnexion_clicked  (GtkWidget   *objet, gpointer         user_data);

void
on_button_Retour_Gestion_clicked  (GtkWidget   *objet, gpointer         user_data);

void
on_button_retour_rdddv_clicked  (GtkWidget   *objet, gpointer         user_data);

void
on_quit_All_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_Disconnect_yass_clicked      (GtkWidget   *objet, gpointer         user_data);

void
on_button_search_yass_clicked   (GtkWidget   *objet, gpointer         user_data);

void
on_ghazi_chercher_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_search_emna_buttonn_clicked         (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_Authentification_buttonLogin_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label_bienvenueAdmin_expose_event   (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label141_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_comboboxentry1_expose_event         (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label_bienvenue_expose_event        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label133_medd_focus                 (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label_Welcome_expose_event          (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label_Authentification_UserName_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_label_Authentification_Password_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);
