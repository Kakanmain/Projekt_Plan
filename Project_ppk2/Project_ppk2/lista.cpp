/** @file */

#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>

#include "klasy.h"

/** @brief Wczytuje nauczycieli, uczniow, lekcje, sale i plan.
 */
void inicjalizuj(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale, struktura_planow& plany) {
	// SALE
	std::ifstream laduj_sale("zapis_sal.txt");
	if (laduj_sale) {
		std::string linia, typ, numer;

		while (std::getline(laduj_sale, linia)) { //bierze linijke z pliku
			if (linia.find("Numer: ") == 0) { 
				numer = linia.substr(7); //Jesli zaczyna sie na "Numer: " to bierze od 7 miejsca i dalej
			}
			else if (linia.find("Typ: ") == 0) {
				typ = linia.substr(5); 
			}
			else if (linia.find("-") == 0) {
				sale.push_back(new sala(typ, numer));
			}
		}
	}
	laduj_sale.close();

	// NAUCZYCIELE
	std::ifstream laduj_nauczycieli("zapis_nauczycieli.txt");
	if (laduj_nauczycieli) {
		std::string linia, imie, nazwisko, przedmiot;

		while (std::getline(laduj_nauczycieli, linia)) {
			if (linia.find("Imie: ") == 0) {
				imie = linia.substr(6);
			}
			else if (linia.find("Nazwisko: ") == 0) {
				nazwisko = linia.substr(10);
			}
			else if (linia.find("Przedmiot prowadzony: ") == 0) {
				przedmiot = linia.substr(22);
			}
			else if (linia.find("-") == 0) {
				nauczyciele.push_back(new nauczyciel(imie, nazwisko, przedmiot));
			}
		}
	}
	laduj_nauczycieli.close();

	// LEKCJE
	std::ifstream laduj_lekcje("zapis_lekcji.txt");
	if (laduj_lekcje) {
		std::string linia, przedmiot, typ, par, prowadzacy, sala_S, im, na, imie_string, nazwisko_string, s;
		int parzy, koniec;
		Node<nauczyciel*>* prowadzacy_wsk = nauczyciele.getHead();

		while (std::getline(laduj_lekcje, linia)) {
			std::stringstream imie, nazwisko;

			if (linia.find("Przedmiot: ") == 0) {
				przedmiot = linia.substr(11);
			}
			else if (linia.find("Typ: ") == 0) {
				typ = linia.substr(5);
			}
			else if (linia.find("Parzystosc: ") == 0) {
				par = linia.substr(12);

				if (par == "Co tydzien") {
					parzy = 0;
				}
				else if (par == "Parzyste tygodnie") {
					parzy = 1;
				}
				else if (par == "Nieparzyste tygodnie") {
					parzy = 2;
				}
			}
			else if (linia.find("Prowadzacy: ") == 0) {
				prowadzacy = linia.substr(12);
				int rozmiar = prowadzacy.size();
				int licz = 0;
				for (int i = 0; i < rozmiar; i++) {
					if (prowadzacy[i] == ' ') { 
						licz++;
					}
					else if(licz == 0){
						imie << prowadzacy[i];
					}
					else {
						nazwisko << prowadzacy[i];
					}
				}
				imie_string = imie.str();
				nazwisko_string = nazwisko.str();
			}
			else if (linia.find("Sala: ") == 0) {
				sala_S = linia.substr(6);
			}
			else if (linia.find("-") == 0) {
				koniec = 0;
				for (Node<nauczyciel*>* curr_n = nauczyciele.getHead(); curr_n != nullptr || koniec != 1; curr_n = curr_n->next) {
					curr_n->value->zwroc_dane(im, na); //bierze imie i nazwisko z listy zaladowanej
					if (imie_string == im && nazwisko_string == na) { //porownuje je z tym co jest zapisane i jesli jest te same to...
						for (Node<sala*>* curr_s = sale.getHead(); curr_s != nullptr; curr_s = curr_s->next) { //...bierze sale i porownuje ja z ta co jest zapisana i...
							curr_s->value->zwroc_dane_s(s);
							if (sala_S == s) { //...jesli to sie zgadza to moze dopiero wyslac lekcje do listy
								lekcje.push_back(new lekcja(przedmiot, typ, parzy, curr_s->value, curr_n->value));
								koniec++;
								break;
							}
						}
						if (koniec == 1) {
							break;
						}
					}
				}
			}
		}
	}
	laduj_lekcje.close();

	// UCZNIOWIE
	std::ifstream laduj_uczniow("zapis_uczniow.txt");
	if (laduj_uczniow) {
		std::string linia, imie, nazwisko, nr_grupy;

		while (std::getline(laduj_uczniow, linia)) {
			if (linia.find("Imie: ") == 0) {
				imie = linia.substr(6);
			}
			else if (linia.find("Nazwisko: ") == 0) {
				nazwisko = linia.substr(10);
			}
			else if (linia.find("Numer_gr: ") == 0) {
				nr_grupy = linia.substr(10);
			}
			else if (linia.find("-") == 0) {
				uczniowie.push_back(new uczen(imie, nazwisko, nr_grupy));
			}
		}
	}
	laduj_uczniow.close();

	// PLAN
	std::ifstream laduj_plan("zapis_planu.txt");
	if (laduj_plan) {
		std::string linia, dzien, przedmiot, typ, godzina_r, trwa, nr;
		int h, m, ht, mt, nr_gr = 0;

		while (std::getline(laduj_plan, linia)) {
			std::stringstream godz_ss, min_ss, trwa_hs, trwa_ms, nr_ss;
			if (linia.find("Dzien: ") == 0) {
				dzien = linia.substr(7);
			}
			else if (linia.find("Godzina rozpoczecia: ") == 0) {
				godzina_r = linia.substr(21);
				int rozmiar = godzina_r.size();
				int licz = 0;
				for (int i = 0; i < rozmiar; i++) {
					if (godzina_r[i] == ' ') {
						licz++;
					}
					else if (licz == 0) {
						godz_ss << godzina_r[i];
					}
					else {
						min_ss << godzina_r[i];
					}
				}
				godz_ss >> h;
				min_ss >> m;
			}
			else if (linia.find("Trwa: ") == 0) {
				trwa = linia.substr(6);
				int rozmiar = trwa.size();
				int licz = 0;
				for (int i = 0; i < rozmiar; i++) {
					if (trwa[i] == ' ') {
						licz++;
					}
					else if (licz == 0) {
						trwa_hs << trwa[i];
					}
					else {
						trwa_ms << trwa[i];
					}
				}
				trwa_hs >> ht;
				trwa_ms >> mt;
			}
			else if (linia.find("Przedmiot: ") == 0) {
				przedmiot = linia.substr(11);
			}
			else if (linia.find("Typ: ") == 0) {
				typ = linia.substr(5);
			}
			else if (linia.find("Nr grupy: ") == 0) {
				nr = linia.substr(10);
				nr_ss << nr;
				nr_ss >> nr_gr;
			}
			else if (linia.find("-") == 0) {
				plany.get_plan(nr_gr)->dodaj_do_planu(h, m, dzien, przedmiot, typ, ht, mt, lekcje, nr_gr, true);
			}
		}
	}
	laduj_plan.close();
}

/** @brief Usuwa dynamicznie zaalokowane dane z list.
 */
void usun_listy(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale) {
	for (Node<nauczyciel*>* curr = nauczyciele.getHead(); curr != nullptr; curr = curr->next) {
		delete curr->value;
	}

	for (Node<uczen*>* curr = uczniowie.getHead(); curr != nullptr; curr = curr->next) {
		delete curr->value;
	}

	for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
		delete curr->value;
	}

	for (Node<sala*>* curr = sale.getHead(); curr != nullptr; curr = curr->next) {
		delete curr->value;
	}
}

/** @brief Przeciazony operator << dla klasy uczen.
 *  @param os Strumien wyjsciowy.
 *  @param u Wskaznik na ucznia.
 *  @return Referencja do strumienia wyjsciowego.
 */
std::ostream& operator<<(std::ostream& os, const uczen* u) { // uczen
	if (!u) return os;

	std::string imie, nazwisko;
	u->zwroc_dane(imie, nazwisko);
	os << "Imie: " << imie << std::endl;
	os << "Nazwisko: " << nazwisko << std::endl;
	os << "Numer_gr: " << u->getNumer_gr() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

/** @brief Przeciazony operator << dla klasy nauczyciel.
 *  @param os Strumien wyjsciowy.
 *  @param u Wskaznik na nauczyciela.
 *  @return Referencja do strumienia wyjsciowego.
 */
std::ostream& operator<<(std::ostream& os, const nauczyciel* n) { // nauczyciel
	if (!n) return os;

	std::string imie, nazwisko;
	n->zwroc_dane(imie, nazwisko);
	os << "Imie: " << imie << std::endl;
	os << "Nazwisko: " << nazwisko << std::endl;
	os << "Przedmiot prowadzony: " << n->getPrzedmiot_prowadzony() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

/** @brief Przeciazony operator << dla klasy sala.
 *  @param os Strumien wyjsciowy.
 *  @param u Wskaznik na sale.
 *  @return Referencja do strumienia wyjsciowego.
 */
std::ostream& operator<<(std::ostream& os, const sala* s) { // sala
	if (!s) return os;

	os << "Numer: " << s->getNumer() << std::endl;
	os << "Typ: " << s->getTyp() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

/** @brief Przeciazony operator << dla klasy lekcja.
 *  @param os Strumien wyjsciowy.
 *  @param u Wskaznik na lekcje.
 *  @return Referencja do strumienia wyjsciowego.
 */
std::ostream& operator<<(std::ostream& os, const lekcja* l) { // lekcja
	if (!l) return os;

	os << "Przedmiot: " << l->getPrzedmiot() << std::endl;
	os << "Typ: " << l->getTyp() << std::endl;

	int p = l->getParzystosc();
	if (p == 0) {
		os << "Parzystosc: Co tydzien" << std::endl;
	}
	else if (p == 1) {
		os << "Parzystosc: Parzyste tygodnie" << std::endl;
	}
	else if (p == 2) {
		os << "Parzystosc: Nieparzyste tygodnie" << std::endl;
	}
	else {
		std::cout << "Cos jest nie tak..." << std::endl;
	}

	std::string imie, nazwisko;
	if (l->getNauczyciel()) {
		l->getNauczyciel()->zwroc_dane(imie, nazwisko);
		os << "Prowadzacy: " << imie << " " << nazwisko << std::endl;
	}
	if (l->getSala()) {
		std::string nr;
		l->getSala()->zwroc_dane_s(nr);
		os << "Sala: " << nr << std::endl;
	}
	os << "---------------------------" << std::endl;
	return os;
}
