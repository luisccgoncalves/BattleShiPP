#include "Boat.h"
#include "Map.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

int Boat::boatID = 1;

Boat::Boat(int x, int y, Map* mapa, bool isAmigo) :
	x(x), y(y), isAmigo(isAmigo), peixe(0), mercadoria(0), 
	boatNr(boatID++), mapa(mapa),isDocked(isAmigo){
}

const int Boat::getBoatNr() {
	return boatNr;
}

bool Boat::setHeading(int x, int y) {

	x = abs(x); y = abs(y);

	if (x < mapa->getCol() && y < mapa->getLin())
		if (mapa->getMapa()[y][x]->canHaveBoat()) {
			headingX = x;
			headingY = y;
			headingSet = true;
			return true;
		}

	return false;
}

void Boat::gotoHeading() {

	//proof of concept
	if (x > headingY) {
		if (mapa->getMapa()[y][x-1]->canHaveBoat())
			if (mapa->getMapa()[y][x-1]->hasBoat() == false) {
				mapa->getMapa()[y][x]->toggleBarco(this);
				mapa->getMapa()[y][--x]->toggleBarco(this);
				return;
			}
	}

	if (y > headingY) {
		if (mapa->getMapa()[y - 1][x]->canHaveBoat())
			if (mapa->getMapa()[y - 1][x]->hasBoat() == false) {
				mapa->getMapa()[y][x]->toggleBarco(this);
				mapa->getMapa()[--y][x]->toggleBarco(this);
				return;
			}
	}
}

void Boat::tick() {
	if (headingSet)
		gotoHeading();
}

Veleiro::Veleiro(int x, int y, Map* mapa, bool isAmigo) :
	Boat(x, y, mapa, isAmigo){
	soldados = soldadosMax = 20;
	agua = aguaMax = 200;
	if (isAmigo)
		cargaMax = 40;
	else
		cargaMax = 0;
}

//void Veleiro::tick() {
//
//}

Galeao::Galeao(int x, int y, Map* mapa, bool isAmigo) :
	Boat(x, y, mapa, isAmigo) {
	soldados = soldadosMax = 40;
	agua = aguaMax = 400;
	cargaMax = 70;
}

//void Galeao::tick() {
//
//}

Escuna::Escuna(int x, int y, Map* mapa, bool isAmigo) :
	Boat(x, y, mapa, isAmigo) {
	soldados = soldadosMax = 10;
	agua = aguaMax = 100;
	cargaMax = 20;
}

//void Escuna::tick() {
//
//}

Fragata::Fragata(int x, int y, Map* mapa, bool isAmigo) :
	Boat(x, y, mapa, isAmigo) {
	soldados = soldadosMax = 50;
	agua = aguaMax = 500;
}

//void Fragata::tick() {
//
//}

Special::Special(int x, int y, Map* mapa, bool isAmigo) :
	Boat(x, y, mapa, isAmigo) {
	soldados = soldadosMax = 2;
	agua = aguaMax = 200;
	cargaMax = 150;
}

//void Special::tick() {
//
//}