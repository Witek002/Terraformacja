#include "program.h"

bool testKarty(karta *c,gracz *g,mars *m)
{
    if(c->getWym().ext)
        if(c->getWym().sym>=g->getSymbole())
            if(c->getWym().temp>=m->getTemp())
                if(c->getWym().tlen>=m->getTlen())
                    if(c->getWym().ocean>=m->getOceany())
                        return 1;
    else
        if(c->getWym().sym>=g->getSymbole())
            if(c->getWym().temp>=m->getTemp())
                if(c->getWym().tlen>=m->getTlen())
                    if(c->getWym().ocean>=m->getOceany())
                        return 1;

    return 0;
}

bool setObszar(teren t, strefa *s)
{
    if(s->getDost()&&!s->getRez())
    {
        s->setDost();
        s->setTeren(t);
        return 1;
    }
    return 0;
}


void kartaZreki(karta* c,gracz *g, mars *m)
{
    if(testKarty(c,g,m))
        g->useKarta(*c);
}

void lasZroslin(gracz *g, strefa *s,mars *m)
{
    zasoby z;
    z.roslinnosc= -8;
    if(g->addZasoby(z)&&setObszar(teren::las,s))
    {
        g->addZasoby(s->getBonus());
        m->addTlen();
        g->addWT();
    }
}

void tempZciepla(gracz *g, mars *m)
{
    zasoby z;
    z.cieplo= -8;
    if(g->addZasoby(z))
    {
        g->addWT();
        m->addTemp();
    }
}

void sprzedaz(gracz *g, karta *c)
{
    g->dropCard(c);
    g->addZloto(1);
}
void elektrownia(gracz *g)
{
    if(g->addZloto(-11))
    {
        produkcja p;
        p.elektrycznosc=1;
        g->addPrdukcja(p);
    }
}
void asteroida(gracz *g, mars *m)
{
    if(g->addZloto(-14))
    {
        g->addWT();
        m->addTemp();
    }
}
void nawodnienie(gracz *g, strefa *s)
{
    if(s->getDost()&&s->getRez()&&g->addZloto(-18))
    {
        g->addZasoby(s->getBonus());
        g->addWT();
        s->setDost();
    }
}
void addZielen(gracz *g, strefa *s,mars *m)
{
    if(s->getDost()&&!s->getRez()&&g->addZloto(-23))
    {
        g->addZasoby(s->getBonus());
        s->setDost();
        m->addTlen();
        g->addWT();
    }
}
void addMiasto(gracz *g, strefa *s)
{
    if(s->getDost()&&!s->getRez()&&g->addZloto(-25))
    {
        g->addZasoby(s->getBonus());
        produkcja p;
        p.zloto=1;
        g->addPrdukcja(p);
        s->setDost();
    }
}


