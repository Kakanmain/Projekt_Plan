/** @file */

#ifndef KLASY_H 
#define KLASY_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

template <typename t>
struct Node {
	t value;
	Node* next;

	Node(t val) : value(val), next(nullptr) {}
};

template <typename t>
class lista {
	Node<t>* head;
	Node<t>* tail;

public:
	lista() : head(nullptr), tail(nullptr) {}

	Node<t>* getHead() const {
		return head;
	}

	void push_back(t val) {
		Node<t>* newNode = new Node<t>(val);

		if (tail == nullptr) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	void remove(t val) {
		if (head == nullptr) return;

		if (head->value == val) {
			Node<t>* temp = head;
			head = head->next;
			if (temp == tail) {
				tail = nullptr;
			}
			delete temp;
			return;
		}

		Node<t>* current = head;
		while (current->next != nullptr && current->next->value != val) {
			current = current->next;
		}

		if (current->next != nullptr) {
			Node<t>* temp = current->next;
			current->next = temp->next;
			if (temp == tail) {
				tail = current;
			}
			delete temp;
		}
	}

	~lista() {
		Node<t>* current = head;
		while (current != nullptr) {
			Node<t>* next = current->next;
			delete current;
			current = next;
		}
	}
};



class osoba {
	std::string imie, nazwisko;
public:
	osoba() {}
	osoba(const std::string& imie, const std::string& nazwisko) : imie(imie), nazwisko(nazwisko){

	}

	void inicjaly() {
		std::cout << std::endl;
		std::cout << "Imie: " << imie << std::endl << "Nazwisko: " << nazwisko << std::endl;
	}

	std::string imiee() const{
		return imie;
	}

	std::string nazwiskoo() const{
		return nazwisko;
	}

	osoba& operator=(const osoba& a) {
		if (this != &a) {
			imie = a.imie;
			nazwisko = a.nazwisko;
		}
		return *this;
	}

	~osoba() {};
};

class uczen : public osoba{
	std::string numer_gr;
public:
	uczen(const std::string imie, const std::string nazwisko, const std::string numer_gr) : osoba(imie, nazwisko), numer_gr(numer_gr) {
		
	}

	void pokaz_dane() {
		osoba::inicjaly();
		std::cout << "Grupa dziekanska: "<<numer_gr << std::endl;
	}

	void zwroc_dane(std::string& i, std::string& n) const{
		i = osoba::imiee();
		n = osoba::nazwiskoo();
	}
	
	std::string getNumer_gr() const {
		return numer_gr;
	}

	~uczen() {};
};

class nauczyciel : public osoba {
	std::string przedmiot_prowadzony;
public:
	nauczyciel() {}
	nauczyciel(const std::string imie, const std::string nazwisko, const std::string przedmiot_prowadzony) : osoba(imie, nazwisko), przedmiot_prowadzony(przedmiot_prowadzony){

	}

	void pokaz_dane() {
		osoba::inicjaly();
		std::cout << "Przedmiot prowadzony: " << przedmiot_prowadzony << std::endl;
	}

	void zwroc_dane(std::string& i, std::string& n) const {
		i = osoba::imiee();
		n = osoba::nazwiskoo();
	}

	std::string getPrzedmiot_prowadzony() const {
		return przedmiot_prowadzony;
	}

	~nauczyciel() {};
};

class sala {
	std::string typ; //wykladowa, laboratoiryjna, komputerowa, ogolna...
	std::string numer;
public:
	sala() {}
	sala(std::string typ, std::string numer) : typ(typ), numer(numer) {

	}

	void pokaz_dane() {
		std::cout << "Numer sali: " << numer << std::endl;
		std::cout << "Typ sali: " << typ << std::endl;
	}

	void pokaz_dane_2() {
		std::cout << "Numer sali: " << numer << std::endl;
		std::cout << "Typ sali: " << typ << std::endl;
		std::cout << std::endl;
	}

	void zwroc_dane_s(std::string& s) const {
		s = numer;
	}

	std::string getNumer() const {
		return numer;
	}

	std::string getTyp() const {
		return typ;
	}

	~sala() {};
};

class lekcja {
protected:
	std::string przedmiot, typ;
	int parzystosc; //0 nie wazne, 1 parzysty dzien, 2 nieparzysty
	sala* klasa;
	nauczyciel* prowadzacy;
public:
	lekcja() {}
	lekcja(std::string przedmiot, std::string typ, int parzystosc, sala* nr, nauczyciel* n) : przedmiot(przedmiot), typ(typ), parzystosc(parzystosc), prowadzacy(n), klasa(nr) {

	}

	void pokaz_dane() {
		std::cout << "-----------------" << std::endl;
		std::cout << przedmiot << ":" << std::endl << "Typ: " << typ << std::endl;
		if (parzystosc == 0) {
			std::cout << "Co tydzien" << std::endl;
		}
		else if (parzystosc == 1) {
			std::cout << "Tylko parzyste tygodnie" << std::endl;
		}
		else if (parzystosc == 2) {
			std::cout << "Tylko nieparzyste tygodnie" << std::endl;
		}
		std::cout << "Prowadzacy: ";
		prowadzacy->pokaz_dane();
		klasa->pokaz_dane();
		std::cout << "-----------------" << std::endl;
	}

	void zwroc_dane_p(std::string& p) const {
		p = przedmiot;
	}

	std::string getPrzedmiot() const {
		return przedmiot;
	}

	std::string getTyp() const {
		return typ;
	}

	int getParzystosc() const {
		return parzystosc;
	}

	nauczyciel* getNauczyciel() const {
		return prowadzacy;
	}

	sala* getSala() const {
		return klasa;
	}

	~lekcja() {};
};

class plan : protected nauczyciel, protected sala {
	int w = 57;
	int k = 16;
	std::string tabela[57][16];
public:
	plan() { //tworzy szkielet planu
		tabela[0][0] = "Godz.";
		tabela[0][2] = "      Poniedzialek";
		tabela[0][4] = "          Wtorek";
		tabela[0][6] = "          Sroda";
		tabela[0][8] = "        Czwartek";
		tabela[0][10] = "         Piatek";
		tabela[0][12] = "          Sobota";
		tabela[0][14] = "        Niedziela";

		//myslniki poziome
		std::stringstream myslniki, myslinik0;
		myslniki << std::setw(25) << std::setfill('-') << "-"; //to dla wierszy
		myslinik0 << std::setw(6) << std::setfill('-') << "-"; //to dla godziny

		for (int j = 1; j < w; j += 5) {
			tabela[j][0] = myslinik0.str();
			for (int i = 1; i < k; i++) {
				if (i % 2 == 1) {

				}
				else {
					tabela[j][i] = myslniki.str();
				}
			}
		}
		// myslniki pionowe
		for (int j = 1; j < k; j += 2) { //to dla |
			for (int i = 0; i < w; i++) {
				if (i == 1) {
					tabela[1][j] = "-";
				}
				else {
					tabela[i][j] = "|";
				}
			}
		}

		//zajmuje sie godzinami
		int h = 8;
		int m = 00;
		for (int i = 2; i <= 55; i++) {
			if (m == 60) { // jak jest 60 minuta to zwieksza godzine o 1
				h++;
				m = 00;
				i++;
			}

			std::stringstream oss;
			oss << std::setw(2) << std::setfill('0') << h << ":" << std::setw(2) << std::setfill('0') << m;
			if (m == 00) {
				tabela[i][0] = oss.str();
			}

			else { //tu s¹ minuty(co 15) mozna zakomentowac
				tabela[i][0] = oss.str();
			}
			m += 15;
		}
	}

	void pokaz_plan() {
		std::cout << "Plan lekcji:" << std::endl << std::endl;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < k; y++) {
				if (y == 0) {
					std::cout << std::setw(6) << std::left << tabela[x][y]; //wyswietla godziny
				}
				else if (y % 2 == 1) { //wyswietla |
					std::cout << tabela[x][y];
					if (y == 15) {
						std::cout << std::endl;
					}
				}
				else {
					std::cout << std::setw(25) << std::left << tabela[x][y]; //wyswietla komorki ogolnie
				}
			}
		}
	}

	void czy_sa_myslniki(int& x) {
		if ((x - 1) % 5 == 0) {
			x++;
		}
	}

	void dodaj_do_planu(int h, int m, std::string dzien, std::string przedmiot, std::string typ, int ht, int mt, lista<lekcja*>& lekcje) {
		int x, y, i_minuty;
		std::stringstream fale, nazwa_lekcji, typ_ss, nauczyciel_ss, sal;
		std::string nr_sali, imie, nazwisko;

		fale << std::setw(25) << std::setfill('~') << "~";

		if (dzien == "poniedzialek" || dzien == "pon") {
			y = 2;
		}
		else if (dzien == "wtorek" || dzien == "wt") {
			y = 4;
		}
		else if (dzien == "sroda" || dzien == "sr") {
			y = 6;
		}
		else if (dzien == "czwartek" || dzien == "czw") {
			y = 8;
		}
		else if (dzien == "piatek" || dzien == "pt") {
			y = 10;
		}
		else if (dzien == "sobota" || dzien == "sob") {
			y = 12;
		}
		else if (dzien == "niedziela" || dzien == "nd") {
			y = 14;
		}
		else {
			std::cout << "Podano zly dzien" << std::endl;
			std::exit(1);
		}

		if (h < 8 || h > 18 || (ht == 0 && mt != 45)) {
			std::cout << "Podano zla godzine" << std::endl;
			std::exit(1);
		}

		if (m == 00) {
			i_minuty = 0;
		}
		else if (m == 15) {
			i_minuty = 1;
		}
		else if (m == 30) {
			i_minuty = 2;
		}
		else if (m == 45) {
			i_minuty = 3;
		}
		else {
			std::cout << "Podano zla minute" << std::endl;
			std::exit(1);
		}

		lekcja* zgodna = nullptr;
		for (Node<lekcja*>* curr = lekcje.getHead(); curr != nullptr; curr = curr->next) {
			if (curr->value->getPrzedmiot() == przedmiot && curr->value->getTyp() == typ) {
				zgodna = curr->value;
				break;
			}
		}
		if (zgodna == nullptr) {
			std::cout << "Nie znaleziono lekcji o nazwie: " << przedmiot << std::endl;
			return;
		}
		nauczyciel* prow = zgodna->getNauczyciel();
		sala* sala_ss = zgodna->getSala();
		prow->zwroc_dane(imie, nazwisko);
		sala_ss->zwroc_dane_s(nr_sali);

		x = 2 + 5 * (-8 + h) + i_minuty; //gorna granica lekcji
		tabela[x][y] = fale.str();
		x++;

		//nazwa lekcji
		czy_sa_myslniki(x);
		nazwa_lekcji << std::setw(25) << przedmiot;
		tabela[x][y] = nazwa_lekcji.str();
		x++;

		//nauczyciel
		czy_sa_myslniki(x);
		nauczyciel_ss << std::setw(25) << imie << " " << nazwisko;
		tabela[x][y] = nauczyciel_ss.str();

		//typ lekcji
		czy_sa_myslniki(x);
		typ_ss << std::setw(12) << typ;
		tabela[x][y] = typ_ss.str();

		//sala
		czy_sa_myslniki(x);
		sal << std::setw(12) << sala_ss;
		tabela[x][y] = sal.str();

		//czy_sa_myslniki(x); //dolna granica lekcji
		int ile = ht * 4 + mt / 15;
		tabela[x + ile-1][y] = fale.str();
	}

	~plan() {};
};

std::ostream& operator<<(std::ostream& os, const uczen* u);
std::ostream& operator<<(std::ostream& os, const nauczyciel* n);
std::ostream& operator<<(std::ostream& os, const sala* s);
std::ostream& operator<<(std::ostream& os, const lekcja* l);

#endif