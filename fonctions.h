/*!
    \file    fonctions.h
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    15 décembre 2022
    \brief   TD BlackJack
*/

/* Interface de l'objet */
#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

/* Inclusion des entetes de librairies */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ----------------- Déclaration des structures ----------------- */

/* Enumération des couleurs des cartes */
typedef enum {
    PIQUE, COEUR, CARREAU, TREFLE
} Couleur;

/* Enumération des valeurs des cartes */
typedef enum {
    AS, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI
} Valeur;

/* Structure d'un élément d'une pile : carte */
typedef struct {
    Couleur couleur;
    Valeur valeur;
} Carte;

typedef struct {
    Carte carte;
} Paquet;

/* Structure d'un joueur */
typedef struct {
    char* nom;
    Paquet* main;
    int budget;
    int mise;
} Joueur;


/* ----------------- Déclaration des prototypes de fonctions ----------------- */

/*!
    \fn      void viderBuffer(void)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    1 décembre 2022
    \brief   Vide le buffer
*/
void viderBuffer(void);

/*!
    \fn      void initPaquet(Paquet *paquet)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    15 décembre 2022
    \brief   Initialise le paquet de cartes
    \param   paquet le paquet de cartes à initialiser
*/
void initPaquet(Paquet *paquet);

/*!
    \fn      void melangerPaquet(Paquet *paquet)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    15 décembre 2022
    \brief   Mélange le paquet de cartes
    \param   paquet le paquet de cartes à mélanger
*/
void melangerPaquet(Paquet *paquet);

/*!
    \fn      void initJoueur(Joueur *joueur, char *nom)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    17 décembre 2022
    \brief   Initialise le joueur
    \param   joueur le joueur à initialiser
    \param   nom le nom du joueur
*/
void initJoueur(Joueur *joueur, char *nom);

/*!
    \fn      Paquet* distribuerMainDeDepart(Paquet *paquet, Joueur *joueur, Joueur *croupier)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    17 décembre 2022
    \brief   Distribue la main de départ au joueur et au croupier
    \param   paquet le paquet de cartes
    \param   joueur le joueur
    \param   croupier le croupier
*/
Paquet* distribuerMainDeDepart(Paquet *paquet, Joueur *joueur, Joueur *croupier);

/*!
    \fn      Paquet* ajouterCarteMain(Joueur *joueur, Paquet *paquet)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    20 décembre 2022
    \brief   Ajoute une carte à la main du joueur
    \param   joueur le joueur auquel on veut ajouter une carte
    \param   paquet le paquet de cartes
*/
Paquet* ajouterCarteMain(Joueur *joueur, Paquet *paquet);

/*!
    \fn      void afficherMain(Joueur *joueur)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    17 décembre 2022
    \brief   Affiche la main du joueur
    \param   joueur le joueur dont on veut afficher la main
*/
void afficherMain(Joueur *joueur);

/*!
    \fn      int calculerScore(Joueur *joueur)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    21 décembre 2022
    \brief   Calcule le score du joueur
    \param   joueur le joueur dont on veut calculer le score
*/
int calculerScore(Joueur *joueur);

/*!
    \fn      void afficherCarte(Carte carte)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    18 décembre 2022
    \brief   Affiche une carte
    \param   carte la carte à afficher
*/
void afficherCarte(Carte carte);

/*!
    \fn      int splitCartes(Joueur *joueur)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    23 décembre 2022
    \brief   Vérifie si le joueur peut splitter ses cartes
    \param   joueur le joueur dont on veut vérifier si il peut splitter ses cartes
*/
int splitCartes(Joueur *joueur);

/*!
    \fn      void jouerBlackjack(Paquet *paquet, Joueur *joueur, Joueur *croupier)
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version, 0.2 ajout de la fonction splitCartes et de l'option pour doubler la mise
    \date    23 décembre 2022, 30 décembre 2022
    \brief   Joue une partie de blackjack
    \param   paquet le paquet de cartes
    \param   joueur le joueur
    \param   croupier le croupier
*/
void jouerBlackjack(Paquet *paquet, Joueur *joueur, Joueur *croupier);

#endif