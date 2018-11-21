#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

void Map::storeMapLine(istringstream &iss, int y) {

	char c;

	for (int x = 0; iss >> c; x++) {

		switch (c) {
		case '.':
			addSeaCell(x,y);
			break;
		case '+':
			break;
		}

	}

	cout << endl;
}

bool Map::load(string filename) {

	ifstream map(filename);
	string line, buff;

	if (!map.is_open()) {
		return false;
	}

	for (int i = 0; !map.eof(); i++) {
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
			cout << "moedas=" << moedas << endl;
			break;
		default:
			storeMapLine(iss, i-3);
		}
	}
	return true;
}

void Map::print() {

	for (auto it:mar) {
		cout << it->getX();
	}
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

int main() {


	Consola::setTextColor(Consola::BRANCO_CLARO);

	//intro();

	Map map;

	map.load("map.txt");

	map.print();

	Consola::getch();

	return 0;
}