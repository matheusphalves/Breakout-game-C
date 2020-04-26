#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "jogo.h"//biblioteca do jogo
#include "menu.h"//biblioteca do menu
#include "arquivos.h"
#include "Funçõesauxiliares.h"//biblioteca de funções auxiliares

void SolicitaAcesso(){
    char senha[8];

    DesenhoMenu(14,64,1);
    gotoxy(4,3);
    printf("CONFIGURAR");
    gotoxy(4,6);
    StringsAuxiliares(5);
    gotoxy(4,7);
    gets(senha);
    if(!strcmp(senha,"96666884")){
        printf("Voce entrou nas configuracoes do jogo!");
        system("pause");
    }else{
        system("cls");
        StringsAuxiliares(6);
        system("pause");
        Menu();
    }


}
