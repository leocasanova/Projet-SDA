#ifndef ARBRE_C
#define ARBRE_C

#include "arbre.h"


arbre* initialisation(int hauteur_max, int y, double seuil_min, double seuil_max, double min_individus, matrice_donnees* data)
{
	arbre* a = (arbre*)malloc(sizeof(arbre));
	a->hauteur_max = hauteur_max;
	a->y=y;
	a->seuil_min = seuil_min;
	a->seuil_max = seuil_max;
	a->min_individus = min_individus; 
	a->matrice = data->matrice;
	
	unsigned int tab[data->nb_lignes]; // on cree un tableau d'index
	for(int i = 0; i < data->nb_lignes; i++)
	{
		tab[i]=i;
	}
	a->racine = creer_noeud(tab, data->nb_lignes,0,a->matrice, y); //on cree la racine <=> noeud 0

	return a;
}

void construction_arbre(arbre* a, noeud* n)
{
	//conditions de construction
	if(a->hauteur_max <= hauteur(a->racine)
	|| n->nb_index < a->min_individus
	|| n->precision < a->seuil_min
	|| n->precision > a->seuil_max
	|| n->mediane == -1)
	{
		return;
	}
	//on cree les 4 noeuds de chaque colonne
	noeud* noeuds[4];
	double precisions[4];
	for(int i = 0; i < 4; i++) 
	{
		noeuds[i] = creer_noeud(n->tab_index, n->nb_index,i+1,a->matrice, a->y);
		creer_enfants(noeuds[i], a->matrice);
		//si la precision du fils gauche est superieure a celle du fils droit alors on garde celle du fils gauche, sinon l'inverse
		precisions[i] = (noeuds[i]->fils_gauche->precision > noeuds[i]->fils_droite->precision) ? noeuds[i]->fils_gauche->precision : noeuds[i]->fils_droite->precision;
	}
	// on calcule la precision de chaque noeud
	double pmax = precisions[0]; int index_max = 0;
	for(int i=1; i < 4; i++) 
	{
		if(precisions[i]>pmax)
		{
			index_max = i;
			pmax=precisions[i];
		}
	} 
	// on assigne au noeud n le noeud qui a la plus grande precision
	*n = *noeuds[index_max];
	// il faut supprimer les autres
	for(int i=0; i<4; i++) 
	{
		if(i != index_max) 
		{
			supprimer(&(noeuds[i]));
		}
	}
	// on continue la construction
	construction_arbre(a, n->fils_gauche);
	construction_arbre(a, n->fils_droite);
}

int maximum(int a, int b)
{
	if (a>=b) return a;
	else return b;
}
	
int hauteur(noeud const * racine)
{
	if (racine==NULL)
		return 0;
	else
		return 1 + maximum(hauteur(racine->fils_gauche), hauteur(racine->fils_droite));
}

// Affiche d'un certain nombre d'espaces, proportionnel à offset
void afficher_offset(int offset)
{
	for(int i = 0 ; i < offset ; i++)
	{
		printf("  "); // 2 espaces
	}
	printf("Niveau %d ",offset-1);
}

// Affichage récursif <=> parcours préfixé
// Précondition : l'arbre peut-être NULL (dans ce cas rien ne s'affiche)
// Initialisation : offset = 0
void affichage_arborescence(noeud * racine, int offset)
{
	if(racine != NULL && racine->mediane != -1)
	{
		// Etape 1 - afficher la valeur
		printf("\n");
		afficher_offset(offset);
		if( offset != 0) // tous les éléments sauf la racine
		{
			printf("|-");
		}
		affichage_infos_noeud(racine);
		
		// Etape 2 - appel récursif avec sous-arbre gauche
			// Si à gauche (et uniquement à gauche) c'est NULL on affiche "|-x"
			if(!est_feuille(racine) && (racine->fils_gauche == NULL) )
			{
				printf("\n");
				afficher_offset(offset+1);
				printf("|-x");
			}
		affichage_arborescence(racine->fils_gauche, offset+1);
		
		// Etape 2 - appel récursif avec sous-arbre de droite
			// Si à droite (et uniquement à droite) c'est NULL on affiche "|-x"
			if( !est_feuille(racine) && (racine->fils_droite == NULL) )
			{
				printf("\n");
				afficher_offset(offset+1);
				printf("|-x");
			}
		affichage_arborescence(racine->fils_droite, offset+1);
	}
	//else <=> arrêt de la récursivité
}


#endif