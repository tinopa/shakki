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
	Aliohjelma tarkistaa ett? k?ytt?j?n antama sy?te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my?s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett? kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto(std::list<Siirto>& lista)
{
	int lahtoX, lahtoY, tuloX, tuloY;
	wstring siirtoS;
	wstring siirtynytNappulaS;
	do {
		wcout << "Anna siirto esim. Rg1-f3 (tai vain g1-f3), linnoitus 0-0 tai 0-0-0\n";
		wcin >> siirtoS;

		if (siirtoS == L"0-0") {
			return Siirto(true, false);
		}
		else if (siirtoS == L"0-0-0") {
			return Siirto(false, true);
		}
		else if (siirtoS.length() == 6) {	//jos siirron ensimm?inen merkki on nappulan kirjain, karsitaan se pois
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

		if ((lahtoX < 0 || lahtoX > 7) || (lahtoY < 0 || lahtoX > 7) || (tuloX < 0 || tuloX > 7) || (tuloY < 0 || tuloY > 7))
			wcout << "siirron t?ytyy olla muotoa esim. Rf1-f3, \n aakkoset v?lilt? a-h\n numerot v?lilt? 1-8\n Nappula on (K,k),(D,d),(R,r),(L,l)\n sotilas j?tet??n merkitsem?tt?\n";
		else if (!onkoSiirtoLaillinen(lahtoX, lahtoY, tuloX, tuloY, lista))
			wcout << "siirron pit?? olla laillinen\n";
		
	} while (((lahtoX < 0 || lahtoX > 7) || (lahtoY < 0 || lahtoX > 7) || (tuloX < 0 || tuloX > 7) || (tuloY < 0 || tuloY > 7)) || !onkoSiirtoLaillinen(lahtoX, lahtoY, tuloX, tuloY, lista));

	Ruutu alkuRuutu(lahtoX, lahtoY);
	Ruutu loppuRuutu(tuloX, tuloY);
	Siirto siirto(alkuRuutu, loppuRuutu);
	Nappula* siirrettava = _asema->_lauta[lahtoX][lahtoY];

	if (siirrettava != NULL && siirrettava->getKoodi() == VS && siirto.getLoppuruutu().getRivi() == 7)
	{
		while (true)
		{
			std::wcout << "Miksi nappulaksi haluat korottaa? (esim. D)\n";
			std::wstring vastaus;
			std::wcin >> vastaus;
			if (vastaus == L"D" || vastaus == L"d") siirto._miksikorotetaan = Asema::vd;
			else if (vastaus == L"T" || vastaus == L"t") siirto._miksikorotetaan = Asema::vt;
			else if (vastaus == L"L" || vastaus == L"l") siirto._miksikorotetaan = Asema::vl;
			else if (vastaus == L"R" || vastaus == L"r") siirto._miksikorotetaan = Asema::vr;
			else continue;

			break;
		}
	}
	else if (siirrettava != NULL && siirrettava->getKoodi() == MS && siirto.getLoppuruutu().getRivi() == 0)
	{
		while (true)
		{
			std::wcout << "Miksi nappulaksi haluat korottaa? (esim. D)\n";
			std::wstring vastaus;
			std::wcin >> vastaus;
			if (vastaus == L"D" || vastaus == L"d") siirto._miksikorotetaan = Asema::md;
			else if (vastaus == L"T" || vastaus == L"t") siirto._miksikorotetaan = Asema::mt;
			else if (vastaus == L"L" || vastaus == L"l") siirto._miksikorotetaan = Asema::ml;
			else if (vastaus == L"R" || vastaus == L"r") siirto._miksikorotetaan = Asema::mr;
			else continue;

			break;
		}
	}

	return siirto;
}

int Kayttoliittyma::kysyVastustajanVari()
{
	int vari;
	wcout << "valkoiset vai mustat (0 tai 1)\n";
	cin >> vari;
	return vari;
}

bool Kayttoliittyma::onkoSiirtoLaillinen(int lahtoX, int lahtoY, int tuloX, int tuloY, std::list<Siirto>& lista) {
	for (Siirto s : lista) {
		if (s.getAlkuruutu().getSarake() == lahtoX && s.getAlkuruutu().getRivi() == lahtoY && s.getLoppuruutu().getSarake() == tuloX && s.getLoppuruutu().getRivi() == tuloY)
			return true;
	}
	return false;
}
