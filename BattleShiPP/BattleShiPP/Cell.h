#ifndef __CELL_H__
#define __CELL_H__

#include <string>

using std::string;

#include "consola.h"
#include "Boat.h"
#include "Sprite.h"

class Cell {

	int x, y;
	
public:
	Cell(int x, int y);
	virtual ~Cell();
	int getX() const;
	int getY() const;
	virtual Sprite getSprite() const = 0;

	virtual bool isFriend() const = 0;
	virtual bool canHaveBoat() const = 0;
	virtual int hasBoat() const = 0;
};

class Harbour: public Cell {

	bool isAmigo;
	bool isPrincipal;
	static char friendID;
	static char enemyID;
	char name;

	vector<Boat*> barcos;
public:

	Harbour(int x, int y, bool isAmigo);
	~Harbour();

	bool isFriend() const override;
	bool canHaveBoat() const override;
	int hasBoat() const override;

	bool &isMain();
	Sprite getSprite() const override;
	vector<Boat*>	 getDockedBoats();
	bool newBoat(bool isFriend, string boatType);

};

class Land : public Cell {

public:

	Land(int x, int y);
	Sprite getSprite() const override;

	bool isFriend() const override;
	bool canHaveBoat() const override;
	int hasBoat() const override;
};

class Sea: public Cell {

	int peixe;
	Boat *barco;

public:

	Sea(int x, int y);
	Sprite getSprite() const;
	int getPeixe() const;

	bool isFriend() const override;
	bool canHaveBoat() const override;
	int hasBoat() const override;
};
#endif