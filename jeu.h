#ifndef JEU_H
#define JEU_H

/* Déclarations des fonctions */
void GestionJeu(int grille[][9], int taille_grille, int pion_bleu, int pion_orange,
                int largeur_case, int offset_x, int offset_y, int croix_bleu, int croix_orange, int nombre_joueurs);

void GestionJeuIA(int grille[][9], int taille_grille, int pion_bleu, int pion_orange,
                  int largeur_case, int offset_x, int offset_y, int croix_bleu, int croix_orange);

void debutJeu(int grille[][9], int taille_grille, int nombre_joueurs, int pion_bleu, int pion_orange, 
int croix_bleu, int croix_orange);
#endif /* JEU_H */
