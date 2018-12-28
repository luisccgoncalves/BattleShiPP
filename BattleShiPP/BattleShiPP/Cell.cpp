#include "Cell.h"
//===============================================================================
//=============================== CLASS CELL ====================================
//===============================================================================

Cell::Cell(int x, int y) :x(x), y(y) {};
//Cell::~Cell() {}

int Cell::getX() const {
	return this->x;
}

int Cell::getY() const {
	return this->y;
}

//===============================================================================
//============================= CLASS HARBOUR ===================================
//===============================================================================

Harbour::Harbour(int x, int y, bool isAmigo) : Cell(x,y), isAmigo(isAmigo) {
	isPrincipal = false;
}

bool Harbour::isFriend() const {
	return isAmigo;
}

bool &Harbour::isMain() {
	return isPrincipal;
}


//===============================================================================
//=============================== CLASS LAND ====================================
//===============================================================================

Land::Land(int x, int y) : Cell(x,y) {};


//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :Cell(x,y), peixe(0) {}

int Sea::getPeixe() const {
	return peixe;
}