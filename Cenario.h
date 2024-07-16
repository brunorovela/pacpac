#include <fstream>

using namespace std;

void Carrega_Matriz();
void RecuperaPontuacao();
void GravaPontuacao(int);

int Mapa[24][32];
char Niveis[] = "nivel0.dat;nivel1.dat;nivel2.dat;nivel3.dat;nivel4.dat;nivel5.dat;nivel6.dat;nivel7.dat;nivel8.dat;nivel9.dat";
char *Nivel;
int iNivel=0;
static bool PrimeiraVez = true;
static bool GameOver = false;
static int UltimoPonto = 0;

void Carrega_Matriz()
{
   int x = 0;
   int y = 0;

   if (PrimeiraVez)
   {
      Nivel = strtok( Niveis, ";" );
      PrimeiraVez = false;
      iNivel = 0;
   } else
   {
      Nivel = strtok( NULL, ";" );
      if (Nivel)
      {
         iNivel++;
      } else
        {
            GameOver=true;
        }
   }

   ifstream LendoArquivo(Nivel, ios::in ); 

   for (x=0;x<24;x++)
   {
      for (y=0;y<32;y++)
      {
         LendoArquivo >> Mapa[x][y];
      }
   }
   LendoArquivo.close();
}

void GravaPontuacao(int vPontos)
{
   if (UltimoPonto < vPontos)
   {
      ofstream AbreArquivo ( "rec.dat", ios::out );
      AbreArquivo << vPontos << endl;
      AbreArquivo.close();
   }
}

void RecuperaPontuacao()
{
   ifstream LendoArquivo("rec.dat", ios::in );

   while (LendoArquivo)
   {
      LendoArquivo >> UltimoPonto;
   }
   LendoArquivo.close();
}
