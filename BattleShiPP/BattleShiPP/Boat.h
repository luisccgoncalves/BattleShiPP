#ifndef __BOAT_H__
#define __BOAT_H__

#include <string>

using std::string;

class Map;

class Boat {

	static int boatID;
	const int boatNr;

protected:

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

	int		headingY, headingX;
public:

	Boat(Map* mapa, bool isAmigo=true);

	const int getBoatNr();
	bool setHeading(int x, int y);

};

class Veleiro :public Boat {

public:

	Veleiro(Map* mapa, bool isAmigo);
};

class Galeao :public Boat {

public:

	Galeao(Map* mapa, bool isAmigo);
};

class Escuna :public Boat {

public:

	Escuna(Map* mapa, bool isAmigo);
};

class Fragata :public Boat {

public:

	Fragata(Map* mapa, bool isAmigo);
};

class Special :public Boat {

public:

	Special(Map* mapa, bool isAmigo);
};
#endif