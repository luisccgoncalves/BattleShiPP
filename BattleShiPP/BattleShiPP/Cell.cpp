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

char Harbour::friendID = 'A';
char Harbour::enemyID = 'a';

Harbour::Harbour(int x, int y, bool isAmigo) : Cell(x,y), isAmigo(isAmigo) {
	isPrincipal = false;
	if (isAmigo)
		name = friendID++;
	else
		name = enemyID++;
}

Harbour::~Harbour() {

	for (vector<Boat*>::iterator it=barcos.begin() ;it!=barcos.end(); it++)
		delete *it;
}

bool Harbour::isFriend() const {
	return isAmigo;
}

bool &Harbour::isMain() {
	return isPrincipal;
}

void Harbour::getSprite(Sprite &sprite) const{
	sprite.setSpriteType(name);
	sprite.setSpriteColor(Consola::VERMELHO);
}

bool Harbour::newBoat(bool isFriend, string boatType){

	switch (boatType[0]) {
	case 'V':
		barcos.push_back(new Veleiro(isFriend));
		break;
	case 'G': 
		barcos.push_back(new Galeao(isFriend));
		break;
	case 'E': 
		barcos.push_back(new Escuna(isFriend));
		break;
	case 'F': 
		barcos.push_back(new Fragata(isFriend));
		break;
	case 'S': 
		barcos.push_back(new Special(isFriend));
		break;
	default:
		return false;
		break;
	}

	return true;
}


//===============================================================================
//=============================== CLASS LAND ====================================
//===============================================================================

Land::Land(int x, int y) : Cell(x,y) {};

void Land::getSprite(Sprite &sprite) const {
	sprite.setSpriteType(Sprite::TERRA);
	sprite.setSpriteColor(Consola::VERDE);
}

bool Land::isFriend() const {
	return false;
}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :Cell(x,y), peixe(0), barco(nullptr) {}

int Sea::getPeixe() const {
	return peixe;
}

void Sea::getSprite(Sprite &sprite) const {
	sprite.setSpriteType(Sprite::AGUA);
	sprite.setSpriteColor(Consola::AZUL);
}

bool Sea::isFriend() const {
	return false;
}