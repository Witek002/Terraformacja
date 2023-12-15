#ifndef DANE_H
#define DANE_H
#include <QRandomGenerator>
#include <QtSql/QSqlDatabase>

enum extreme
{
    min = 0,
    max = 1
};
enum teren
{
    nic = 0,
    las = 1,
    miasto = 2,
    ocean = 3,
    inny = 4
};
enum typ
{
    aktywna = 1,
    natychmiastowa = 2,
    wydarzenie = 3
};
struct zasoby
{
    int zloto,
        stal,
        tytan,
        roslinnosc,
        elektrycznosc,
        cieplo;
};
struct produkcja
{
    int zloto,
        stal,
        tytan,
        roslinnosc,
        elektrycznosc,
        cieplo;
};
struct symbole
{
    int budowla,
        kosmos,
        energia,
        nauka,
        jowisz,
        ziemia,
        roslinnosc,
        mikroby,
        zwierzeta,
        miasto,
        wydarzenie;
};
struct wymagania
{
    int tlen,
        temp,
        ocean;
    symbole sym;
    extreme ext;
};

class karta
{
public:
    karta(){ID=0;};
    karta(int n){ID=n;};
    int getID() { return ID; }
    typ getTyp() { return t; }
    zasoby getZasoby() { return zas; }
    produkcja getProdukcja() { return pro; }
    symbole getSymbole() { return sym; }
    int getKoszt() { return zas.zloto; }
    wymagania getWym() {return wym;}
    int getPZ(){return PZ;}
    int getWT(){return WT;}
    int getTemp(){return temp;}
    int getTlen(){return tlen;}
    teren getObszar(){return obszar;}
private:
    int ID,     //id karty w BD
        WT = 0,
        PZ = 0,
        temp = 0,
        tlen = 0;
    zasoby zas;
    produkcja pro;
    symbole sym;
    wymagania wym;
    teren obszar;
    typ t;
};

class korporacja
{
public:
    korporacja();
    zasoby getZ(){return zas;}
    symbole getS(){return sym;}
    produkcja getP(){return prod;}
private:
    symbole sym;
    zasoby zas;
    produkcja prod;
};

class gracz
{
public:
    gracz();
    gracz(korporacja k);
    void resizeReka();
    void resizeStol();
    void resizeStos();
    zasoby getZasoby() { return zasob; }
    produkcja getProdukcja() { return prod; }
    symbole getSymbole() { return symbol; }
    bool addZasoby(zasoby add);
    bool addPrdukcja(produkcja add);
    void addSymbole(symbole add);
    void dobranie(karta card);
    void useKarta(karta card);
    void getKarta(karta* card);
    void nastepnePokolenie();
    void dropCard(karta *card);
    bool addZloto(int z);
    void addWT(int i=1){WT+=i;}
    void addPZ(int i=1){PZ+=i;}
private:
    int WT, PZ;
    korporacja korpo;
    zasoby zasob;
    produkcja prod;
    symbole symbol;
    int rekaSize, R = 0;
    karta* reka = new karta[16];
    int stolSize, S = 0;
    karta* stol = new karta[20];
    int stosSize, T = 0;
    karta* stos = new karta[20];
};

class strefa
{
public:
    strefa(int id=0,bool r=0,char* n=nullptr);
    bool getRez(){return rezerwacja;}
    bool getDost(){return dostepnosc;}
    zasoby getBonus(){return bonus;}
    int getId(){return ID;}
    void setDost(bool b=0){dostepnosc=b;}
    void setTeren(teren n){t=n;}
    teren getTeren(){return t;}
private:
    char* nazwa[20]; //nazwa obszaru, jeśli jest
    zasoby bonus;   //bonus obszaru, jeśli jest
    int ID; //położenie obszaru
    bool dostepnosc=1;  //czy jest zajęty
    bool rezerwacja;    //czy jest zarezerwowany, np.: dla oceanu
    teren t;    //teren jaki się na nim znajduje
};

class mars
{
public:
    mars();
    karta* giveKarta();
    void nastepnePokolenie();
    void addTemp(int i=1){temperatura += i*2;}
    int getTemp(){return temperatura;}
    void addTlen(int i=1){tlen += i;}
    int getTlen(){return tlen;}
    void addOceany(int i=1){oceany += i;}
    int getOceany(){return oceany;}
private:
    int aktualna,   //wieszchnia karta w talii
        pokolenie,  //aktualne pokolenie
        temperatura,
        tlen,
        oceany;
    karta* talia[250];  //karty do dobrania
    //karta* smietnik[250];
    strefa* obszary[64];    //mapa
    gracz* player;  //gracz
};

bool operator>=(const symbole s1, const symbole s2);

bool operator<=(const symbole s1, const symbole s2);
#endif // DANE_H
