/*
Projekt: Plan lekcji
Przy stworzeniu planu, tworzy sie ogolny zarys planu lekcji. (Dni, liczba mozliwych lekcji i godziny)
Plan bedzie tez mial kazdy nauczyciel i sala.
Plany bedzie mozna modfikowac i usuwac
Plan mozna wyswietlic, co bedzie pokazywalo zajecia, godziny, itp.
Po zapytaniu o przedmiot pokaze kiedy jest w jakiej sali.
Po zapytanu o sale wyswietli jakie zajecia i kiedy sa w tej sali
*/

#include <iostream>
#include "klasy.h"

struct Dane {
	nauczyciel* n[18];
	lekcja* l[18];
	uczen* u[25];
};

Dane inicjalizujDane() {
	Dane d;

	sala* s1 = new sala("ogolna", '3');

	//Nauczyciele (imie, nazwisko, przedmiot)
	d.n[0] = new nauczyciel("Justyna", "Juszczyk-Synowiec", "fizyka");
	d.n[1] = new nauczyciel("Jerzy", "Bodzenta", "fizyka");
	d.n[2] = new nauczyciel("Jacek", "Checinski", "elektronika i miernictwo");
	d.n[3] = new nauczyciel("Krzysztof", "Bernacki", "elektronika i miernictwo");
	d.n[4] = new nauczyciel("Ewa", "Lobos", "analiza matematyczna i algebra liniowa");
	d.n[5] = new nauczyciel("Bartlomiej", "Pawlik", "analiza matematyczna i algebra liniowa");
	d.n[6] = new nauczyciel("Jan", "Machniewski", "podstawy elektrotechniki");
	d.n[7] = new nauczyciel("Andrzej", "Pulka", "podstawy elektrotechniki");
	d.n[8] = new nauczyciel("Agnieszka", "Danek", "algorytmy i struktury danych");
	d.n[9] = new nauczyciel("Zbigniew", "Czech", "algorytmy i struktury danych");
	d.n[10] = new nauczyciel("Robert", "Tutajewicz", "podstawy informatyki");
	d.n[11] = new nauczyciel("Roman", "Starosolski", "programowanie komputerow");
	d.n[12] = new nauczyciel("Grzegorz", "Kwiatkowski", "programowanie komputerow");
	d.n[13] = new nauczyciel("Tomasz", "Rudnicki", "teoria ukladow cyfrowych");
	d.n[14] = new nauczyciel("Adam", "Opara", "teoria ukladow cyfrowych");
	d.n[15] = new nauczyciel("Piotr", "Zemla", "wychowanie fizyczne");
	d.n[16] = new nauczyciel("Beata", "Badowska-Ekiert", "jezyk angielski");

	//Lekcje  (nazwa, typ, parzystosc, sala, nauczyciel)
	d.l[0] = new lekcja("Fizyka", "CW", 0, s1, d.n[0]);
	d.l[1] = new lekcja("Fizyka", "WYK", 0, s1, d.n[1]);
	d.l[2] = new lekcja("Elektronika i miernictwo", "CW", 0, s1, d.n[2]);
	d.l[3] = new lekcja("Elektronika i miernictwo", "WYK", 0, s1, d.n[3]);
	d.l[4] = new lekcja("Analiza matematyczna i algebra liniowa", "CW", 0, s1, d.n[4]);
	d.l[5] = new lekcja("Analiza matematyczna i algebra liniowa", "WYK", 0, s1, d.n[5]);
	d.l[6] = new lekcja("Podstawy elektrotechniki", "CW", 1, s1, d.n[6]);
	d.l[7] = new lekcja("Podstawy elektrotechniki", "WYK", 1, s1, d.n[7]);
	d.l[8] = new lekcja("Algorytmy i struktury danych", "CW", 1, s1, d.n[8]);
	d.l[9] = new lekcja("Algorytmy i struktury danych", "WYK", 1, s1, d.n[9]);
	d.l[10] = new lekcja("Podstawy informatyki", "CW", 1, s1, d.n[10]);
	d.l[11] = new lekcja("Podstawy informatyki", "WYK", 2, s1, d.n[11]);
	d.l[12] = new lekcja("Programowanie komputerow", "CW", 0, s1, d.n[11]);
	d.l[13] = new lekcja("Programowanie komputerow", "LAB", 2, s1, d.n[12]);
	d.l[14] = new lekcja("Teoria ukladow cyfrowych", "CW", 2, s1, d.n[13]);
	d.l[15] = new lekcja("Teoria ukladow cyfrowych", "WYK", 0, s1, d.n[14]);
	d.l[16] = new lekcja("Wychowanie fizyczne", "CW", 0, s1, d.n[15]);
	d.l[17] = new lekcja("Jezyk angielski (C1)", "LEKT", 0, s1, d.n[16]);

	//Lekcje  (imie, nazwisko, gr dziekanska)
	d.u[0] = new uczen("Andrzej", "Piaseczny", 3);
	d.u[1] = new uczen("Katarzyna", "Nowicka", 1);
	d.u[2] = new uczen("Michal", "Kowalewski", 4);
	d.u[3] = new uczen("Patrycja", "Jablonska", 2);
	d.u[4] = new uczen("Tomasz", "Stepien", 5);
	d.u[5] = new uczen("Julia", "Wojcik", 6);
	d.u[6] = new uczen("Sebastian", "Krawczyk", 3);
	d.u[7] = new uczen("Aleksandra", "Piekarska", 2);
	d.u[8] = new uczen("lukasz", "Baran", 4);
	d.u[9] = new uczen ("Natalia", "Lis", 1);
	d.u[10] = new uczen("Damian", "Mazur", 5);
	d.u[11] = new uczen("Dominika", "Szymanska", 6);
	d.u[12] = new uczen("Kacper", "Zawadzki", 2);
	d.u[13] = new uczen("Maja", "Sikora", 3);
	d.u[14] = new uczen("Piotr", "Blaszczyk", 4);
	d.u[15] = new uczen("Amelia", "Rutkowska", 1);
	d.u[16] = new uczen("Jan", "Kubiak", 6);
	d.u[17] = new uczen("Zuzanna", "Czarnecka", 2);
	d.u[18] = new uczen("Oliwia", "Kowalczyk", 3);
	d.u[19] = new uczen("Adam", "Krol", 5);
	d.u[20] = new uczen("Magdalena", "Pawlak", 4);
	d.u[21] = new uczen("Bartlomiej", "Jasinski", 2);
	d.u[22] = new uczen("Karolina", "Witkowska", 6);
	d.u[23] = new uczen("Marcin", "Lesniak", 1);
	d.u[24] = new uczen("Joanna", "Sawicka", 3);


	return d;
}

void usunDane(Dane& d) {
	for (int i = 0; i < 18; i++) {
		delete d.l[i];
	}
	for (int i = 0; i < 17; i++) {
		delete d.n[i];
	}
	for (int i = 0; i < 25; i++) {
		delete d.u[i];
	}
}

int main() {
	int odp;
	plan p1, p2, p3, p4, p5, p6;
	Dane d = inicjalizujDane();

	std::cout << "===Plan lekcji===" << std::endl;
	std::cout << "1. Pokaz plan lekcji" << std::endl;
	std::cout << "2. Pokaz dane ucznia" << std::endl;
	std::cout << "3. Pokaz dane nauczyciela" << std::endl;
	std::cout << "4. Pokaz dane lekcji" << std::endl;
	std::cout << "5. Pokaz dane sali" << std::endl;
	std::cout << "6. Wyjdz" << std::endl;
	std::cout << "Wybierz opcje: ";
	std::cin >> odp;
	std::cout << std::endl;

	if (odp == 1) {
		p1.pokaz_plan();
	} else if(odp == 2) {
		d.u[5]->pokaz_dane();
	}
	else if (odp == 3) {
		d.n[1]->pokaz_dane();
	}
	else if (odp == 4) {
		d.l[10]->pokaz_dane();
	}
	else if (odp == 5) {
		/*s1->pokaz_dane(); //nie dzia³a*/ 
	}
	else if (odp == 6) {
		return 0;
	}
	else {
		std::cout << "Bledna odpowiedz. Wybierz pomiedzy 1, a 6" << std::endl;
	}

	usunDane(d);
}