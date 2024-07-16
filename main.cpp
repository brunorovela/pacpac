#include <allegro.h>
#include "Cenario.h"
#include "CParede.h"
#include "CQueijo.h"
#include "CInimigo.h"
#include "CJogador.h"

void Monta_Cenario(CParede [],CQueijo [],CInimigo []);
void Desativa_objetos(CParede [],CQueijo [],CInimigo []);
void PrencheVisao(int [],int,int,int);
void Pausar_Jogo(BITMAP *);
int Conta_Queijo();
void Reinicia_Fase(CParede [],CQueijo [],CInimigo []);
void Posiciona_Inimigos(CInimigo []);
void Muda_Fase(CParede [],CQueijo [],CInimigo []);

volatile long int fps = 0;
volatile long int contador = 0;
int mostra_fps = 0;
int conta_fps = 0;

int Telax = 800;
int Telay = 600;

int j = 0;

int Buffer_Teclado = 0;
int iTotQueijo = 0;

const int iTamPasso = 25;
const int iTotalQue = 768; // Máximo de queijos por cenário
const int iTotalIni = 15;  // Máximo de inimigos por cenário
const int iTotalPar = 400; // Máximo de Paredes por cenário

void cont_fps()
{
   fps++;
   conta_fps++;
}
END_OF_FUNCTION(cont_fps);

void tempo()
{
   contador++;
}
END_OF_FUNCTION(tempo);

int main(int argc, char *argv[])
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, Telax, Telay, 0, 0);
	LOCK_VARIABLE(fps);
	LOCK_FUNCTION(cont_fps);
	install_int_ex(cont_fps, BPS_TO_TIMER(60));
	LOCK_VARIABLE(contador);
	LOCK_FUNCTION(tempo);
	install_int(tempo, 100);

	BITMAP *buffer = NULL;
	buffer = create_bitmap(Telax,Telay);
	clear_bitmap(buffer);

	BITMAP *ff = NULL;
	ff = create_bitmap(SCREEN_W,SCREEN_H);
	clear_bitmap(ff);
	ff = load_bitmap("ff.bmp",NULL); // Final Feliz

	BITMAP *ft = NULL;
	ft = create_bitmap(SCREEN_W,SCREEN_H);
	clear_bitmap(ft);
	ft = load_bitmap("ft.bmp",NULL); // Final Triste
   
	BITMAP *Avatar = NULL;
	Avatar = create_bitmap(25,25);
	clear_bitmap(Avatar);
	Avatar = load_bitmap("avatar.bmp",NULL);

	Carrega_Matriz();
 
	CParede Parede[iTotalPar];
	CQueijo Queijo[iTotalQue];
	CInimigo Fantasma[iTotalIni];
	CJogador PacPac;

	Monta_Cenario(Parede,Queijo,Fantasma);

	bool bPause = false;
	int i = 0;
	int j = 0;
	int iVisao[4] = {0,0,0,0};
	int iPacx = 0;
	int iPacy = 0;

	iTotQueijo=Conta_Queijo();

	PacPac.Setaxy(25,25);
	RecuperaPontuacao();

	while(!GameOver)
	{
      while( fps > 0) 
      {
         clear(buffer);

         iPacx = PacPac.Pegax();
         iPacy = PacPac.Pegay();

         // Desenha os queijos
         for (i=0;i<iTotalQue;i++)
         {
            if (Queijo[i].bAtivo)
            {
               Queijo[i].Atualiza(buffer);
            }
         }

         // Desenha as paredes
         for (i=0;i<iTotalPar;i++)
         {
            if (Parede[i].bAtivo)
            {
               Parede[i].Atualiza(buffer);
            }
         } 

         // Desenha os inimigos
         for (i=0;i<iTotalIni;i++)
         {
            if (Fantasma[i].bAtivo)
            {
               //Colisão do PacPac com os fantasmas
               if (PacPac.Colisao(Fantasma[i].Pegax(),Fantasma[i].Pegay(),Fantasma[i].iAltura,Fantasma[i].iLargura))
               {
                  Posiciona_Inimigos(Fantasma);
                  PacPac.Setaxy(25,25);
                  PacPac.iVida--;
                  break;
               }
               PrencheVisao(iVisao,Fantasma[i].Pegax() / iTamPasso,Fantasma[i].Pegay() / iTamPasso,1);
               Fantasma[i].IAForte(iVisao,iPacx,iPacy);
               Fantasma[i].Atualiza(buffer);
            }
         }

         // Colisão do PacPac com o Queijo.
         for (i=0;i<iTotalQue;i++)
         {
            if (Queijo[i].bAtivo)
            {
               if (PacPac.Colisao(Queijo[i].Pegax(),Queijo[i].Pegay(),Queijo[i].iAltura,Queijo[i].iLargura))
               {
                  if (Queijo[i].bAtivo)
                  {
                     Queijo[i].bAtivo = false;
                     PacPac.iPontos += 50;
                     PacPac.iQueijos++;
                     break;
                  }
               }
            }
         }

         //Desenha Avatar
         if (PacPac.iVida > 0)
         {
            for (i=0;i<PacPac.iVida;i++)
            {
               textprintf_ex(buffer,font,610,585,makecol(255,255,0),-1, "Vidas:");
               draw_sprite(buffer,Avatar,675+i*25,575);
            }
         } else GameOver = true;

         PacPac.Atualiza(buffer);
         PrencheVisao(iVisao,PacPac.Pegax() / iTamPasso,PacPac.Pegay() / iTamPasso,1);
         PacPac.Controle(iVisao);

         textprintf_ex(buffer,font,650,0,makecol(255,0,0),-1, "Pontos..: %d",PacPac.iPontos);
         textprintf_ex(buffer,font,650,10,makecol(255,255,0),-1, "Queijos.: %d",PacPac.iQueijos);
         textprintf_ex(buffer,font,550,0,makecol(255,255,0),-1, "Nivel.: %d",iNivel);
         textprintf_ex(buffer,font,550,10,makecol(255,0,0),-1, "Total.: %d",iTotQueijo);

         if (bPause)
         {
            bPause = false;
            Pausar_Jogo(buffer);
         }

         if (PacPac.iQueijos == iTotQueijo)
         {
            if (iNivel < 9)
            {
               PacPac.Setaxy(25,25);
               PacPac.ResetarDirecao();
               PacPac.iQueijos = 0;
               Muda_Fase(Parede,Queijo,Fantasma);
               bPause = true;
            } else GameOver = true;
          
         }
         fps--;
      }
      vsync();      
      draw_sprite(screen,buffer,0,0);

      // Teclas do Jogo
      if (Buffer_Teclado == 0)
      {
         if (key[KEY_F2]) // Reinicia Fase
         {
            PacPac.Setaxy(25,25);
            PacPac.iQueijos = 0;
            if (PacPac.iPontos >= 10000)
            {
               PacPac.iPontos -= 10000;
            } else PacPac.iPontos = 0;
            PacPac.ResetarDirecao();
            Desativa_objetos(Parede,Queijo,Fantasma);
            Monta_Cenario(Parede,Queijo,Fantasma);
            iTotQueijo=Conta_Queijo();
            Buffer_Teclado = 30;
         }
         if (key[KEY_F11]) // Avança uma fase
         {
            PacPac.Setaxy(25,25);
            PacPac.ResetarPontos();
            PacPac.ResetarDirecao();
            Muda_Fase(Parede,Queijo,Fantasma);
            Buffer_Teclado = 30;
         }
         if (key[KEY_P]) // Pausa Jogo
         {
            Pausar_Jogo(buffer);
            Buffer_Teclado = 30;
         }
         if (key[KEY_ESC]) // Sai do jogo
         {
            GameOver = true;
         }
      } else Buffer_Teclado--;
	}

   if (iNivel == 9 && GameOver && PacPac.iQueijos == iTotQueijo)
   {
      while(!key[KEY_ENTER])
      {
         //Final feliz
         clear(buffer);
         draw_sprite(buffer,ff,0,0);
         textprintf_ex(buffer,font,340,250,makecol(255,0,0),-1, "Ultima Pontuacao");
         textprintf_ex(buffer,font,340,260,makecol(255,255,0),-1, "%d",UltimoPonto);
         textprintf_ex(buffer,font,340,276,makecol(255,0,0),-1, "Pontuacao Atual");
         textprintf_ex(buffer,font,340,286,makecol(255,255,0),-1, "%d",PacPac.iPontos);
         draw_sprite(screen,buffer,0,0);
      }
   } else
   {
      //Final Triste
      while(!key[KEY_ENTER])
      {
         clear(buffer);
         draw_sprite(buffer,ft,0,0);
         textprintf_ex(buffer,font,340,104,makecol(255,0,0),-1, "Ultima Pontuacao");
         textprintf_ex(buffer,font,340,114,makecol(255,255,0),-1, "%d",UltimoPonto);
         textprintf_ex(buffer,font,340,130,makecol(255,0,0),-1, "Pontuacao Atual");
         textprintf_ex(buffer,font,340,140,makecol(255,255,0),-1, "%d",PacPac.iPontos);
         draw_sprite(screen,buffer,0,0);
      }
   }

   GravaPontuacao(PacPac.iPontos);

   Avatar = NULL;
   ff = NULL;
   ft = NULL;
   Nivel = NULL;
   buffer = NULL;

   delete Avatar;
   delete ff;
   delete ft;
   delete Nivel;
   delete buffer;

   allegro_exit();
   return 0;     
}

void Monta_Cenario(CParede Parede[],CQueijo Queijo[],CInimigo Fantasma[])
{
   int x = 0;
   int y = 0;
   int iFantasma = 0;
   int iParede = 0;
   int iQueijo = 0;

   for (x=0; x<24; x++)
   {
      for (y=0;y<32;y++)
      {
         //Posiciona as Paredes
         if (Mapa[x][y] == 1)
         {
            Parede[iParede].Setaxy(y*25,x*25);
            Parede[iParede].bAtivo = true;
            iParede++;
         }
         //Posiciona os Queijos
         if (Mapa[x][y] == 0 || Mapa[x][y] == 2)
         {
            Queijo[iQueijo].Setaxy(y*25,x*25);
            Queijo[iQueijo].bAtivo = true;
            iQueijo++;
         }
         //Posiciona os Fantasmas
         if (Mapa[x][y] == 2)
         {
            Fantasma[iFantasma].Setaxy(y*25,x*25);
            Fantasma[iFantasma].Setaxy(y*25,x*25);
            Fantasma[iFantasma].bAtivo = true;
            iFantasma++;
         }
      }
   }
}

void PrencheVisao(int vVisao[],int vMx,int vMy,int vDirecao)
{
   //cima
   if (Mapa[vMy-vDirecao][vMx] == 1)
   {
      vVisao[0] = 0;
   } else vVisao[0] = iTamPasso;
   
   //baixo
   if (Mapa[vMy+vDirecao][vMx] == 1)
   {
      vVisao[1] = 0;
   } else vVisao[1] = iTamPasso;
   
   //esquerda
   if (Mapa[vMy][vMx-vDirecao] == 1)
   {
      vVisao[2] = 0;
   } else vVisao[2] = iTamPasso;
   
   //direita
   if (Mapa[vMy][vMx+vDirecao] == 1)
   {
      vVisao[3] = 0;
   } else vVisao[3] = iTamPasso;
}

int Conta_Queijo()
{
   int x = 0;
   int y = 0;
   int iTotal = 0;

   for (x=0;x<24;x++)
   {
      for (y=0;y<32;y++)
      {
         if (Mapa[x][y] == 0 || Mapa[x][y] == 2)
         {
            iTotal++;
         }
      }
   }
   return iTotal;
}

void Pausar_Jogo(BITMAP *buffer)
{
	BITMAP *imgPause = NULL;

	imgPause = load_bitmap("pause.bmp",NULL);

	while(!key[KEY_ENTER])
	{
		draw_sprite(buffer,imgPause,250,200);
		draw_sprite(screen,buffer,0,0);
      fps = 0;
	}

	imgPause = NULL;
	delete imgPause;
}

void Desativa_objetos(CParede Parede[],CQueijo Queijo[],CInimigo Fantasma[])
{
   int i = 0;

   for (i=0; i<iTotalPar; i++)
   {
      Parede[i].bAtivo = false;
   }

   for (i=0;i<iTotalQue;i++)
   {
      Queijo[i].bAtivo = false;
   }

   for (i=0;i<iTotalIni;i++)
   {
      Fantasma[i].bAtivo = false;
   }
}

void Reinicia_Fase(CParede Parede[],CQueijo Queijo[],CInimigo Fantasma[])
{
   Desativa_objetos(Parede, Queijo, Fantasma);
   Monta_Cenario(Parede, Queijo, Fantasma);
   iTotQueijo = Conta_Queijo();
}

void Muda_Fase(CParede Parede[],CQueijo Queijo[],CInimigo Fantasma[])
{
   Desativa_objetos(Parede, Queijo, Fantasma);
   Carrega_Matriz();
   Monta_Cenario(Parede, Queijo, Fantasma);
   iTotQueijo = Conta_Queijo();
}

void Posiciona_Inimigos(CInimigo Fantasma[])
{
   int x = 0;
   int y = 0;
   int iFantasma = 0;

   for (x=0; x<24; x++)
   {
      for (y=0; y<32; y++)
      {
         //Posiciona os Fantasmas
         if (Mapa[x][y] == 2)
         {
            Fantasma[iFantasma].Setaxy(y*25,x*25);
            Fantasma[iFantasma].Setaxy(y*25,x*25);
            iFantasma++;
         }
      }
   }
}
END_OF_MAIN();
