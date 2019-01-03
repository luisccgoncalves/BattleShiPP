#ifndef __BOAT_H__
#define __BOAT_H__

#include <string>

using std::string;

class Map;

class Boat {

	static int boatID;
	const int boatNr;

protected:

	int		x, y;
	bool	isAmigo;
	bool	isDocked;

	int		soldados;
	int		soldadosMax;

	int		agua;
	int		aguaMax;

	int		peixe;
	int		mercadoria;
	int		cargaMax;

	Map*	mapa;

	bool	headingSet = false;
	int		headingY, headingX;
public:

	Boat(int x, int y, Map* mapa, bool isAmigo=true);

	const int getBoatNr();
	bool setHeading(int x, int y);
	void gotoHeading();
	void tick();

};

class Veleiro :public Boat {

public:

	Veleiro(int x, int y, Map* mapa, bool isAmigo);
	//void tick() override;
};

class Galeao :public Boat {

public:

	Galeao(int x, int y, Map* mapa, bool isAmigo);
	//void tick() override;
};

class Escuna :public Boat {

public:

	Escuna(int x, int y, Map* mapa, bool isAmigo);
	//void tick() override;
};

class Fragata :public Boat {

public:

	Fragata(int x, int y, Map* mapa, bool isAmigo);
	//void tick() override;
};

class Special :public Boat {

public:

	Special(int x, int y, Map* mapa, bool isAmigo);
	//void tick() override;
};
#endif