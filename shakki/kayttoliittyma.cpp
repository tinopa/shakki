#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	SetConsoleOutputCP(65001);

	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 7) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8;
			}
			if (j == 0 && i == 6) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 7;
			}
			if (j == 0 && i == 5) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 6;
			}
			if (j == 0 && i == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 5;
			}
			if (j == 0 && i == 3) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 4;
			}
			if (j == 0 && i == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 3;
			}
			if (j == 0 && i == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 2;
			}
			if (j == 0 && i == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 1;
			}
			if (i % 2 != 0){
				if (j % 2 == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED);
			}
			else {
				if (j % 2 != 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED);
			}

			if (_asema->_lauta[j][i] != NULL) {
				wcout << " " << _asema->_lauta[j][i]->getUnicode() << " ";
			}
			else {
				wcout << "   ";
			}			
		}
		wcout << "\n";
	}
	wcout << " " << " a " << " b " << " c " << " d " << " e " << " f " << " g " << " h \n";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	int lahtoX, lahtoY, tuloX, tuloY;
	wstring siirtoS;
	wstring siirtynytNappulaS;
	do {
		wcout << "Anna vastustajan siirto esim. Rg1-f3, linnoitus 0-0 tai 0-0-0\n";
		wcin >> siirtoS;

		if (siirtoS == L"0-0") {
			return Siirto(true, false);
		}
		else if (siirtoS == L"0-0-0") {
			return Siirto(false, true);
		}
		else if (siirtoS.length() == 6) {	//jos siirron ensimmäinen merkki on nappulan kirjain, karsitaan se pois
			siirtynytNappulaS = siirtoS[0];
			siirtoS.erase(0, 1);
		}
		else {
			siirtynytNappulaS = L"s";
		}
		lahtoX = siirtoS[0] - 'a';
		lahtoY = _wtoi(&siirtoS[1]) - 1;
		tuloX = siirtoS[3] - 'a';
		tuloY = _wtoi(&siirtoS[4]) - 1;

		if (((lahtoX < 0 || lahtoX > 7) || (lahtoY < 0 || lahtoX > 7) || (tuloX < 0 || tuloX > 7) || (tuloY < 0 || tuloY > 7)))
			wcout << "siirron täytyy olla muotoa esim. Rf1-f3, \n aakkoset väliltä a-h\n numerot väliltä 1-8\n Nappula on (K,k),(D,d),(R,r),(L,l)\n sotilas jätetään merkitsemättä\n";
		
	} while (((lahtoX < 0 || lahtoX > 7) || (lahtoY < 0 || lahtoX > 7) || (tuloX < 0 || tuloX > 7) || (tuloY < 0 || tuloY > 7)));

	Ruutu alkuRuutu(lahtoX, lahtoY);
	Ruutu loppuRuutu(tuloX, tuloY);

	return Siirto(alkuRuutu, loppuRuutu);
	
}

int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
