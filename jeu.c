#include <stdlib.h>
#include <graph.h>
#include "jeu.h"
#include "utilitaires.h"
#include "graphique.h"


void GestionJeu(int grille[][9], int taille_grille, int pion_bleu, int pion_orange, int largeur_case, int offset_x, int offset_y, int croix_bleu, int croix_orange, int nombre_joueurs) {
	int x, y, caseX, caseY, tour = 0, etat = 0;  /* 0 = placement du pion, 1 = placement de la croix */
	int dernierXBleu = -1, dernierYBleu = -1;
	int dernierXOrange = -1, dernierYOrange = -1;

	couleur grisClair = CouleurParComposante(255, 255, 255);
	couleur noir = CouleurParComposante(0, 0, 0);
	couleur bleu = CouleurParComposante(2, 183, 219);
	couleur orange = CouleurParComposante(250, 143, 2);

	int xTexte = 380, yTexte = 560, largeurTexte = 480, hauteurTexte = 25;  /* Position et taille de la zone texte*/

	while (1) {

    	/* Choisir la couleur du texte et afficher le texte approprié*/
    	if (etat == 0) {  /*Placement du pion*/
		if (tour % 2 == 1) {
			ChoisirCouleurDessin(orange);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur orange", 1);
		} else {
			ChoisirCouleurDessin(bleu);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur bleu", 1);
		}
    	} else {  /* Placement de la croix*/
		if (tour % 2 == 1) {
			ChoisirCouleurDessin(orange);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur orange de placer la croix", 1);
		} else {
			ChoisirCouleurDessin(bleu);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur bleu de placer la croix", 1);
		}
	}

    	/* Gestion des clics de la souris*/
	if (SourisCliquee()) {
		SourisPosition();
		x = _X;
		y = _Y;

        	/* Calcul des indices de la case cliquée*/
		caseX = (x - offset_x) / largeur_case;
		caseY = (y - offset_y) / largeur_case;

        	/* Vérification si les coordonnées de la case sont valides*/
		if (caseX >= 0 && caseX < taille_grille && caseY >= 0 && caseY < taille_grille) {
            	if (etat == 0) {  /*Placement du pion*/
			int dernierX = (tour % 2 == 0) ? dernierXBleu : dernierXOrange;
			int dernierY = (tour % 2 == 0) ? dernierYBleu : dernierYOrange;

                	if (grille[caseY][caseX] == 0 &&  /* Case vide */
                    	((dernierX == -1 && dernierY == -1) ||  /* Premier placement */
			DeplacementValide(dernierX, dernierY, caseX, caseY))) {
                    	/*Effacer la dernière position du pion*/
                		if (dernierX != -1 && dernierY != -1) {
                			grille[dernierY][dernierX] = 0;
                			RedessinerCase(dernierX, dernierY, largeur_case, offset_x, offset_y);
                		}

                    	/* Affichage du nouveau pion*/
                		int pion = (tour % 2 == 0) ? pion_bleu : pion_orange;
						int ajustement_x = (taille_grille <= 4) ? -30 : 0; /* Décale les pions à droite pour une petite grille*/
						int ajustement_y = (taille_grille <= 4) ? -30 : 0; /*Décale les pions vers le haut pour une petite grille*/
                		int pion_x = offset_x + caseX * largeur_case + (largeur_case - 50) / 2 + ajustement_x;
                		int pion_y = offset_y + caseY * largeur_case + (largeur_case - 50) / 2 + ajustement_y;
                		AfficherPion(pion_x, pion_y, pion);

                    	/*Mise à jour de la grille*/
                		grille[caseY][caseX] = (tour % 2 == 0) ? 1 : 2;

                    	/* Mise à jour des coordonnées du dernier pion*/
                		if (tour % 2 == 0) {
                			dernierXBleu = caseX;
                			dernierYBleu = caseY;
                		} else {
                			dernierXOrange = caseX;
                			dernierYOrange = caseY;
                		}

                    	etat = 1;  /* Passage à l'état de placement de la croix*/
                	}
            	} else if (etat == 1) {  /* Placement de la croix*/
                	if (grille[caseY][caseX] == 0) {  /*La case est vide*/
                    	/*  Ajout de la croix à la grille*/
                	grille[caseY][caseX] = (tour % 2 == 0) ? 3 : 4;

                    	/*Affichage de la croix*/
                	int croix_x = offset_x + caseX * largeur_case + (largeur_case - 50) / 2;
                	int croix_y = offset_y + caseY * largeur_case + (largeur_case - 50) / 2;
                	int croix = (tour % 2 == 0) ? croix_bleu : croix_orange;
                	AfficherCroix(croix_x, croix_y, croix);

                    	/*Passage au prochain tour*/
                	tour++;
                	ChoisirCouleurDessin(grisClair);
    					RemplirRectangle(xTexte, yTexte, largeurTexte, hauteurTexte);  /*Zone d'effacement du texte*/
                	etat = 0;

                    	/*Vérification des conditions de blocage*/
                	if (tour >= 2) {
                		if (EstBloque(grille, taille_grille, dernierXBleu, dernierYBleu)) {
                			MenuFin(2, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);
                            	return;  /* Fin du jeu*/
                		} else if (EstBloque(grille, taille_grille, dernierXOrange, dernierYOrange)) {
                			MenuFin(1, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);
                            	return;  /*  Fin du jeu*/
                		}
                	}
                }
            }
        }
    }

    	/* Vérification de la fin de la partie*/
    if (EstGrillePleine(grille, taille_grille)) {
    	int gagnant = (tour % 2 == 0) ? 2 : 1;
    	MenuFin(gagnant, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);
        	return;  /* Fin du jeu*/
    }
}
}




void GestionJeuIA(int grille[][9], int taille_grille, int pion_bleu, int pion_orange, int largeur_case, int offset_x, int offset_y, int croix_bleu, int croix_orange) {

int x, y, caseX, caseY, tour = 0, etat = 0;  /* 0 = placement du pion, 1 = placement de la croix */

	int dernierXBleu = -1, dernierYBleu = -1;

	int dernierXOrange = -1, dernierYOrange = -1;
	int xTexte = 380, yTexte = 560, largeurTexte = 500, hauteurTexte = 25;  /* Position et taille de la zone texte*/
	couleur grisClair = CouleurParComposante(255, 255, 255);
	couleur noir = CouleurParComposante(0, 0, 0);
	couleur bleu = CouleurParComposante(2, 183, 219);
	couleur orange = CouleurParComposante(250, 143, 2);

	while (1) {

   	/* Choisir la couleur du texte et afficher le texte approprié*/
    	if (etat == 0) {  /* Placement du pion*/
		if (tour % 2 == 1) {
			ChoisirCouleurDessin(orange);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur orange", 1);
		} else {
			ChoisirCouleurDessin(bleu);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur bleu", 1);
		}
    	} else {  /* Placement de la croix*/
		if (tour % 2 == 1) {
			ChoisirCouleurDessin(orange);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur orange de placer la croix", 1);
		} else {
			ChoisirCouleurDessin(bleu);
			EcrireTexte(xTexte, yTexte + 20, "C'est au tour du joueur bleu de placer la croix", 1);
		}
	}


	if (tour % 2 == 0) {

	        	/* Tour du joueur humain (bleu) */

		if (SourisCliquee()) {

			SourisPosition();

			x = _X;

			y = _Y;

	            	/* Calcul des indices de la case cliquée */

			caseX = (x - offset_x) / largeur_case;

			caseY = (y - offset_y) / largeur_case;

	            	/* Vérification si les coordonnées de la case sont valides */

			if (caseX >= 0 && caseX < taille_grille && caseY >= 0 && caseY < taille_grille) {

				if (etat == 0 && grille[caseY][caseX] == 0 &&

					(dernierXBleu == -1 || DeplacementValide(dernierXBleu, dernierYBleu, caseX, caseY))) {

	                    	/* Effacer la dernière position du pion */

					if (dernierXBleu != -1 && dernierYBleu != -1) {

						grille[dernierYBleu][dernierXBleu] = 0;

						RedessinerCase(dernierXBleu, dernierYBleu, largeur_case, offset_x, offset_y);

					}


                    	/* Affichage du pion bleu */
                    int ajustement_x = (taille_grille <= 4) ? -30 : 0; /* Décale les pions à droite pour une petite grille*/
                    int ajustement_y = (taille_grille <= 4) ? -30 : 0; /* Décale les pions vers le haut pour une petite grille*/
					int pion_x = offset_x + caseX * largeur_case + (largeur_case - 50) / 2 + ajustement_x;
					int pion_y = offset_y + caseY * largeur_case + (largeur_case - 50) / 2 + ajustement_y;
					AfficherPion(pion_x, pion_y, pion_bleu);

	                    	/* Mise à jour de la grille */

					grille[caseY][caseX] = 1;

					dernierXBleu = caseX;

					dernierYBleu = caseY;

	                    	etat = 1;  /* Passage à l'état de placement de la croix */

				} else if (etat == 1 && grille[caseY][caseX] == 0) {

	                    	/* Placement de la croix */

					int croix_x = offset_x + caseX * largeur_case + (largeur_case - 50) / 2;
					int croix_y = offset_y + caseY * largeur_case + (largeur_case - 50) / 2;
					AfficherCroix(croix_x, croix_y, croix_bleu);

					grille[caseY][caseX] = 3;

					tour++;
					ChoisirCouleurDessin(grisClair);
    					RemplirRectangle(xTexte, yTexte, largeurTexte, hauteurTexte);  /*Zone d'effacement du texte*/
					etat = 0;

				}

			}

		}

	} else {

	        	/* Tour de l'IA (orange) */

		int pionX, pionY, croixX, croixY;

	        	/* Placer le pion de l'IA dans une zone valide */

		do {

			pionX = rand() % taille_grille;

			pionY = rand() % taille_grille;

	            	/* Vérifier si la case est vide et si le déplacement est valide par rapport au dernier pion */

		} while (grille[pionY][pionX] != 0 ||
			(dernierXOrange != -1 && dernierYOrange != -1 && !DeplacementValide(dernierXOrange, dernierYOrange, pionX, pionY)));
		if (dernierXOrange != -1 && dernierYOrange != -1) {
	            	/* Effacer la dernière position du pion de l'IA */
			grille[dernierYOrange][dernierXOrange] = 0;
			RedessinerCase(dernierXOrange, dernierYOrange, largeur_case, offset_x, offset_y);
		}

	        	/* Affichage du pion orange */
        	int ajustement_x = (taille_grille <= 4) ? -30 : 0; /* Décale les pions à droite pour une petite grille*/
        	int ajustement_y = (taille_grille <= 4) ? -30 : 0; /* Décale les pions vers le haut pour une petite grille*/
			int pion_x = offset_x + pionX * largeur_case + (largeur_case - 50) / 2 + ajustement_x;
			int pion_y = offset_y + pionY * largeur_case + (largeur_case - 50) / 2 + ajustement_y;
			AfficherPion(pion_x, pion_y, pion_orange);

	        	/* Mise à jour de la grille */
		grille[pionY][pionX] = 2;
		dernierXOrange = pionX;
		dernierYOrange = pionY;
	        	/* Attente avant de placer la croix de l'IA */
		Delai(500);

	        	/* Placer la croix de l'IA */
		do {
			croixX = rand() % taille_grille;
			croixY = rand() % taille_grille;
	        	} while (grille[croixY][croixX] != 0 || (croixX == pionX && croixY == pionY));  /* Éviter de placer la croix sur le pion */

	        	/* Affichage de la croix orange */
			int croix_x = offset_x + croixX * largeur_case + (largeur_case - 50) / 2;
			int croix_y = offset_y + croixY * largeur_case + (largeur_case - 50) / 2;
			AfficherCroix(croix_x, croix_y, croix_orange);

	        	/* Mise à jour de la grille */
			grille[croixY][croixX] = 4;
			ChoisirCouleurDessin(grisClair);
    			RemplirRectangle(xTexte, yTexte, largeurTexte, hauteurTexte);  /* Zone d'effacement du texte*/
			tour++;
		}
	    	/* Vérification des conditions de fin de jeu après chaque tour */
		if (tour >= 2) {
			if (EstBloque(grille, taille_grille, dernierXBleu, dernierYBleu)) {
						MenuFin(2, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);  /* Fin du jeu, l'IA a gagné */
				return;
			} else if (EstBloque(grille, taille_grille, dernierXOrange, dernierYOrange)) {
						MenuFin(1, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);  /* Fin du jeu, le joueur humain a gagné */
				return;
			}
		}
	    	/* Vérification de la fin de la partie si la grille est pleine */
		if (EstGrillePleine(grille, taille_grille)) {
	        	int gagnant = (tour % 2 == 0) ? 2 : 1;  /* L'IA ou le joueur humain a gagné */
				MenuFin(gagnant, grille, taille_grille, pion_bleu, pion_orange, croix_bleu, croix_orange);  /* Fin du jeu */
	        	return;  /* Fin du jeu */

		}

	}

}



void debutJeu(int grille[][9], int taille_grille, int nombre_joueurs, int pion_bleu, int pion_orange, int croix_bleu, int croix_orange) {
	couleur grisClair = CouleurParComposante(255, 255, 255);

	/* Afficher le menu graphique pour la sélection */
	MenuGraphique(&taille_grille, &nombre_joueurs);

	/* Si les valeurs sont correctement définies, démarrer la partie */
	if (taille_grille > 0 && nombre_joueurs > 0) {
		int largeur_case = 500 / taille_grille; /* Calcul de la largeur d'une case */
		int offset_x = (1000 - taille_grille * largeur_case) / 2;
		int offset_y = (600 - taille_grille * largeur_case) / 2;
		if (taille_grille <= 4) {
			pion_bleu = ChargerSprite("Pionb_100x100.png");
			pion_orange = ChargerSprite("Pionc_100x100.png");
		} else {
			pion_bleu = ChargerSprite("Pionb_50x50.png");
			pion_orange = ChargerSprite("Pionc_50x50.png");
		}

		EffacerEcran(CouleurParComposante(255,255,255));
		AfficherGrille(taille_grille, largeur_case, offset_x, offset_y);
		ReinitialiserGrille(grille, taille_grille); 


		/* Lancer la gestion du jeu */

		if (nombre_joueurs == 1) {
			GestionJeuIA(grille, taille_grille, pion_bleu, pion_orange, largeur_case, offset_x, offset_y, croix_bleu, croix_orange);
			LibererSprite(pion_bleu);
    		LibererSprite(pion_orange);
    		LibererSprite(croix_bleu);
    		LibererSprite(croix_orange);
		} else {
			GestionJeu(grille, taille_grille, pion_bleu, pion_orange, largeur_case, offset_x, offset_y, croix_bleu, croix_orange, nombre_joueurs);
			LibererSprite(pion_bleu);
    		LibererSprite(pion_orange);
    		LibererSprite(croix_bleu);
    		LibererSprite(croix_orange);

		}

	}
}


