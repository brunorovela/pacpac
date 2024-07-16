#include "CParede.h"

CParede::CParede()
{
   this->iPosx = 0;
   this->iPosy = 0;
   this->iLargura = 25;
   this->iAltura = 25;
   this->bAtivo = false;
   this->imgParede = NULL;
   this->imgParede = load_bitmap("parede.bmp",NULL);
}

CParede::~CParede()
{
   delete this->imgParede;
}
void CParede::Setaxy(int vx, int vy)
{
   this->iPosx = vx;
   this->iPosy = vy;
}
void CParede::Setax(int vx)
{
   this->iPosx = vx;
}
void CParede::Setay(int vy)
{
   this->iPosy = vy;
}
int CParede::Pegax()
{
   return this->iPosx;
}
int CParede::Pegay()
{
   return this->iPosy;
}
void CParede::Atualiza(BITMAP *buffer)
{
   draw_sprite(buffer,this->imgParede,this->iPosx,this->iPosy);
}
