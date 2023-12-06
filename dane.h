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
        ocean,
        sym;
    extreme ext;
};

class karta
{
public:
    karta();
    karta(int n){ID=n;};
    int getID() { return ID; }
    typ getTyp() { return t; }
    zasoby getZasoby() { return zas; }
    produkcja getProdukcja() { return pro; }
    symbole getSymbole() { return sym; }
    int getKoszt() { return zas.zloto; }
private:
    int ID, WT = 0, PZ = 0, temp = 0, tlen = 0;
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

private:
    symbole sym;
    zasoby zas;
    produkcja prod;
};

class gracz
{
public:
    gracz();
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


private:
    char* nazwa[20];
    zasoby bonus;
    int ID;
    bool dostepnosc;
};

class mars
{
public:
    mars();
    karta* giveKarta();
    void nastepnePokolenie();
private:
    int aktualna,pokolenie,temperatura,tlen;
    karta* talia[250];
    //karta* smietnik[250];
    strefa obszary[64];
    gracz* player;
};



#endif // DANE_H
