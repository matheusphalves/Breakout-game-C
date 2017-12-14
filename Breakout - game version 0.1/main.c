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
int i,j,k;
void gotoxy(int x, int y){//Seta cursor para as coordenadas solicitadas
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}
void textcolor (int cor){//Colore blocos e textos

    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= cor);
}

int main(){
    Menu();
return 0;
}
