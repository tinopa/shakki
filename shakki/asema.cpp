#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = NULL;
		}
	}
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;
	for (int i = 0; i < 8; i++)
		_lauta[i][1] = vs;

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;
	for (int i = 0; i < 8; i++)
		_lauta[i][6] = ms;

	//alustetaan kaikki booleanit
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;

	_siirtovuoro = 0;
}


void Asema::paivitaAsema(Siirto* siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL;
			_lauta[6][0] = vk;
			_lauta[7][0] = NULL;
			_lauta[5][0] = vt;
		}
		else if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL;
			_lauta[6][7] = mk;
			_lauta[7][7] = NULL;
			_lauta[5][7] = mt;
		}
	}

	// onko pitk‰ linna
	else if (siirto->onkoPitk‰linna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL;
			_lauta[2][0] = vk;
			_lauta[0][0] = NULL;
			_lauta[3][0] = vt;
		}
		else if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL;
			_lauta[2][7] = mk;
			_lauta[0][7] = NULL;
			_lauta[3][7] = mt;
		}
	}


	// Kaikki muut siirrot
	else {
		int alkuRiviInt, alkuSarakeInt, loppuRiviInt, loppuSarakeInt;

		//Ottaa siirron alkuruudussa olleen nappulan talteen 
		alkuRiviInt = siirto->getAlkuruutu().getRivi();
		alkuSarakeInt = siirto->getAlkuruutu().getSarake();

		Nappula* nappula = _lauta[alkuSarakeInt][alkuRiviInt];
		int nappulaKoodi = nappula->getKoodi();

		//Laittaa talteen otetun nappulan uuteen ruutuun
		loppuRiviInt = siirto->getLoppuruutu().getRivi();
		loppuSarakeInt = siirto->getLoppuruutu().getSarake();

		// Tarkistetaan oliko sotilaan kaksoisaskel
		if ((nappulaKoodi == VS || nappulaKoodi == MS) &&
			(alkuRiviInt - loppuRiviInt == 2 || alkuRiviInt - loppuRiviInt == -2))

			kaksoisaskelSarakkeella = alkuSarakeInt;
		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if 
		(
			nappulaKoodi == VS || nappulaKoodi == MS && (alkuSarakeInt != loppuSarakeInt) 
			&& (_lauta[loppuSarakeInt][loppuRiviInt] == NULL) 
			&& _lauta[loppuSarakeInt][alkuRiviInt]->getVari() != nappula->getVari()
		)
			_lauta[loppuSarakeInt][alkuRiviInt] = NULL;

		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		//else {
		_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		_lauta[loppuSarakeInt][loppuRiviInt] = nappula;
		//}
		if (siirto->_miksikorotetaan != NULL)
			_lauta[loppuRiviInt][loppuSarakeInt] = siirto->_miksikorotetaan;

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappulaKoodi == VK)
			_onkoValkeaKuningasLiikkunut = true;
		else if (nappulaKoodi == MK)
			_onkoMustaKuningasLiikkunut = true;

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		else if (nappulaKoodi == VT) {
			if (siirto->getAlkuruutu().getSarake() == 0) //daamin puoleinen valkoinen torni liikkunut
				_onkoValkeaDTliikkunut = true;
			else if (siirto->getAlkuruutu().getSarake() == 7) //kuninkaan puoleinen valkoinen torni liikkunut
				_onkoValkeaKTliikkunut = true;
		}
		else if (nappulaKoodi == MT) {
			if (siirto->getAlkuruutu().getSarake() == 0) //daamin puoleinen musta torni liikkunut
				_onkoMustaDTliikkunut = true;
			else if (siirto->getAlkuruutu().getSarake() == 7) //kuninkaan puoleinen musta torni liikkunut
				_onkoMustaKTliikkunut = true;
		}
	}
	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0)
		_siirtovuoro = 1;
	else
		_siirtovuoro = 0;
}



int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro)
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi()
{

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

	//1. Nappuloiden arvo
	//positiiviset arvot tarkoittavat sit‰, ett‰ valkoisilla on etu. Neg. arvot tarkoittavat, ett‰ mustalla on etu
	double arvojenErotus = laskeNappuloidenArvo(0) - laskeNappuloidenArvo(1);

	//2. Kuningas turvassa

	//3. Arvosta keskustaa

	// 4. Arvosta linjoja


	return arvojenErotus * 1; //t‰h‰n voi tulevaisuudessa lis‰t‰ muiden vaiheiden tuloksia ja muuttaa kertoimia
}


double Asema::laskeNappuloidenArvo(int vari)
{
	double arvoSumma = 0;

	const double daami	= 9;
	const double torni = 5;
	const double lahetti = 3.25;
	const double ratsu = 3;
	const double sotilas = 1;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_lauta[i][j] != NULL && _lauta[i][j]->getVari() == vari) {
				switch (_lauta[i][j]->getKoodi()){

				case VT:
				case MT:
					arvoSumma += torni;
					break;
				case VR:
				case MR:
					arvoSumma += ratsu;
					break;
				case VL:
				case ML:
					arvoSumma += lahetti;
					break;
				case VD:
				case MD:
					arvoSumma += daami;
					break;
				case VS:
				case MS:
					arvoSumma += sotilas;
					break;
				}
			}
		}
	}

	return arvoSumma;
}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double Asema::nappuloitaKeskella(int vari)
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa

	//valkeille ydinkeskusta



	//valkeille laitakeskusta



	//mustille ydinkeskusta

	//mustille laitakeskusta

}


double Asema::linjat(int vari)
{
	return 0;

	//valkoiset

	//mustat

}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	//turha funktio ainakin toistaiseksi
	MinMaxPaluu paluuarvo;

	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);

	if (siirrot.size() == 0)
	{
		paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}

	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? INT_MIN : INT_MAX);
	for (auto s : siirrot)
	{
		Asema uusi_asema = *this;
		uusi_asema.paivitaAsema(&s);

		MinMaxPaluu arvo = uusi_asema.minimax(syvyys - 1);

		if
			((_siirtovuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo) ||
				(_siirtovuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo))
		{
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = arvo._parasSiirto;
		}
	}
	return paluuarvo;
}

MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	std::list<Siirto> lista;
	this->annaLaillisetSiirrot(lista);
	Ruutu kuningas;

	
	if (lista.size() == 0) {
		//matti tai patti
		//etsit‰‰n kuningas
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (_lauta[i][j] == NULL)
					continue;
				if (_lauta[i][j]->getKoodi() == VK) {
					kuningas.setSarake(i);
					kuningas.setRivi(j);
					break;
				}
			}
		}

		//matti
		if (!this->onkoRuutuUhattu(&kuningas, 1)) {
			paluu._evaluointiArvo = -100000;
			return paluu;
		}
		//patti
		if (this->onkoRuutuUhattu(&kuningas, 1)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}

	//kantatapaus
	if (syvyys == 0) {
		paluu._evaluointiArvo = this->evaluoi();
		return paluu;
	}

	double max = -100000;
	Siirto parasSiirto;

	for (Siirto s : lista) {
		Asema uusiAsema = *this;
		uusiAsema.paivitaAsema(&s);
		double evArvo = uusiAsema.mini(syvyys - 1)._evaluointiArvo;

		if (evArvo > max) {
			max = evArvo;
			parasSiirto = s;
		}
	}
	paluu._evaluointiArvo = max;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;
	std::list<Siirto> lista;
	this->annaLaillisetSiirrot(lista);
	Ruutu kuningas;


	if (lista.size() == 0) {
		//matti tai patti
		//etsit‰‰n kuningas
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (_lauta[i][j] == NULL)
					continue;
				if (_lauta[i][j]->getKoodi() == MK) {
					kuningas.setSarake(i);
					kuningas.setRivi(j);
					break;
				}
			}
		}

		//matti
		if (!this->onkoRuutuUhattu(&kuningas, 0)) {
			paluu._evaluointiArvo = 100000;
			return paluu;
		}
		//patti
		if (this->onkoRuutuUhattu(&kuningas, 0)) {
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}

	//kantatapaus
	if (syvyys == 0) {
		paluu._evaluointiArvo = this->evaluoi();
		return paluu;
	}

	double min = 100000;
	Siirto parasSiirto;

	for (Siirto s : lista) {
		Asema uusiAsema = *this;
		uusiAsema.paivitaAsema(&s);
		double evArvo = uusiAsema.maxi(syvyys - 1)._evaluointiArvo;

		if (evArvo < min) {
			min = evArvo;
			parasSiirto = s;
		}
	}
	paluu._evaluointiArvo = min;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::list<Siirto> vastustajaSiirrotLista;
	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL)
				continue;
			if (this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), this, vastustajanVari);
		}
	}
	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	for (auto s : vastustajaSiirrotLista) {
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi())
			return true;
	}
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{
	int kX, kY; //kuninkaan koodinaatit
	int vastustajanVari;

	if (vari == 0) {
		vastustajanVari = 1;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (_lauta[i][j] == NULL)
					continue;
				if (_lauta[i][j]->getKoodi() == VK) {
					kX = i;
					kY = j;
					break;
				}
			}
		}
	}
	else {
		vastustajanVari = 0;
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++) {
				if (_lauta[i][j] == NULL)
					continue;
				if (_lauta[i][j]->getKoodi() == MK) {
					kX = i;
					kY = j;
					break;
				}
			}
		}
	}
	

	//1. versio ei toimi, koska lista.remove(s) ei toimi ilma == overloadausta
	//for (Siirto s : lista) {
	//	if (s.getAlkuruutu().getSarake() == kX && s.getAlkuruutu().getRivi() == kY) {
	//		//siirrossa siirret‰‰n kuningasta
	//		Asema temp = *this;									//otetaan asemasta kopio
	//		std::list<Siirto> vastustajaSiirtoLista;
	//		temp.paivitaAsema(&s);								//tehd‰‰n siirto kopioasemassa
	//		temp.annaLaillisetSiirrot(vastustajaSiirtoLista);	//otetaan vastustajan uudet siirrot talteen kopioasemasta
	//		for (Siirto vs : vastustajaSiirtoLista)				//k‰yd‰‰n kaikki vastustajan siirrot l‰pi
	//			if (vs.getLoppuruutu().getSarake() == s.getLoppuruutu().getSarake() && vs.getLoppuruutu().getRivi() == s.getLoppuruutu().getRivi())
	//				lista.remove(s);							//jos mik‰‰n vastustajan siirron loppuruutu on sama, kuin kuninkaan siirron loppuruutu,
	//	}														//poistetaan se laillisten siirtojen listasta
	//}

	//2. versio tuntivideosta
	Asema testiAsema;
	std::list<Siirto> siivottuSiirrotLista;
	for (auto s : lista) {
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int x, y;

		//kuninkaan siirto?
		if (s.onkoLyhytLinna()) {
			x = 6;
			if (this->_siirtovuoro == 0)
				y = 0;
			else
				y = 7;
		}
		else if(s.onkoPitk‰linna()){
			x = 2;
			if (this->_siirtovuoro == 0)
				y = 0;
			else
				y = 7;
		}
		else {
			Nappula* siirtyva = this->_lauta[s.getAlkuruutu().getSarake()][s.getAlkuruutu().getRivi()];
			if (siirtyva->getKoodi() == VK || siirtyva->getKoodi() == MK) {
				x = s.getLoppuruutu().getSarake();
				y = s.getLoppuruutu().getRivi();
			}
			else {
				//Ei ole, kuninkaan sijainti sama kuin ennen siirron s kokeilua
				x = kX;
				y = kY;
			}
		}

		//huom !vari
		if (!testiAsema.onkoRuutuUhattu(&Ruutu(x, y), vastustajanVari))
			siivottuSiirrotLista.push_back(s);

	}
	lista = siivottuSiirrotLista;
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari) {
	if (vari == 0) {
		if (!_onkoValkeaKuningasLiikkunut && !onkoRuutuUhattu(&Ruutu(4, 0), 1)) {
			//valkea kuningas ei ole liikkunut eik‰ ole shakissa

			//pitk‰ linna
			if (!_onkoValkeaDTliikkunut)
				if (_lauta[1][0] == NULL && _lauta[2][0] == NULL && _lauta[3][0] == NULL)
					if (!onkoRuutuUhattu(&Ruutu(2, 0), 1) && !onkoRuutuUhattu(&Ruutu(3, 0), 1))
						lista.push_back(Siirto(false, true));

			//lyhyt linna
			if (!_onkoValkeaKTliikkunut)
				if (_lauta[5][0] == NULL && _lauta[6][0] == NULL)
					if (!onkoRuutuUhattu(&Ruutu(5, 0), 1) && !onkoRuutuUhattu(&Ruutu(6, 0), 1))
						lista.push_back(Siirto(true, false));
		}
	}
	else {
		if (!_onkoMustaKuningasLiikkunut && !onkoRuutuUhattu(&Ruutu(4, 7), 0)) {
			//musta kuningas ei ole liikkunut eik‰ ole shakissa

			//pitk‰ linna
			if (!_onkoMustaDTliikkunut)
				if (_lauta[1][0] == NULL && _lauta[2][7] == NULL && _lauta[3][7] == NULL)
					if (!onkoRuutuUhattu(&Ruutu(2, 7), 0) && !onkoRuutuUhattu(&Ruutu(3, 7), 0))
						lista.push_back(Siirto(false, true));

			//lyhyt linna
			if (!_onkoMustaKTliikkunut)
				if (_lauta[5][0] == NULL && _lauta[6][7] == NULL)
					if (!onkoRuutuUhattu(&Ruutu(5, 7), 0) && !onkoRuutuUhattu(&Ruutu(6, 7), 0))
						lista.push_back(Siirto(true, false));
		}
	}
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	//raakasiirrot
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] != NULL && this->_lauta[i][j]->getVari() == _siirtovuoro)
				this->_lauta[i][j]->annaSiirrot(lista, &Ruutu(i, j), this, _siirtovuoro);
		}
	}
	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
	annaLinnoitusSiirrot(lista, _siirtovuoro);

}
