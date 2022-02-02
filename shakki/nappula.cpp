#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int i = 0;
	bool vapaaPosX = true,	//miss‰ suunnissa on vapaita ruutuja
		 vapaaNegX = true, 
		 vapaaPosY = true, 
		 vapaaNegY = true;	
	Ruutu r;				//ruutu johon yritet‰‰n menn‰

	while (vapaaPosX || vapaaNegX || vapaaPosY || vapaaNegY) {
		//k‰yt‰nnˆss‰ samaa koodiaa nelj‰‰n kertaan, vois varmaa teh‰ funktioillaki jos keksii miten sen nyt asettelee
		//muuttuu Ruutu r konstruktori, ensimm‰inen if lause ja elset

		if (vapaaPosX) {	//tarkistetaan seuraava ruutu oikealta puolelta
			r = Ruutu(ruutu->getSarake() + i, ruutu->getRivi());
			if (r.getSarake() < 8) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
					//ruutu on tyhj‰ ja siihe voidaan siirty‰
					lista.push_back(Siirto(*ruutu, r));
				}
				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					//ruudulla on toinen nappula
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						//ruudulla on vastustajan nappula, siihen voidaan siirty‰
						lista.push_back(Siirto(*ruutu, r));
					}
					else {
						//ruudulla on oma nappula, ei voi siirty‰
						vapaaPosX = false;
					}
				}
			}
			else {
				//yritet‰‰n siirt‰‰ nappulaa laudan ulkopuolelle. ei onnistu
				vapaaPosX = false;
			}
		}

		if (vapaaNegX) {	//tarkistetaan seuraava ruutu vasemmalta puolelta
			r = Ruutu(ruutu->getSarake() - i, ruutu->getRivi());
			if (r.getSarake() > -1) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) 
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari)
						lista.push_back(Siirto(*ruutu, r));
					else
						vapaaNegX = false;
				}
			}
			else
				vapaaNegX = false;
		}

		if (vapaaPosY) {	//tarkistetaan seuraava ruutu yl‰puolelta
			r = Ruutu(ruutu->getSarake(), ruutu->getRivi() + i);
			if (r.getRivi() < 8) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL)
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) 
						lista.push_back(Siirto(*ruutu, r));
					else
						vapaaPosY = false;
				}
			}
			else
				vapaaPosY = false;
		}

		if (vapaaNegY) {	//tarkistetaan seuraava ruutu alapuolelta
			r = Ruutu(ruutu->getSarake(), ruutu->getRivi() - i);
			if (r.getRivi() > -1) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL)
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari)
						lista.push_back(Siirto(*ruutu, r));
					else
						vapaaNegY = false;
				}
			}
			else
				vapaaNegY = false;
		}
		i++;
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett‰ kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l‰hetill‰,
	oman nappulan p‰‰lle ei voi menn‰ ja vastustajan nappulan voi syˆd‰.

	Kaikki muu kuninkaaseen liittyv‰ tarkistus tehd‰‰n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Ruutu r = Ruutu(ruutu->getSarake(), ruutu->getRivi() + 1); //ruutu johon yritet‰‰n liikkua
	if (r.getRivi() < 8) {
		//1 ruutu eteenp‰in
		if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
			lista.push_back(Siirto(*ruutu, r));
		}
		//katsontaan onko mahdollista menn‰ kaksi ruutua eteenp‰in
		if (ruutu->getRivi() == 1 && asema->_lauta[r.getSarake()][r.getRivi() + 1] == NULL)
				lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake(), r.getRivi() + 1)));
		//katsotaan onko edess‰ oikealla vastustajan nappulaa
		if(asema->_lauta[r.getSarake() + 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() + 1][r.getRivi()]->getVari() != vari)
			lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() + 1, r.getRivi())));
		//katsontaan onko edess‰ vasemmalla vastustajan palikkaa
		if (asema->_lauta[r.getSarake() - 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() - 1][r.getRivi()]->getVari() != vari)
			lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() - 1, r.getRivi())));
	}
	else {
		//korotus
	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
