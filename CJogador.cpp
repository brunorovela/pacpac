#include "CJogador.h"

   static int iVelSprite = 0;
   static int iDirecao = -1;

CJogador::CJogador()
{
   this->imgJogador = NULL;
   this->imgJogador = load_bitmap("pacpac.bmp",NULL);
   this->iPosx = 0;
   this->iPosy = 0;
   this->iLargura = 25;
   this->iAltura = 25;
   this->iSpritex = 0;
   this->iSpritey = 0;
   this->iPontos = 0;
   this->iQueijos = 0;
   this->iVida = 5;

   ::iVelSprite = 4;
}

CJogador::~CJogador()
{
   delete this->imgJogador;
}

void CJogador::Setaxy(int vx, int vy)
{
   this->iPosx = vx;
   this->iPosy = vy;
}

void CJogador::Setax(int vx)
{
   this->iPosx += vx;
   if (vx<0)
   {
      this->iSpritey = 25;
   }
   if (vx>0)
   {
      this->iSpritey = 0;
   }
}

void CJogador::Setay(int vy)
{
   this->iPosy += vy;
   if (vy<0)
   {
      this->iSpritey = 50;
   }
   if (vy>0)
   {
      this->iSpritey = 75;
   }
}

int CJogador::Pegax()
{
   return this->iPosx;
}

int CJogador::Pegay()
{
   return this->iPosy;
}

void CJogador::Atualiza(BITMAP *buffer)
{

   if (this->iSpritex >= 100)
   {
      this->iSpritex = 0;
   }

   blit(imgJogador,buffer,this->iSpritex,this->iSpritey,this->iPosx,
   this->iPosy,this->iLargura,this->iAltura);

   ::iVelSprite--;
   if (::iVelSprite<=0)
   {
      this->iSpritex += 25;
      ::iVelSprite=4;
   }
}

void CJogador::Controle(int vDirecao[])
{
   static int Buffer_Teclado = 0;

   if (key[KEY_UP])
   {
      ::iDirecao = 0;
    }else
    if (key[KEY_DOWN])
    {
       ::iDirecao = 1;
    }else
    if (key[KEY_LEFT])
    {
       ::iDirecao = 2;
    }else
    if (key[KEY_RIGHT])
    {
       ::iDirecao = 3;
    }

   if (Buffer_Teclado == 0)
   {
      if (::iDirecao == 0)
      {
         this->Setay(-vDirecao[0]);
         Buffer_Teclado = 10;
      }else 
      if (::iDirecao == 1)
      {
         this->Setay(vDirecao[1]);
         Buffer_Teclado = 10;
      }else 
      if (::iDirecao == 2)
      {
         this->Setax(-vDirecao[2]);
         Buffer_Teclado = 10;
      } else 
      if (::iDirecao == 3)
      {
         this->Setax(vDirecao[3]);
         Buffer_Teclado = 10;
      }
   } else   Buffer_Teclado--;
}

bool CJogador::Colisao(int obj2x,int obj2y, int obj2a, int obj2l)
{
    if (this->iPosx+this->iLargura > obj2x && 
        this->iPosx < obj2x+obj2l && 
        this->iPosy+this->iAltura > obj2y && 
        this->iPosy < obj2y+obj2a)
 		{
 		   return true;
		 } else 
		   return false;

}
void CJogador::ResetarPontos()
{
   this->iPontos = 0;
}
void CJogador::ResetarDirecao()
{
   ::iDirecao = -1;
}

