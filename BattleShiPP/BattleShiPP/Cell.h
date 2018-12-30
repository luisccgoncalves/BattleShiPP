#ifndef __CELL_H__
#define __CELL_H__

#include "consola.h"
#include "Boat.h"

class Cell {

	int x, y;
	
public:
	Cell(int x, int y);
	virtual ~Cell() = 0;
	int getX() const;
	int getY() const;
	virtual void getSprite(char &sprite, int &sprColor) const = 0;
};

class Harbour: public Cell {

	bool isAmigo;
	bool isPrincipal;

public:

	Harbour(int x, int y, bool isAmigo);

	bool isFriend()const;
	bool &isMain();
	void getSprite(char &sprite, int &sprColor) const;

};

class Land : public Cell {

public:

	Land(int x, int y);
	void getSprite(char &sprite, int &sprColor) const;
};

class Sea: public Cell {

	int peixe;
	Boat *barco;

public:

	Sea(int x, int y);
	void getSprite(char &sprite, int &sprColor) const;
	int getPeixe() const;

};
#endif