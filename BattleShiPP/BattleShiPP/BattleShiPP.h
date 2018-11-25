#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const vector<string> Comandos{ 
	"exec",			//0
	"compranav",	//1
	"vendenav",		//2
	"lista",		//3
	"compra",		//4
	"vende",		//5
	"move",			//6
	"auto",			//7
	"stop",			//8
	"pirata",		//9
	"evpos",		//10
	"evnav",		//11
	"moedas",		//12
	"vaipara",		//13
	"comprasold",	//14
	"saveg",		//15
	"loadg",		//16
	"delg"			//17
};

static const vector<char> boatType{
	'V',			//0 - Veleiro
	'G',			//1 - Galeão
	'E',			//2 - Escuna
	'F'				//3 - Fragata
};

enum Direction {
	North=0,
	East,
	South,
	West
};

//class ponto? pair<int,int>?
typedef struct {
	int x, y;
}xy;

class Boat {
	//Esta classe pode ser melhorada com herança e polimorfismo
	int		x, y;
	bool	isAmigo;
	bool	justSpawned;
	int		tipo;	//sub-classe?
	int		preco;
	int		soldados;
	int		agua;
	int		peixe;
	int		peixeMax;

public:

	Boat(int x, int y, bool isAmigo, int bType, bool justSpawned=false);

	int getX() const;
	int getY() const;

	void setX(int newX);
	void setY(int newY);

	void removeSpawnDizziness();
	bool canMove();

	void move(Direction d);

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

	Harbour getMainHarbour();
	bool	addBoat(string param);
	bool	addSeaCell(int x, int y);
	bool	addLandCell(int x, int y);
	bool	addHarbour(int x, int y, char c);
	bool	load(string filename);
	void	print(int xOffset, int yOffset);
	void	updateMainHarbour();
	void	update();
	bool	isWater(int x, int y);
	bool	hasBoat(int x, int y);

	xy		getFreeCoordsNear(Harbour porto);

};

void	printBanner();
void	intro();
void	printInterface();
bool	isCmdValid(string linha);
int		getBoatType(string param);
int		getComandosPos(string cmd);
void	execCMD(Map &mapa, stringstream &cmdlist);

void	compraNav(Map &mapa, string cmd);

#endif
