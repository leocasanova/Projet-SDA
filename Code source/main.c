#include "donnees.h"
#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>


// Fonction d'affiche de la matrice de donnees
void afficher_matrice(matrice_donnees* p_matrice)
{
    if (p_matrice == NULL)
    {
        printf("pointeur NULL...\n");
    }
	else
	{
		int lig, col;
		for (lig = 0; lig < p_matrice->nb_lignes; lig++)
		{
			for (col = 0; col < p_matrice->nb_colonnes; col++)
			{
				printf(" %lg", p_matrice->matrice[lig][col]);
			}
			printf("\n");
		}
		printf("\n");
	}    
}

arbre* commencement(matrice_donnees * donnees)
{
	int y, t_max;
	double s_min, s_max, nb_min_individu;
	printf("Choisissez l'espece a predire :\nIris setosa (1)\nIris versicolor (2)\nIris virginica (3)\n");
	scanf("%d", &y);
	printf("Choisissez le seuil minimal de precision (%%)\n");
	scanf("%lg", &s_min);
	s_min = s_min/100;
	printf("Choisissez le seuil maximal de precision (%%)\n");
	scanf("%lg", &s_max);
	s_max = s_max/100;
	printf("Choisissez le nombre minimal d'individus par echantillon (%%)\n");
	scanf("%lg", &nb_min_individu);
	nb_min_individu = nb_min_individu/100;
	printf("Choisissez la taille maximale de l'arbre\n");
	scanf("%d", &t_max);

	return initialisation(t_max,y,s_min,s_max,nb_min_individu,donnees);
}

void Menu(arbre* a)
{
	int n;
	printf("\nVeuillez choisir un numero entre 1 et 6 : \n");
	printf("1. Afficher la hauteur de l'arbre\n");
	printf("2. Afficher la largeur de l'arbre (nombre de feuilles)\n");
	printf("3. Afficher l'arbre sous forme arborescente\n");
	printf("4. Afficher les feuilles\n");
	printf("5. Predire\n");
	printf("6. Quitter\n\n\n");
	scanf("%d", &n);
	
	if(n == 1)
	{
		printf("\nLa hauteur de l'arbre est : %d\n", hauteur(a->racine));
	}
	else if(n == 2)
	{
		printf("\nLa largeur de l'arbre est : %d\n", nombre_feuilles(a->racine));
	}
	else if(n == 3)
	{
		affichage_arborescence(a->racine,1);
	}
	else if(n == 4)
	{
		printf("\nFonction en cours de creation...\n");
	}
	else if(n == 5)
	{
		printf("\nFonction en cours de creation...\n");
	}
	else if(n == 6)
	{
		exit(0);
	} 
	else 
	{
		printf("\nNombre non reconnu. Veuillez choisir a nouveau :\n");
	}
	Menu(a);
}

int main(int argc, char **argv)
{
	matrice_donnees * donnees = charger_donnnees("iris.txt");
	arbre* a = commencement(donnees);
	construction_arbre(a, a->racine);
	Menu(a);
	
	return 0;
}
