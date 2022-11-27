#include <stdio.h>
#include <raylib.h>
#include "includes/test.h"
#include "includes/menu_accueil.h"
#include "includes/menu_UI.h"


#define TITLE "ECE City"

int main (void){

    //ini_Menu(GetMousePosition(),GetScreenWidth(),GetScreenHeight(),"ECE CITY");
    menu(GetMousePosition(),GetScreenWidth(),GetScreenHeight()); //prendre en para screen size et mouse position

    return 0;
}