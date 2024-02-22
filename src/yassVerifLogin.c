#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "yassVerifLogin.h"

int  yassVerifLogin(char usernameLogin[], char passwordLogin[])
{

FILE *f;
char nom[50];
char prenom[50];
char username[50];
char password[50];
int role;

f=fopen("utilisateur.txt","r");

	   while(fscanf(f, "%s %s %s %s %d",nom,prenom,username,password,&role)!= EOF)
	{
	if( (strcmp(username,usernameLogin) == 0) && (strcmp(password,passwordLogin) == 0) ){
			fclose(f);
				return 1;
			}	
	  }
	fclose(f);
	 return 0;

}
