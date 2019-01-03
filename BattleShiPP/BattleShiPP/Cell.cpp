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
	s.setSpriteColor(Consola::VERMELHO_CLARO);

	return s;
}

vector<Boat*> Harbour::getDockedBoats() {
	return barcos;
}

bool Harbour::newBoat(bool isFriend, string boatType, Map* mapa){

	switch (boatType[0]) {
	case 'V':
		barcos.push_back(new Veleiro(this->getX(), this->getY(), mapa, isFriend));
		break;
	case 'G': 
		barcos.push_back(new Galeao(this->getX(), this->getY(), mapa, isFriend));
		break;
	case 'E': 
		barcos.push_back(new Escuna(this->getX(), this->getY(), mapa, isFriend));
		break;
	case 'F': 
		barcos.push_back(new Fragata(this->getX(), this->getY(), mapa, isFriend));
		break;
	case 'S': 
		barcos.push_back(new Special(this->getX(), this->getY(), mapa, isFriend));
		break;
	default:
		return false;
		break;
	}

	return true;
}

void Harbour::tick() {

	for (auto barco : barcos)
		barco->tick();
}

void Harbour::toggleBarco(Boat* barco) {

	//Search for barco, if present, delete it from the vector
	for (unsigned int i = 0; i < barcos.size(); i++) {
		if (barcos[i]->getBoatNr() == barco->getBoatNr()) {
			barcos.erase(barcos.begin() + i);
			return;
		}
	}

	//If not present, add it
	barcos.push_back(barco);
	return;
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

void Land::tick() {
	return;
}

void Land::toggleBarco(Boat* barco){}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :Cell(x,y), peixe(peixeMax), barco(nullptr) {}

Sea::~Sea() {
	if (barco != nullptr)
		delete barco;
}
int Sea::getPeixe() const {
	return peixe;
}

Sprite Sea::getSprite() const {
	Sprite s;

	if (barco == nullptr) {
		s.setSpriteType(Sprite::AGUA);
		s.setSpriteColor(Consola::AZUL);
	}
	else {
		s.setSpriteType(to_string(barco->getBoatNr())[0]);
		s.setSpriteColor(Consola::CINZENTO);
	}

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

void Sea::tick() {

	//Update peixe
	if (peixe < peixeMax)
		peixe++;

	//Update barco
	if (barco != nullptr)
		barco->tick();
}

void Sea::toggleBarco(Boat* barco) {

	if (this->barco == nullptr)
		this->barco = barco;
	else if (barco->getBoatNr() == this->barco->getBoatNr())
		this->barco = nullptr;
}