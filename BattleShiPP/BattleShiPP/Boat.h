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
public:

	Boat(bool isAmigo=true);

	const int getBoatNr();
	void tick();

};

class Veleiro :public Boat {

public:

	Veleiro(bool isAmigo);
};

class Galeao :public Boat {

public:

	Galeao(bool isAmigo);
};

class Escuna :public Boat {

public:

	Escuna(bool isAmigo);
};

class Fragata :public Boat {

public:

	Fragata(bool isAmigo);
};

class Special :public Boat {

public:

	Special(bool isAmigo);
};
#endif