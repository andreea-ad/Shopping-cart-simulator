#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
};

struct Fav{
  int codProdus;
  char numeProdus[30];
};

typedef struct nod{
  int codProdus;
  unsigned int cantitateProdus;
  char numeProdus[30];
  float pretProdus, pretTotal;
  struct nod *urm;
}Tnod;

typedef struct lista{
  Tnod *primul, *ultimul;
}Tlista;

char nume[15], prenume[15], adresa[30], ch;
long numarTelefon;
int plata, livrare;

FILE *fproduse, *bproduse, *favorite;


//FUNCTII PENTRU CITIRE/AFISARE PRODUSE STOC, VALIDARE ETC

void citireTabelProduseFemei(struct Produs f[])
{ int i;
  fproduse=fopen("produseFemei.txt","r");
  if(fproduse==NULL)
    {
      printf("Fisierul cu produse pentru femei nu a putut fi deschis\n");
      exit(1);
    }
  for(i=0;i<15;i++)
    {
      fscanf(fproduse,"%d",&f[i].codProdus);
      fscanf(fproduse,"%s",f[i].numeProdus);
      fscanf(fproduse,"%f",&f[i].pretProdus);
    }
}

void citireTabelProduseBarbati(struct Produs b[])
{ int i;
  bproduse=fopen("produseBarbati.txt","r");
  if(bproduse==NULL)
    {
      printf("Fisierul cu produse pentru barbati nu a putut fi deschis\n");
      exit(1);
    }
  for(i=0;i<15;i++)
    {
      fscanf(bproduse,"%d",&b[i].codProdus);
      fscanf(bproduse,"%s",b[i].numeProdus);
      fscanf(bproduse,"%f",&b[i].pretProdus);
    }
}


void afisareTabelProduseFemei(struct Produs f[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t%30s\t%.2f\n",f[i].codProdus,f[i].numeProdus,f[i].pretProdus);
  }
}

void afisareTabelProduseBarbati(struct Produs b[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t%30s\t%.2f\n",b[i].codProdus,b[i].numeProdus,b[i].pretProdus);
  }
}

int validareProdusFemei(int cod, struct Produs f[])
{
    int i;
    for(i=0;i<15;i++)
    {
        if(cod==f[i].codProdus)
            return 1;
        else
            return 0;
    }
}

int validareProdusBarbati(int cod, struct Produs b[])
{
    int i;
    for(i=0;i<15;i++)
    {
        if(cod==b[i].codProdus)
            return 1;
        else
            return 0;
    }
}

int nrProduseFavorite()     //returneaza nr de linii(produse) din fisier
{
    char c;
    int nrProduse=0;
    while((c=getch(favorite))!=EOF)
        if(c=='\n')
            nrProduse++;
    return nrProduse;
}

void citireProduseFavorite(struct Fav p[])
{
    favorite=fopen("favorite.txt","a+");
    if(favorite==NULL)
    {
        printf("Fisierul cu produse favorite nu a putut fi accesat!\n");
        exit(1);
    }
    int i,nrProduse=nrProduseFavorite();
    for(i=0;i<nrProduse;i++)
    {
        fscanf(favorite,"%d",&p[i].codProdus);
        fscanf(favorite,"%s",p[i].numeProdus);
    }
}

void adaugareProdusLaFavorite(int cod, char *nume, struct Produs f[], struct Produs b[], struct Fav p[])
{
    while(!validareProdusFemei(cod,f)&&!validareProdusBarbati(cod,b))
    {
        printf("Codul introdus nu apartine unui produs din gama magazinului! Introduceti alt cod:\n");
        scanf("%d",&cod);
    }

    int i, nrProduse=nrProduseFavorite();
    for(i=0;i<nrProduse;i++)
        {   if(cod!=p[i].codProdus)     //verifica daca produsul nu exista deja in lista de favorite
                fprintf(favorite,"%d\t %30s\n",cod,nume);
            else
                printf("Produsul exista deja in lista de favorite!\n");
        }
}

void afisareProduseFavorite(struct Fav p[])
{
    int i, nrProduse=nrProduseFavorite();
    printf("COD PRODUS\t NUME PRODUS\n");
    for(i=0;i<nrProduse;i++)
    {
        printf("%d\t %30s\n",p[i].codProdus, p[i].numeProdus);
    }
}

void datePersonale()                    //citeste datele personale ale clientului
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

void plataSiLivrare()                   //citeste metodele de plata/livrare dorite de client
{
  printf("Introduceti cifra corespunzatoare metodei de plata dorite:\n 1-NUMERAR/RAMBUS\n 2-ONLINE CU CARD BANCAR\n");
  scanf("%d",&plata);
  while(plata!=1 && plata!=2)
    { printf("Metoda de plata inexistenta! Introduceti o alta metoda de plata\n");
      scanf("%d",&plata);
    }
  printf("Introduceti cifra corespunzatoare metodei de livrare dorite:\n 1-CURIER(15.99 lei)\n 2-POSTA(9.99 lei)\n");
  scanf("%d",&livrare);
  while(livrare!=1 && livrare!=2)
    { printf("Metoda de livrare inexistenta! Introduceti o alta metoda de livrare\n");
      scanf("%d",&livrare);
    }
}

void sumarComanda()                   //afiseaza datele de contact ale clientului si optiunile de plata/livrare
{
  printf("SUMAR COMANDA\n");
  printf("DATE PERSONALE CLIENT:\n NUME:%15s\n PRENUME:%15s\n ADRESA LIVRARE:%30s\n NUMAR DE TELEFON:%ld\n",nume, prenume, adresa, numarTelefon);
  switch(plata)
  { case 1: printf("Metoda de plata: NUMERAR/RAMBUS\n");
            break;
    case 2: printf("Metoda de plata: ONLINE CU CARD BANCAR\n");
            break;
  }

  switch(livrare)
  { case 1: printf("Metoda de livrare: CURIER\n");
            break;
    case 2: printf("Metoda de livrare: POSTA\n");
            break;
  }
}

//FUNCTII PENTRU LISTA


void initializareLista(Tlista *lista)
{
    lista->primul=lista->ultimul=NULL;
    printf("Cosul de cumparaturi este gol\n");
}

Tnod *cautaProdusInCos(Tlista *lista, int cod)
{
    Tnod *temp=lista->primul;
    while(temp)
    {
        if(temp->codProdus==cod)      //cauta produsul in cos in functie de codul introdus(daca exista, returneaza nodul aferen)
            return temp;
        temp=temp->urm;
    }
}

void adaugareProdusInLista(Tlista *lista, int cod, char *nume, float pret, struct Produs f[], struct Produs b[])
{
    int cantitate;
    Tnod *nodNou;
    nodNou=(Tnod *)malloc(sizeof(Tnod));            //aloca memorie pentru produsul(nodul) curent
    if(nodNou==NULL)
    {
        printf("EROARE ALOCARE MEMORIE\n");
        exit(1);
    }
    if(tolower(ch)=='f')
            if(validareProdusFemei(cod,f))          //verifica daca produsul exista in gama de produse pt femei
            {
                nodNou->codProdus=cod;
                strcpy(nodNou->numeProdus,nume);
                nodNou->pretProdus=pret;
                nodNou->pretTotal=1;
                nodNou->cantitateProdus=1;
            }
    else if(tolower(ch)=='b')
            if(validareProdusBarbati(cod,b))        //verifica daca produsul exista in gama de produse pt barbati
            {
                nodNou->codProdus=cod;
                strcpy(nodNou->numeProdus,nume);
                nodNou->pretProdus=pret;
                nodNou->pretTotal=1;
                nodNou->cantitateProdus=1;
            }
    else
        {
            printf("Optiune inexistenta! Alegeti f pentru FEMEI sau b pentru BARBATI\n");
            return 0;
        }
    if(lista->primul==NULL)                         //verifica daca exista produse in cos/lista
        lista->primul=nodNou;
    else{
        Tnod *temp=cautaProdusInCos(&lista,cod);
        if(temp==NULL)                              //produsul curent nu exista in cos si va fi adaugat la final
        {
            nodNou=lista->primul;
            while(nodNou)
            {
                nodNou=nodNou->urm;
            }
            nodNou->codProdus=cod;
            strcpy(nodNou->numeProdus,nume);
            nodNou->pretProdus=pret;
            nodNou->pretTotal=pret;
            nodNou->cantitateProdus=1;
            nodNou->urm=NULL;
        }
        else                                        //produsul curent exista in cos si cantitatea acestuia se poate mari/micsora daca este de dorit
        {
            printf("Produsul exista deja in cos! Doriti sa mariti cantitatea acestuia? [d/n]\n");
            char optiune;
            scanf("%c",&optiune);
            if(optiune=='d')
            {
                printf("Introduceti cantitatea dorita:\n");
                scanf("%ld",&cantitate);
                if(cantitate>0 && cantitate>nodNou->cantitateProdus)    //verifica daca cantitatea dorita este o valoare pozitiva mai mica decat cantitatea actuala
                {
                    modificareCantitate(&lista,cod,cantitate);
                    printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                }
                else
                {
                    while(cantitate<0 || cantitate<nodNou->cantitateProdus)
                    {
                        printf("Cantitatea introdusa nu este valida! Introduceti alta valoare mai mare decat %d\n",nodNou->cantitateProdus);
                        scanf("%ld",&cantitate);
                    }
                    modificareCantitate(&lista,cod,cantitate);
                    printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                }
            }
            else
            {
                printf("Doriti sa micsorati cantitatea produsului? [d/n]\n");
                scanf("%c",&optiune);
                if(optiune=='d')
                {
                    printf("Introduceti cantitatea dorita:\n");
                    scanf("%ld",&cantitate);
                    if(cantitate>=0 && cantitate<nodNou->cantitateProdus)   //verifica daca cantitatea dorita este pozitiva si mai mica decat cantitatea actuala
                    {
                        modificareCantitate(&lista,cod,cantitate);
                        printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                    }
                    else
                    {
                        while(cantitate<0 || cantitate>nodNou->cantitateProdus)
                        {
                            printf("Cantitatea introdusa nu este valida! Introduceti alta valoare din intervalul [0,%d):",nodNou->cantitateProdus);
                            scanf("%ld",&cantitate);
                        }
                        modificareCantitate(&lista,cod,cantitate);
                        printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                    }
                }
            }
        }
    }
}

void modificareCantitate(Tlista *lista, int cod, unsigned int cantitate)
{
    Tnod *temp=lista->primul;
    while(temp->codProdus!=cod && temp)
            temp=temp->urm;
    temp->cantitateProdus=cantitate;
}

void stergeProdusDinLista(Tlista *lista, int cod)
{
    Tnod *temp=cautaProdusInCos(&lista,cod), *p;
    if(temp==NULL)
    {
        printf("Produsul cu codul %d nu a fost gasit in cos\n",cod);
        return 0;
    }
    else
    {
        p=temp->urm;
        if(p!=NULL)
            p->urm=p->urm->urm;
        if(p->urm->urm==NULL)
            lista->ultimul=p;
        free(temp);
    }
}

void calculPret(Tlista *lista)
{
    Tnod *temp=lista->primul;
    while(temp)
    {
        temp->pretTotal=temp->pretProdus*temp->cantitateProdus;
        temp=temp->urm;
    }
}

float totalPlata(Tlista lista)
{
    float sumaTotala=0;
    Tnod *temp=lista.primul;
    while(temp)
    {
        sumaTotala=sumaTotala+temp->pretTotal;
        temp=temp->urm;
    }
    return sumaTotala;
}

void afisareLista(Tlista lista)
{
    Tnod *temp=lista.primul;
    printf("COD PRODUS\tNUME PRODUS\t CANTITATE PRODUS\t PRET TOTAL PRODUS\n");
    while(temp)
    {
        printf("%d\t%30s\t%d\t%.2f\n",temp->codProdus,temp->numeProdus,temp->cantitateProdus,temp->pretTotal);
        temp=temp->urm;
    }
}

void eliberareMemorie(Tlista *lista)
{
    Tnod *temp;
    while(temp=lista->primul)
    {
        lista->primul=lista->primul->urm;
        free(temp);
    }
    lista->primul=NULL;
}

int main()
{
    Tlista cosCumparaturi;
    int n=nrProduseFavorite();
    struct Produs f[15];
    struct Produs b[15];
    struct Fav p[n];
    unsigned short optiune,ok=1;
    citireTabelProduseFemei(f);
    citireTabelProduseBarbati(b);
    citireProduseFavorite(p);
    printf("\t\t MENIU\n");
    printf("\t 1. Initializeaza cosul de cumparaturi\n");
    printf("\t 2. Afiseaza lista cu produse\n");
    printf("\t 3. Adauga produs in cos\n");
    printf("\t 4. Adauga produs la favorite\n");
    printf("\t 5. Afiseaza produsele favorite\n");
    printf("\t 6. Sterge produs din cos\n");
    printf("\t 7. Afiseaza sumarul comenzii\n");
    printf("\t 8. Goleste cosul de cumparaturi\n");
    printf("\t 9. Proceseaza comanda\n");
    printf("\t 10. Inchide aplicatia\n");
    printf("Introduceti cifra corespunzatoare actiunii dorite:\n");
    scanf("%hi",&optiune);
    do{
        while(optiune<1 || optiune>10)
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
                      {  printf("Ce lista doriti sa afisati? f-femei, b-barbati\n");
                         scanf("%c",ch);
                          if(tolower(ch)=='f')
                              afisareTabelProduseFemei(f);
                          else
                              afisareTabelProduseBarbati(b);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 3: if(ok)
                    {
                        int cod;
                        char denumire[30];
                        float pret;
                        printf("Produsul pe care doriti sa-l adaugati face parte din gama de produse pentru: f-femei/b-barbati\n");
                        scanf("%c",&ch);
                        printf("Introduceti codul produsului:\n");
                        scanf("%d",&cod);
                        printf("Introduceti denumirea produsului:\n");
                        fgets(denumire,15,stdin);
                        printf("Introduceti pretul produsului:\n");
                        scanf("%f",&pret);
                        adaugareProdusInLista(&cosCumparaturi,cod,&denumire,pret,f,b);
                        printf("Produsul cu codul %d a fost adaugat cu succes in cos!\n",cod);
                    }
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 4: if(ok)
                      {
                        int cod;
                        char denumire[30];
                        printf("Introduceti codul produsului pe care doriti sa-l adaugati la favorite:\n");
                        scanf("%d",&cod);
                        printf("Introduceti denumirea produsului pe care doriti sa-l adaugati la favorite:\n");
                        fgets(denumire,30,stdin);
                        adaugareProdusLaFavorite(cod,&denumire,p,f,b);
                        printf("Produsul cu codul %d a fost adaugat cu succes la favorite!\n",cod);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 5: if(ok)
                      {
                        afisareProduseFavorite(p);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 6: if(ok)
                      {
                        int cod;
                        printf("Introduceti codul produsului pe care doriti sa-l stergeti din cosul de cumparaturi:\n");
                        scanf("%",&cod);
                        stergeProdusDinLista(&cosCumparaturi,cod);
                        printf("Produsul cu codul %d a fost sters cu succes din cos!\n",cod);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 7: if(ok)
                      {
                        calculPret(&cosCumparaturi);
                        datePersonale();
                        plataSiLivrare();
                        sumarComanda();
                        printf("Produsele adaugate in cos sunt:\n");
                        afisareLista(cosCumparaturi);
                        printf("TOTAL PLATA: %.2f\n",totalPlata(cosCumparaturi));
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 8: if(ok)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Cosul de cumparaturi a fost golit! Reinitializati-l pentru o comanda noua\n");
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 9: if(ok)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Comanda a fost procesata! Reinitializati cosul de cumparaturi pentru a plasa o noua comanda\n");
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 10: exit(1);
                     printf("Rularea aplicatiei a fost oprita\n");
        }
    }while(optiune!=10);
}

