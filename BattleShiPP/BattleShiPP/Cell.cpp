#include "Cell.h"
//===============================================================================
//=============================== CLASS CELL ====================================
//===============================================================================

Cell::Cell(int x, int y) :x(x), y(y) {};
Cell::~Cell() {}

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

void Harbour::getSprite(char &sprite, int &sprColor) const{
	sprite = '1';
	sprColor = Consola::VERMELHO;
}


//===============================================================================
//=============================== CLASS LAND ====================================
//===============================================================================

Land::Land(int x, int y) : Cell(x,y) {};

void Land::getSprite(char &sprite, int &sprColor) const {
	sprite = '+';
	sprColor = Consola::VERDE;
}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :Cell(x,y), peixe(0), barco(nullptr) {}

int Sea::getPeixe() const {
	return peixe;
}

void Sea::getSprite(char &sprite, int &sprColor) const {
	sprite = '.';
	sprColor = Consola::AZUL;
}