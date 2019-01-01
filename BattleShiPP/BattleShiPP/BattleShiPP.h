#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>

#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <ctime>

#include "Cell.h"

using namespace std;

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

	enum heading{
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

class UI {

	static const string banner;
	static const vector<string> comandos;
	static const vector<char> boatType;

	int xOffset = 1;
	int yOffset = 1;

	bool isNum(string num);
public:

	UI();

	void	intro();
	void	printInterface(const Map &mapa);
	void	updateInterface();
	void	updateInterface(const Map &mapa);
	bool	isCmdValid(string linha);
	int		getComandosPos(string cmd);
	void	execCMD(Map &mapa, stringstream &cmdlist);
	void	processCMD(stringstream &buffer, const string &linha);
	void	resetPrompt();
	void	resetLastCmd();
	void	compraNav(Map &mapa, string cmd);
	void	printMap(const Map &printThis);

};
#endif
