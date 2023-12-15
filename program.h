#ifndef PROGRAM_H
#define PROGRAM_H
#include "dane.h"

//faza badań
void badania(int ilosc=4);

//faza akcji
void kartaZreki(karta *c, gracz *p, mars *m);

//void projektStandardowy();

void lasZroslin(gracz *p, strefa *s);

void tempZciepla(gracz *p, strefa *s);

//projekty standardowe
void sprzedaz(gracz *p, karta *c);
void elektrownia(gracz *p);
void asteroida(gracz *p, mars *m);
void nawodnienie(gracz *p, strefa *s);
void addZielen(gracz *p, strefa *s, mars *m);
void addMiasto(gracz *p, strefa *s);

//faza produkcji
void prod(gracz *g){g->nastepnePokolenie();}

//inne
bool setObszar(teren t, strefa *s);

bool testKarty(karta *c,gracz *g,mars *m);
#endif // PROGRAM_H
