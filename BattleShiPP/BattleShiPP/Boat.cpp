#include "Boat.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

Boat::Boat(bool isAmigo, int bType, bool justSpawned) :
	isAmigo(isAmigo), tipo(bType), justSpawned(justSpawned) {

}

int Boat::getX() const {
	return x;
}

int Boat::getY() const {
	return y;
}

void Boat::setX(int newX) {
	x = newX;
}

void Boat::setY(int newY) {
	y = newY;
}

void Boat::removeSpawnDizziness() {

	justSpawned = false;
}

bool Boat::canMove() {

	if (justSpawned) {
		removeSpawnDizziness();
		return false;
	}
	else
		return true;
}
