#ifndef DONNEES_H
#define DONNEES_H

//----------------------------------------------------------
// Données
//----------------------------------------------------------

typedef struct 
{
	unsigned int nb_colonnes; // la 1ere <=> classe à prédire (Y). Autres colonnes <=> variables d'observatio (Xi)
	unsigned int nb_lignes;   // <=> les individus
	double** matrice;         // tableau de tableaux de réels (i.e. tableaux 2D de réels)
} matrice_donnees;


matrice_donnees* charger_donnnees(const char* nom_fichier);


#endif