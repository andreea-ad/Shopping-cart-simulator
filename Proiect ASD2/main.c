#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
};

typedef struct nod{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
  int cantitateProdus;
  struct nod *urm;
}Tnod;

typedef struct lista{
  Tnod *primul, *ultimul;
}Tlista;

char nume[15], prenume[15], adresa[30];
long numarTelefon;
int plata, livrare;
char ch;

FILE *fproduse, *bproduse, *favorite;

void citireTabelProduseFemei(int *n, struct Produs f[])
{ int i;
  fproduse=fopen("produseFemei.txt","r");
  if(fproduse==NULL)
    { printf("Fisierul cu produse pentru femei nu a putut fi deschis\n");
      exit(1);
    }
  fscanf(fproduse,"%d",n);
  for(i=0;i<*n;i++)
    { fscanf(fproduse,"%d",&f[i].codProdus);
      fscanf(fproduse,"%s",f[i].numeProdus);
      fscanf(fproduse,"%f",&f[i].pretProdus);
    }
}

void citireTabelProduseBarbati(int *n, struct Produs b[])
{ int i;
  bproduse=fopen("produseBarbati.txt","r");
  if(bproduse==NULL)
    { printf("Fisierul cu produse pentru barbati nu a putut fi deschis\n");
      exit(1);
    }
  fscanf(bproduse,"%d",n);
  for(i=0;i<*n;i++)
    { fscanf(bproduse,"%d",&b[i].codProdus);
      fscanf(bproduse,"%s",b[i].numeProdus);
      fscanf(bproduse,"%f",&b[i].pretProdus);
    }
}

void afisareTabelProduseFemei(int *n, struct Produs f[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\tPRET PRODUS\n);
  for(i=0;i<*n;i++)
  {
    printf("%3d\t%30s\t%.2f\n",f[i].codProdus,f[i].numeProdus,f[i].pretProdus);
  }
}

void afisareTabelProduseBarbati(int *n, struct Produs b[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\tPRET PRODUS\n);
  for(i=0;i<*n;i++)
  {
    printf("%3d\t%30s\t%.2f\n",b[i].codProdus,b[i].numeProdus,b[i].pretProdus);
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
  printf("SUMAR COMANDA\n);
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

void initializareLista(Tlista *lista)
{
    lista->primul=lista->ultimul=NULL;
    printf("Cosul de cumparaturi este gol\n");
}

int verificaProdus(int *n,int cod,char *nume,float pret,struct Produs f[],struct Produs b[])
{
    int i;
    for(i=0;i<*n;i++)
    {
        if(cod==f[i].codProdus || cod==b[i].codProdus && strcmp(nume,f[i].numeProdus)==0 || strcmp(nume,b[i])==0 && pret==f[i].pretProdus || pret==b[i].pretProdus)
            return 1;
        else
            return 0;
    }
}

Tnod *cautaProdusInCos(Tlista *lista, int cod)
{
    Tnod *temp=lista->primul;
    while(temp!=NULL)
    {

    }
}
void adaugareProduseInLista(Tlista *lista, int *n, int cod, struct Produs f[], struct Produs b[])
{
    Tnod *p=cautaProdusInCos(&lista,);
    if(p==NULL)
    {
        Tnod *nodNou;
        nodNou=(Tnod *)malloc(sizeof(Tnod));
        if(nodNou==NULL)
        {
            printf("EROARE!\n");
            exit(1);
        }
        if(ch=='f')
            if(verificaProdus(&n,cod,f))

                   {
                       printf("Produsul exista deja in cos! Doriti sa mai adaugati o bucata? [d/n]\n");
                       char optiune;
                       scanf("%c",&optiune);
                       if(optiune=='d')
                            marireCantitate(&lista,cod);
                       else
                            {   printf("Doriti sa eliminati produsul din cos? [d/n]\n");
                                scanf("%c",&optiune);
                                if(optiune=='d')
                                    micsorareCantitate(&lista,cod);
                            }
                   }
                else{   nodNou->p->codProdus=f.codProdus;
                    strcpy(nodNou->p->numeProdus,f.numeProdus);
                    nodNou->p->pretProdus=f.pretProdus;
                    nodNou->cantitateProdus=1;
                    nodNou->urm=NULL;
                    if(lista->primul==NULL)
                        lista->primul=lista->ultimul=nodNou;
                    else
                    {
                        lista->ultimul->urm=nodNou;
                        lista->ultimul=nodNou;
                    }
                }

        else if(ch=='b')
            if(verificaProdus(&n,cod,b))
            {   nodNou->p->codProdus=b.codProdus;
                strcpy(nodNou->p->numeProdus,b.numeProdus);
                nodNou->p->pretProdus=b.pretProdus;
                nodNou->cantitateProdus=1;
                nodNou->urm=NULL;
                if(lista->primul==NULL)
                    lista->primul=lista->ultimul=nodNou;
                else
                {
                    lista->ultimul->urm=nodNou;
                    lista->ultimul=nodNou;
                }
            }


    }
}



void adaugareProdusLaFavorite(int *n,int cod, char *nume, float pret, Tlista *lista, struct Produs f[], struct Produs b[], struct Produs p[])
{
    if(verificaProdus(&n,cod,&nume,pret,f,b))
    {   favorite=fopen("favorite.txt","r+");
        if(favorite==NULL)
        {
            printf("Fisierul cu produse favorite nu a putut fi accesat!\n");
            exit(1);
        }
        int i,nrProduse=0;
        char c;
        unsigned int cantitate;
        while((c=getch(favorite))!=EOF)
            if(c=='\n')
                nrProduse++;
        for(i=0;i<nrProduse;i++)
            {   fscanf(favorite,"%d",&p[i].codProdus);
                fscanf(favorite,"%s",p[i].numeProdus);
                fscanf(favorite,"%f",&p[i].pretProdus);
            }
        fprintf(favorite,"COD PRODUS\t NUME PRODUS\t, PRET PRODUS\n");
        for(i=0;i<nrProduse;i++)
            if(cod==p[i].codProdus)
                {   printf("Doriti sa mariti cantitatea produsului cu codul %d [d/n]?",cod);
                    if((c=getch())=='d')
                    {   printf("Introduceti cantitatea dorita:");
                        scanf("%d",&cantitate);
                        marireCantitate(cod,cantitate,&lista);
                    }
                    printf("Doriti sa micsorati cantitatea produsului cu codul %d [d/n]?",cod);
                    if((c=getch())=='d')
                    {   printf("Introduceti cantitatea dorita:");
                        scanf("%d",&cantitate);
                        micsorareCantitate(cod,cantitate,&lista);
                    }
            else
                    {   fprintf(favorite,"%3d",cod);
                        fprintf(favorite,"%30s",nume);
                        fprintf(favorite,"%.2f",pret);
                    }
                }
    }

void marireCantitate(int cod, unsigned int cantitate, Tlista *lista)
{
    Tnod *temp=lista->primul;
    if(cantitate>temp->cantitateProdus)
    {   while(temp.codProdus!=cod && temp!=NULL)
            temp=temp->urm;
        temp->cantitateProdus=cantitate;
    }
}

void micsorareCantitate(int cod, unsigned int cantitate, Tlista *lista)
{
    Tnod *temp=lista->primul;
    if(cantitate<temp->cantitateProdus)
        {   while(temp.codProdus!=cod && temp!=NULL)
                temp=temp->urm;
            temp->cantitateProdus=cantitate;
        }
}

void afisareLista()
float totalPlata()

int main()
{
    Tlist cosCumparaturi;
    int *n;
    struct Produs f[15];
    struct Produs b[15];
    citireTabelProduseFemei(&n,f);
    citireTabelProduseBarbati(&n,b);
    unsigned short optiune,ok=1;
    printf("\t\t MENIU\n");
    printf("\t 1. Afiseaza lista cu produse\n");
    printf("\t 2. Initializare cos de cumparaturi\n");
    printf("\t 3. Adauga produs in cos\n");
    printf("\t 4. Adauga produs la favorite\n");
    printf("\t 5. Sterge produs din cos\n");
    printf("\t 6. Goleste cosul de cumparaturi\n");
    printf("\t 7. Afiseaza sumarul comenzii\n");
    printf("\t 8. Procesare comanda\n");
    printf("\t 9. Inchide aplicatia\n");
    printf("Introduceti o cifra corespunzatoare actiunii dorite:\n");
    scanf("%hi",&optiune);
    do{
        while(optiune<1 || optiune>9)
        {
            printf("EROARE: Valoarea introdusa trebuie sa fie din intervalul [1,9]!\n");
            printf("Introduceti alta cifra corespunzatoare actiunii dorite:\n");
            scanf("%hi",&optiune);
        }
        switch(optiune)
        {
            case 1: initializareLista(&cosCumparaturi);
                    ok=1;
                    break;
            case 2: if(ok)
                        {   printf("Ce lista doriti sa afisati? f-femei, b-barbati\n");
                            scanf("%c",ch);
                            if(tolower(ch)=='f')
                                afisareTabelProduseFemei(&n,f);
                            else
                                afisareTabelProduseBarbati(&n,b);
                            break;
                        }
            case 3: adaugareProduseInLista()
        }
    }
}
