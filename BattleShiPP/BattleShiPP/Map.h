#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <sstream>

using namespace std;

#include "Cell.h"

class Map {

	int lin, col;
	int moedas;
	int probpirata;
	int preconavio;
	int precosoldado;
	int precovendpeixe;
	int precocompmercad;
	int precovendmercad;
	int soldadosporto;
	int probevento;
	int probtempestade;
	int probsereias;
	int prombotim;

	vector<vector<Cell*>> mapa;
	static const vector<string> direccao;

public:

	enum heading {
		D,
		E,
		C,
		B,
		CE,
		CD,
		BE,
		BD
	};

	Harbour*	getMainHarbour();

	Cell*	getCell(int x, int y) const;
	int		getLin() const;
	int		getCol() const;

	bool	load(string filename);

	bool	setMoedas(int incdec);
	bool	buyBoat(string boatType);
};
#endif