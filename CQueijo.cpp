#include "CQueijo.h"

CQueijo::CQueijo()
{
   this->iPosx = 0;
   this->iPosy = 0;
   this->iLargura = 25;
   this->iAltura = 25;
   this->bAtivo = false;
   this->imgQueijo = NULL;
   this->imgQueijo = load_bitmap("queijo.bmp",NULL);
}

CQueijo::~CQueijo()
{
   delete this->imgQueijo;
}

void CQueijo::Setaxy(int vx, int vy)
{
   this->iPosx = vx;
   this->iPosy = vy;
}

void CQueijo::Setax(int vx)
{
   this->iPosx += vx;
}

void CQueijo::Setay(int vy)
{
   this->iPosy += vy;
}

int CQueijo::Pegax()
{
   return this->iPosx;
}
int CQueijo::Pegay()
{
   return this->iPosy;
}
void CQueijo::Atualiza(BITMAP *buffer)
{
   draw_sprite(buffer,this->imgQueijo,this->iPosx,this->iPosy);
}

