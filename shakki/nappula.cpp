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
	int lahtoruutuY = ruutu->getRivi(), lahtoruutuX = ruutu->getSarake(), lahtoruudunNappulanVari, tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	for (int i = lahtoruutuX + 1; i < 8; i++) {
		if (asema->_lauta[i][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
		}
		else if (asema->_lauta[i][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[i][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
				break;
			}
		}
	}
	for (int i = lahtoruutuX - 1; i >= 0; i--) {
		if (asema->_lauta[i][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
		}
		else if (asema->_lauta[i][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[i][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
				break;
			}
		}
	}
	for (int i = lahtoruutuY + 1; i < 8; i++) {
		if (asema->_lauta[lahtoruutuX][i] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
		}
		else if (asema->_lauta[lahtoruutuX][i] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][i]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
				break;
			}
		}
	}
	for (int i = lahtoruutuY - 1; i >= 0; i--) {
		if (asema->_lauta[lahtoruutuX][i] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
		}
		else if (asema->_lauta[lahtoruutuX][i] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][i]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
				break;
			}
		}
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi(), lahtoruutuX = ruutu->getSarake(), lahtoruudunNappulanVari, tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 2 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 2]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 2 >= 0) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 2]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 2 < 8) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 2]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 2 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 2]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 2][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 2][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 2][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 2][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
			}
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int i = 1;
	bool vapaaYlaOikea = true,
		 vapaaYlaVasen = true,
		 vapaaAlaOikea = true,
		 vapaaAlaVasen = true;
	Ruutu r;

	while (vapaaAlaOikea || vapaaAlaVasen || vapaaYlaOikea || vapaaYlaVasen) {

		if (vapaaYlaOikea) {
			//tarkistetaan seuraava ruutu yläviistossa oikealle
			r = Ruutu(ruutu->getSarake() + i, ruutu->getRivi() + i);
			if (r.getSarake() < 8 && r.getRivi() < 8) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
					//ruutu on tyhjä ja siihe voidaan siirtyä
					lista.push_back(Siirto(*ruutu, r));
				}
				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					//ruudulla on toinen nappula
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						//ruudulla on vastustajan nappula, siihen voidaan siirtyä
						lista.push_back(Siirto(*ruutu, r));
						vapaaYlaOikea = false;
					}
					else {
						//ruudulla on oma nappula, ei voi siirtyä
						vapaaYlaOikea = false;
					}
				}
			}
			else {
				//yritetään siirtää nappulaa laudan ulkopuolelle. ei onnistu
				vapaaYlaOikea = false;
			}
		}

		if (vapaaYlaVasen) {
			//tarkistetaan seuraava ruutu yläviistossa vasemmalle
			r = Ruutu(ruutu->getSarake() - i, ruutu->getRivi() + i);
			if (r.getSarake() > -1 && r.getRivi() < 8) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL)
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						lista.push_back(Siirto(*ruutu, r));
						vapaaYlaVasen = false;
					}
					else
						vapaaYlaVasen = false;
				}
			}
			else
				vapaaYlaVasen = false;
		}

		if (vapaaAlaOikea) {
			//tarkistetaan seuraava ruutu alaviistosssa oikealle
			r = Ruutu(ruutu->getSarake() + i, ruutu->getRivi() - i);
			if (r.getSarake() < 8 && r.getRivi() > - 1) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL)
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						lista.push_back(Siirto(*ruutu, r));
						vapaaAlaOikea = false;
					}
					else
						vapaaAlaOikea = false;
				}
			}
			else
				vapaaAlaOikea = false;
		}

		if (vapaaAlaVasen) {
			//tarkistetaan seuraava ruutu alaviistossa vasemmalle
			r = Ruutu(ruutu->getSarake() - i, ruutu->getRivi() - i);
			if (r.getSarake() > -1 && r.getRivi() > -1) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL)
					lista.push_back(Siirto(*ruutu, r));

				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						lista.push_back(Siirto(*ruutu, r));
						vapaaAlaVasen = false;
					}
					else
						vapaaAlaVasen = false;
				}
			}
			else
				vapaaAlaVasen = false;
		}
		i++;
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	this->Torni::annaSiirrot(lista, ruutu, asema, vari);
	this->Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi(), lahtoruutuX = ruutu->getSarake(), lahtoruudunNappulanVari, tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	if (lahtoruutuX + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));
		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));
			}
		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

		}
		else if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));
			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
			}
		}
	}

	if (lahtoruutuY + 1 < 8) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
		}
		else if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
			}
		}
	}

	if (lahtoruutuY - 1 >= 0) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
		}
		else if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
			}
		}
	}
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Ruutu r;
	if (vari == 0) {
		//valkoisen sotilaan siirrot
		r = Ruutu(ruutu->getSarake(), ruutu->getRivi() + 1);
		if (r.getRivi() < 8) {
			//1 ruutu eteenpäin
			if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
				lista.push_back(Siirto(*ruutu, r));
				//katsontaan onko mahdollista mennä kaksi ruutua eteenpäin
				if (ruutu->getRivi() == 1 && asema->_lauta[r.getSarake()][r.getRivi() + 1] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake(), r.getRivi() + 1)));
			}
			//katsotaan onko edessä oikealla vastustajan nappulaa. Tarkistaa ensin onko oikealla lautaa jäljellä
			if (r.getSarake() + 1 < 8 && asema->_lauta[r.getSarake() + 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() + 1][r.getRivi()]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() + 1, r.getRivi())));
			//katsontaan onko edessä vasemmalla vastustajan palikkaa. Tarkistaa ensin onko vasemmalla lautaa jäljellä
			if (r.getSarake() - 1 >= 0 && asema->_lauta[r.getSarake() - 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() - 1][r.getRivi()]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() - 1, r.getRivi())));
		}
		if(r.getRivi() == 8) {
			lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(r.getSarake(), r.getRivi())), lista, asema);
		}
	}
	else {
		//mustan sotilaan siirrot
		r = Ruutu(ruutu->getSarake(), ruutu->getRivi() - 1); //ruutu johon yritetään liikkua
		if (r.getRivi() > -1) {
			//1 ruutu eteenpäin
			if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
				lista.push_back(Siirto(*ruutu, r));
				//katsontaan onko mahdollista mennä kaksi ruutua eteenpäin
				if (ruutu->getRivi() == 6 && asema->_lauta[r.getSarake()][r.getRivi() - 1] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake(), r.getRivi() - 1)));
			}
			//katsotaan onko edessä oikealla vastustajan nappulaa
			if (r.getSarake() + 1 < 8 && asema->_lauta[r.getSarake() + 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() + 1][r.getRivi()]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() + 1, r.getRivi())));
			//katsontaan onko edessä vasemmalla vastustajan palikkaa
			if (r.getSarake() - 1 >= 0 && asema->_lauta[r.getSarake() - 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() - 1][r.getRivi()]->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(r.getSarake() - 1, r.getRivi())));
		}
		if (r.getRivi() == 0) {
			lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(r.getSarake(), r.getRivi())), lista, asema);
		}
	}
	
	if (asema->kaksoisaskelSarakkeella != -1 && abs(asema->kaksoisaskelSarakkeella - ruutu->getSarake()) == 1)
	{
		if (vari == 0 && ruutu->getRivi() == 4)
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][4] && asema->_lauta[asema->kaksoisaskelSarakkeella][4]->getKoodi() == MS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 5)));
		if (vari == 1 && ruutu->getRivi() == 3)
			if (asema->_lauta[asema->kaksoisaskelSarakkeella][3] && asema->_lauta[asema->kaksoisaskelSarakkeella][3]->getKoodi() == VS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 2)));
	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	// valkea korottaa
	if (siirto->getLoppuruutu().getRivi() == 7) {
		siirto->_miksikorotetaan = asema->vd;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->vt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->vl;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->vr;
		lista.push_back(ratsuksi);
	}
	// musta korottaa
	else if (siirto->getLoppuruutu().getRivi() == 0) {
		siirto->_miksikorotetaan = asema->md;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->mt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->ml;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->mr;
		lista.push_back(ratsuksi);
	}
}
