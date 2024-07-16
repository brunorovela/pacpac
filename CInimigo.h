#ifndef CInimigo_h
#define CInimigo_h

#include <allegro.h>

class CInimigo
{
private:
   BITMAP *imgInimigo;
   int iPosx;
   int iPosy;
public:
   int iLargura;
   int iAltura;
   int iVelocidade;
   bool bAtivo;

   CInimigo();
   ~CInimigo();
   void Setax(int);
   void Setay(int);
   void Setaxy(int,int);
   void IAFugir(int [],int,int);
   void IAForte(int [],int,int);
   int Pegax();
   int Pegay();
   void Atualiza(BITMAP *);
};

#endif
