// lista.h
#ifndef LISTA_H
#define LISTA_H

#include "klasy.h"

void inicjalizuj(lista<nauczyciel*>&, lista<uczen*>&, lista<lekcja*>&, lista<sala*>&);

void usun_listy(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale);
#endif
