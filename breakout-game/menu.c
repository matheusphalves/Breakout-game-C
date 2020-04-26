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
#include "Funçõesauxiliares.h"//biblioteca de funções auxiliares
//auxiliares
#define ENTER 13
#define ICON 219
//Variáveis e funções globais
extern int i,j,k;
extern void gotoxy(int x,int y);
extern void textcolor(int cor);
//Variáveis de apoio
char moldura[20][90];
char desliga=1,op;
void DesenhoMenu(char a, char b,char entrou){//Desenha as diversas telas entre os menus
system("cls");
textcolor(15);
for(i=0;i<a;i++){
    for(j=0;j<b;j++){
        if(i==0||i==a-1||j==0||j==b-1)
            putchar(ICON);
        else if(op==3){
                if((i>2)&&(j==20||j==40))
                    printf("%c",220);
                else if(i==3||i==6)
                    printf("%c",220);
                else putchar(' ');
        }else
            putchar(' ');
    }
putchar('\n');
}
    if(entrou==0){
    textcolor(10);
    gotoxy(6,3);
    printf(" _____ _____ _____ _____ _____ _____ _____ _____    _____ _____ _____ _____ ");
    gotoxy(6,4);
    printf("| __  | __  |   __|  _  |  |  |     |  |  |_   _|  |   __|  _  |     |   __|");
    gotoxy(6,5);
    printf("| __ -|    -|   __|     |    -|  |  |  |  | | |    |  |  |     | | | |   __|");
    gotoxy(6,6);
    printf("|_____|__|__|_____|__|__|__|__|_____|_____| |_|    |_____|__|__|_|_|_|_____|");
    }else if(entrou==2){
    textcolor(10);
    gotoxy(15,3);
    printf(" _____ _____ _____ _____    _____ _____ _____ _____ ");
    gotoxy(15,4);
    printf("|   __|  _  |     |   __|  |     |  |  |   __| __  |");
    gotoxy(15,5);
    printf("|  |  |     | | | |   __|  |  |  |  |  |   __|    -|");
    gotoxy(15,6);
    printf("|_____|__|__|_|_|_|_____|  |_____|\___/|_____|__|__|");
    }
j=1;
op=1;
}
void Controles(){//Exibe como jogar e informações extras
    system("cls");
    fflush(stdin);
    DesenhoMenu(14,64,1);
    gotoxy(4,3);
    printf("INSTRUCOES");
    gotoxy(6,4);
    printf("- Use as teclas A e D para movimentar a raquete.");
    gotoxy(4,6);
    printf("INFORMACOES EXTRAS");
    gotoxy(6,8);
    printf("- Contem niveis desafiantes, inspirado no BreakOut Atari");
    gotoxy(6,9);
    printf("- Sistema de aumento gradativo de dificuldade");
    gotoxy(6,10);
    printf("- Sistema de ranking");
    getch();
    DesenhoMenu(24,90,0);

}
void Ranking(){//Mostra o ranking dos jogadores
    DesenhoMenu(20,60,1);
    gotoxy(25,2);
    printf("RANKING GERAL");
    gotoxy(3,5);
    printf("Nome do jogador");
    gotoxy(26,5);
    printf("Pontuacao");
    gotoxy(43,5);
    printf("Nivel atingido");
    DadosJogadoresPassados();
        if(getch()==ENTER)
        ZeraRanking();
        DesenhoMenu(24,90,0);
}
void SobreJogo(){//Informações adicionais sobre o projeto
    system("cls");
    DesenhoMenu(14,70,1);
    gotoxy(4,3);
    printf("SOBRE O JOGO");
    gotoxy(6,4);
    printf("Desenvolvido por: Matheus Phelipe (Graduando em Eng. Comp)");
    gotoxy(6,6);
    printf("Disciplina: Linguagem de Programacao Imperativa - LPI");
    gotoxy(6,8);
    printf("Orientador: Prof. Joabe Jesus");
    gotoxy(6,10);
    printf("Instituicao: UPE/POLI");
    getch();
    DesenhoMenu(24,90,0);
}
void Configurar(){//Configurar algumas coisas sobre o jogo
    SolicitaAcesso();
}
void Diagnosticos(){
    system("cls");
    printf("[AREA DE DIAGNOSTICOS DO JOGO]\n\n");
    Abertura();
    getch();
    DesenhoMenu(24,90,0);
}
void Seletor(){//Seletor de opção entre os menus
        switch(getch()){
            case 's':
            case 'S':
                op++;
                j++;
                k+=2;
                Beep(1000,25);
                break;
            case 'w':
            case 'W':
                op--;
                j--;
                k-=2;
                Beep(1000,25);
                break;
            case 'd':
            case 'D':
                Diagnosticos();
                break;
            case ENTER:
                Beep(2000,50);
                if(op==1)
                    Jogar();
                else if(op==2)
                    Controles();
                else if(op==3)
                    Ranking();
                else if(op==4)
                    SobreJogo();
                else if(op==5)
                    Configurar();
                else if(op==6){
                    desliga=0;
                    system("cls");
                    printf("OBRIGADO POR JOGAR!");
                }
                op=1; j=1;k=0;
                break;
    }
        if(op<=0){
            op=6;
            j=6;
            k=10;
        }else if(op>=7){
            op=1;
            j=1;
            k=0;
        }
}
void SeletorMenu(){
    for(i=0;i<12;i+=2){
        textcolor(15);
        gotoxy(38,8+i);
        putchar(ICON);
        if(op==j&&j>=1&&j<=6){
            textcolor(9);
            gotoxy(38,8+k);
            putchar(ICON);
        }
    }
    textcolor(15);
    gotoxy(40,8);
    printf("JOGAR");
    gotoxy(40,10);
    printf("CONTROLES");
    gotoxy(40,12);
    printf("RANKING");
    gotoxy(40,14);
    printf("SOBRE O JOGO");
    gotoxy(40,16);
    printf("CONFIGURACOES");
    gotoxy(40,18);
    printf("SAIR");
}
void Menu(){//Menu inicial do jogo
    LoadFile();
    DesenhoMenu(24,90,0);
    while(desliga!=0){//Loop principal do jogo
    SeletorMenu();
    Seletor();
    SaveFile();//Salva os dados do jogador que morreu
    }
    SaveFile();//Salva dados dos ranking
}
