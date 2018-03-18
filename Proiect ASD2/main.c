#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
};

/*struct Cos{
  char Produs[30];
  int cantitateProdus;

};*/


char nume[15], prenume[15], adresa[30];
long numarTelefon;
int plata, livrare;

FILE *fproduse;

void citireTabelProduse(int *n, struct Produs p[])
{ int i;
  fproduse=fopen("produse.txt","r");
  if(fproduse==NULL)
    { printf("Fisierul nu a putut fi deschis\n");
      exit(1);
    }
  fscanf(fproduse,"%d",n);
  for(i=0;i<*n;i++)
    { fscanf(fproduse,"%d",&p[i].codProdus);
      fscanf(fproduse,"%s",p[i].numeProdus);
      fscanf(fproduse,"%f",&p[i].pretProdus);
    }
}

void afisareTabelProduse(int *n, struct Produs p[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\tPRET PRODUS\n);
  for(i=0;i<*n;i++)
  {
    printf("%4d\t%30s\t%.2f\n",p[i].codProdus,p[i].numeProdus,p[i].pretProdus);
  }
}

void datePersonale()
{
  printf("Introduceti numele dumneavoastra\n");
  fgets(nume,15,stdin);
  fflush(stdin);
  printf("Introduceti prenumele dumneavoastra\n");
  fgets(prenume,15,stdin);
  fflush(stdin);
  printf("Introduceti adresa de livrare\n");
  fgets(adresa,30,stdin);
  fflush(stdin);
  printf("Introduceti numarul dumneavoastra de telefon\n");
  scanf("%ld",&numarTelefon);
}

void plataSiLivrare()
{ printf("Introduceti cifra corespunzatoare metodei de plata dorite:\n 1-NUMERAR/RAMBUS\n 2-ONLINE CU CARD BANCAR\n");
  scanf("%d",&plata);
  printf("Introduceti cifra corespunzatoare metodei de livrare dorite:\n 1-CURIER(15.99 lei)\n 2-POSTA(9.99 lei)\n");
  scanf("%d",&livrare);
}

void sumarComanda()
{
  printf("SUMAR COMANDA\n;
  printf("DATE PERSONALE CLIENT:\n NUME%15s\n PRENUME%15s\n ADRESA LIVRARE%30s\n NUMAR DE TELEFON%ld\n",nume, prenume, adresa, numarTelefon);
  printf("PRODUSE ADAUGATE IN COS:\n);
  afisareLista();
  switch(plata)
  { case 1: printf("Metoda de plata: NUMERAR/RAMBUS\n");
            break;
    case 2: printf("Metoda de plata: ONLINE CU CARD BANCAR\n");
            break;
    default:printf("Metoda de plata inexistenta!\n");
  }

  switch(livrare)
  { case 1: printf("Metoda de livrare: CURIER\n");
            break;
    case 2: printf("Metoda de livrare: POSTA\n");
            break;
    default:printf("Metoda de livrare inexistenta!\n");
  }
  printf("TOTAL PLATA:\n);
  totalPlata();
}


void creareLista()
void adaugareProduseInLista()
void listaVida()
void stergeProdusDinLista()
void adaugareProdusLaFavorite()
void marireCantitate()
void micsorareCantitate()
void afisareLista()
float totalPlata()

int main()
{

}
