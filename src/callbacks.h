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

void
on_button_search_key_ETS_clicked       (GtkWidget *objet_graphique, gpointer user_data);
