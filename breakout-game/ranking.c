#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "jogo.h"//biblioteca do jogo
#include "menu.h"//biblioteca do menu
#include "Funçõesauxiliares.h"//biblioteca de funções auxiliares
#define ENTER 13
//Variáveis e funções globais
extern int i,j,k;
extern void gotoxy(int x,int y);
extern void textcolor(int cor);
extern struct jogador{//Jogador atual
    char nome[12];
    char vidas;
    char nivel;
    int pontos;
    int velocidade;
};
extern struct jogador player;//Jogador atual

//Variável de dados sobre jogadores passados
struct JOGADORES{
    char nome[20];
    char nivel;
    int pontos;
};//tipo JOGADOR
struct JOGADORES JogadoresRanking[10];//Comporta no máximo 10 jogadas anteriores

//variável que mostra ranking
char MostreRanking=0;//bug que duplicava o resultado anterior (resolvido)
char iniciou=1;//permite que o programa leia o arquivo apenas uma vez

void DadosJogadorAtual(){//Impressão dos dados dos jogadores
    while(1){//não deixa que usuario digite um nome alem do limite
    DesenhoMenu(14,70,1);
    gotoxy(4,3);
    printf("INFORME O SEU NOME");
    gotoxy(6,4);
    strlen(player.nome);
    gets(player.nome);
        if(strlen(player.nome)>13){
            system("cls");
            gotoxy(4,10);
            StringsAuxiliares(1);
            gotoxy(4,11);
            system("pause");
            continue;
        }else break;
    }
}
void FormaDadosJogadores(){//Geração dos dados iniciais dos jogadores
    for(i=0;i<10;i++){
        strcpy(JogadoresRanking[i].nome,"-----");
        JogadoresRanking[i].pontos=0;
        JogadoresRanking[i].nivel=0;
    }
}
void MesmoJogador(){//Verifica se foi o mesmo jogador já existente no ranking
    for(i=0;i<10;i++){
        if(!strcmp(JogadoresRanking[i].nome,player.nome)&&player.pontos>JogadoresRanking[i].pontos){//atualizando valor do mesmo jogador
            JogadoresRanking[i].pontos=player.pontos;
            JogadoresRanking[i].nivel=player.nivel;
                    strcpy(JogadoresRanking[i].nome,JogadoresRanking[i+1].nome);
                    JogadoresRanking[i].pontos=JogadoresRanking[i+1].pontos;
                    JogadoresRanking[i].nivel=JogadoresRanking[i+1].nivel;
                 break;
        }
    }
}
void AtualizaDadosJogadores(){
    for(i=0;i<10;i++){
        if(player.pontos>JogadoresRanking[i].pontos&&player.pontos!=1){//atualizada dados com novo jogador
            for(j=9;j>i;j--){//Atualiza lista, mantendo-a em ordem descrescente (pontos)
                strcpy(JogadoresRanking[j].nome,JogadoresRanking[j-1].nome);
                JogadoresRanking[j].pontos=JogadoresRanking[j-1].pontos;
                JogadoresRanking[j].nivel=JogadoresRanking[j-1].nivel;
            }
            strcpy(JogadoresRanking[i].nome,player.nome);//dados do jogador que teve a maior pontuação
            JogadoresRanking[i].pontos=player.pontos;
            JogadoresRanking[i].nivel=player.nivel;
            player.pontos=1;
                break;
        }
    }
}
void ZeraRanking(){//Função que apaga todos os dados sobre os jogadores
    DesenhoMenu(14,64,1);
    gotoxy(28,3);
    printf("APAGAR RANKING");
    gotoxy(6,4);
    printf(">Uma vez apagado, os dados nao podem ser resgatados.");
    gotoxy(4,6);
    printf("DESEJA APAGAR O RANKING?");
    gotoxy(6,8);
    printf("Tecle enter para confirmar");
    gotoxy(6,10);
    printf("Tecle qualquer outra tecla para cancelar");
    if(getch()==ENTER){
        DesenhoMenu(14,64,1);
        gotoxy(32,3);
        SaveFile();
        printf("RANKING APAGADO.");
        FormaDadosJogadores();
        system("pause");
    }
}
void DadosJogadoresPassados(){//Dados existentes na partida atual (também serve para resgatar os dados em arquivos)
    if(player.pontos==0)
    FormaDadosJogadores();
    if(iniciou==1){
        LoadFile();//Efetua leitura do ranking no arquivo
        iniciou==0;
    }
    AtualizaDadosJogadores();
    for(i=0;i<10;i++){
    gotoxy(2,8+i);
    printf("%d",i+1);
    gotoxy(5,8+i);
    puts(JogadoresRanking[i].nome);
    gotoxy(30,8+i);
    printf("%d",JogadoresRanking[i].pontos);
    gotoxy(50,8+i);
    printf("%d",JogadoresRanking[i].nivel);
    }
    gotoxy(2,20);
    printf("Tecle enter para apagar o ranking.");
    gotoxy(2,21);
    printf("Tecle qualquer outra tecla para voltar");
}
