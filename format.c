/*
** Code written by TheFiremanH.
** All of that is openSource, your welcome.
**        """   
** -\-    _|__  
**  |\___/  ' \ 
**  \     /(((/ 
**   \___/)))/  
** Use this code to remove all non escential spaces and tabulabulations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
	int modifs = 0;
	int modifsTmp = 1;
	char nomDeFichier[255];
	FILE* fichier = NULL;
	FILE* temp = NULL;

	printf("\nEntrer le nom de fichier : ");
	scanf("%s", nomDeFichier);
	printf("\n***\nFichier confirmé : %s\n***", nomDeFichier);
	
	int caracterePrecedent = 0;
	int caractereActuel = 0;
	while (modifsTmp != 0)
	{
		modifsTmp = 0;
		bool recordIt = false;
		temp = tmpfile();
		fichier = fopen(nomDeFichier, "r+");
		if (temp == NULL || fichier == NULL) 
		{ 
			printf("\nUnable to create temp file"); 
			return 0; 
		}
		rewind(temp);
		do
		{
			caractereActuel = fgetc(fichier);
			printf("\nChecking %d (%c), previously checking %d (%c)", caractereActuel, caractereActuel, caracterePrecedent, caracterePrecedent);
			if (caractereActuel != EOF)
			{
				if (caractereActuel == '\n') 
				{
					if (caracterePrecedent == ' ') // si le caractere avant un retour est un espace
					{
						recordIt = false; // ne pas l'enregistrer
					}
					if (caracterePrecedent == '\t')
					{
						recordIt = false; // ne pas l'enregistrer 
					}
				}
				if (recordIt)
				{
					fputc(caracterePrecedent, temp);
					printf("\n vvv Caractere %d (%c) was saved", caracterePrecedent, caracterePrecedent);
				}
				else
				{
					printf("\n xxx Caractere %d (%c) was not saved", caracterePrecedent, caracterePrecedent);
					modifs++;
					modifsTmp++;
				}
				recordIt = true;
				caracterePrecedent = caractereActuel;
			}
			else
			{
				printf("\nEnd of document detected, saving previous charactere");
				fputc(caracterePrecedent, temp);
				break;
			}
		} while (caractereActuel != EOF);

		printf("\nSaving temp file to file");
		rewind(fichier);
		fclose(fichier);
		printf("\n  > Original file is being recycled.");
		fichier = fopen(nomDeFichier, "w");
		if (fichier == NULL) 
		{ 
			printf("/nUnable to write on the old file"); 
			return 0; 
		}
		rewind(temp);
		rewind(fichier);
		printf("\n  > Writing the modifications");
		while(!feof(temp))
		{
			fputc(fgetc(temp), fichier);
		}
		rewind(temp);
		fclose(temp);
		rewind(fichier);
		fclose(fichier);
		printf("\n\nTempfile saved. modifsTmp = %d", modifsTmp);
	}
	printf("\n%d characteres were deleted.\n", modifs);

	return 0;
}

