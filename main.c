#include <stdio.h>
#include <raylib.h>
#include "includes/test.h"
#include "includes/menu_accueil.h"
#include "includes/menu_UI.h"


#define TITLE "ECE City"

int main (void){

    menu(GetMousePosition(),GetScreenWidth(),GetScreenHeight()); //prendre en para screen size et mouse position

    return 0;
}