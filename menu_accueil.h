#ifndef PROJET_MENU_ACCUEIL_H
#define PROJET_MENU_ACCUEIL_H


#define WIDTH 1920
#define HEIGHT 1080
#include <raylib.h>

void afficher_menu_accueil(int* pointeurEtat);
void afficher_modes_jeu(int* pointeurEtat,Texture2D image,Texture2D image2);
void afficher_options_jeu(int* pointeurEtat);
void afficher_credits(int* pointeurEtat);
void afficher_regles(int* pointeurEtat);
void bouton_Retour(int* pointeurEtat);



typedef enum {
    Accueil,
    Jouer_Nouvelle_Partie,
    Charger_Partie,
    Options,

}Menu_Bouttons;

#endif //PROJET_MENU_ACCUEIL_H
