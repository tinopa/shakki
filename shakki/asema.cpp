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
		// (asetetaan kaksoisaskel-lippu)

		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if (nappulaKoodi == VS || nappulaKoodi == MS) {
			//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
			////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		}
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		//else {
		_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
		_lauta[loppuSarakeInt][loppuRiviInt] = nappula;
		//}
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
	return 0;

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

	//1. Nappuloiden arvo

	//2. Kuningas turvassa

	//3. Arvosta keskustaa

	// 4. Arvosta linjoja

}


double Asema::laskeNappuloidenArvo(int vari)
{
	return 0;

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
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.

	// Rekursion kantatapaus 1: peli on loppu

	// Rekursion kantatapaus 2: katkaisusyvyydess‰

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;
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
	for (Siirto s : vastustajaSiirrotLista) {
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi())
			return true;
	}
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{

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
	annaLinnoitusSiirrot(lista, _siirtovuoro);

}
