/*
Projekt: Plan lekcji
Przy stworzeniu planu, tworzy sie ogolny zarys planu lekcji. (Dni, liczba mozliwych lekcji i godziny) GIT
Plan bedzie tez mial kazdy nauczyciel i sala.
Plan mozna wyswietlic, co bedzie pokazywalo zajecia, godziny, itp.
Po zapytaniu o przedmiot pokaze kiedy jest w jakiej sali. GIT
Po zapytanu o sale wyswietli jakie zajecia i kiedy sa w tej sali
Mo¿e dawanie danych do listy z pliku? GIT
*/

#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>

#include "klasy.h"
#include "lista.h"

void alt(std::string& p) {
	std::transform(p.begin(), p.end(), p.begin(), ::tolower);

	if (p == "fizyka") {
		p = "Fizyka";
	}
	else if(p == "eim" || p == "elektronika i miernictwo") {
		p = "Elektronika i miernictwo";
	}
	else if (p == "amial" || p == "analiza matematyczna i algebra liniowa") {
		p = "Analiza matematyczna i algebra liniowa";
	}
	else if (p == "pe" || p == "podstawy elektrotechniki") {
		p = "Podstawy elektrotechniki";
	}
	else if (p == "aisd" || p == "algorytmy i struktury danych") {
		p = "Algorytmy i struktury danych";
	}
	else if (p == "pi" || p == "podstawy informatyki") {
		p = "Podstawy informatyki";
	}
	else if (p == "pk" || p == "programowanie komputerow") {
		p = "Programowanie komputerow";
	}
	else if (p == "tuc" || p == "teoria ukladow cyfrowych") {
		p = "Teoria ukladow cyfrowych";
	}
	else if (p == "wf" || p == "wychowanie fizyczne") {
		p = "Wychowanie fizyczne";
	}
	else if (p == "angielski" || p == "jezyk angielski" || p == "angol") {
		p = "Jezyk angielski";
	}
	else {
		std::cerr << "Zla nazwa przedmiotu!" << std::endl;
		std::exit(1);
	}
}

void f_plan(plan& p1, plan& p2, plan& p3, plan& p4, plan& p5, plan& p6, lista<lekcja*>& lekcje) {
	int odp, godzina, minuta, /*rozmiar,*/ godzina_trwa, minuta_trwa;
	std::string dzien, przedmiot;
	plan* plans[6] = { &p1, &p2, &p3, &p4, &p5, &p6 };

	std::cout << "===Plan lekcji===" << std::endl;
	std::cout << "1. Pokaz plan lekcji" << std::endl;
	std::cout << "2. Dodaj lekcje do planu" << std::endl;
	std::cout << "3. Usun lekcje z planu" << std::endl;
	std::cout << "4. Wroc" << std::endl;
	std::cout << "Wybierz opcje: ";
	std::cin >> odp;
	std::cout << std::endl;

	if (odp == 1) {
		std::cout << "Podaj numer grupy: ";
		std::cin >> odp;
		std::cout << std::endl;

		if (odp >= 1 && odp <= 6) {
			plans[odp - 1]->pokaz_plan();
		}
		else {
			std::cout << "Bledny numer grupy" << std::endl;
		}
	}
	else if (odp == 2) {
		std::cout << "Podaj numer grupy: ";
		std::cin >> odp;
		std::cout << std::endl;

		std::cout << "Podaj godzine (Od 8:00 do 17:30)(np. 8 15 dla 08:15): ";
		std::cin >> godzina>>minuta;

		std::cout << "Podaj dzien (np. poniedzialek): ";
		std::cin >> dzien;
		
		std::cout << "Podaj nazwe przedmiotu: ";
		std::cin >> przedmiot;
		alt(przedmiot);

		std::cout << "Podaj czas trwania (np. 1 30 dla 1h 30min): ";
		std::cin >> godzina_trwa >> minuta_trwa;
		std::cout<< std::endl;

		if (odp >= 1 && odp <= 6) {
			plans[odp - 1]->dodaj_do_planu(godzina, minuta, dzien, przedmiot, godzina_trwa, minuta_trwa);
		}
		else {
			std::cout << "Bledny numer grupy" << std::endl;
		}
		plans[odp - 1]->pokaz_plan();
	}
	else if (odp == 3) {

	}
	else if (odp == 4) {
		//tu ma byc nic
	}
	else {
		std::cout << "Bledny numer" << std::endl;
	}
}

void f_uczen(lista<uczen*>& uczniowie) {
	int odp;
	std::cout << "===Uczen===" << std::endl;
	std::cout << "1. Pokaz dane ucznia" << std::endl;
	std::cout << "2. Pokaz dane wszystkich uczniow" << std::endl;
	std::cout << "3. Pokaz plan lekcji ucznia" << std::endl;
	std::cout << "4. Wroc" << std::endl;
	std::cout << "Wybierz opcje: ";
	std::cin >> odp;
	std::cout << std::endl;

	if (odp == 1) {
		int licz = 0;
		std::string imie, nazwisko, im, na;

		std::cout << "Podaj imie: ";
		std::cin >> imie;
		std::cout << std::endl;

		std::cout << "Podaj nazwisko: ";
		std::cin >> nazwisko;
		std::cout << std::endl;

		for (Node<uczen*>* curr = uczniowie.getHead(); curr != nullptr; curr = curr->next) {
			curr->value->zwroc_dane(im, na);
			if (imie == im && nazwisko == na) {
				curr->value->pokaz_dane();
			}
		}
		if (licz == 0) {
			std::cout << "Nie odnaleziono nauczyciela z podanych danych" << std::endl;
		}
	}
	else if (odp == 2) {
		std::cout << "===== UCZNIOWIE =====" << std::endl;
		for (Node<uczen*>* curr = uczniowie.getHead(); curr != nullptr; curr = curr->next) {
			curr->value->pokaz_dane();
		}
	}
	else if (odp == 3) {
		
	}
	else if (odp == 4) {
		//tu ma byc nic
	}
	else {
		std::cout << "Bledny numer" << std::endl;
	}
}

void f_nauczyciel(lista<nauczyciel*>& nauczyciele) {
	{
		int odp;
		std::cout << "===Nauczyciel===" << std::endl;
		std::cout << "1. Pokaz dane Nauczyciela" << std::endl;
		std::cout << "2. Pokaz dane wszystkich nauczycieli" << std::endl;
		std::cout << "3. Pokaz plan lekcji nauczyciela" << std::endl;
		std::cout << "4. Wroc" << std::endl;
		std::cout << "Wybierz opcje: ";
		std::cin >> odp;
		std::cout << std::endl;
		if (odp == 1) {
			int licz = 0;
			std::string imie, nazwisko, im, na;

			std::cout << "Podaj imie: ";
			std::cin >> imie;
			std::cout << std::endl;

			std::cout << "Podaj nazwisko: ";
			std::cin >> nazwisko;
			std::cout << std::endl;

			for (Node<nauczyciel*>* curr = nauczyciele.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->zwroc_dane(im, na);
				if (imie == im && nazwisko == na) {
					curr->value->pokaz_dane();
					licz++;
				}
			}
			if (licz == 0) {
				std::cout << "Nie odnaleziono nauczyciela z podanych danych" << std::endl;
			}
		}
		else if (odp == 2) {
			std::cout << "===== NAUCZYCIELE =====" << std::endl;
			for (Node<nauczyciel*>* curr = nauczyciele.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->pokaz_dane();
			}
		}
		else if (odp == 3) {

		}
		else if (odp == 4) {
			//tu ma byc nic
		}
		else {
			std::cout << "Bledny numer" << std::endl;
		}
	}
}

void f_lekcji(lista<lekcja*>& lekcje) {
	{
		int odp;
		std::cout << "===Lekcja===" << std::endl;
		std::cout << "1. Pokaz dane lekcji" << std::endl;
		std::cout << "2. Pokaz dane wszystkich lekcji" << std::endl;
		std::cout << "3. Pokaz plan lekcji przedmiotu" << std::endl;
		std::cout << "4. Wroc" << std::endl;
		std::cout << "Wybierz opcje: ";
		std::cin >> odp;
		std::cout << std::endl;
		if (odp == 1) {
			int licz = 0;
			std::string przedmiot, pr;

			std::cout << "Podaj nazwe przedmiotu: ";
			std::cin >> przedmiot;
			std::cout << std::endl;

			alt(przedmiot);

			for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->zwroc_dane_p(pr);
				if (przedmiot == pr) {
					curr->value->pokaz_dane();
					licz++;
				}
			}

			if (licz == 0) {
				std::cout << "Nie odnaleziono podanego przedmiotu" << std::endl;
			}
		}
		else if (odp == 2) {
			std::cout << "===== LEKCJE =====" << std::endl;
			for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->pokaz_dane();
			}
		}
		else if (odp == 3) {

		}
		else if (odp == 4) {
			//tu ma byc nic
		}
		else {
			std::cout << "Bledny numer" << std::endl;
		}
	}
}

void f_sala(lista<sala*>& sale) {
	{
		int odp;
		std::cout << "===SALA===" << std::endl;
		std::cout << "1. Pokaz dane sali" << std::endl;
		std::cout << "2. Pokaz dane wszystkich sal" << std::endl;
		std::cout << "3. Pokaz plan lekcji sali" << std::endl;
		std::cout << "4. Wroc" << std::endl;
		std::cout << "Wybierz opcje: ";
		std::cin >> odp;
		std::cout << std::endl;
		if (odp == 1) {
			int licz = 0;
			std::string salaa, sa;

			std::cout << "Podaj numer sali: ";
			std::cin >> salaa;
			std::cout << std::endl;

			for (Node<sala*>* curr = sale.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->zwroc_dane_s(sa);
				if (salaa == sa) {
					curr->value->pokaz_dane();
					licz++;
				}
			}
			if (licz == 0) {
				std::cout << "Nie odnaleziono podanej sali" << std::endl;
			}
		}
		else if (odp == 2) {
			std::cout << "===== SALE =====" << std::endl;
			for (Node<sala*>* curr = sale.getHead(); curr != nullptr; curr = curr->next) {
				curr->value->pokaz_dane_2();
			}
		}
		else if (odp == 3) {

		}
		else if (odp == 4) {
			//tu ma byc nic
		}
		else {
			std::cout << "Bledny numer" << std::endl;
		}
	}
}


int main() {
	// Listy
	lista<nauczyciel*> lista_nauczycieli;
	lista<lekcja*> lista_lekcji;
	lista<uczen*> lista_uczniow;
	lista<sala*> lista_sal;
	int odp;
	plan p1, p2, p3, p4, p5, p6;

	inicjalizuj(lista_nauczycieli, lista_uczniow, lista_lekcji, lista_sal); //inicjalizuje dane

	/*std::ofstream zapis("zapis_lekcji.txt");
	if (zapis) {
		for (Node<lekcja*>* curr = lista_lekcji.getHead(); curr != nullptr; curr = curr->next) {
			zapis << curr->value;
		}
	}*/

	//p1.pokaz_plan();

	while (true) { //dzieki temu while program sie nie zamyka poki sie nie wybierze opcji 6
		std::cout << std::endl;
		std::cout << "===MENU===" << std::endl;
		std::cout << "1. Plan lekcji" << std::endl;
		std::cout << "2. Uczen" << std::endl;
		std::cout << "3. Nauczyciel" << std::endl;
		std::cout << "4. Lekcja" << std::endl;
		std::cout << "5. Sala" << std::endl;
		std::cout << "6. Wyjdz" << std::endl;
		std::cout << "Wybierz opcje: ";
		std::cin >> odp;
		std::cout << std::endl;

		if (odp == 1) {
			f_plan(p1, p2, p3, p4, p5, p6, lista_lekcji);
		}
		else if (odp == 2) {
			f_uczen(lista_uczniow);
		}
		else if (odp == 3) {
			f_nauczyciel(lista_nauczycieli);
		}
		else if (odp == 4) {
			f_lekcji(lista_lekcji);
		}
		else if (odp == 5) {
			f_sala(lista_sal);
		}
		else if (odp == 6) {
			return 0;
		}
		else {
			std::cout << "Bledna odpowiedz. Wybierz pomiedzy 1, a 6" << std::endl;
		}
	}

	usun_listy(lista_nauczycieli, lista_uczniow, lista_lekcji, lista_sal); //usuwa dane

	return 0;
}