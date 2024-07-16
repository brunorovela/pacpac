#ifndef CQueijo_h
#define CQueijo_h

#include <allegro.h>

class CQueijo
{
private:
   BITMAP *imgQueijo;
   int iPosx;
   int iPosy;
public:
   int iLargura;
   int iAltura;
   bool bAtivo;

   CQueijo();
   ~CQueijo();
   void Setax(int);
   void Setay(int);
   void Setaxy(int,int);
   int Pegax();
   int Pegay();
   void Atualiza(BITMAP *);
};

#endif
