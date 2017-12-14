#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED
#endif // JOGO_H_INCLUDED
void DesenhaTela();//Desenha a tela de jogo
void MexeBase();//Mexe a raquete usando as teclas A e W
void Bola();//Movimenta a bola, usando coordenadas
void BolaAleatoria();//Gera bola aleatória, deixando o jogo mais desafiante
void PlacarVidaVelocidade();//Informa dados vitais do jogador, como vidas restantes e seus pontos
void ReiniciaJogo();//Reinicia jogo a cada derrota
void Rebate_Barra();//Rebate a bola quando entra em contato com a raquete
void Fases();//Fases do jogo
void ChecaBlocoDestruido();//Checa se bloco foi destruído e deve ser apagado
void ApagaBloco();//Apaga bloco e faz com que a bola não colida nessa região
void FimdeJogo();//Encerra jogo e informa alguns dados do jogador
void ConfiguracaoInicial();//Configurações iniciais do jogo
void Jogar();//Função principal, onde contém as outras
void StatusGame(); //Função que exibe status de vida, morte e pausa
