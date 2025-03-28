/*
Projekt: Plan lekcji
Przy stworzeniu planu, tworzy siê ogólny zarys planu lekcji. (Dni, liczba mo¿liwych lekcji i godziny)
Plan bedzie tez mial kazdy nauczyciel i sala.
Plany bedzie mozna modfikowac i usuwac
Plan mozna wyswietlic, co bedzie pokazywalo zajecia godziny itp.
Po zapytaniu o przedmiot poka¿e kiedy jest w jakiej sali.
*/

#include <iostream>
#include "klasy.h"

int main() {
	plan plan1;

	std::cout << "Twoj plan lekcji:" << std::endl;
	plan1.pokaz();
}