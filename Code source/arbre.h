#ifndef ARBRE_H
#define ARBRE_H

#include "donnees.h"
#include "noeud.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//----------------------------------------------------------
// Arbre
//----------------------------------------------------------

typedef struct 
{
	double seuil_min, seuil_max, min_individus;
	int hauteur_max, largeur, y;
	noeud* racine;
	double** matrice;
} arbre;


arbre* initialisation(int hauteur_max, int y, double seuil_min, double seuil_max, double min_individus, matrice_donnees* data); //assigne tous les parametres a l'arbre

void construction_arbre(arbre* a, noeud* n); //fonction recursive qui construit l'arbre a partir d'une racine

int maximum(int a, int b);
int hauteur(noeud const * racine);

void afficher_offset(int offset);
void affichage_arborescence(noeud * racine, int offset);


#endif