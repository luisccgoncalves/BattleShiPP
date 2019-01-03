#ifndef __CELL_H__
#define __CELL_H__

#include <string>

using std::string;
using std::to_string;

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
	virtual Boat* hasBoat(int boatNr) const = 0;
	virtual void tick() = 0;
	virtual void toggleBarco(Boat * barco) = 0;
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
	Boat* hasBoat(int boatNr) const override;

	bool &isMain();
	Sprite getSprite() const override;
	vector<Boat*>	 getDockedBoats();
	bool newBoat(bool isFriend, string boatType, Map* mapa);
	void tick()override;
	void toggleBarco(Boat * barco) override;
};

class Land : public Cell {

public:

	Land(int x, int y);
	Sprite getSprite() const override;

	bool isFriend() const override;
	bool canHaveBoat() const override;
	int hasBoat() const override;
	Boat* hasBoat(int boatNr) const override;
	void tick()override;
	void toggleBarco(Boat * barco) override;
};

class Sea: public Cell {

	int peixe;
	static const int peixeMax = 5;
	Boat *barco;

public:

	Sea(int x, int y);
	Sprite getSprite() const;
	int getPeixe() const;

	bool isFriend() const override;
	bool canHaveBoat() const override;
	int hasBoat() const override;
	Boat* hasBoat(int boatNr) const override;
	void tick()override;
	void toggleBarco(Boat * barco) override;
};
#endif