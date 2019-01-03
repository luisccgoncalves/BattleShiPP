#include "Boat.h"
#include "Map.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

int Boat::boatID = 1;

Boat::Boat(Map* mapa, bool isAmigo) :
	isAmigo(isAmigo), peixe(0), mercadoria(0), boatNr(boatID++), mapa(mapa){

	//Enemy ships spawn undocked
	if(!isAmigo)
		isDocked = false;
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
			return true;
		}

	return false;
}

Veleiro::Veleiro(Map* mapa, bool isAmigo) :
	Boat(mapa, isAmigo){
	soldados = soldadosMax = 20;
	agua = aguaMax = 200;
	if (isAmigo)
		cargaMax = 40;
	else
		cargaMax = 0;
}

Galeao::Galeao(Map* mapa, bool isAmigo) :
	Boat(mapa, isAmigo) {
	soldados = soldadosMax = 40;
	agua = aguaMax = 400;
	cargaMax = 70;
}

Escuna::Escuna(Map* mapa, bool isAmigo) :
	Boat(mapa, isAmigo) {
	soldados = soldadosMax = 10;
	agua = aguaMax = 100;
	cargaMax = 20;
}
Fragata::Fragata(Map* mapa, bool isAmigo) :
	Boat(mapa, isAmigo) {
	soldados = soldadosMax = 50;
	agua = aguaMax = 500;
}

Special::Special(Map* mapa, bool isAmigo) :
	Boat(mapa, isAmigo) {
	soldados = soldadosMax = 2;
	agua = aguaMax = 200;
	cargaMax = 150;
}