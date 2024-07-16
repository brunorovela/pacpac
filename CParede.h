#ifndef Parede_h
#define Parede_h

#include <allegro.h>

class CParede
{
private:
   BITMAP *imgParede;
   int iPosx;
   int iPosy;
public:
   int iLargura;
   int iAltura;
   bool bAtivo;

   CParede();
   ~CParede();
   void Setax(int);
   void Setay(int);
   void Setaxy(int,int);
   int Pegax();
   int Pegay();
   void Atualiza(BITMAP *);
};

#endif
