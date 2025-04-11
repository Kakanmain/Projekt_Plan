#ifndef KLASY_H 
#define KLASY_H

#include <string>
#include <sstream>
#include <iomanip>

/*class lista {
	plan*** tablica;
	int wiersze, kolumny;
public:
	lista(int w, int k) : wiersze(w), kolumny(k){
		tablica = new plan ** [wiersze];
		for (int i = 0; i < wiersze; ++i) {
			tablica[i] = new plan * [kolumny];
			for (int j = 0; j < kolumny; ++j) {
				tablica[i][j] = new plan();
			}
		}
		
	}

	~lista() {
		for (int i = 0; i < wiersze; ++i) {
			for (int j = 0; j < kolumny; ++j)
				delete tablica[i][j];
			delete[] tablica[i];
		}
		delete[] tablica;
	}
};*/

class plan{	
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
		
		for (int j = 1; j < w; j+=5) {
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
				} else {
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
			//else { //tu s¹ minuty(co 15)
			//	tabela[i][0] = oss.str();
			//}
			m += 15;	
		}
	}

	void pokaz_plan() {
		std::cout << "Twoj plan lekcji:" << std::endl << std::endl;
		for (int x = 0; x < w; x++) {
			for (int y= 0; y < k; y++) {
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

	~plan() {};
};

class grupa {
	int numer;
	std::string* lista_uczniow = new std::string[20];

public:
	grupa(int numer) : numer(numer) {

	};

	~grupa() {};
};


class osoba {
	std::string imie, nazwisko;
public:
	osoba(const std::string imie, const std::string nazwisko) : imie(imie), nazwisko(nazwisko){

	}

	void inicjaly() {
		std::cout << std::endl;
		std::cout << "Imie: " << imie << std::endl << "Nazwisko: " << nazwisko << std::endl;
	}

	~osoba() {};
};

class uczen : public osoba{
	int numer_gr;
public:
	uczen(const std::string imie, const std::string nazwisko, int numer_gr) : osoba(imie, nazwisko), numer_gr(numer_gr) {
		
	}

	void pokaz_dane() {
		osoba::inicjaly();
		std::cout << "Grupa dziekanska: "<<numer_gr << std::endl;
	}


	~uczen() {};
};

class nauczyciel : public osoba {
	std::string przedmiot_prowadzony;
public:
	nauczyciel(const std::string imie, const std::string nazwisko, const std::string przedmiot_prowadzony) : osoba(imie, nazwisko), przedmiot_prowadzony(przedmiot_prowadzony){

	}

	void pokaz_dane() {
		osoba::inicjaly();
		std::cout << "Przedmiot prowadzony: " << przedmiot_prowadzony << std::endl;
	}

	~nauczyciel() {};
};

class sala {
	std::string typ; //wykladowa, laboratoiryjna, komputerowa, ogolna...
	char numer;
public:
	sala(std::string typ, char numer) : typ(typ), numer(numer) {

	}

	void pokaz_dane() {
		std::cout << "Numer sali: " << numer << std::endl;
		std::cout << "Typ sali: " << typ << std::endl;	
	}

	~sala() {};
};

class lekcja {
	std::string przedmiot, typ;
	int parzystosc; //0 nie wazne, 1 parzysty dzien, 2 nieparzysty
	sala* klasa;
	nauczyciel* prowadzacy;
public:
	lekcja(std::string przedmiot, std::string typ, int parzystosc, sala* nr, nauczyciel* n) : przedmiot(przedmiot), typ(typ), parzystosc(parzystosc), prowadzacy(n), klasa(nr){

	}

	void pokaz_dane() {
		std::cout << "-----------------" << std::endl;
		std::cout << przedmiot << ":" << std::endl << "Typ: "<< typ << std::endl;
		if (parzystosc == 0){
		std::cout<<"Co tydzien" << std::endl;
		}
		else if (parzystosc == 1) {
			std::cout << "Tylko parzyste tygodnie" << std::endl;
		}else if(parzystosc == 2) {
			std::cout << "Tylko nieparzyste tygodnie" << std::endl;
		}
		std::cout << "Prowadzacy: ";
		prowadzacy->pokaz_dane();
		klasa->pokaz_dane();
		std::cout <<"-----------------"<< std::endl;
	}
};


#endif
