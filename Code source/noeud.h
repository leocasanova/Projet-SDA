#ifndef NOEUD_H
#define NOEUD_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "donnees.h"

//----------------------------------------------------------
// Noeud
//----------------------------------------------------------

typedef struct _noeud
{
unsigned int* tab_index, nb_index, x;
double precision;
double mediane;
double y;
bool est_gauche;
struct _noeud * pere;
struct _noeud * fils_gauche;
struct _noeud * fils_droite;
} noeud;

noeud* creer_noeud(unsigned int* tab_index, unsigned int nb_index, unsigned int x, double** matrice, double y); 

void trier_noeud(noeud* n, double** m);
double calculer_mediane(noeud* n, double** m);
void calculer_precision(noeud* n, double** m);

void creer_enfants(noeud* n, double** m);

void affichage_infos_noeud(noeud const *n);
void affichage_valeurs_noeud(noeud const *n, double** m);

bool est_feuille(noeud const * element);
int nombre_feuilles(noeud const * parent);

void supprimer(noeud* * p_arbre);


#endif 
