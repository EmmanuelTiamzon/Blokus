#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

typedef struct {
    int x, y;
    int largeur, hauteur;
    char texte[20];
    couleur couleurTexte;
} Bouton;

void AfficherPion(int x, int y, int pion);
void AfficherCroix(int x, int y, int croix);
void RedessinerCase(int caseX, int caseY, int largeur_case, int offset_x, int offset_y);
void MenuGraphique(int *taille_grille, int *nombre_joueurs);
void MenuFin(int gagnant, int grille[][9], int taille_grille, int pion_bleu, int pion_orange,
             int croix_bleu, int croix_orange);
void ReinitialiserGrille(int grille[][9], int taille_grille);
void DessinerBouton(Bouton bouton);
int EstClique(Bouton bouton, int x, int y);
void AfficherGrille(int taille_grille, int largeur_case, int offset_x, int offset_y);


#endif /* GRAPHIQUE_H */
