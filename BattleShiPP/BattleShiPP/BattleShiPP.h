#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"

using namespace std;

static const vector<char> boatType{
	'V',			//0 - Veleiro
	'G',			//1 - Gale�o
	'E',			//2 - Escuna
	'F'				//3 - Fragata
};

enum class Direction {
	North=0,
	East,
	South,
	West,
	ENUM_SIZE
};

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


public:

	Harbour		getMainHarbour();

	Cell*	getCell(int x, int y) const;
	int		getLin() const;
	int		getCol() const;

	bool	load(string filename);
	void	updateMainHarbour();
};



class UI {

	static const string banner;
	static const vector<string> comandos;

	int xOffset = 1;
	int yOffset = 1;

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
