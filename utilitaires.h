#ifndef UTILITAIRES_H
#define UTILITAIRES_H

void Delai(int duree_ms);
int EstBloque(int grille[][9], int taille_grille, int caseX, int caseY);
int EstGrillePleine(int grille[][9], int taille_grille);
int DeplacementValide(int caseXActuelle, int caseYActuelle, int caseXCible, int caseYCible);
#endif /*UTILITAIRES_H*/