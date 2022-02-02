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
	int i = 0;
	bool vapaaYlaOikea = true,
		 vapaaYlaVasen = true,
		 vapaaAlaOikea = true,
		 vapaaAlaVasen = true;
	Ruutu r;

	while (vapaaAlaOikea || vapaaAlaVasen || vapaaYlaOikea || vapaaYlaVasen) {

		if (vapaaYlaOikea) {
			//tarkistetaan seuraava ruutu yl‰viistossa oikealle
			r = Ruutu(ruutu->getSarake() + i, ruutu->getRivi() + i);
			if (r.getSarake() < 8 && r.getRivi() < 8) {
				if (asema->_lauta[r.getSarake()][r.getRivi()] == NULL) {
					//ruutu on tyhj‰ ja siihe voidaan siirty‰
					lista.push_back(Siirto(*ruutu, r));
				}
				else if (asema->_lauta[r.getSarake()][r.getRivi()] != NULL) {
					//ruudulla on toinen nappula
					if (asema->_lauta[r.getSarake()][r.getRivi()]->getVari() != vari) {
						//ruudulla on vastustajan nappula, siihen voidaan siirty‰
						lista.push_back(Siirto(*ruutu, r));
						vapaaYlaOikea = false;
					}
					else {
						//ruudulla on oma nappula, ei voi siirty‰
						vapaaYlaOikea = false;
					}
				}
			}
			else {
				//yritet‰‰n siirt‰‰ nappulaa laudan ulkopuolelle. ei onnistu
				vapaaYlaOikea = false;
			}
		}

		if (vapaaYlaVasen) {
			//tarkistetaan seuraava ruutu yl‰viistossa vasemmalle
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
						vapaaYlaOikea = false;
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
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
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
		if (asema->_lauta[r.getSarake() + 1][r.getRivi()] != NULL && asema->_lauta[r.getSarake() + 1][r.getRivi()]->getVari() != vari)
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
