#include "dane.h"

gracz::gracz(korporacja k)
{
    korpo = k;
    zasob = k.getZ();
    prod = k.getP();
    symbol = k.getS();
}

void gracz::resizeReka()
{
    int newsize = rekaSize + 4;
    karta* nowa = new karta[newsize];
    if (reka != nullptr)
    {
        for (int i = 0; i < rekaSize; i++)
        {
            nowa[i] = reka[i];
        }
    }
    delete[] reka;
    reka = nowa;
    rekaSize = newsize;
}

void gracz::resizeStol()
{
    int newsize = stolSize + 10;
    karta* nowa = new karta[newsize];
    if (stol != nullptr)
    {
        for (int i = 0; i < stolSize; i++)
        {
            nowa[i] = stol[i];
        }
    }
    delete[] stol;
    stol = nowa;
    stolSize = newsize;
}

void gracz::resizeStos()
{
    int newsize = stosSize + 10;
    karta* nowa = new karta[newsize];
    if (stos != nullptr)
    {
        for (int i = 0; i < stosSize; i++)
        {
            nowa[i] = stos[i];
        }
    }
    delete[] stos;
    stos = nowa;
    stosSize = newsize;
}

bool gracz::addZasoby(zasoby add)
{
    if (zasob.cieplo + add.cieplo >= 0)
        if (zasob.elektrycznosc + add.elektrycznosc >= 0)
            if (zasob.roslinnosc + add.roslinnosc >= 0)
                if (zasob.stal + add.stal >= 0)
                    if (zasob.tytan + add.tytan >= 0)
                        if (zasob.zloto + add.zloto >= 0)
                        {
                            zasob.cieplo += add.cieplo;
                            zasob.elektrycznosc += add.elektrycznosc;
                            zasob.roslinnosc += add.roslinnosc;
                            zasob.stal += add.stal;
                            zasob.tytan += add.tytan;
                            zasob.zloto += add.zloto;
                            return 1;
                        }
    return 0;
}

bool gracz::addPrdukcja(produkcja add)
{
    if (prod.zloto + add.zloto + WT > 0)
        if (prod.cieplo + add.cieplo >= 0)
            if (prod.elektrycznosc + add.elektrycznosc >= 0)
                if (prod.roslinnosc + add.roslinnosc >= 0)
                    if (prod.stal + add.stal >= 0)
                        if (prod.tytan + add.tytan >= 0)
                        {
                            prod.zloto += add.zloto;
                            prod.cieplo += add.cieplo;
                            prod.elektrycznosc += add.elektrycznosc;
                            prod.roslinnosc += add.roslinnosc;
                            prod.stal += add.stal;
                            prod.tytan += add.tytan;
                            return 1;
                        }
    return 0;
}

void gracz::addSymbole(symbole add)
{
    symbol.budowla += add.budowla;
    symbol.energia += add.energia;
    symbol.jowisz += add.jowisz;
    symbol.kosmos += add.kosmos;
    symbol.miasto += add.miasto;
    symbol.mikroby += add.mikroby;
    symbol.nauka += add.nauka;
    symbol.roslinnosc += add.roslinnosc;
    symbol.wydarzenie += add.wydarzenie;
    symbol.ziemia += add.ziemia;
    symbol.zwierzeta += add.zwierzeta;
}

void gracz::useKarta(karta card)
{
    if (addZasoby(card.getZasoby()) && addPrdukcja(card.getProdukcja()))//jeśli gracza stać, użyj karty
    {
        addSymbole(card.getSymbole());
        addPZ();
        if (card.getTyp() != typ::aktywna)//odkładanie kart na stos
        {
            T++;
            if (T >= stosSize)
                resizeStos();
            stos[T] = card;
        }
        else        //odkładanie kart na stół
        {
            S++;
            if (S >= stolSize)
                resizeStol();
            stol[S] = card;
        }
        dropCard(&card);
    }
}

void gracz::dropCard(karta *card)
{
    bool t = 0;
    for (int i = 0; i < R - 1; i++) //przesówanie kart w ręce
    {
        if (reka[i].getID() == card->getID())
            t = 1;
        if (t)
            reka[i] = reka[i + 1];
    }
}

void gracz::dobranie(karta card)
{
    if(zasob.zloto>=3)
    {
        zasob.zloto-=3;
        getKarta(&card);
    }
}

void gracz::nastepnePokolenie()
{
    zasob.cieplo+=zasob.elektrycznosc;
    zasob.cieplo+=prod.cieplo;
    zasob.elektrycznosc = prod.elektrycznosc;
    zasob.roslinnosc+=prod.roslinnosc;
    zasob.stal+=prod.stal;
    zasob.tytan+=prod.tytan;
    zasob.zloto+=prod.zloto;
    zasob.zloto+=WT;
}

void gracz::getKarta(karta* card)
{
    reka[R] = *card;
    R++;
    if(R>=rekaSize)
        resizeReka();
}

bool gracz::addZloto(int z)
{
    if(zasob.zloto+z>=0)
    {
        zasob.zloto+=z;
        return true;
    }
    return false;
}

korporacja::korporacja()
{

}

mars::mars()
{
    srand(time(0));
    int n;
    for (int i = 0; i < 250; i++)
    {
        n = rand() % 250 + 1;
        int j = 0;
        do
        {
            if (talia[j]->getID() == n)
            {
                n = rand() % 250 + 1;
                j = 0;
            }
            else
                j++;
        } while (j < i);
        talia[i] = new karta(n);
    }
    aktualna=-1;
}

strefa::strefa(int id,bool r,char* n)
{
    ID = id;
    *nazwa = n;
    rezerwacja = r;
}

karta* mars::giveKarta()
{
    this->aktualna++;
    return talia[aktualna];
}

void mars::nastepnePokolenie()
{
    pokolenie++;
    player->nastepnePokolenie();
    //badania, wymagana przeróbka na eventy
    player->getKarta(giveKarta());
    player->getKarta(giveKarta());
    player->getKarta(giveKarta());
    player->getKarta(giveKarta());
}


bool operator>=(const symbole s1, const symbole s2)
{
    if(s1.budowla>=s2.budowla)
        if(s1.energia>=s2.energia)
            if(s1.jowisz>=s2.jowisz)
                if(s1.kosmos>=s2.kosmos)
                    if(s1.miasto>=s2.miasto)
                        if(s1.mikroby>=s2.mikroby)
                            if(s1.nauka>=s2.nauka)
                                if(s1.roslinnosc>=s2.roslinnosc)
                                    if(s1.wydarzenie>=s2.wydarzenie)
                                        if(s1.ziemia>=s2.ziemia)
                                            if(s1.zwierzeta>=s2.zwierzeta)
                                                return 1;
    return 0;
}

bool operator<=(const symbole s1, const symbole s2)
{
    if(s1.budowla<=s2.budowla)
        if(s1.energia<=s2.energia)
            if(s1.jowisz<=s2.jowisz)
                if(s1.kosmos<=s2.kosmos)
                    if(s1.miasto<=s2.miasto)
                        if(s1.mikroby<=s2.mikroby)
                            if(s1.nauka<=s2.nauka)
                                if(s1.roslinnosc<=s2.roslinnosc)
                                    if(s1.wydarzenie<=s2.wydarzenie)
                                        if(s1.ziemia<=s2.ziemia)
                                            if(s1.zwierzeta<=s2.zwierzeta)
                                                return 1;
    return 0;
}

