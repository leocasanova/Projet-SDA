#include "donnees.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


matrice_donnees* charger_donnnees(const char* nom_fichier)
{
	FILE* fichier = fopen(nom_fichier,"r");
	if( fichier != NULL )
	{
		unsigned int nb_lignes;
		unsigned int nb_colonnes;
	
		// Etape 1 - traitement première ligne
		fscanf(fichier, "%u %u", &nb_lignes, &nb_colonnes); // %u <=> unsigned int
		fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
				
		// Etape 2 - allocation des lignes de la matrice
		double** matrice = (double**) malloc( nb_lignes * sizeof(double*) );
		
		// Etape 3 - remplissage de la matrice
		for(int ligne = 0 ; ligne < nb_lignes ; ligne++)
		{
			// allocation des colonnes de la matrice (pour chaque ligne)
			matrice[ligne] = (double*) malloc( nb_colonnes * sizeof(double) );

			for(int colonne = 0 ; colonne < nb_colonnes ; colonne++)
			{
				if(colonne != nb_colonnes-1)
				{
					fscanf(fichier, "%lg ", &matrice[ligne][colonne]);
				}
				else // dernière colonne (où le réel n'est pas suivi d'un espace)
				{
					fscanf(fichier, "%lg" , &matrice[ligne][colonne]);
				}
			}
			
			fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
		}
		
		matrice_donnees * data = (matrice_donnees*)malloc(sizeof(matrice_donnees));
		data->nb_colonnes = nb_colonnes;
		data->nb_lignes = nb_lignes;
		data->matrice = matrice;
		
		fclose(fichier);
		return data;
	}

	printf("Fichier %s inconnu.\n", nom_fichier);
	return NULL;
}


