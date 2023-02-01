/*!
    \file    fonctions.c
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    15 décembre 2022
    \brief   TD Blackjack
*/

/* Inclusion du fichier .h */
#include "fonctions.h"

/* Vider le Buffer */
void viderBuffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Procédure d'initialisation du Paquet de Cartes */
void initPaquet(Paquet* paquet) {
    int int_i; // Variable de boucle
    int int_j; // Variable de boucle
    int int_k; // Variable de boucle

    int_i = 0;

    for (int_j = 0; int_j < 4; int_j++) {        // On parcourt les couleurs
        for (int_k = 0; int_k < 13; int_k++) {   // On parcourt les valeurs
            paquet[int_i].carte.couleur = int_j; // On affecte la couleur
            paquet[int_i].carte.valeur = int_k;  // On affecte la valeur
            int_i++;
        }
    }
}

/* Procédure de mélange du Paquet de Cartes */
void melangerPaquet(Paquet* paquet) {
    Paquet temp; // Variable temporaire
    int int_i;
    int int_j;

    for (int_i = 0; int_i < 52; int_i++) { // On parcourt le paquet
        int_j = rand() % 52;               // On génère un nombre aléatoire
        temp = paquet[int_i];              // On stocke la carte dans la variable temporaire
        paquet[int_i] = paquet[int_j];     // On échange les cartes
        paquet[int_j] = temp;              // On échange les cartes
    }
}

/* Procédure d'initialisation du Joueur */
void initJoueur(Joueur* joueur, char* str_nom) {
    int int_i;

    joueur -> nom = str_nom;                      // On affecte le nom du joueur
    joueur -> main = malloc(11 * sizeof(Paquet)); // On alloue la mémoire pour la main du joueur

    for (int_i = 0; int_i < 11; int_i++) {        // On parcourt la main du joueur
        joueur -> main[int_i].carte.valeur = -1;  // On met la valeur à -1
        joueur -> main[int_i].carte.couleur = -1; // On met la couleur à -1
    }
}

/* Procédure de distribution des mains de jeu de départ */
Paquet* distribuerMainDeDepart(Paquet* paquet, Joueur* joueur, Joueur* croupier) {
    int int_i;

    joueur -> main[0] = paquet[0];   // On donne la première carte au joueur
    croupier -> main[0] = paquet[1]; // On donne la deuxième carte au croupier
    joueur -> main[1] = paquet[2];   // On donne la troisième carte au joueur
    croupier -> main[1] = paquet[3]; // On donne la quatrième carte au croupier

    /* On supprime les 4 premières cartes du paquet en décalant les indices */
    for (int_i = 0; int_i < 48; int_i++) {
        paquet[int_i] = paquet[int_i + 4];
    }

    /* On met les 4 dernières cartes à -1 */
    for (int_i = 48; int_i < 52; int_i++) {
        paquet[int_i].carte.valeur = -1;
        paquet[int_i].carte.couleur = -1;
    }

    return paquet; // On retourne le paquet
}

/* Procédure d'ajout d'une carte à la main du joueur */
Paquet* ajouterCarteMain(Joueur* joueur, Paquet* paquet) {
    int int_i;
    int int_j;

    for (int_i = 9; int_i >= 0; int_i--) {              // On parcourt la main du joueur
        joueur -> main[int_i+1] = joueur -> main[int_i]; // On décale les cartes vers la droite pour avoir de la place pour la nouvelle carte au rang 0
    }

    joueur -> main[0] = paquet[0];          // On donne la première carte du paquet au joueur

    for (int_j = 0; int_j < 51; int_j++) {
        paquet[int_j] = paquet[int_j + 1];  // On décale les cartes du paquet vers la gauche
    }

    return paquet; // On retourne le paquet
}

/* Procédure d'affichage de la main du joueur */
void afficherMain(Joueur* joueur) {
    int int_i;
    int int_score;
    
    printf("\033[1m%s : \033[0m\n", joueur -> nom);    // On affiche le nom du joueur  
    printf("------------------\n");  
    for (int_i = 0; int_i < 11; int_i++) { // On parcourt la main du joueur
        while (joueur -> main[int_i].carte.valeur != -1) {               // Tant que la valeur de la carte n'est pas -1
            if (joueur -> main[int_i].carte.valeur == 0) {               // Si la valeur de la carte est 0
                printf("| As ");                                         // On affiche "As"
            } else if (joueur -> main[int_i].carte.valeur == 10) {       // Si la valeur de la carte est 10
                printf("| Valet ");                                      // On affiche "Valet"
            } else if (joueur -> main[int_i].carte.valeur == 11) {       // Si la valeur de la carte est 11
                printf("| Dame ");                                       // On affiche "Dame"
            } else if (joueur -> main[int_i].carte.valeur == 12) {       // Si la valeur de la carte est 12
                printf("| Roi ");                                        // On affiche "Roi"
            } else {
                printf("| %d ", joueur -> main[int_i].carte.valeur + 1); // Sinon on affiche la valeur de la carte + 1
            }
            if (joueur -> main[int_i].carte.couleur == 0) {              // Si la couleur de la carte est 0
                printf("de Coeur");                                      // On affiche "de Coeur"
            } else if (joueur -> main[int_i].carte.couleur == 1) {       // Si la couleur de la carte est 1
                printf("de Carreau");                                    // On affiche "de Carreau"
            } else if (joueur -> main[int_i].carte.couleur == 2) {       // Si la couleur de la carte est 2
                printf("de Pique");                                      // On affiche "de Pique"
            } else if (joueur -> main[int_i].carte.couleur == 3) {       // Si la couleur de la carte est 3
                printf("de Trèfle");                                     // On affiche "de Trèfle"
            }
            printf("\n");
            break;
        }
    }
    printf("------------------\n");

    /* On affiche le score */
    int_score = calculerScore(joueur); // On calcule le score
    printf("\033[1mScore : %d\033[0m\n", int_score); 
}

/* Procédure d'affichage d'une seule carte */
void afficherCarte(Carte carte) {
    if (carte.valeur == 0) {                 // Si la valeur de la carte est 0
        printf("| As ");                     // On affiche "As"
    } else if (carte.valeur == 10) {         // Si la valeur de la carte est 10
        printf("| Valet ");                  // On affiche "Valet"
    } else if (carte.valeur == 11) {         // Si la valeur de la carte est 11
        printf("| Dame ");                   // On affiche "Dame"
    } else if (carte.valeur == 12) {         // Si la valeur de la carte est 12
        printf("| Roi ");                    // On affiche "Roi"
    } else {
        printf("| %d ", carte.valeur + 1);   // Sinon on affiche la valeur de la carte + 1
    }
    if (carte.couleur == 0) {                // Si la couleur de la carte est 0
        printf("de Coeur");                  // On affiche "de Coeur"
    } else if (carte.couleur == 1) {         // Si la couleur de la carte est 1
        printf("de Carreau");                // On affiche "de Carreau"
    } else if (carte.couleur == 2) {         // Si la couleur de la carte est 2
        printf("de Pique");                  // On affiche "de Pique"
    } else if (carte.couleur == 3) {         // Si la couleur de la carte est 3
        printf("de Trèfle");                 // On affiche "de Trèfle"
    }
    printf("\n");
}

/* Fonction de calcul du score de la main du joueur */
int calculerScore(Joueur* joueur) {
    int int_score; // Score du joueur
    int int_as;    // Nombre d'As
    int int_i;     // Variable de boucle

    int_score = 0;
    int_as = 0;

    /* On parcourt la main du joueur */
    for (int_i = 0; int_i < 10; int_i++) {
        if (joueur -> main[int_i].carte.valeur == 0) { // Si c'est un As
            int_as++;        // On incrémente le nombre d'As
        } else if (joueur -> main[int_i].carte.valeur == 10 || joueur -> main[int_i].carte.valeur == 11 || joueur -> main[int_i].carte.valeur == 12) { // Si c'est Valet, Dame ou Roi
            int_score += 10; // On ajoute 10 au score
        } else {             // Si c'est un nombre
            int_score += joueur -> main[int_i].carte.valeur + 1; // On ajoute la valeur de la carte au score
        }
    }

    /* On calcule le score en fonction du nombre d'As */
    for (int_i = 0; int_i < int_as; int_i++) {
        if (int_score + 11 > 21) { // Si le score + 11 est supérieur à 21
            int_score += 1;        // On ajoute 1 au score
        } else {
            int_score += 11;       // Sinon on ajoute 11 au score
        }
    }

    return int_score; // On retourne le score
}

/* Fonction de comparaison de valeur de la première et deuxième carte de la main du joueur pour l'option de split */
int splitCartes(Joueur *joueur) {
    /* Si le joueur à deux cartes de même valeur et si il a assez d'argent */
    if (((joueur -> main[0].carte.valeur == joueur -> main[1].carte.valeur) || (joueur -> main[0].carte.valeur == 9 && joueur -> main[1].carte.valeur == 10) || (joueur -> main[0].carte.valeur == 10 && joueur -> main[1].carte.valeur == 9) || (joueur -> main[0].carte.valeur == 9 && joueur -> main[1].carte.valeur == 11) || (joueur -> main[0].carte.valeur == 11 && joueur -> main[1].carte.valeur == 9) || (joueur -> main[0].carte.valeur == 9 && joueur -> main[1].carte.valeur == 12) || (joueur -> main[0].carte.valeur == 12 && joueur -> main[1].carte.valeur == 9) || (joueur -> main[0].carte.valeur == 10 && joueur -> main[1].carte.valeur == 11) || (joueur -> main[0].carte.valeur == 11 && joueur -> main[1].carte.valeur == 10) || (joueur -> main[0].carte.valeur == 10 && joueur -> main[1].carte.valeur == 12) || (joueur -> main[0].carte.valeur == 12 && joueur -> main[1].carte.valeur == 10) || (joueur -> main[0].carte.valeur == 11 && joueur -> main[1].carte.valeur == 12) || (joueur -> main[0].carte.valeur == 12 && joueur -> main[1].carte.valeur == 11)) && ((joueur -> mise)*2 <= joueur -> budget)) {
        return 1; // On retourne 1
    } else {
        return 0; // Sinon on retourne 0
    }
}

/* Procédure pour jouer au Blackjack */
void jouerBlackjack(Paquet* paquet, Joueur* joueur, Joueur* croupier) {
    /* Déclaration des variables */
    int int_choix;           // Choix du joueur
    int int_scoreJoueur;     // Score du joueur 
    int int_scoreMain2;      // Score de la main 2
    int int_scoreCroupier;   // Score du croupier
    int int_retour;          // Retour de la fonction scanf
    int int_split;           // Variable de split
    int int_mise;            // Mise du joueur
    Joueur* main2;           // Main 2 du joueur
    Carte carteMainCroupier; // Carte de la main du croupier

    main2 = malloc(sizeof(Joueur)); // On alloue de la mémoire pour la main 2 du joueur

    /* Initialisation des variables */
    int_choix = 0; 
    int_scoreJoueur = 0;
    int_scoreCroupier = 0;
    int_scoreMain2 = 0;

    /* Mélange du paquet */
    melangerPaquet(paquet);

    /* Mise du joueur */
    printf("\033[1mCombien voulez-vous miser ?\033[0m\n");
    int_retour = scanf("%d", &int_mise);
    viderBuffer();
    while (int_retour != 1 || int_mise > joueur -> budget || int_mise < 0) {
        printf("Veuillez entrer un nombre valide.\n");
        int_retour = scanf("%d", &int_mise);
        viderBuffer();
    }
    /* On met à jour le budget du joueur et la mise */
    joueur -> mise = int_mise;
    joueur -> budget -= joueur -> mise;

    /* Distribution des cartes de départ */
    paquet = distribuerMainDeDepart(paquet, joueur, croupier);
    
    /* Calcul du score du joueur */
    int_scoreJoueur = calculerScore(joueur);

    /* Calcul du score du croupier */
    int_scoreCroupier = calculerScore(croupier);

    /* On affiche seulement la première carte du croupier */
    carteMainCroupier = croupier -> main[0].carte;
    printf("\n\033[1mMain du croupier :\033[0m\n");
    printf("------------------\n");
    afficherCarte(carteMainCroupier);
    /* On affiche la deuxième face cachée */
    printf("| ▒\n");
    printf("------------------\n\n");

    /* Affichage de la main de départ et de la mise */
    printf("Mise : %d\n\n", joueur -> mise);
    afficherMain(joueur);
    printf("\n");

    if (int_scoreJoueur == 21 && int_scoreCroupier != 21) {      // Si le joueur a un blackjack et le croupier n'en a pas
        printf("\033[1mBLACKJACK ! Vous avez gagné !\033[0m\n\n");
        afficherMain(croupier);
        printf("\n");
        joueur -> budget += joueur -> mise * 2.5;
    } 
    else if (int_scoreJoueur == 21 && int_scoreCroupier == 21) { // Si le joueur et le croupier ont un blackjack
        printf("\033[1mEgalité !\033[0m\n\n");
        afficherMain(croupier);
        printf("\n");
        joueur -> budget += joueur -> mise;
    } 
    else if (int_scoreJoueur != 21 && int_scoreCroupier == 21) { // Si le joueur n'a pas de blackjack et le croupier en a un
        printf("\033[1mBLACKJACK pour le croupier ! Vous avez perdu !\033[0m\n\n");
        afficherMain(croupier);
        printf("\n");
    } 
    else {
        /* Tant que le joueur ne dépasse pas 21, il peut demander une nouvelle carte */
        while (int_scoreJoueur < 21) {
            /* Options de jeu */
            printf("Voulez-vous une nouvelle carte ? (1 = Oui, 0 = Non)\n");
            /* Si le joueur possède assez d'argent on propose de doubler la mise */
            if ((joueur -> mise)*2 <= joueur -> budget) {
                printf("Voulez-vous doubler la mise et tirer qu'une seule carte ? (2 = Oui, 0 = Non)\n");
            }
            /* Si les deux cartes du joueur sont identiques proposer de spliter le jeu */
            int_split = splitCartes(joueur);
            if (int_split == 1) {
                printf("Voulez-vous spliter votre main ? (3 = Oui, 0 = Non)\n");
            }

            int_retour = scanf("%d", &int_choix);
            printf("\n");
            if (!int_retour) {
                printf("Erreur de saisie !\n");
                break;
            }

            else if (int_choix == 1) {
                paquet = ajouterCarteMain(joueur, paquet); // On ajoute une carte à la main du joueur
                printf("Voici votre nouvelle main :\n\n"); // On affiche la nouvelle main du joueur
                afficherMain(joueur);
                printf("\n");
                int_scoreJoueur = calculerScore(joueur);   // On recalcule le score du joueur

                if (int_scoreJoueur > 21) {                // Si le joueur dépasse 21, il a perdu
                    printf("Vous avez dépassé 21 c'est perdu !\n");
                    printf("La main du croupier était :\n\n"); // On affiche la main du croupier
                    afficherMain(croupier);
                    return;                               // On sort de la procédure de jeu
                }
                else if (int_scoreJoueur == 21) {         // Si le joueur a 21,
                    break;                                // On sort de la boucle
                }
            } 
            else if (int_choix == 2) {
                paquet = ajouterCarteMain(joueur, paquet); // On ajoute une carte à la main du joueur
                joueur -> budget -= joueur -> mise;        // On retire la mise du budget
                joueur -> mise *= 2;                       // On double la mise
                printf("Voici votre nouvelle main :\n\n"); // On affiche la nouvelle main du joueur
                afficherMain(joueur);
                printf("\n");
                int_scoreJoueur = calculerScore(joueur);   // On recalcule le score du joueur

                if (int_scoreJoueur > 21) {
                    printf("Vous avez dépassé 21 c'est perdu !\n");
                    printf("La main du croupier était :\n\n");
                    afficherMain(croupier);
                    return;
                }
                else if (int_scoreJoueur == 21) {
                    break;
                }
                break;
            }
            else if (int_choix == 3) {
                /* Création d'une nouvelle main */
                initJoueur(main2, "Votre seconde main"); /* On initialise la main2 */

                /* On ajoute la deuxième carte de la main du joueur à la main2 */
                main2 -> main[0] = joueur -> main[1];      // On copie la deuxième carte de la main du joueur dans la main2
                joueur -> main[1].carte.couleur = -1;      // On vide la deuxième carte de la main du joueur
                joueur -> main[1].carte.valeur = -1;       // On vide la deuxième carte de la main du joueur
                paquet = ajouterCarteMain(joueur, paquet); // On ajoute une carte à la main du joueur
                paquet = ajouterCarteMain(main2, paquet);  // On ajoute une carte à la main2

                /* On affiche les deux mains */
                printf("Voici votre première main :\n\n"); // On affiche la main du joueur
                afficherMain(joueur);
                printf("\n");
                printf("Voici votre deuxième main :\n\n"); // On affiche la main2
                afficherMain(main2);
                printf("\n");
                int_scoreJoueur = calculerScore(joueur);   // On recalcule le score du joueur.
                int_scoreMain2 = calculerScore(main2);     // On recalcule le score de la main2.
                
                joueur -> budget -= joueur -> mise;        // On retire la mise du budget
                main2 -> mise = joueur -> mise;            // On donne la mise à la main2

                /* Options de jeu */
                while (int_scoreJoueur < 21) {
                    printf("Voulez-vous une nouvelle carte pour votre première main ? (1 = Oui, 0 = Non)\n");
                    printf("Voulez-vous doubler la mise et tirer qu'une seule carte ? (2 = Oui, 0 = Non)\n");
                    int_retour = scanf("%d", &int_choix);
                    printf("\n");

                    if (!int_retour) {
                        printf("Erreur de saisie !\n");
                        break;
                    }
                    else if (int_choix == 1) {
                        paquet = ajouterCarteMain(joueur, paquet);
                        printf("Voici votre nouvelle main :\n\n");
                        afficherMain(joueur);
                        printf("\n");
                        int_scoreJoueur = calculerScore(joueur);

                        if (int_scoreJoueur > 21) {
                            printf("Vous avez dépassé 21 c'est perdu pour cette main !\n");
                            break;
                        }
                        else if (int_scoreJoueur == 21) {
                            break;
                        }
                    }
                    else if (int_choix == 2) {
                        paquet = ajouterCarteMain(joueur, paquet);
                        joueur -> budget -= joueur -> mise;
                        joueur -> mise *= 2;
                        printf("Voici votre nouvelle main :\n\n");
                        afficherMain(joueur);
                        printf("\n");
                        int_scoreJoueur = calculerScore(joueur);

                        if (int_scoreJoueur > 21) {
                            printf("Vous avez dépassé 21 c'est perdu pour cette main !\n");
                            break;
                        }
                        else if (int_scoreJoueur == 21) {
                            break;
                        }
                        break;                        
                    }
                    else {
                        break;
                    }
                }
                while (int_scoreMain2 < 21) {
                    printf("Voulez-vous une nouvelle carte pour votre deuxième main ? (1 = Oui, 0 = Non)\n");
                    printf("Voulez-vous doubler la mise et tirer qu'une seule carte ? (2 = Oui, 0 = Non)\n");
                    int_retour = scanf("%d", &int_choix);
                    printf("\n");

                    if (!int_retour) {
                        printf("Erreur de saisie !\n");
                        break;
                    }
                    else if (int_choix == 1) {
                        paquet = ajouterCarteMain(main2, paquet);
                        printf("Voici votre nouvelle main :\n\n");
                        afficherMain(main2);
                        printf("\n");
                        int_scoreMain2 = calculerScore(main2);

                        if (int_scoreMain2 > 21) {
                            printf("Vous avez dépassé 21 c'est perdu !\n");
                            return;
                        }
                        else if (int_scoreMain2 == 21) {
                            break;
                        }
                    } 
                    else if (int_choix == 2) {
                        paquet = ajouterCarteMain(joueur, paquet);
                        joueur -> budget -= joueur -> mise;
                        joueur -> mise *= 2;
                        printf("Voici votre nouvelle main :\n\n");
                        afficherMain(joueur);
                        printf("\n");
                        int_scoreJoueur = calculerScore(joueur);

                        if (int_scoreJoueur > 21) {
                            printf("Vous avez dépassé 21 pour la deuxième main c'est perdu !\n");
                            return;
                        }
                        else if (int_scoreJoueur == 21) {
                            break;
                        }
                        break;                        
                    }
                    else {
                        break;
                    }
                }
            }
            if (int_scoreJoueur > 21) {
                printf("Vous avez dépassé 21 c'est perdu !\n");
                return;
            }
            else if (int_scoreJoueur == 21) {
                return;
            }
            else if (int_choix == 0) {
                break;
            }
        }

        /* Affichage complet de la main du croupier */
        printf("Le croupier dévoile sa deuxième carte :\n\n"); // On affiche la deuxième carte du croupier
        afficherMain(croupier);
        printf("\n");

        /* Sinon, le croupier joue */
        int_scoreCroupier = calculerScore(croupier); // On calcule le score du croupier

        while (int_scoreCroupier < 17) {
            /* Le croupier tire une carte */
            paquet = ajouterCarteMain(croupier, paquet); 

            printf("Voici la nouvelle main du croupier :\n\n");
            afficherMain(croupier);
            printf("\n");

            /* Calcul du score du croupier */
            int_scoreCroupier = calculerScore(croupier);

            /* Si le croupier dépasse 21, le joueur a gagné */
            if (int_scoreCroupier > 21) {
                printf("Vous avez gagné !\n");
                joueur -> budget += joueur -> mise * 2;
                return;
            }
            else if (int_scoreCroupier == 21) {
                break;
            }
        } 

        /* Vérification des scores et du gagnant */
        /* Vérification de la première main */

        /* Si le croupier a un score supérieur au joueur, le joueur a perdu */
        if (int_scoreCroupier > int_scoreJoueur && int_scoreCroupier <= 21) {
            printf("Vous avez perdu pour la première main !\n");
        }
        /* Si le croupier a un score inférieur au joueur, le joueur a gagné */
        else if (int_scoreCroupier < int_scoreJoueur && int_scoreJoueur <= 21) {
            printf("Vous avez gagné pour la première main !\n");
            joueur -> budget += joueur -> mise * 2;
        }
        /* Si le croupier a un score égal au joueur, il y a égalité */
        else if (int_scoreCroupier == int_scoreJoueur) {
            printf("Egalité pour la première main !\n");
            joueur -> budget += joueur -> mise;
        }

        /* Vérification de la deuxième main */

        /* Si le joueur a une deuxième main */
        if (int_scoreMain2 != 0) {
            /* Si le croupier a un score supérieur au joueur, le joueur a perdu */
            if (int_scoreCroupier > int_scoreMain2 && int_scoreCroupier <= 21) {
                printf("Vous avez perdu pour la deuxième main !\n");
            }
            /* Si le croupier a un score inférieur au joueur, le joueur a gagné */
            else if (int_scoreCroupier < int_scoreMain2 && int_scoreMain2 <= 21) {
                printf("Vous avez gagné pour la deuxième main !\n");
                joueur -> budget += main2 -> mise * 2;
            }
            /* Si le croupier a un score égal au joueur, il y a égalité */
            else if (int_scoreCroupier == int_scoreMain2) {
                printf("Egalité pour la deuxième main !\n");
                joueur -> budget += main2 -> mise;
            }
        }
    }
    /* Libération de la mémoire */
    free(main2 -> main);
    free(main2);
}   
