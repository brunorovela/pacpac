#include "CInimigo.h"

CInimigo::CInimigo()
{
   this->imgInimigo = NULL;
   this->imgInimigo = load_bitmap("fantasma.bmp",NULL);
   this->iPosx = 0;
   this->iPosy = 0;
   this->iLargura = 25;
   this->iAltura = 25;
   this->iVelocidade = 30;
   this->bAtivo = false;
}

CInimigo::~CInimigo()
{
   delete imgInimigo;
}

void CInimigo::Setaxy(int vx, int vy)
{
   this->iPosx = vx;
   this->iPosy = vy;
}

void CInimigo::Setax(int vx)
{
   this->iPosx += vx;
}
void CInimigo::Setay(int vy)
{
   this->iPosy += vy;
}

void CInimigo::IAFugir(int vDirecao[],int iPacx, int iPacy)
{
   static int iTempo=0;
   int bMover = false;
   
   if (iTempo == 0)
   {
      if (bMover==false)
      {
         if (this->iPosy > iPacy)
         {
            if (vDirecao[0] != 0)
            {
               this->Setay(vDirecao[0]);
               bMover=true;
            }
         }
         if (this->iPosy < iPacy)
         {
            if (-vDirecao[1] != 0)
            {
               this->Setay(vDirecao[1]);
               bMover=true;
            }
         }  
      }

      if (bMover==false)
      {
         if (this->iPosx > iPacx)
         {
            if (vDirecao[2] != 0)
            {
               this->Setax(vDirecao[2]);
               bMover=true;
            }
         }
         if (this->iPosx < iPacx)
         {
            if (vDirecao[3] != 0)
            {
               this->Setax(-vDirecao[3]);
               bMover=true;
            }
         }
      }
      iTempo = iVelocidade;
   } else   iTempo--;
}

void CInimigo::IAForte(int vDirecao[],int iPacx, int iPacy)
{
   static int iTempo=0;
   int bMover = false;
   
   if (iTempo == 0)
   {
      if (bMover==false)
      {
         if (this->iPosy > iPacy)
         {
            if (vDirecao[0] != 0)
            {
               this->Setay(-vDirecao[0]);
               bMover=true;
            }
         }
         if (this->iPosy < iPacy)
         {
            if (vDirecao[1] != 0)
            {
               this->Setay(vDirecao[1]);
               bMover=true;
            }
         }  
      }

      if (bMover==false)
      {
         if (this->iPosx > iPacx)
         {
            if (vDirecao[2] != 0)
            {
               this->Setax(-vDirecao[2]);
               bMover=true;
            }
         }
         if (this->iPosx < iPacx)
         {
            if (vDirecao[3] != 0)
            {
               this->Setax(vDirecao[3]);
               bMover=true;
            }
         }
      }
      iTempo = iVelocidade;
   } else   iTempo--;
}
int CInimigo::Pegax()
{
   return this->iPosx;
}
int CInimigo::Pegay()
{
   return this->iPosy;
}
void CInimigo::Atualiza(BITMAP *buffer)
{
   draw_sprite(buffer, imgInimigo, iPosx, iPosy);
}

