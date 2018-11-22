#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

#include "BattleShiPP.h"
#include "consola.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

Boat::Boat(int x, int y, bool isAmigo) :x(x), y(y), isAmigo(isAmigo) {};

int Boat::getX() const {
	return x;
}

int Boat::getY() const {
	return y;
}

//===============================================================================
//=============================== CLASS PORT ====================================
//===============================================================================

Port::Port(int x, int y, bool isAmigo) :x(x), y(y), isAmigo(isAmigo) {};

int Port::getX() const {
	return x;
}

int Port::getY() const {
	return y;
}

bool Port::isFriend() const {
	return isAmigo;
}

//===============================================================================
//=============================== CLASS LAND ====================================
//===============================================================================

Land::Land(int x, int y) : x(x), y(y) {};

int Land::getX() const {
	return x;
}

int Land::getY() const {
	return y;
}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :x(x), y(y), peixe(0){}

int Sea::getX() const {
	return x;
}

int Sea::getY() const {
	return y;
}

int Sea::getPeixe() const{
	return peixe;
}

//===============================================================================
//================================ CLASS MAP ====================================
//===============================================================================

bool Map::addSeaCell(int x, int y) {

	try {
		mar.push_back(new Sea(x, y));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

bool Map::addLandCell(int x, int y) {

	try {
		terra.push_back(new Land(x, y));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

bool Map::addPort(int x, int y, char c) {

	try {
		portos.push_back(new Port(x, y, c < 'Z'));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

void Map::storeMapLine(istringstream &iss, int y) {

	char c;

	for (int x = 0; iss >> c; x++) {

		switch (c) {
		case '.':
			addSeaCell(x,y);
			break;
		case '+':
			addLandCell(x, y);
			break;
		default:
			addPort(x, y, c);
			break;
		}
	}
}

bool Map::load(string filename) {

	ifstream map(filename);
	string line, buff;

	if (!map.is_open()) {
		return false;
	}

	for (int i = 0, y=0; !map.eof(); i++) {
		getline(map, line);
		istringstream iss(line);

		switch (i) {
		case 0:
			iss >> buff >> lin;
			break;
		case 1:
			iss >> buff >> col;
			break;
		case 2:
			iss >> buff >> moedas;
			break;
		case 3:
			iss >> buff >> probpirata;
			break;
		case 4:
			iss >> buff >> preconavio;
			break;
		case 5:
			iss >> buff >> precosoldado;
			break;
		case 6:
			iss >> buff >> precovendpeixe;
			break;
		case 7:
			iss >> buff >> precocompmercad;
			break;
		case 8:
			iss >> buff >> precovendmercad;
			break;
		case 9:
			iss >> buff >> soldadosporto;
			break;
		case 10:
			iss >> buff >> probevento;
			break;
		case 11:
			iss >> buff >> probtempestade;
			break;
		case 12:
			iss >> buff >> probsereias;
			break;
		case 13:
			iss >> buff >> prombotim;
			break;			
		default:
			storeMapLine(iss, y++);
		}
	}
	return true;
}

void Map::print(int xOffset, int yOffset) {

	static char bFriend='A', bEnemy='a';

	for (auto it:mar) {
		for(int xSquare=0;xSquare<2;xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
					Consola::setBackgroundColor(Consola::AZUL);
				else
					Consola::setBackgroundColor(Consola::AZUL_CLARO);
				cout << ".";
			}
	}

	for (auto it : terra) {
		for (int xSquare = 0; xSquare < 2; xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
					Consola::setBackgroundColor(Consola::VERDE);
				else
					Consola::setBackgroundColor(Consola::VERDE_CLARO);
				cout << "+";
			}
	}

	for (auto it : portos) {
		
		Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
		for (int xSquare = 0; xSquare < 2; xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				cout << (it->isFriend() ? bFriend : bEnemy);
			}
		bEnemy++;
		bFriend++;
	}
	
	Consola::setBackgroundColor(Consola::PRETO);
}

//===============================================================================
//============================== FUNCTIONS ======================================
//===============================================================================

void printBanner() {

	cout << "  ____        _   _   _       _____ _     _ _____  _____  " << endl;
	cout << " |  _ \\      | | | | | |     / ____| |   (_)  __ \\|  __ \\ " << endl;
	cout << " | |_) | __ _| |_| |_| | ___| (___ | |__  _| |__) | |__) |" << endl;
	cout << " |  _ < / _` | __| __| |/ _ \\\\___ \\| '_ \\| |  ___/|  ___/ " << endl;
	cout << " | |_) | (_| | |_| |_| |  __/____) | | | | | |    | |     " << endl;
	cout << " |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_|_|lus |_|lus  " << endl;

}

void intro() {

	for (int i = 14; i >= 0; i--) {
		Consola::gotoxy(0, i);
		printBanner();
		Sleep(80);
		//Beep(50*i, 100);
		if (i)Consola::clrscr();
	}
	
}

void printInterface() {

	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 24; y++) {
			Consola::gotoxy(x, y);

			//Primeira linha
			if (y == 0) {
				if (x == 0)
					cout << (char)201;
				else if (x == 79)
					cout << (char)187;
				else if (x==41)
					cout << (char)203;
				else
					cout << (char)205;
			}//Prompt
			else if (y == 21) {
				if (x == 0)
					cout << (char)204;
				else if (x == 79)
					cout << (char)185;
				else if (x == 41)
					cout << (char)202;
				else
					cout << (char)205;
			}//Ultima linha
			else if(y==23){
				if (x == 0)
					cout << (char)200;
				else if (x == 79)
					cout << (char)188;
				else
					cout << (char)205;
			}//Linhas restantes
			else {
				if (x == 0||x == 79||(x == 41 && y < 21))
					cout << (char)186;
			}

		}
	}
}

bool isCmdValid(string linha) {

	istringstream iss(linha);

	vector<string> tokens{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };

	for (auto it : Comandos)
		if (it == tokens.front())
			return true;

	return false;

	//if (tokens.front() == "lista")
	//	return true;
	//else
	//	return false;
}

int main() {

	Map map;

	map.load("map.txt");


	Consola::setTextColor(Consola::BRANCO_CLARO);

	//intro();
	Consola::clrscr();
		
	printInterface();
	map.print(1,1);
	Consola::gotoxy(1, 22);
	cout << '>';

	bool running = true;
	//string linha;
	ostringstream buffer;

	while (running) {

		string linha;
		
		getline(cin,linha);

		if (linha == "sair") {
			running = false;
		}
		else if (linha== "prox"){
			//executacomandos()
			//actualiza movimentos()
		}
		else {

			Consola::clrspc(42, 20, 37);

			if (isCmdValid(linha)) {
				buffer << linha << endl;
				Consola::setTextColor(Consola::VERDE_CLARO);
			}
			else {
				Consola::setTextColor(Consola::VERMELHO_CLARO);
			}

			cout << '>' << linha;
			Consola::setTextColor(Consola::BRANCO);
			Consola::clrspc(2, 22, 77);
		}
	}

	return 0;
}