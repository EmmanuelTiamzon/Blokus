#include <stdlib.h>
#include <graph.h>
#include <time.h>
#include "utilitaires.h"
#include "jeu.h"
#include "graphique.h"


void Delai(int duree_ms) {

/* La duree est en millisecondes. Le principe est d'effectuer une boucle vide. */

long fin = clock() + duree_ms * CLOCKS_PER_SEC / 1000;  /* Convertir la duree en unites de clock() */

	while (clock() < fin) {

    	/* Rien à faire ici, juste attendre */

	}

}

int EstBloque(int grille[][9], int taille_grille, int caseX, int caseY) {
	int i;
	int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

	for (i = 0; i < 8; i++) {

		int dirX = caseX + directions[i][0];

		int dirY = caseY + directions[i][1];

		if (dirX >= 0 && dirX < taille_grille && dirY >= 0 && dirY < taille_grille) {

			if (grille[dirY][dirX] == 0) {

				return 0;

			}

		}

	}

	return 1;

}




int EstGrillePleine(int grille[][9], int taille_grille) {
	int i,j;
	for ( i = 0; i < taille_grille; i++) {

		for (j = 0; j < taille_grille; j++) {

    	if (grille[i][j] == 0) { 
    	/* Si une case est vide, la grille n'est pas pleine */

			return 0;

		}

	}

}

return 1; /* La grille est pleine */

}

/* Fonction pour verifier si le deplacement est valide (pas plus de 1 case) */

int DeplacementValide(int caseXActuelle, int caseYActuelle, int caseXCible, int caseYCible) {

	return (abs(caseXActuelle - caseXCible) <= 1) && (abs(caseYActuelle - caseYCible) <= 1);

}