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

class plan {	
	int w = 44;
	int k = 9;
	std::string p[44][9];
public:
	plan() { //tworzy szkielet planu
		p[0][0] = "Lp.";
		p[0][1] = "Godz.";
		p[0][2] = "Poniedzialek";
		p[0][3] = "Wtorek";
		p[0][4] = "Sroda";
		p[0][5] = "Czwartek";
		p[0][6] = "Piatek";
		p[0][7] = "Sobota";
		p[0][8] = "Niedziela";
		for (int i = 1; i <= 43; i++) {
			p[i][0] = std::to_string(i);
		}
		int h = 8;
		int m = 00;

		for (int i = 1; i <= 43; i++) {
			if (m == 60) {
				h++;
				m = 00;
			}
			
			std::stringstream oss;
			oss << std::setw(2) << std::setfill('0') << h << ":" << std::setw(2) << std::setfill('0') << m;
			
			if (m == 00) {
				p[i][1] = oss.str();
			}
			else {
				p[i][1] = oss.str();
			}
			m += 15;	
		}
	}

	void pokaz() {
		for (int x = 0; x < w; x++) {
			for (int y= 0; y < k; y++) {
				std::cout << std::setw(15) << std::left << p[x][y];
				if (y == k-1) {
					std::cout << std::endl;
				}
			}
		}
			
	}

	~plan() {
		std::cout << "Plan zosta³ usuniêty" << std::endl;
	}
};

class nauczyciel {
	std::string imie, nazwisko, przedmiot_prowadzony;
};

class klasa {
	std::string typ;
	char numer;
};

class lekcja {
	std::string przedmiot, nauczyciel, klasa, dzien;
	int klasa, lp;

public:
	lekcja(std::string przedmiot, std::string nauczyciel, int klasa, int lp, std::string dzien) {

	}
};


#endif
