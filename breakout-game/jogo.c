#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "ranking.h"
#include "menu.h"
#include "Funçõesauxiliares.h"//biblioteca de funções auxiliares
//desenhos
#define ICON 219
#define ENTER 13

//desenho tela e barra
char retang[30][70];
char barra[20];
int barraESQ=15;
//variáveis e funções globais
extern int i,j,k;
extern void gotoxy(int x,int y);
extern void textcolor(int cor);
//coordenadas da bola
char bolaX=25,bolaY=15;
char direcaoX=1,direcaoY=1;
//dados do jogador
struct jogador
{
    char nome[12];
    char vidas;
    char nivel;
    int pontos;
    int velocidade;
};
struct jogador player;
//construção dos blocos
struct BLOCOSJOGO
{
    char blocos[5];
    char verificador;
    char apagado;
    char coordenadaX;//coordenadas X e Y de cada bloco
    char coordenadaY;
};
struct BLOCOSJOGO bloco[9][9];
char contabloco=0;
char seletor=0;
char QtdeBlocos=0;
void DesenhaTela() //OK Construção da matriz e raquete
{
    char i,j;
    system("cls");
    for(i=0; i<30; i++)
    {
        for(j=0; j<75; j++)
        {
            if(i==0||i==29||j==0||j==49||j==74)
                printf("%c",ICON);
            else printf(" ");
        }
        printf("\n");
    }
    for(i=0; i<20; i++) //desenho da barra
    {
        barra[i]=ICON;
    }
    gotoxy(barraESQ,27);
    textcolor(11);
    printf("%s",barra);
}
void StatusGame(){
    textcolor(3);
    gotoxy(52,20);
    printf("STATUS");
    gotoxy(52,21);
    if(i==0)
    {
        textcolor(2);
        printf("EM JOGO");
        gotoxy(52,22);
        printf("Acerte os blocos!     ");
    }
    else if(i==1)
    {
        textcolor(4);
        printf("MORREU!");
        gotoxy(52,22);
        printf("Tecle algo para jogar!");
    }
    else if(i==2){
        textcolor(5);
        printf("PAUSADO");
        gotoxy(52,22);
        printf("Enter para continuar!");
    }
}
void PlacarVidaVelocidade() // Informações gerais sobre o jogador
{
    textcolor(3);
    gotoxy(52,2);
    printf("JOGADOR");
    gotoxy(52,3);
    printf("%s",player.nome);
    gotoxy(52,4);
    printf("PONTUACAO");
    gotoxy(52,6);
    printf("%d pontos",player.pontos);
    gotoxy(52,8);
    printf("VIDAS RESTANTES");
    gotoxy(52,10);
    printf("%d",player.vidas);
    gotoxy(52,12);
    printf("NIVEL");
    gotoxy(52,14);
    printf("%d",player.nivel);
    gotoxy(52,16);
    printf("VELOCIDADE ATUAL");
    gotoxy(52,17);
    printf("%d",player.velocidade);
    StatusGame();
}
void MexeBase() //OK Movimentação da raquete
{
    switch(getch())
    {
    case 'A':
    case 'a':
        if(barraESQ>1)
            barraESQ-=2;
        gotoxy(barraESQ,27);
        textcolor(11);
        puts(barra);
        gotoxy(barraESQ+20,27);
        printf("  ");
        break;
    case 'D':
    case 'd':
        if(barraESQ<28)
            barraESQ+=2;
        gotoxy(barraESQ,27);
        textcolor(11);
        puts(barra);
        gotoxy(barraESQ-2,27);
        printf("  ");
        break;
    case ENTER:
        while(1){
        i=2;
        PlacarVidaVelocidade();
            if(getch()==ENTER){
                i=0;
                break;
            }
        }
        break;
    }
}
void Bola() //OK Movimento da bola
{
    gotoxy(bolaX,bolaY);
    putchar(' ');
    if(bolaX==1||bolaX==48)
    {
        direcaoX=-direcaoX;
        Beep(500,15);
    }
    if(bolaY==1||bolaY==28)
    {
        direcaoY=-direcaoY;
        Beep(500,15);
    }
    bolaX+=direcaoX;
    bolaY+=direcaoY;
    gotoxy(bolaX,bolaY);
    textcolor(11);
    printf("@");
}
void BolaAleatoria() //OK Geração de bola em local aleatório
{
    srand(time(NULL));
    while(1)
    {
        bolaX=rand()%50;
        bolaY=rand()%30;
        if(bolaX>1&&bolaX<48&&bolaY>22&&bolaY<25)
            break;
        else continue;
    }
}
void ReiniciaJogo() //Recomeça partida após uma derrota
{
    if(direcaoY>0)
        direcaoY=-direcaoY;//garante que bola sempre suba no reinicio de jogada

    gotoxy(bolaX,bolaY);
    printf(" ");
    PlacarVidaVelocidade();
    BolaAleatoria();
    Bola();
    for(i=1; i<48; i++)
    {
        gotoxy(i,27);
        printf(" ");
    }
    barraESQ=15;
    MexeBase();
    if(getch())
    {
        i=0;
        Sleep(2000);
    }
}
void Rebate_Barra() //OK Condição para bola ser rebatida pela raquete
{
    if(bolaY==26&&bolaX>=barraESQ&&bolaX<=barraESQ+19)
    {
        direcaoY=-direcaoY;
        if(direcaoX<0) //bola movimento << eixo X
        {
            if(bolaX>=barraESQ+13&&bolaX<=barraESQ+19&&barraESQ!=28) direcaoX=-direcaoX;
        }
        else if(direcaoX>0)  //bola movimento >> eixo X
        {
            if(bolaX>=barraESQ&&bolaX<=barraESQ+3&&barraESQ!=1) direcaoX=-direcaoX;
        }
        Beep(500,15);
    }
    else if(bolaY>26)
    {
        direcaoY=-direcaoY;//garante que bola sempre suba no reinicio de jogada
        i=1;
        player.vidas--;
        ReiniciaJogo();
    }
}
void Fases() //Constroi blocos a serem destruídos bem como as suas fases
{
    QtdeBlocos=0;
    contabloco=0;
    i=0;
    j=0;
    k=0;
    char termo=0,termo2=0;
    for(i=0; i<9; i++) //construção dos blocos
    {
        for(j=0; j<9; j++)
        {
            for(k=0; k<4; k++)
            bloco[i][j].blocos[k]=ICON;
            bloco[i][j].verificador=1;
            bloco[i][j].coordenadaX=0;
            bloco[i][j].coordenadaY=0;
        }
    }

    if(contabloco==0)//seletor de fases
        seletor+=1;

    if(seletor==1) //FASE 1
    {
        for(i=0; i<7; i++)
        {
            for(j=0; j<9; j++)
            {
                textcolor(i+1);
                gotoxy(3+termo,3+termo2);
                puts(bloco[i][j].blocos);
                bloco[i][j].coordenadaX=3+termo;
                bloco[i][j].coordenadaY=3+termo2;
                contabloco++;
                termo+=5;
            }
            termo=0;
            termo2+=2;
        }
    }
    else if(seletor==2)  //FASE 2
    {
        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                textcolor(14);
                if((i+j>=termo2&&i+j<=8)||(i+j==termo2&&i+j!=8))
                {
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                else if(i+j==8)
                {
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                else
                {
                    textcolor(9);
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                termo+=5;
            }
            termo=0;
            termo2+=2;
        }
    }
    else if(seletor==3)  //FASE 3
    {
        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                if((i==2||i==5||i==8)&&j>=1&&j<=7)
                {
                    textcolor(5);
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                if(i>2&&i<5)
                {
                    textcolor(6);
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                else if(i>5&&i<8)
                {
                    textcolor(8);
                    gotoxy(3+termo,3+termo2);
                    puts(bloco[i][j].blocos);
                    bloco[i][j].coordenadaX=3+termo;
                    bloco[i][j].coordenadaY=3+termo2;
                    contabloco++;
                }
                termo+=5;
            }
            termo=0;
            termo2+=2;
        }
    }
    i=0;
}
void ChecaBlocoDestruido() //checa se bloco foi destruído
{
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            if(bloco[i][j].coordenadaX!=0&&bloco[i][j].coordenadaY!=0)
            {
                if((bolaX==bloco[i][j].coordenadaX||bolaX==bloco[i][j].coordenadaX+5)&&(bolaY==bloco[i][j].coordenadaY)&&(bloco[i][j].verificador==1))
                {
                    direcaoX=-direcaoX;
                    bloco[i][j].verificador=0;
                    bloco[i][j].apagado=0;
                    player.pontos+=10;
                    contabloco--;
                    Beep(2500,15);
                }
                else if((bolaX>=bloco[i][j].coordenadaX&&bolaX<=bloco[i][j].coordenadaX+5)&&(bolaY==bloco[i][j].coordenadaY+1||bolaY==bloco[i][j].coordenadaY-1)&&(bloco[i][j].verificador==1))
                {
                    direcaoY=-direcaoY;
                    bloco[i][j].verificador=0;
                    bloco[i][j].apagado=0;
                    player.pontos+=10;
                    contabloco--;
                    Beep(2500,15);
                }

            }
        }
    }
}
void ApagaBloco() //OK apaga os blocos atingidos pelo jogador
{
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            if(bloco[i][j].apagado==0)
            {
                if(bloco[i][j].coordenadaX!=0&&bloco[i][j].coordenadaY!=0)
                {
                    if(bloco[i][j].verificador==0)
                    {
                        gotoxy(bloco[i][j].coordenadaX,bloco[i][j].coordenadaY);
                        bloco[i][j].apagado=1;
                        printf("     ");
                    }
                }
            }
        }
    }
}
void FimdeJogo()
{
    system("cls");
    DesenhoMenu(10,90,2);

    gotoxy(40,10);
    StringsAuxiliares(2);//Pontos feitos
    gotoxy(40,11);
    StringsAuxiliares(3);//Tecle algo para salvar e voltar
    system("pause");
    system("cls");
    seletor=0;
    DesenhoMenu(24,90,0);
    MesmoJogador();//atualiza dados de um jogador existente somente se sua pontuação for maior que a anterior(bug que só deixava a primeira posição)
    //Função MesmoJogador se encontra no arquivo ranking.c
}
void ConfiguracaoInicial()
{
    DadosJogadorAtual();
    player.pontos=0;
    player.vidas=1;
    player.nivel=0;
    player.velocidade=125;
    DesenhaTela();
    BolaAleatoria();
    contabloco=0;//garante que fases serão construídas
}
void Jogar()
{
    ConfiguracaoInicial();
    while(1)
    {
        if(contabloco==0)
        {
            player.velocidade-=25;
            player.nivel++;
            Fases();
            ReiniciaJogo();
        }
        if(kbhit())
            MexeBase();
        Rebate_Barra();
        Bola();
        PlacarVidaVelocidade();
        ChecaBlocoDestruido();
        ApagaBloco();
        if(player.vidas==-1){
            break;
        }
        Sleep(player.velocidade);
    }
    FimdeJogo();
}
