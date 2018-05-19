#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
};

typedef struct Anod{                //nod arbore binar de cautare
  int codProdus;
  struct Anod *st;
  struct Anod *dr;
}Snod;

typedef struct Lnod{                 //nod lista simplu inlantuita
  int codProdus;
  unsigned int cantitateProdus;
  char numeProdus[30];
  float pretProdus, pretTotal;
  struct Lnod *urm;
}Tnod;

typedef struct lista{
  Tnod *primul, *ultimul;
}Tlista;

Snod *nodCrt;
char nume[15], prenume[15], adresa[30];
long numarTelefon;
int plata, livrare, tip;

FILE *fproduse, *bproduse;


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
  printf("COD PRODUS\tNUME PRODUS\t\t\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t\t%-30s\t%.2f\n",f[i].codProdus,f[i].numeProdus,f[i].pretProdus);
  }
}

void afisareTabelProduseBarbati(struct Produs b[])
{ int i;
  printf("COD PRODUS\tNUME PRODUS\t\t\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t\t%-30s\t%.2f\n",b[i].codProdus,b[i].numeProdus,b[i].pretProdus);
  }
}

void datePersonale()                    //citeste datele personale ale clientului
{
  printf("Introduceti numele dumneavoastra\n");
  scanf("%*c");
  fgets(nume,15,stdin);
  printf("Introduceti prenumele dumneavoastra\n");
  fgets(prenume,15,stdin);
  printf("Introduceti adresa de livrare\n");
  fgets(adresa,30,stdin);
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
  printf("\t\t\tSUMAR COMANDA\n");
  printf("DATE PERSONALE CLIENT:\nNUME:%s\nPRENUME:%s\nADRESA LIVRARE:%s\nNUMAR DE TELEFON:%ld\n",nume, prenume, adresa, numarTelefon);
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

//FUNCTII PENTRU ARBORE

void inserareInArbore(Snod *nod,int cod)                     //insereaza nodul cu codul dat in arbore
{
    if(nod)
        {   if(nod->codProdus==cod)
                printf("Codul exista deja in arbore!\n");
            else
                {
                    if(nod->codProdus<cod)
                        inserareInArbore(nod->dr,cod);
                    else
                        inserareInArbore(nod->st,cod);
                }
        }
    else
        {                                                       //primul nod inserat din arbore
            nod=(Snod*)malloc(sizeof(Snod));
            nod->codProdus=cod;
            nod->st=nod->dr=0;
        }
}

int cautare(Snod *nod, int cod)             //cauta nodul cu codul dat in arbore
{
    if(nod!=NULL)
    {
        if(nod->codProdus==cod)
            return 1;
        else
        {
            if(nod->codProdus<cod)
                cautare(nod->dr,cod);
            else
                cautare(nod->st,cod);
        }
    }
    return 0;
}

void construireArbore(Tlista lista)
{
    Tnod *temp=lista.primul;
    while(temp)
    {
        inserareInArbore(nodCrt,temp->codProdus);        //pe masura ce parcurge lista insereaza codurile produselor in arborele binar de cautare
        temp=temp->urm;
    }
}

//FUNCTII PENTRU LISTA

void initializareLista(Tlista *lista)
{
    lista->primul=lista->ultimul=NULL;
}

Tnod *cautaProdusInCos(Tlista *lista, char *denumire)
{
    Tnod *temp=lista->primul;
    while(temp!=NULL)
    {
         printf("ABC");
         if(strcmp(temp->numeProdus,denumire)==0)     //cauta produsul in cos in functie de numele introdus(daca exista, returneaza nodul aferent)
            return temp;
         temp=temp->urm;
    }
    return NULL;
}

int adaugareProdusInLista(Tlista *lista, int cod, char *nume, float pret)
{
    Tnod *nodNou;
    nodNou=(Tnod *)malloc(sizeof(Tnod));            //aloca memorie pentru produsul(nodul) curent
    if(nodNou==NULL)
    {
        printf("EROARE ALOCARE MEMORIE\n");
        exit(1);
    }
    if(lista->primul==NULL)                         //verifica daca exista produse in cos si daca nu exista, adauga produsul curent in primul nod
        {
            nodNou->codProdus=cod;
            strcpy(nodNou->numeProdus,nume);
            nodNou->pretProdus=pret;
            nodNou->pretTotal=pret;
            nodNou->cantitateProdus=1;
            lista->primul=nodNou;
            nodNou->urm=NULL;
        }
    else
        {
            //Tnod *temp=cautaProdusInCos(&lista,nume);
            if(!cautare(nodCrt,cod))                              //produsul curent nu exista in cos si va fi adaugat la final
                {
                    nodNou=lista->primul;
                    while(nodNou)
                        nodNou=nodNou->urm;
                    nodNou->codProdus=cod;
                    strcpy(nodNou->numeProdus,nume);
                    nodNou->pretProdus=pret;
                    nodNou->pretTotal=pret;
                    nodNou->cantitateProdus=1;
                    nodNou->urm=NULL;
                    return 1;
                }
            else                                        //produsul curent exista in cos si cantitatea acestuia se poate mari/micsora daca este de dorit
                {
                    printf("Produsul exista deja in cos! Doriti sa mariti cantitatea acestuia? 1-DA,2-NU\n");
                    int optiune;
                    scanf("%d",&optiune);
                    if(optiune==1)
                        {
                            int cantitate;
                            printf("Introduceti cantitatea dorita:\n");
                            scanf("%d",&cantitate);
                            if(cantitate>0 && cantitate>nodNou->cantitateProdus)    //verifica daca cantitatea dorita este o valoare pozitiva mai mica decat cantitatea actuala
                                {
                                    modificareCantitate(&lista,cod,cantitate);
                                    nodNou->pretTotal=cantitate*nodNou->pretProdus;
                                    printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                                }
                            else
                                {
                                    while(cantitate<0 || cantitate<nodNou->cantitateProdus)
                                        {
                                            printf("Cantitatea introdusa nu este valida! Introduceti alta valoare mai mare decat %d\n",nodNou->cantitateProdus);
                                            scanf("%d",&cantitate);
                                        }
                                    modificareCantitate(&lista,cod,cantitate);
                                    nodNou->pretTotal=cantitate*nodNou->pretProdus;
                                    printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                                }
                            return 1;
                        }
                    else
                        {
                            printf("Doriti sa micsorati cantitatea produsului? 1-DA,2-NU\n");
                            scanf("%d",&optiune);
                            if(optiune==1)
                                {
                                    int cantitate;
                                    printf("Introduceti cantitatea dorita:\n");
                                    scanf("%d",&cantitate);
                                    if(cantitate>=0 && cantitate<nodNou->cantitateProdus)   //verifica daca cantitatea dorita este pozitiva si mai mica decat cantitatea actuala
                                        {
                                            modificareCantitate(&lista,cod,cantitate);
                                            nodNou->pretTotal=cantitate*nodNou->pretProdus;
                                            printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                                        }
                                    else
                                        {
                                            while(cantitate<0 || cantitate>nodNou->cantitateProdus)
                                                {
                                                    printf("Cantitatea introdusa nu este valida! Introduceti alta valoare din intervalul [0,%d):",nodNou->cantitateProdus);
                                                    scanf("%d",&cantitate);
                                                }
                                            modificareCantitate(&lista,cod,cantitate);
                                            nodNou->pretTotal=cantitate*nodNou->pretProdus;
                                            printf("Aveti %d produse %s in cos\n",nodNou->cantitateProdus,nodNou->numeProdus);
                                        }
                                    return 1;
                                }
                            else
                            {
                                printf("Produsul cu codul %d nu a fost adaugat in cosul de cumparaturi!\n",cod);
                                return 0;
                            }
                        }
                }
        }
}

void modificareCantitate(Tlista *lista, int cod, int cantitate)
{
    Tnod *temp=lista->primul;
    while(temp->codProdus!=cod && temp)
            temp=temp->urm;
    temp->cantitateProdus=cantitate;
}


int stergereProdusDinLista(Tlista *lista, int cod)
{
    Tnod *c, *a;
    c=lista->primul;
    if(lista->primul->codProdus==cod)
    {
        a=lista->primul;
        lista->primul=lista->primul->urm;
        free(a);
        return 1;
    }
    else
    {
        while(c->urm->codProdus!=cod)
        {
            c=c->urm;
            a=c->urm;
            c->urm=a->urm;
            if(a==lista->ultimul)
                lista->ultimul=c;
            free(a);
            return 1;
        }
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
    printf("COD PRODUS\tNUME PRODUS\t\t\tCANTITATE PRODUS\t PRET TOTAL PRODUS\n");
    while(temp)
    {
        printf("%d\t\t%s\t\t\t%d\t%.2f\n",temp->codProdus,temp->numeProdus,temp->cantitateProdus,temp->pretTotal);
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
    struct Produs f[15];
    struct Produs b[15];
    int optiune,ok=0;
    citireTabelProduseFemei(f);
    citireTabelProduseBarbati(b);
    do{
        printf("\n\n");
        printf("\t\t MENIU\n");
        printf("\t 1. Initializeaza cosul de cumparaturi\n");
        printf("\t 2. Afiseaza lista cu produse disponibile\n");
        printf("\t 3. Adauga produs in cos\n");
        printf("\t 4. Sterge produs din cos\n");
        printf("\t 5. Afiseaza produsele adaugate in cos\n");
        printf("\t 6. Afiseaza sumarul comenzii\n");
        printf("\t 7. Goleste cosul de cumparaturi\n");
        printf("\t 8. Proceseaza comanda\n");
        printf("\t 9. Inchide aplicatia\n");
        printf("\n\n");
    	printf("Introduceti cifra corespunzatoare actiunii dorite:\n");
    	scanf("%d",&optiune);
        while(optiune<1 || optiune>9)
        {
            printf("EROARE: Valoarea introdusa trebuie sa fie din intervalul [1,9]!\n");
            printf("Introduceti alta cifra corespunzatoare actiunii dorite:\n");
            scanf("%d",&optiune);
        }
        switch(optiune)
        {
            case 1: initializareLista(&cosCumparaturi);
                    printf("Cosul de cumparaturi este gol\n");
                    ok=1;
                    break;
            case 2: if(ok)
                      {  printf("Ce lista doriti sa afisati? 1-femei, 2-barbati\n");
                         int tip;
                         scanf("%d",&tip);
                         if(tip==1)
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
                        printf("Introduceti codul produsului:\n");
                        scanf("%d",&cod);
                        printf("Introduceti denumirea produsului:\n");
                        scanf("%*c");
                        fgets(denumire,30,stdin);
                        printf("Introduceti pretul produsului:\n");
                        scanf("%f",&pret);
                        construireArbore(cosCumparaturi);
                        if(adaugareProdusInLista(&cosCumparaturi,cod,&denumire,pret))
                            printf("Produsul cu codul %d a fost adaugat cu succes in cos!\n",cod);
                    }
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 4: if(ok)
                      {
                        int cod;
                        printf("Introduceti codul produsului pe care doriti sa-l stergeti din cosul de cumparaturi:\n");
                        scanf("%d",&cod);
                        if(stergereProdusDinLista(&cosCumparaturi,cod))
                            printf("Produsul cu codul %d a fost sters cu succes din cosul de cumparaturi\n",cod);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 5: if(ok)
                        afisareLista(cosCumparaturi);
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 6: if(ok)
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
            case 7: if(ok)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Cosul de cumparaturi a fost golit! Reinitializati-l pentru o comanda noua\n");
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 8: if(ok)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Comanda a fost procesata! Reinitializati cosul de cumparaturi pentru a plasa o noua comanda\n");
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1\n");
                    break;
            case 9: exit(1);
                    printf("Rularea aplicatiei a fost oprita\n");
                    break;
        }
    }while(optiune>0 && optiune<10);
}

