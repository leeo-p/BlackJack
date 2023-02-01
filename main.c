/*!
    \file    main.c
    \author  Léo Portet <portetleo@cy-tech.fr>
    \version 0.1 première version
    \date    15 décembre 2022
    \brief   TD Blackjack
*/

/* Inclusion du fichier .h */
#include "fonctions.h"

/*!
    \fn         int main(int argc, char *argv[])
    \author     Léo Portet <portetleo@cy-tech.fr>
    \version    0.1 première version
    \date       15 décembre 2022
    \brief      Programme principal
    \param argc nombre d'arguments en entrée
    \param argv valeur d'arguments en entrée
    \return     0 si tout est OK
*/
int main(int argc, char *argv[]) {
    srand(time(NULL)); // Initialisation de rand

    Paquet *paquet;
    Joueur *joueur;
    Joueur *croupier;
    int int_retour;
    int int_budget;
    char str_nom[20];

    paquet = malloc(52 * sizeof(Paquet));
    joueur = malloc(sizeof(Joueur));
    croupier = malloc(sizeof(Joueur));

    printf("\033[H\033[2J"); // Efface l'écran
    printf("###########################################################################################################################################################################################################\n");
    printf("#\t\t\t\t\t\t  /$$$$$$$  /$$        /$$$$$$   /$$$$$$  /$$   /$$\t    /$$$$$  /$$$$$$   /$$$$$$  /$$   /$$                                                          #\n");
    printf("#\t\t\t\t\t\t | $$__  $$| $$       /$$__  $$ /$$__  $$| $$  /$$/\t   |__  $$ /$$__  $$ /$$__  $$| $$  /$$/                                                          #\n");
    printf("#\t\t\t\t\t\t | $$  | $$| $$      | $$    $$| $$   __/| $$ /$$/ \t      | $$| $$    $$| $$   __/| $$ /$$/                                                           #\n");
    printf("#\t\t\t\t\t\t | $$$$$$$ | $$      | $$$$$$$$| $$      | $$$$$/  \t      | $$| $$$$$$$$| $$      | $$$$$/                                                            #\n"); 
    printf("#\t\t\t\t\t\t | $$__  $$| $$      | $$__  $$| $$      | $$  $$  \t /$$  | $$| $$__  $$| $$      | $$  $$                                                            #\n");
    printf("#\t\t\t\t\t\t | $$  | $$| $$      | $$  | $$| $$    $$| $$|  $$ \t| $$  | $$| $$  | $$| $$    $$| $$|  $$                                                           #\n");
    printf("#\t\t\t\t\t\t | $$$$$$$/| $$$$$$$$| $$  | $$|  $$$$$$/| $$ |  $$\t|  $$$$$$/| $$  | $$|  $$$$$$/| $$ |  $$                                                          #\n");
    printf("#\t\t\t\t\t\t |_______/ |________/|__/  |__/ |______/ |__/  |__/\t |______/ |__/  |__/ |______/ |__/  |__/                                                          #\n");
    printf("###########################################################################################################################################################################################################\n");    
    printf("\n\n");

    printf("\033[1mBienvenue à la table de jeu ! Vous allez affronter le croupier.\033[0m\n\n");

    /* Demander le nom du joueur */
    printf("Entrez votre nom : ");
    int_retour = scanf("%s", str_nom);
    viderBuffer();

    while (int_retour != 1) {
        printf("Entrez un nom valide : ");
        int_retour = scanf("%s", str_nom);
        viderBuffer();
    }
    joueur -> nom = str_nom;

    /* Demander le budget du joueur au début de la partie */
    printf("Entrez votre budget de jeu : ");
    int_retour = scanf("%d", &int_budget);
    viderBuffer();

    while (int_retour != 1 || int_budget <= 0) {
        printf("Entrez un nombre positif : ");
        int_retour = scanf("%d", &int_budget);
        viderBuffer();
    }
    joueur -> budget = int_budget;
    printf("\n");

    printf("\033[1mBonjour %s, vous avez %d €. \033[0m \n\n", joueur -> nom, joueur -> budget);

    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________\n");
    /* Boucle de jeu */
    while (int_budget > 0) {
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________\n\n");
        /* Initialisations */
        initJoueur(joueur, joueur -> nom);
        initJoueur(croupier, "Croupier");
        initPaquet(paquet);
        jouerBlackjack(paquet, joueur, croupier);

        if (joueur -> budget == 0) {
            printf("\033[1mDésolé vous n'avez plus d'argent. La partie est terminée !\033[0m\n");
            exit(0);
        }

        printf("\n\n");
        printf("\033[1mVotre budget est de %d €.\033[0m\n", joueur -> budget);
        printf("\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________\n");
    }
    /* On libère la mémoire */
    free(joueur -> main);
    free(joueur -> nom);
    free(croupier -> main);
    free(joueur);
    free(croupier);
    free(paquet);
    
    return 0;
}