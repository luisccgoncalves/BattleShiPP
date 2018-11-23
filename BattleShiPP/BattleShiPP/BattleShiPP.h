#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const vector<string> Comandos{ 
	"exec",
	"compranav",
	"vendenav",
	"lista",
	"compra",
	"vende",
	"move",
	"auto",
	"stop",
	"pirata",
	"evpos",
	"evnav",
	"moedas",
	"vaipara",
	"comprasold",
	"saveg",
	"loadg",
	"delg"
};

class Boat {
	//Esta classe pode ser melhorada com herança e polimorfismo
	int x, y;
	bool isAmigo;
	int tipo;	//sub-classe?
	int preco;
	int soldados;
	int agua;
	int peixe;
	int peixeMax;

public:

	Boat(int x, int y, bool isAmigo);

	int getX() const;
	int getY() const;


};

class Harbour {

	int x, y;
	bool isAmigo;
	bool isPrincipal;

public:

	Harbour(int x, int y, bool isAmigo);

	int getX() const;
	int getY() const;
	bool isFriend()const;
	bool &isMain();

};

class Land {

	int x, y;

public:

	Land(int x, int y);

	int getX() const;
	int getY() const;

};

class Sea {

	int x, y;
	int peixe;

public:

	Sea(int x, int y);

	int getX() const;
	int getY() const;
	int getPeixe() const;

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

	vector<Sea*> mar;
	vector<Land*> terra;
	vector<Harbour*> portos;
	vector<Boat*> barcos;

	void storeMapLine(istringstream &iss, int y);

public:

	bool addSeaCell(int x, int y);
	bool addLandCell(int x, int y);
	bool addHarbour(int x, int y, char c);
	bool load(string filename);
	void print(int xOffset, int yOffset);
	void updateMainHarbour();
};

void printBanner();
void intro();
void printInterface();
bool isCmdValid(string linha);

#endif
