# Jeu de Placement et de Blocage (Grille Dynamique)

## **Description du projet**
Ce programme est un jeu stratégique basé sur une grille dynamique où deux joueurs (ou un joueur contre une IA) placent des pions et des croix pour bloquer leur adversaire.
Il intègre une interface graphique interactive, des règles simples, et une logique modulaire pour faciliter l'extension et l'amélioration.

---

## **Fonctionnalités principales**
- **Menu graphique interactif** :
  - Sélection de la taille de la grille (3x3 à 9x9).
  - Choix entre deux modes de jeu : 1 joueur contre IA ou 2 joueurs.
  - Bouton "Confirmer" pour valider les choix et démarrer la partie.
  
- **Affichage dynamique de la grille** :
  - La grille est centrée automatiquement et s’adapte à la taille choisie.
  - Les cellules sont bien délimitées et interactives.

- **Modes de jeu** :
  - **Mode 2 joueurs** : Deux joueurs humains jouent à tour de rôle.
  - **Mode 1 joueur** : Le joueur affronte une IA avec des placements stratégiques.

- **Conditions de fin** :
  - Un joueur est bloqué : l’autre gagne.
  - La grille est pleine : le joueur ayant placé le dernier pion gagne.

- **Menu de fin** :
  - Affiche le gagnant avec un message coloré.
  - Boutons "Quitter" pour fermer le programme et "Rejouer" pour recommencer une partie.

---

## **Structure du projet**
Le code est organisé en plusieurs fichiers pour assurer modularité et lisibilité :
- **`main.c`** : Point d’entrée du programme. Initialise les ressources et orchestre les appels aux fonctions principales.
- **`graphique.c`** :
  - Gestion de l’interface graphique (menus, affichage de la grille, pions et croix).
- **`jeu.c`** :
  - Logique du jeu : alternance des tours, placement des pions et croix, gestion des conditions de fin.
- **`utilitaires.c`** :
  - Fonctions génériques (vérification des déplacements, détection de blocage, etc.).

---

## **Dépendances**
Le programme utilise la bibliothèque graphique **`graph.h`**. Assurez-vous qu’elle est installée avant de compiler.

### **Prérequis :**
1. Un environnement Linux ou compatible avec **`graph.h`**.
2. Un compilateur C (comme `gcc`).
3. Assurez vous d'avoir tout les fichiers .c et .h et Makefile et tout image .png dans un seul et même dossier

---

## **Compilation et exécution**
1. **Compiler le programme :**
   make run
	ou si vous ne souhaitez pas utiliser le Makefile même s'il est la pour simplifier :
   gcc main.c graphique.c jeu.c utilitaires.c -o jeu -lgraph ; ./jeu

## Auteur
* Prénom Nom : Wael ATIK & Emmanuel TIAMZON
* Étudiant à l’IUT de Fontainebleau (UPEC)

## Remarque
Ce projet n’est pas destiné à un usage commercial. Il a été créé dans un but d’apprentissage uniquement.
