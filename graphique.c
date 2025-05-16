#include <stdlib.h>
#include <graph.h>
#include "graphique.h"
#include "jeu.h"


/* Afficher un pion */
void AfficherPion(int x, int y, int pion) {
    AfficherSprite(pion, x, y);
}



/* Afficher une croix */
void AfficherCroix(int x, int y, int croix) {
    AfficherSprite(croix, x, y);
}

/* Redessiner une case */
void RedessinerCase(int caseX, int caseY, int largeur_case, int offset_x, int offset_y) {
    int x = offset_x + caseX * largeur_case;
    int y = offset_y + caseY * largeur_case;

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    RemplirRectangle(x, y, largeur_case, largeur_case);
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    DessinerRectangle(x, y, largeur_case, largeur_case);
}

void MenuGraphique(int *taille_grille, int *nombre_joueurs) {
    int i;
    couleur grisClair = CouleurParComposante(255, 255, 255);
    couleur noir = CouleurParComposante(0, 0, 0);
    couleur orange = CouleurParComposante(250, 143, 2);
    couleur cyan = CouleurParComposante(2, 183, 219);

    int pion_bleu, pion_orange, croix_bleu, croix_orange; /* Déclarer les variables pour les sprites*/

    EffacerEcran(grisClair);

    Bouton boutonsGrille[] = {
        {150, 70, 70, 50, "3x3", noir}, {250, 70, 70, 50, "4x4", noir},
        {350, 70, 70, 50, "5x5", noir}, {450, 70, 70, 50, "6x6", noir},
        {550, 70, 70, 50, "7x7", noir}, {650, 70, 70, 50, "8x8", noir},
        {750, 70, 70, 50, "9x9", noir}
    };

    Bouton bouton1J = {440, 240, 50, 50, "IA", cyan};
    Bouton bouton2J = {520, 240, 50, 50, "2J", orange};
    Bouton confirmer = {430, 400, 120, 50, "Confirmer?", noir};

    EcrireTexte(300, 50, "Veuillez choisir la taille de la grille : ", 1);

    for (i = 0; i < 7; i++) {
        DessinerBouton(boutonsGrille[i]);
    }

    EcrireTexte(230, 200, "Voulez-vous demarrer une partie a un ou deux joueurs?", 1);

    DessinerBouton(bouton1J);
    DessinerBouton(bouton2J);

    int choix_grille_precedent = -1;
    int choix_mode_precedent = -1;

    while (1) {
        if (SourisCliquee()) {
            SourisPosition();
            int x = _X, y = _Y;

            for (i = 0; i < 7; i++) {
                if (EstClique(boutonsGrille[i], x, y)) {
                    *taille_grille = i + 3;

                    if (choix_grille_precedent != -1) {
                        Bouton bouton_precedent = boutonsGrille[choix_grille_precedent];
                        ChoisirCouleurDessin(grisClair);
                        RemplirRectangle(bouton_precedent.x, bouton_precedent.y, bouton_precedent.largeur, bouton_precedent.hauteur);
                        DessinerBouton(bouton_precedent);
                    }

                    ChoisirCouleurDessin(noir);
                    RemplirRectangle(boutonsGrille[i].x, boutonsGrille[i].y, boutonsGrille[i].largeur, boutonsGrille[i].hauteur);
                    DessinerBouton(boutonsGrille[i]);
                    choix_grille_precedent = i;

                    EcrireTexte(360, 330, "Taille de grille selectionnee", 1);
                    break;
                }
            }

            if (EstClique(bouton1J, x, y)) {
                *nombre_joueurs = 1;

                ChoisirCouleurDessin(grisClair);
                RemplirRectangle(340, 350, 200, 40);

                if (choix_mode_precedent == 2) {
                    ChoisirCouleurDessin(grisClair);
                    RemplirRectangle(bouton2J.x, bouton2J.y, bouton2J.largeur, bouton2J.hauteur);
                    DessinerBouton(bouton2J);
                }

                ChoisirCouleurDessin(cyan);
                RemplirRectangle(bouton1J.x, bouton1J.y, bouton1J.largeur, bouton1J.hauteur);
                DessinerBouton(bouton1J);
                choix_mode_precedent = 1;

                EcrireTexte(360, 370, "Mode 1 joueur selectionne", 1);

            } else if (EstClique(bouton2J, x, y)) {
                *nombre_joueurs = 2;

                ChoisirCouleurDessin(grisClair);
                RemplirRectangle(340, 350, 200, 40);

                if (choix_mode_precedent == 1) {
                    ChoisirCouleurDessin(grisClair);
                    RemplirRectangle(bouton1J.x, bouton1J.y, bouton1J.largeur, bouton1J.hauteur);
                    DessinerBouton(bouton1J);
                }

                ChoisirCouleurDessin(orange);
                RemplirRectangle(bouton2J.x, bouton2J.y, bouton2J.largeur, bouton2J.hauteur);
                DessinerBouton(bouton2J);
                choix_mode_precedent = 2;

                EcrireTexte(360, 370, "Mode 2 joueur selectionne", 1);
            }

            if (*taille_grille > 0 && *nombre_joueurs > 0) {
                DessinerBouton(confirmer);
                if (EstClique(confirmer, x, y)) {
                    return;
                }
            }
        }
    }
}


/* Fonction pour réinitialiser la grille */
void ReinitialiserGrille(int grille[][9], int taille_grille) {
    int i, j;
    for (i = 0; i < taille_grille; i++) {
        for (j = 0; j < taille_grille; j++) {
            grille[i][j] = 0;
        }
    }
}

/* Menu de fin */
void MenuFin(int gagnant, int grille[][9], int taille_grille, int pion_bleu, int pion_orange,
   int croix_bleu, int croix_orange) {
    int x, y;

    EffacerEcran(CouleurParComposante(255, 255, 255));

    /* Affichage du message de fin */
    if (gagnant == 1) {
        ChoisirCouleurDessin(CouleurParComposante(2, 183, 219));
        EcrireTexte(400, 300, "Le joueur bleu a gagne !", 1);
        ChoisirCouleurDessin(CouleurParComposante(250, 143, 2));
        EcrireTexte(400, 350, "Le joueur orange a perdu.", 1);
    } else if (gagnant == 2) {
        ChoisirCouleurDessin(CouleurParComposante(250, 143, 2));
        EcrireTexte(400, 300, "Le joueur orange a gagne !", 1);
        ChoisirCouleurDessin(CouleurParComposante(2, 183, 219));
        EcrireTexte(400, 350, "Le joueur bleu a perdu.", 1);
    }

    /* Définition des boutons */
    Bouton quitter = {430, 380, 120, 40, "Quitter ?"};
    Bouton recommencer = {410, 460, 160, 40, "Recommencer ?"};

    /* Dessiner les boutons */
    DessinerBouton(quitter);
    DessinerBouton(recommencer);

    while (1) {
        if (SourisCliquee()) {
            SourisPosition();
            x = _X;
            y = _Y;

            /* Vérifier si le clic est sur le bouton "Quitter" */
            if (EstClique(quitter, x, y)) {
                FermerGraphique();
                return;
            }

            /* Vérifier si le clic est sur le bouton "Recommencer" */
            else if (EstClique(recommencer, x, y)) {
                int taille_grille = 0;
                int nombre_joueurs = 0;
                debutJeu(grille, taille_grille, nombre_joueurs, pion_bleu, pion_orange, croix_bleu, croix_orange);
                /* Réinitialiser la grille */
                ReinitialiserGrille(grille, taille_grille);

                /* Relancer le jeu */
                debutJeu(grille, taille_grille,nombre_joueurs, pion_bleu, pion_orange, croix_bleu, croix_orange);
                return;
            }
        }
    }
}





/* Dessiner un bouton */
void DessinerBouton(Bouton bouton) {
    ChoisirCouleurDessin(bouton.couleurTexte);
    DessinerRectangle(bouton.x, bouton.y, bouton.largeur, bouton.hauteur);
    EcrireTexte(bouton.x + 10, bouton.y + bouton.hauteur / 2 + 5, bouton.texte, 1);
}

/* Vérifier si un bouton a été cliqué */
int EstClique(Bouton bouton, int x, int y) {
    return (x >= bouton.x && x <= bouton.x + bouton.largeur && y >= bouton.y && y <= bouton.y + bouton.hauteur);
}

/* Afficher la grille */
void AfficherGrille(int taille_grille, int largeur_case, int offset_x, int offset_y) {
    int i, j;

    for (i = 0; i < taille_grille; i++) {
        for (j = 0; j < taille_grille; j++) {
            int x = offset_x + j * largeur_case;
            int y = offset_y + i * largeur_case;
            DessinerRectangle(x, y, largeur_case, largeur_case);
        }
    }
}
