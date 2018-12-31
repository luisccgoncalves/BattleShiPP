#ifndef __CELL_H__
#define __CELL_H__

#include "consola.h"
#include "Boat.h"
#include "Sprite.h"

class Cell {

	int x, y;
	
public:
	Cell(int x, int y);
	virtual ~Cell() = 0;
	int getX() const;
	int getY() const;
	virtual void getSprite(Sprite &sprite) const = 0;

	virtual bool isFriend() const = 0;
};

class Harbour: public Cell {

	bool isAmigo;
	bool isPrincipal;
	static char friendID;
	static char enemyID;
	char name;

public:

	Harbour(int x, int y, bool isAmigo);

	bool isFriend()const;
	bool &isMain();
	void getSprite(Sprite &sprite) const;

};

class Land : public Cell {

public:

	Land(int x, int y);
	void getSprite(Sprite &sprite) const;

	bool isFriend() const;
};

class Sea: public Cell {

	int peixe;
	Boat *barco;

public:

	Sea(int x, int y);
	void getSprite(Sprite &sprite) const;
	int getPeixe() const;

	bool isFriend() const;
};
#endif