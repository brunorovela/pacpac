#ifndef CJogador_h
#define CJogador_h

#include <allegro.h>

class CJogador
{
private:
   BITMAP *imgJogador;
   int iPosx;
   int iPosy;
   int iSpritex;
   int iSpritey;
public:
   int iLargura;
   int iAltura;
   int iPontos;
   int iQueijos;
   int iVida;

   CJogador();
   ~CJogador();
   void Setax(int);
   void Setay(int);
   void Setaxy(int,int);
   void ResetarPontos();
   void ResetarDirecao();
   int Pegax();
   int Pegay();
   void Atualiza(BITMAP *buffer);
   void Controle(int []);
   bool Colisao(int ,int , int , int);
};

#endif
