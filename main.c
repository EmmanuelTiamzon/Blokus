#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

#include "graphique.h"
#include "jeu.h"
#include "utilitaires.h"

int main() {
    InitialiserGraphique();
    CreerFenetre(10, 10, 1000, 600);

    couleur grisClair = CouleurParComposante(255, 255, 255);
    EffacerEcran(grisClair);

    int pion_bleu = ChargerSprite("Pionb_50x50.png");
    int pion_orange = ChargerSprite("Pionc_50x50.png");
    int croix_bleu = ChargerSprite("croixb4x4.png");
    int croix_orange = ChargerSprite("croixo4x4.png");
    int taille_grille = 0, nombre_joueurs = 0;
    int grille[9][9] = {0};

    /* Démarrage du jeu */
    debutJeu(grille,taille_grille,nombre_joueurs,pion_bleu,pion_orange,croix_bleu,croix_orange);

    /* Libérer les ressources avant de fermer */
    LibererSprite(pion_bleu);
    LibererSprite(pion_orange);
    LibererSprite(croix_bleu);
    LibererSprite(croix_orange);
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}
