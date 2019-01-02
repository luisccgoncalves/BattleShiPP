#include "Boat.h"
#include "Map.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

int Boat::boatID = 1;

Boat::Boat(bool isAmigo) :
	isAmigo(isAmigo), peixe(0), mercadoria(0), boatNr(boatID++){

	//Enemy ships spawn undocked
	if(!isAmigo)
		isDocked = false;
}

const int Boat::getBoatNr() {
	return boatNr;
}
void Boat::tick() {
}

Veleiro::Veleiro(bool isAmigo) :
	Boat(isAmigo){
	soldados = soldadosMax = 20;
	agua = aguaMax = 200;
	if (isAmigo)
		cargaMax = 40;
	else
		cargaMax = 0;
}

Galeao::Galeao(bool isAmigo) :
	Boat(isAmigo) {
	soldados = soldadosMax = 40;
	agua = aguaMax = 400;
	cargaMax = 70;
}

Escuna::Escuna(bool isAmigo) :
	Boat(isAmigo) {
	soldados = soldadosMax = 10;
	agua = aguaMax = 100;
	cargaMax = 20;
}
Fragata::Fragata(bool isAmigo) : 
	Boat(isAmigo) {
	soldados = soldadosMax = 50;
	agua = aguaMax = 500;
}

Special::Special(bool isAmigo) :
	Boat(isAmigo) {
	soldados = soldadosMax = 2;
	agua = aguaMax = 200;
	cargaMax = 150;
}