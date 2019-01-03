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

bool Harbour::isFriend() const{
	return isAmigo;
}

bool Harbour::canHaveBoat() const {
	return true;
}

int Harbour::hasBoat() const {
	return barcos.size();
}

Boat* Harbour::hasBoat(int boatNr) const {

	if (barcos.size()) {
		for (auto it : barcos)
			if (it->getBoatNr() == boatNr)
				return it;
	}

	return nullptr;			
}

bool &Harbour::isMain() {
	return isPrincipal;
}

Sprite Harbour::getSprite() const{

	Sprite s;
	s.setSpriteType(name);
	s.setSpriteColor(Consola::VERMELHO);

	return s;
}

vector<Boat*> Harbour::getDockedBoats() {
	return barcos;
}

bool Harbour::newBoat(bool isFriend, string boatType, Map* mapa){

	switch (boatType[0]) {
	case 'V':
		barcos.push_back(new Veleiro(mapa, isFriend));
		break;
	case 'G': 
		barcos.push_back(new Galeao(mapa, isFriend));
		break;
	case 'E': 
		barcos.push_back(new Escuna(mapa, isFriend));
		break;
	case 'F': 
		barcos.push_back(new Fragata(mapa, isFriend));
		break;
	case 'S': 
		barcos.push_back(new Special(mapa, isFriend));
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

Sprite Land::getSprite() const {

	Sprite s;
	s.setSpriteType(Sprite::TERRA);
	s.setSpriteColor(Consola::VERDE);

	return s;
}

bool Land::isFriend() const {
	return false;
}

bool Land::canHaveBoat() const {
	return false;
}

int Land::hasBoat() const {
	return 0;
}

Boat* Land::hasBoat(int boatNr) const {
	return nullptr;
}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :Cell(x,y), peixe(0), barco(nullptr) {}

int Sea::getPeixe() const {
	return peixe;
}

Sprite Sea::getSprite() const {
	Sprite s;
	s.setSpriteType(Sprite::AGUA);
	s.setSpriteColor(Consola::AZUL);

	return s;
}

bool Sea::isFriend() const {
	return false;
}

bool Sea::canHaveBoat() const {
	return true;
}

int Sea::hasBoat() const {
	return (barco != nullptr);
}

Boat* Sea::hasBoat(int boatNr) const {
	return barco;
}