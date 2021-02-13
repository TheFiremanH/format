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
	int passages = 0;
	char nomDeFichier[255];
	FILE* fichier = NULL;
	FILE* temp = NULL;

	printf("\nEntrer le nom de fichier : ");
	scanf("%s", nomDeFichier);
	printf("\n***\nFichier confirmé : %s\n***", nomDeFichier);

	int caracterePrecedent = 0;
	int caractereActuel = 0;
	int caractereTransfert = 0;
	while (modifsTmp != 0)
	{
		passages++;
		modifsTmp = 0;
		bool recordIt = false;
		temp = tmpfile();
		fichier = fopen(nomDeFichier, "r+");
		if (temp == NULL || fichier == NULL)
		{
			printf("\nUnable to create files");
			return 0;
		}
		rewind(temp);
		do
		{
			caractereActuel = fgetc(fichier);
			if (caractereActuel == '\n')
			{
				if (caracterePrecedent == ' ') // si le caractere avant un retour est un espace
				{
					recordIt = false; // ne pas l'enregistrer
					modifs++;
					modifsTmp++;
				}
				if (caracterePrecedent == '\t')
				{
					recordIt = false; // ne pas l'enregistrer
					modifs++;
					modifsTmp++;
				}
			}
			if (caracterePrecedent == 255)
			{
				recordIt = false;
			}

			if (recordIt)
			{
				fputc(caracterePrecedent, temp);
				//printf("\n vvv Caractere %d (%c) was saved", caracterePrecedent, caracterePrecedent);
			}
			else
			{
				//printf("\n xxx Caractere %d (%c) was not saved", caracterePrecedent, caracterePrecedent);
			}
			recordIt = true;
			caracterePrecedent = caractereActuel;
		} while (caractereActuel != EOF);

		rewind(fichier);
		fclose(fichier);
		fichier = fopen(nomDeFichier, "w");
		if (fichier == NULL)
		{
			printf("/nUnable to write on the old file");
			return 0;
		}
		rewind(temp);
		rewind(fichier);
		//printf("\n > Writing the modifications :");
		while(!feof(temp))
		{
			caractereTransfert = fgetc(temp);
			if (caractereTransfert >= 0)
			{
				//printf("\n    >> %c (%d)", caractereTransfert, caractereTransfert);
				fputc(caractereTransfert, fichier);
			}
			else
			{
				//printf("\n   xx> %c (%d)", caractereTransfert, caractereTransfert);
			}
		}
		rewind(temp);
		fclose(temp);
		rewind(fichier);
		fclose(fichier);
	}
	printf("\n\n%d characteres were deleted.\nThe file was used %d times\n\n", modifs, passages);

	return 0;
}
