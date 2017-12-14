#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "jogo.h"
#include "ranking.h"
#include "arquivos.h"
//variáveis de outros arquivos .C
extern struct jogador
{
    char nome[12];
    char vidas;
    char nivel;
    int pontos;
    int velocidade;
};
extern struct jogador player;

void StringsAuxiliares(int a){//Função que exibe avisos em determinados momentos da execução do programa a= numero do aviso
    typedef struct warnings{
        char texto[60];
    }alertas;
    alertas avisos[10];
    if(a==1){//aviso de limite excedido de nome do jogador
        strcpy(avisos[a].texto,"*Limite de caracteres excedido. Digite novamente.");
        puts(avisos[a].texto);
    }else if(a==2){//informa o salvamento do jogo
        printf("Fim de jogo!\nPONTOS FEITOS = %d",player.pontos);
    }else if(a==3){//informa o salvamento do jogo
        strcpy(avisos[a].texto,"Tecle algo para voltar e salvar.");
        puts(avisos[a].texto);
    }else if(a==4){//informa o salvamento do jogo
        strcpy(avisos[a].texto,"Jogo salvo.");
        puts(avisos[a].texto);
    }else if(a==5){
        strcpy(avisos[a].texto,"Área restrita. Informe sua senha para prosseguir.");
        puts(avisos[a].texto);
    }else if(a==6){
        strcpy(avisos[a].texto,"Acesso negado. Tente novamente.");
        puts(avisos[a].texto);
    }
}
