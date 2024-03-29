/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "ets.h"
#include "interface.h"
#include "support.h"
#include "fonction.h"
#include "yassAjoutRegister.h"
#include "yassVerifLogin.h"
#include "fonctions.h"



int
main (int argc, char *argv[])
{
  GtkWidget *windowAuthentification;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory ("../pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */

        windowAuthentification = create_windowAuthentification ();
	GtkWidget *Authentification_buttonLogin= (lookup_widget(windowAuthentification,"Authentification_buttonLogin") ) ;
	apply_style_bg(Authentification_buttonLogin , "#E2A36D") ;
	gtk_widget_show (windowAuthentification);

 /*********GHazii ****/ 
//	GtkWidget *Interface_De_la_page_Dacceuil;
//	Interface_De_la_page_Dacceuil = create_Interface_De_la_page_Dacceuil ();
//	gtk_widget_show (Interface_De_la_page_Dacceuil);

  
/********* EMNA ****/  

  //GtkWidget *affichage = create_affichage ();
  
  //  GtkTreeView *treeviewEmna = lookup_widget(affichage, "treeview1");
  //afficher_donneur(treeviewEmna) ; 
  // gtk_widget_show (affichage);
  

 /***** YASSMINE ***/ 
//	GtkWidget *yasmine_home_window = create_yasmine_home_window();

//	gtk_widget_show (yasmine_home_window);
  gtk_main ();
  return 0;
}

