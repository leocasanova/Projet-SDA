#include "noeud.h"


noeud* creer_noeud(unsigned int* tab_index, unsigned int nb_index, unsigned int x, double** matrice, double y)
{
	noeud* element = (noeud*)malloc(sizeof(noeud));
	element->x = x; //colonne Xi
	unsigned int* tab = malloc(nb_index * sizeof(unsigned int));
	memcpy(tab, tab_index, nb_index * sizeof(unsigned int)); //Copie du tableau d'index dans 'tab'
	element->tab_index = tab;
	element->nb_index = nb_index;
	element->fils_gauche = NULL;
	element->fils_droite = NULL;
	element->y = y; //Premiere colonne Y

	trier_noeud(element, matrice);
	element->mediane = calculer_mediane(element,  matrice);
	calculer_precision(element, matrice);
	return	element;
}

//Creation des sous echantillons, cad un tableau gauche et un tableau droit divise en fonction de la mediane (note : ce sont des tableaux d'index)
void creer_enfants(noeud* n, double** m)
{
	int i;
	unsigned int nb_gauche; //nombre d'element dans le tableau gauche
	for(i = 0; i < n->nb_index; i++)
	{
		if(m[n->tab_index[i]][n->x] > n->mediane)
		{
			nb_gauche = i;
			break; //On a atteint une valeur superieure a la mediane
		}
	}
	//declaration du sous echantillon de gauche
	unsigned int tab_gauche[nb_gauche];
	//remplissage du sous echantillon de gauche avec des index
	for(i = 0; i < nb_gauche;i++)
	{
		tab_gauche[i] = n->tab_index[i]; 
	}
	unsigned int nb_droit = n->nb_index - i; //nombre d'element dans le tableau droit
	//declaration du sous echantillon de droite
	unsigned int tab_droit[nb_droit];
	//remplissage du sous echantillon de droite avec des index
	for(i = 0; i< nb_droit; i++)
	{
		tab_droit[i] = n->tab_index[nb_gauche + i];
	}
	noeud* gauche = creer_noeud(tab_gauche, nb_gauche, n->x, m, n->y); //creation du noeug gauche
	gauche->est_gauche = true; //le noeud est a gauche donc on le met a true
	noeud* droit = creer_noeud(tab_droit, nb_droit, n->x, m, n->y); //creation du noeug droit
	droit->est_gauche = false; //le noeud est a droite donc on le met a false
	
	gauche->pere = n; //le pere de gauche est le noeud avec lequel on cree les enfants
	droit->pere = n; //idem pour le noeud droit
	n->fils_gauche = gauche; //assignation du fils gauche du noeud avec le noeud gauche
	n->fils_droite = droit; //idem pour le fils droit
}

//Tri bulle pour ranger les indices du tableau d'indices dans l'ordre en fonctions des valeurs Xi
void trier_noeud(noeud* n, double** m)
 {
	 int array_size = n->nb_index;
	 int i, j, temp;
	 for (i = 0; i < (array_size - 1); ++i)
	 {
		  for (j = 0; j < array_size - 1 - i; ++j )
		  {
			   if (m[n->tab_index[j]][n->x] > m[n->tab_index[j+1]][n->x]) 	//on est dans une colonne Xi, on regarde si la valeur precedente est superieur a la suivante
			   {															//si c'est le cas :
					temp = n->tab_index[j+1];								//on echange la place des indices (qui correspondent aux valeurs) de notre tableau d'indices
					n->tab_index[j+1] = n->tab_index[j];
					n->tab_index[j] = temp;
			   }
		  }
	 }
 }  

//On peut alors calculer la mediane maitenant que le tableau est trié
double calculer_mediane(noeud* n, double** m)
{
	//conditions de calcul
	if(n->nb_index < 2)
	{
		return -1;
	}
	
	int i;	
	for(i = 1; i < n->nb_index && m[n->tab_index[i]][n->x] == m[n->tab_index[i-1]][n->x]; i++); //tant que i < nombre d'index du noeud ET que les Xi d'une colonne sont egaux; i++
	
	if(i == n->nb_index) //cad tous les Xi de la colonne sont egaux
	{
		return -1;
	}
	
	//conditions validees, on peut calculer la mediane
	double mediane;
	int p;
	if(n->nb_index%2 == 0)
	{
		p = ((n->nb_index)/2);
		mediane = (m[n->tab_index[p-1]][n->x] + m[n->tab_index[p]][n->x])/2; // on soustrait 1 a p car notre tab commence par 0
	}
	else
	{
		p = (n->nb_index+1)/2;
		mediane = m[n->tab_index[p-1]][n->x]; // on soustrait 1 a p car notre tab commence par 0
	}
	
	//on verifie que la mediane n est pas le max
	if(mediane == m[n->tab_index[n->nb_index-1]][n->x])
	{
		int i;
		for(i=n->nb_index-1; i>= 0 ; i--)
		{
			if(m[n->tab_index[i]][n->x] != mediane)
			{
				break;
			}
		}
		mediane = m[n->tab_index[i]][n->x];
	}
	return mediane;
}

void calculer_precision(noeud* n, double** m)
{
	int cpt = 0;
	for(int i = 0; i < n->nb_index; i++)
	{
		//on compte le nombre de fois que l'iris recherché apparait dans notre noeud
		if(n->y == m[n->tab_index[i]][0]) 
		{
			cpt++;
		}
	}
	n->precision = (double)cpt/n->nb_index; //on divise par le nombre total d'individus pour avoir la precision
}

void affichage_infos_noeud(noeud const *n)
{
	printf(" Nombre d'individus: %d | X%d %s %lg | Precision: %lg %%\n",n->nb_index,n->x, n->est_gauche ? "<=":">", n->mediane , n->precision*100);
}

//fonction pour voir les valeurs du noeud pour tester au cours de la realisation du programme
void affichage_valeurs_noeud(noeud const* n, double** m) 
{
	for(int i=0; i < n->nb_index; i++) 
	{
		printf("%d| indice: %d valeur: %lg\n",i,n->tab_index[i], m[n->tab_index[i]][n->x]);
	}
}

bool est_feuille(noeud const* element)
{
	bool feuille = false;
	
	if( element != NULL )
	{
		if( (element->fils_gauche == NULL) && (element->fils_droite == NULL) )
		{
			feuille = true;
		}
	}
	return feuille;
}

int nombre_feuilles(noeud const* parent)
{
	if(parent == NULL)
	{
		return 0;
	}
	if(est_feuille(parent))
	{
		return 1;
	}
	return nombre_feuilles(parent->fils_gauche) + nombre_feuilles(parent->fils_droite);
}

void supprimer(noeud** p_arbre)
{
	noeud * arbre = *p_arbre;
	if( arbre != NULL ) // <=> if( (*p_arbre) != NULL )
	{
		supprimer( &(arbre->fils_gauche) ); // <=> supprimer( &( (*p_arbre)->fils_gauche ) );
		supprimer( &(arbre->fils_droite) ); // <=> supprimer( &( (*p_arbre)->fils_droite ) );
		
		free(arbre); // <=> free(*p_arbre)  : libération de la zone mémoire pointée
		*p_arbre = NULL; // surtout pas arbre = NULL, car arbre est LOCALE ici (et donc *p_arbre non modifié)
	}
	//else <=> arrêt de la récursivité
}

