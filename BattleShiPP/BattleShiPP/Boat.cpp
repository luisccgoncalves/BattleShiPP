#include "Boat.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

Boat::Boat(bool isAmigo) :
	isAmigo(isAmigo) {

}

Veleiro::Veleiro(bool isAmigo) :
	Boat(isAmigo) {

}

Galeao::Galeao(bool isAmigo) :
	Boat(isAmigo) {

}

Escuna::Escuna(bool isAmigo) :
	Boat(isAmigo) {

}
Fragata::Fragata(bool isAmigo) : 
	Boat(isAmigo) {

}

Special::Special(bool isAmigo) :
	Boat(isAmigo) {

}