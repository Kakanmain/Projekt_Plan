#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>

#include "klasy.h"

void inicjalizuj(lista<nauczyciel*>& nauczyciele, lista<uczen*>& uczniowie, lista<lekcja*>& lekcje, lista<sala*>& sale) {
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

	Node<sala*>* s = sale.getHead();
	sala* ogolna = s->value; s = s->next;
	sala* aulaA = s->value; s = s->next;
	sala* aulaB = s->value; s = s->next;
	sala* aulaC = s->value; s = s->next;
	sala* laboratoryjna = s->value; s = s->next;
	sala* komputerowa = s->value;

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
		int parzy, koniec = 0;
		std::stringstream imie, nazwisko;
		Node<nauczyciel*>* prowadzacy_wsk = nauczyciele.getHead();

		while (std::getline(laduj_lekcje, linia)) {
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
					if (prowadzacy[i] == " ") { //tu jest problem
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
				for (Node<nauczyciel*>* curr_n = nauczyciele.getHead(); curr_n != nullptr || koniec == 1; curr_n = curr_n->next) {
					curr_n->value->zwroc_dane(im, na);
					if (imie_string == im && nazwisko_string == na) {
						for (Node<sala*>* curr_s = sale.getHead(); curr_s != nullptr || koniec == 1; curr_s = curr_s->next) {
							curr_s->value->zwroc_dane_s(s);
							if (sala_S == s) {
								lekcje.push_back(new lekcja(przedmiot, typ, parzy, curr_s->value, curr_n->value));
								koniec++;
							}
						}
					}
				}
				

				//Tu kontynuuj. Prowadzacy i sala s¹ stringami, a nie np. *sala. ZnaleŸæ gdzie jest dany nauczyciel w liscie i go porownac 
			}
		}
	}
	laduj_lekcje.close();

	//Node<nauczyciel*>* n = nauczyciele.getHead();

	/*lekcje.push_back(new lekcja("Fizyka", "CW", 0, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Fizyka", "WYK", 0, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Elektronika i miernictwo", "CW", 0, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Elektronika i miernictwo", "WYK", 0, aulaB, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Analiza matematyczna i algebra liniowa", "CW", 0, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Analiza matematyczna i algebra liniowa", "WYK", 0, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Podstawy elektrotechniki", "CW", 1, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Podstawy elektrotechniki", "WYK", 1, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Algorytmy i struktury danych", "CW", 1, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Algorytmy i struktury danych", "WYK", 1, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Podstawy informatyki", "CW", 1, ogolna, n->value));
	lekcje.push_back(new lekcja("Podstawy informatyki", "WYK", 2, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Programowanie komputerow", "WYK", 0, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Programowanie komputerow", "LAB", 2, komputerowa, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Teoria ukladow cyfrowych", "CW", 2, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Teoria ukladow cyfrowych", "WYK", 0, aulaA, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Wychowanie fizyczne", "CW", 0, ogolna, n->value)); n = n->next;
	lekcje.push_back(new lekcja("Jezyk angielski", "LEKT", 0, ogolna, n->value)); n = n->next;*/

	// UCZNIOWIE
	uczniowie.push_back(new uczen("Andrzej", "Piaseczny", 3));
	uczniowie.push_back(new uczen("Katarzyna", "Nowicka", 1));
	uczniowie.push_back(new uczen("Michal", "Kowalewski", 4));
	uczniowie.push_back(new uczen("Patrycja", "Jablonska", 2));
	uczniowie.push_back(new uczen("Tomasz", "Stepien", 5));
	uczniowie.push_back(new uczen("Julia", "Wojcik", 6));
	uczniowie.push_back(new uczen("Sebastian", "Krawczyk", 3));
	uczniowie.push_back(new uczen("Aleksandra", "Piekarska", 2));
	uczniowie.push_back(new uczen("lukasz", "Baran", 4));
	uczniowie.push_back(new uczen("Natalia", "Lis", 1));
	uczniowie.push_back(new uczen("Damian", "Mazur", 5));
	uczniowie.push_back(new uczen("Dominika", "Szymanska", 6));
	uczniowie.push_back(new uczen("Kacper", "Zawadzki", 2));
	uczniowie.push_back(new uczen("Maja", "Sikora", 3));
	uczniowie.push_back(new uczen("Piotr", "Blaszczyk", 4));
	uczniowie.push_back(new uczen("Amelia", "Rutkowska", 1));
	uczniowie.push_back(new uczen("Jan", "Kubiak", 6));
	uczniowie.push_back(new uczen("Zuzanna", "Czarnecka", 2));
	uczniowie.push_back(new uczen("Oliwia", "Kowalczyk", 3));
	uczniowie.push_back(new uczen("Adam", "Krol", 5));
	uczniowie.push_back(new uczen("Magdalena", "Pawlak", 4));
	uczniowie.push_back(new uczen("Bartlomiej", "Jasinski", 2));
	uczniowie.push_back(new uczen("Karolina", "Witkowska", 6));
	uczniowie.push_back(new uczen("Marcin", "Lesniak", 1));
	uczniowie.push_back(new uczen("Joanna", "Sawicka", 3));
	uczniowie.push_back(new uczen("Baltazar", "Gabka", 5));
}

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

std::ostream& operator<<(std::ostream& os, const uczen* u) {
	if (!u) return os;

	std::string imie, nazwisko;
	u->zwroc_dane(imie, nazwisko);
	os << "Imie: " << imie << std::endl;
	os << "Nazwisko: " << nazwisko << std::endl;
	os << "Numer_gr: " << u->getNumer_gr() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const nauczyciel* n) {
	if (!n) return os;

	std::string imie, nazwisko;
	n->zwroc_dane(imie, nazwisko);
	os << "Imie: " << imie << std::endl;
	os << "Nazwisko: " << nazwisko << std::endl;
	os << "Przedmiot prowadzony: " << n->getPrzedmiot_prowadzony() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const sala* s) {
	if (!s) return os;

	os << "Numer: " << s->getNumer() << std::endl;
	os << "Typ: " << s->getTyp() << std::endl;
	os << "---------------------------" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const lekcja* l) {
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
