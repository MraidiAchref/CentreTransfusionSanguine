#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "yassAjoutRegister.h"

void yassAjoutRegister(char nom[], char prenom[], char username[], char password[], int role){

FILE *f;

f=fopen("utilisateur.txt","a+");
	if(f != NULL){

		fprintf(f,"%s %s %s %s %d \n",nom,prenom,username,password,role);

fclose(f);
	}else printf("impossible d'ouvrir le fichier \n");

}
