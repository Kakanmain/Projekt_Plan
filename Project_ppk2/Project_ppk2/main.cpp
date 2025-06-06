/** @file */
/*
Projekt: Plan lekcji
Przy stworzeniu planu, tworzy sie ogolny zarys planu lekcji. (Dni, liczba mozliwych lekcji i godziny) GIT
Plan bedzie tez mial kazdy nauczyciel i sala.
Plan mozna wyswietlic, co bedzie pokazywalo zajecia, godziny, itp. GIT
Po zapytaniu o przedmiot pokaze kiedy jest w jakiej sali. GIT
Moze dawanie danych do listy z pliku? GIT
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
		std::cout << "Zla nazwa przedmiotu!" << std::endl;
		std::exit(1);
	}
}

/** @brief Obsluguje interfejs zwiazany z planem lekcji.
 *  Umozliwia wyswietlanie i dodawanie lekcji do planu.
 */
void f_plan(struktura_planow& plany, lista<lekcja*>& lekcje) {
	int odp, godzina, minuta, godzina_trwa, minuta_trwa;
	std::string dzien, przedmiot, typ;

	std::cout << "===Plan lekcji===" << std::endl;
	std::cout << "1. Pokaz plan lekcji" << std::endl;
	std::cout << "2. Dodaj lekcje do planu" << std::endl;
	std::cout << "3. Wroc" << std::endl;
	std::cout << "Wybierz opcje: ";
	std::cin >> odp;
	std::cout << std::endl;

	if (odp == 1) {
		std::cout << "Podaj numer grupy: ";
		std::cin >> odp;
		std::cout << std::endl;

		if (odp >= 1 && odp <= 6) {
			plany.get_plan(odp)->pokaz_plan();
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

		std::cout << "Podaj typ przedmiotu (CW, WYK, LAB, LEKT): ";
		std::cin >> typ;

		std::cout << "Podaj czas trwania (np. 1 30 dla 1h 30min): ";
		std::cin >> godzina_trwa >> minuta_trwa;
		std::cout<< std::endl;

		if (odp >= 1 && odp <= 6) {
			plany.get_plan(odp)->dodaj_do_planu(godzina, minuta, dzien, przedmiot, typ, godzina_trwa, minuta_trwa, lekcje, odp, false);
		}
		else {
			std::cout << "Bledny numer grupy" << std::endl;
		}
		plany.get_plan(odp)->pokaz_plan();
	}
	else if (odp == 3) {
		//tu ma byc nic
	}
	else {
		std::cout << "Bledny numer" << std::endl;
	}
}

/** @brief Obsluguje interfejs zwiazany z uczniami.
 *  Umozliwia wyswietlanie danych i dodawanie uczniow.
 */
void f_uczen(lista<uczen*>& uczniowie, struktura_planow& plany) {
	std::string imie, nazwisko, nr_gr;
	int odp, nr;
	std::cout << "===Uczen===" << std::endl;
	std::cout << "1. Pokaz dane ucznia" << std::endl;
	std::cout << "2. Pokaz dane wszystkich uczniow" << std::endl;
	std::cout << "3. Pokaz plan lekcji ucznia" << std::endl;
	std::cout << "4. Dodaj ucznia" << std::endl;
	std::cout << "5. Wroc" << std::endl;
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
		std::string temp_im, temp_na;
		std::cout << "Podaj imie: ";
		std::cin >> imie;
		std::cout << "Podaj nazwisko: ";
		std::cin >> nazwisko;
		for (Node<uczen*>* curr = uczniowie.getHead(); curr != nullptr; curr = curr->next) {
			curr->value->zwroc_dane(temp_im, temp_na);
			if (imie == temp_im && nazwisko == temp_na) {
				nr_gr = curr->value->getNumer_gr();
				int nr = std::stoi(nr_gr);
				plany.get_plan(nr)->pokaz_plan(); //Dziwnie sie wywoluje ten plan, jakby caly rozwalony, a nic nie zmieniam w nim. nie wiem
			}
		}
	}
	else if (odp == 4) {

		std::cout << "Podaj imie: ";
		std::cin >> imie;
		std::cout << "Podaj nazwisko: ";
		std::cin >> nazwisko;
		std::cout << "Podaj numer grupy: ";
		std::cin >> nr_gr;
		uczniowie.push_back(new uczen(imie, nazwisko, nr_gr));

		std::ofstream zapis_uczniow("zapis_uczniow.txt", std::ios::app);
		if (zapis_uczniow) {
			zapis_uczniow << "Imie: " << imie << std::endl;
			zapis_uczniow << "Nazwisko: " << nazwisko << std::endl;
			zapis_uczniow << "Nr_grupy: " << nr_gr << std::endl;
			zapis_uczniow << "---------------------------" << std::endl;
		}
	}
	else if (odp == 4) {
		//tu ma byc nic
	}
	else {
		std::cout << "Bledny numer" << std::endl;
	}
}

/** @brief Obsluguje interfejs zwiazany z nauczycielami.
 *  Umozliwia wyswietlanie danych nauczycieli
 */
void f_nauczyciel(lista<nauczyciel*>& nauczyciele, struktura_planow& plany, lista<lekcja*>& lekcje) {
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
			std::string imie, nazwisko, temp_imie, temp_nazwisko;
			std::cout << "Podaj imie nauczyciela: ";
			std::cin >> imie;
			std::cout << "Podaj nazwisko nauczyciela: ";
			std::cin >> nazwisko;
			std::cout << std::endl;

			plan pn; // tymczasowy plan pn

			std::ifstream plik("zapis_planu.txt");
			if (!plik) {
				std::cout << "Nie mozna otworzyc zapis_planu.txt" << std::endl;
				return;
			}

			std::string linia, dzien, przedmiot, typ;
			int h = 0, m = 0, ht = 0, mt = 0, nr_gr = 0;

			while (std::getline(plik, linia)) {
				if (linia.find("Dzien: ") == 0) {
					dzien = linia.substr(7);
				}
				else if (linia.find("Godzina rozpoczecia: ") == 0) {
					std::stringstream ss(linia.substr(21));
					ss >> h >> m;
				}
				else if (linia.find("Trwa: ") == 0) {
					std::stringstream ss(linia.substr(6));
					ss >> ht >> mt;
				}
				else if (linia.find("Przedmiot: ") == 0) {
					przedmiot = linia.substr(11);
				}
				else if (linia.find("Typ: ") == 0) {
					typ = linia.substr(5);
				}
				else if (linia.find("Nr grupy: ") == 0) {
					nr_gr = std::stoi(linia.substr(10));
				}
				else if (linia.find("---") == 0) {
					lekcja* pasujaca = nullptr;
					for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
						curr->value->getNauczyciel()->zwroc_dane(temp_imie, temp_nazwisko);
						if (curr->value->getPrzedmiot() == przedmiot &&
							curr->value->getTyp() == typ &&
							temp_imie == imie &&
							temp_nazwisko == nazwisko) {

							pn.dodaj_do_planu(h, m, dzien, przedmiot, typ, ht, mt, lekcje, nr_gr, true);
							break;
						}
					}
				}
			}

			std::cout << "=== PLAN NAUCZYCIELA: " << imie << " " << nazwisko << " ===" << std::endl << std::endl;
			pn.pokaz_plan();
		}
		else if (odp == 4) {
			//tu ma byc nic
		}
		else {
			std::cout << "Bledny numer" << std::endl;
		}
	}
}

/** @brief Obsluguje interfejs zwiazany z lekcjami.
 *  Umozliwia wyswietlanie danych lekcji
 */
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
			std::string pr;
			std::cout << "Podaj nazwe przedmiotu: ";
			std::cin >> pr;
			std::cout << std::endl;
			alt(pr);

			plan pl;

			std::ifstream plik("zapis_planu.txt");
			if (!plik) {
				std::cout << "Nie mozna otworzyc zapis_planu.txt" << std::endl;
				return;
			}

			std::string linia, dzien, typ, przedmiot;
			int h = 0, m = 0, ht = 0, mt = 0, nr_gr = 0;

			while (std::getline(plik, linia)) {
				if (linia.find("Dzien: ") == 0) dzien = linia.substr(7);
				else if (linia.find("Godzina rozpoczecia: ") == 0) {
					std::stringstream(linia.substr(21)) >> h >> m;
				}
				else if (linia.find("Trwa: ") == 0) {
					std::stringstream(linia.substr(6)) >> ht >> mt;
				}
				else if (linia.find("Przedmiot: ") == 0) {
					przedmiot = linia.substr(11);
				}
				else if (linia.find("Typ: ") == 0) {
					typ = linia.substr(5);
				}
				else if (linia.find("Nr grupy: ") == 0) {
					nr_gr = std::stoi(linia.substr(10));
				}
				else if (linia.find("---") == 0) {
					for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
						if (curr->value->getPrzedmiot() == przedmiot && curr->value->getTyp() == typ && pr == przedmiot) {
							pl.dodaj_do_planu(h, m, dzien, przedmiot, typ, ht, mt, lekcje, nr_gr, true);
							break;
						}
					}
					przedmiot.clear();
				}
			}
			std::cout << "=== PLAN PRZEDMIOTU: " << przedmiot << " ===" << std::endl << std::endl;
			pl.pokaz_plan();
		}
		else if (odp == 4) {
			//tu ma byc nic
		}
		else {
			std::cout << "Bledny numer" << std::endl;
		}
	}
}

/** @brief Obsluguje interfejs zwiazany z salami.
 *  Umozliwia wyswietlanie danych sal
 */
void f_sala(lista<sala*>& sale, lista<lekcja*>& lekcje) {
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
			std::string numer_sali, numer;
			std::cout << "Podaj numer sali: ";
			std::cin >> numer_sali;
			std::cout << std::endl;

			plan ps;

			std::ifstream plik("zapis_planu.txt");
			if (!plik) {
				std::cout << "Nie mozna otworzyc zapis_planu.txt" << std::endl;
				return;
			}

			std::string linia, dzien, przedmiot, typ;
			int h = 0, m = 0, ht = 0, mt = 0, nr_gr = 0;

			while (std::getline(plik, linia)) {
				if (linia.find("Dzien: ") == 0) dzien = linia.substr(7);
				else if (linia.find("Godzina rozpoczecia: ") == 0) std::stringstream(linia.substr(21)) >> h >> m;
				else if (linia.find("Trwa: ") == 0) {
					std::stringstream(linia.substr(6)) >> ht >> mt;
				}
				else if (linia.find("Przedmiot: ") == 0) { 
					przedmiot = linia.substr(11); 
				}
				else if (linia.find("Typ: ") == 0) {
					typ = linia.substr(5);
				}
				else if (linia.find("Nr grupy: ") == 0) {
					nr_gr = std::stoi(linia.substr(10));
				}
				else if (linia.find("---") == 0) {
					for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
						std::string sala_nr;
						curr->value->getSala()->zwroc_dane_s(sala_nr);
						if (curr->value->getPrzedmiot() == przedmiot &&
							curr->value->getTyp() == typ &&
							sala_nr == numer_sali) {
							ps.dodaj_do_planu(h, m, dzien, przedmiot, typ, ht, mt, lekcje, nr_gr, true);
							break;
						}
					}
				}
			}
			std::cout << "=== PLAN SALI: " << numer_sali << " ==="<< std::endl<< std::endl;
			ps.pokaz_plan();
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
	struktura_planow wszystkie_plany;
	int odp;

	inicjalizuj(lista_nauczycieli, lista_uczniow, lista_lekcji, lista_sal, wszystkie_plany); //inicjalizuje dane

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
			f_plan(wszystkie_plany, lista_lekcji);
		}
		else if (odp == 2) {
			f_uczen(lista_uczniow, wszystkie_plany);
		}
		else if (odp == 3) {
			f_nauczyciel(lista_nauczycieli, wszystkie_plany, lista_lekcji);
		}
		else if (odp == 4) {
			f_lekcji(lista_lekcji);
		}
		else if (odp == 5) {
			f_sala(lista_sal, lista_lekcji);
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