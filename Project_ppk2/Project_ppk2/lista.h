/** @file */

#ifndef LISTA_H
#define LISTA_H

#include "klasy.h"

/** Inicjalizuje dane do list
 * @param nauczyciele Do tej listy sa wczytywani nauczyciele
 * @param uczniowie Do tej listy sa wczytywani uczniowie
 * @param lekcje Do tej listy sa wczytywane lekcje
 * @param sale Do tej listy sa wczytywane sale
 * @author Dyba
 *	*/
void inicjalizuj(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale);

/** Usuwa listy
 * @param nauczyciele Usuwa liste nauczyciele
 * @param uczniowie Usuwa liste uczniowie
 * @param lekcje Usuwa liste lekcje
 * @param sale Usuwa liste sale
 * @author Dyba
 *	*/
void usun_listy(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale);
#endif
