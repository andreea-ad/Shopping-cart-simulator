#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs{
  int codProdus;
  char numeProdus[30];
  float pretProdus;
};

/*typedef struct Anod{                //nod arbore binar de cautare
  int codProdus;
  struct Anod *st;
  struct Anod *dr;
}Snod;*/

typedef struct nod{                 //nod lista simplu inlantuita
  int codProdus;
  unsigned int cantitateProdus;
  char numeProdus[30];
  float pretProdus, pretTotal;
  struct nod *urm;
}Tnod;

typedef struct lista{
  Tnod *primul, *ultimul;
}Tlista;

//Snod *nodCrt;
char nume[15], prenume[15], adresa[30];
long numarTelefon;
int plata, livrare, tip;

FILE *fproduse, *bproduse;


//FUNCTII PENTRU CITIRE/AFISARE PRODUSE STOC, VALIDARE ETC

void citireTabelProduseFemei(struct Produs f[])                         //citeste produsele pentru femei din fisier
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

void citireTabelProduseBarbati(struct Produs b[])                         //citeste produsele pentru barbati din fisier
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


void afisareTabelProduseFemei(struct Produs f[])                            //afiseaza un tabel cu produsele citite pentru femei
{ int i;
  printf("COD PRODUS\tNUME PRODUS\t\t\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t\t%-30s\t%.2f\n",f[i].codProdus,f[i].numeProdus,f[i].pretProdus);
  }
}

void afisareTabelProduseBarbati(struct Produs b[])                         //afiseaza un tabel cu produsele citite pentru barbati
{ int i;
  printf("COD PRODUS\tNUME PRODUS\t\t\tPRET PRODUS\n");
  for(i=0;i<15;i++)
  {
    printf("%d\t\t%-30s\t%.2f\n",b[i].codProdus,b[i].numeProdus,b[i].pretProdus);
  }
}

void datePersonale()                    //citeste datele personale ale clientului
{
  printf("Introduceti numele dumneavoastra:\n");
  scanf("%*c");
  fgets(nume,15,stdin);
  printf("Introduceti prenumele dumneavoastra:\n");
  fgets(prenume,15,stdin);
  printf("Introduceti adresa de livrare:\n");
  fgets(adresa,30,stdin);
  printf("Introduceti numarul dumneavoastra de telefon:\n");
  scanf("%ld",&numarTelefon);
}

void plataSiLivrare()                   //citeste metodele de plata/livrare dorite de client
{
  printf("Introduceti cifra corespunzatoare metodei de plata dorite:\n 1-NUMERAR/RAMBUS\n 2-ONLINE CU CARD BANCAR\n");
  scanf("%d",&plata);
  while(plata!=1 && plata!=2)
    { printf("Metoda de plata inexistenta! Introduceti o alta metoda de plata.\n");
      scanf("%d",&plata);
    }
  printf("Introduceti cifra corespunzatoare metodei de livrare dorite:\n 1-CURIER(15.99 lei)\n 2-POSTA(9.99 lei)\n");
  scanf("%d",&livrare);
  while(livrare!=1 && livrare!=2)
    { printf("Metoda de livrare inexistenta! Introduceti o alta metoda de livrare.\n");
      scanf("%d",&livrare);
    }
}

void sumarComanda()                   //afiseaza datele de contact ale clientului si optiunile de plata/livrare
{
  printf("\t\t\t\t\t\tSUMAR COMANDA\n");
  printf("DATE PERSONALE CLIENT:\nNUME: %s\nPRENUME: %s\nADRESA LIVRARE: %s\nNUMAR DE TELEFON: 0%ld\n",nume, prenume, adresa, numarTelefon);
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
/*
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
*/


//FUNCTII PENTRU LISTA

void initializareLista(Tlista *lista)               //initializeaza primul si ultimul nod al listei cu NULL
{
    lista->primul=lista->ultimul=NULL;
}
void esteNull(Tnod *x)                              //verifica daca un nod este nul
{
    if (x == NULL)
    {
        printf("\nEROARE ALOCARE MEMORIE!\n");
        system("pause");
        exit(0);
    }
}

Tnod *cautaProdusInLista(Tlista *lista, char *nume)            //cauta produsul cu numele dat in lista
{
    Tnod *temp = lista->primul;
    while (temp)
    {
        if (strcmp(nume, temp->numeProdus) == 0)
            return temp;
        temp = temp->urm;
    }
    return NULL;
}

int adaugaProdusInLista(Tlista *lista, int cod, char *denumire, float pret)     //adauga produsul cu codul, denumirea si pretul date in lista
{
    Tnod *adr = cautaProdusInLista(lista, denumire);
    if (adr == NULL)
    {
        Tnod *NewNod;
        NewNod = (Tnod *)malloc(sizeof(Tnod));
        esteNull(NewNod);
        NewNod->codProdus=cod;
        NewNod->cantitateProdus=1;
        strcpy(NewNod->numeProdus,denumire);
        NewNod->pretProdus=pret;
        NewNod->pretTotal=pret;
        NewNod->urm = NULL;
        if (lista->primul == NULL)                                 //lista este goala
        {   lista->primul = lista->ultimul = NewNod;
            return 1;
        }
        else if(lista->primul->codProdus > cod)                   //adaugare in fata
        {
            NewNod->urm = lista->primul;
            lista->primul = NewNod;
            return 1;
        }
        else if (lista->ultimul->codProdus < cod)                //adaugare la sfarsit
        {
            lista->ultimul->urm = NewNod;
            lista->ultimul = NewNod;
            return 1;
        }
        else                                                    //adaugare la mijloc
        {
            Tnod *temp = lista->primul, *prev;
            while (temp != NULL && temp->codProdus > cod)
            {
                prev = temp;
                temp = temp->urm;
            }
            NewNod->urm = temp;
            prev->urm = NewNod;
            return 1;
        }
    }
    else                                                                             //produsul/nodul exista in lista si se modifica cantitatea daca este dorit
        {
            printf("Produsul exista deja in cos! Doriti sa modificati cantitatea acestuia? 1-DA, 2-NU.\n");
            int optiune;
            scanf(" %d",&optiune);
            while(optiune!=1&&optiune!=2)
            {
                printf("Optiunea introdusa este invalida!\n Introduceti optiunea 1 pentru DA si optiunea 2 pentru NU.\n");
                scanf(" %d",&optiune);
            }
                if(optiune==1)
                {   int cantitate;
                    printf("Introduceti cantitatea dorita:\n");
                    scanf(" %d",&cantitate);
                    while(cantitate<=0 || cantitate>100)
                    {
                        printf("Cantitatea introdusa trebuie sa fie din intervalul (0,100]\n Introduceti alta cantitate:");
                        scanf(" %d",&cantitate);
                    }
                    adr->cantitateProdus=cantitate;
                    adr->pretTotal=adr->cantitateProdus*adr->pretProdus;
                    return 1;
                }
                else if(optiune==2)
                    return 0;
        }
    return 0;
}

int stergereProdusDinLista(Tlista *lista, int cod)                                      //cauta un nod dupa cod si sterge daca il gaseste in lista
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
    return 0;
}

float totalPlata(Tlista lista)                                      //aduna toate variabilele pretTotal din lista si calculeaza suma de plata
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

void afisareLista(Tlista lista)                                                 //afiseaza toate nodurile din lista
{
    Tnod *temp=lista.primul;
    printf("COD PRODUS\tCANTITATE PRODUS\tPRET TOTAL PRODUS\tNUME PRODUS\n");
    while(temp)
    {
        printf("%d\t\t%d\t\t\t%0.2f\t\t\t%10s\n",temp->codProdus,temp->cantitateProdus,temp->pretTotal, temp->numeProdus);
        temp=temp->urm;
    }
}

void eliberareMemorie(Tlista *lista)                                            //sterge fiecare nod din lista
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
    int optiune,ok=0,ok1=0,ok2=0;
    citireTabelProduseFemei(f);
    citireTabelProduseBarbati(b);
    do{
        printf("\n\n");
        printf("====================================================================================================================\n");
        printf("\t\t\t\t\t\t MENIU\n");
        printf("\t\t\t 1. Initializeaza cosul de cumparaturi\n");
        printf("\t\t\t 2. Afiseaza lista cu produse disponibile\n");
        printf("\t\t\t 3. Adauga produs in cos\n");
        printf("\t\t\t 4. Sterge produs din cos\n");
        printf("\t\t\t 5. Afiseaza produsele adaugate in cos\n");
        printf("\t\t\t 6. Introdu datele de contact si preferintele pentru livrare/plata\n");
        printf("\t\t\t 7. Afiseaza sumarul comenzii\n");
        printf("\t\t\t 8. Goleste cosul de cumparaturi\n");
        printf("\t\t\t 9. Proceseaza comanda\n");
        printf("\t\t\t 10. Inchide aplicatia\n");
        printf("====================================================================================================================\n");
        printf("\n\n");
    	printf("Introduceti cifra corespunzatoare actiunii dorite:\n");
    	scanf("%d",&optiune);
        while(optiune<1 || optiune>10)
        {
            printf("EROARE: Valoarea introdusa trebuie sa fie din intervalul [1,9]!\n Introduceti alta cifra corespunzatoare actiunii dorite:\n");
            scanf(" %d",&optiune);
        }
        switch(optiune)
        {
            case 1: initializareLista(&cosCumparaturi);
                    printf("Cosul de cumparaturi este gol.\n");
                    ok=1;
                    break;
            case 2: if(ok)
                      {  printf("Ce lista doriti sa afisati? 1-femei, 2-barbati.\n");
                         int tip;
                         scanf("%d",&tip);
                         while(tip!=1&&tip!=2)
                         {
                             printf("Optiunea introdusa este invalida! Introduceti 1 pentru a afisa lista cu produse pentru femei si 2 pentru a afisa lista cu produse pentru barbati.\n");
                             scanf(" %d",&tip);
                         }
                         if(tip==1)
                              afisareTabelProduseFemei(f);
                         else
                              afisareTabelProduseBarbati(b);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
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
                        //construireArbore(cosCumparaturi);
                        if(adaugaProdusInLista(&cosCumparaturi,cod,denumire,pret))
                            {   printf("Produsul cu codul %d a fost adaugat cu succes in cos!\n",cod);
                                ok2=1;
                            }
                    }
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    break;
            case 4: if(ok)
                      {
                        int cod;
                        printf("Introduceti codul produsului pe care doriti sa-l stergeti din cosul de cumparaturi:\n");
                        scanf(" %d",&cod);
                        if(stergereProdusDinLista(&cosCumparaturi,cod))
                            printf("Produsul cu codul %d a fost sters cu succes din cosul de cumparaturi!\n",cod);
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    break;
            case 5: if(ok)
                        afisareLista(cosCumparaturi);
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    break;
            case 6: if(ok)
                        {
                            datePersonale();
                            plataSiLivrare();
                            ok1=1;
                        }
                    else
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    break;
            case 7: if(ok&&ok1)
                      {
                        sumarComanda();
                        printf("Produsele adaugate in cos sunt:\n");
                        afisareLista(cosCumparaturi);
                        printf("TOTAL PLATA: %.2f\n",totalPlata(cosCumparaturi));
                      }
                    else if(ok==0)
                        printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    else if(ok1==0)
                        printf("Datele de contact nu au fost introduse! Alegeti optiunea 6.\n");
                    break;
            case 8: if(ok)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Cosul de cumparaturi a fost golit! Reinitializati-l pentru o comanda noua.\n");
                      }
                    else
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    break;
            case 9: if(ok&&ok1&&ok2)
                      {
                          eliberareMemorie(&cosCumparaturi);
                          printf("Comanda a fost procesata! Reinitializati cosul de cumparaturi pentru a plasa o noua comanda.\n");
                      }
                    else if(ok==0)
                      printf("Cosul de cumparaturi nu a fost initializat! Alegeti optiunea 1.\n");
                    else if(ok1==0)
                      printf("Datele de contact nu au fost introduse! Alegeti optiunea 6.\n");
                    else if(ok2==0)
                      printf("Nu exista produse adaugate in cos! Alegeti optiunea 3 pentru a adauga produse in cos.\n");
                    break;
            case 10: exit(1);
                     printf("Rularea aplicatiei a fost oprita.\n");
                     break;
        }
    }while(optiune>=1 && optiune<=10);
}

