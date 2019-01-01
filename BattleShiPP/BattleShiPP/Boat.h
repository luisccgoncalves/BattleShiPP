#ifndef __BOAT_H__
#define __BOAT_H__

#include <string>

using std::string;

class Boat {

	bool	isAmigo;

	int		soldados;
	int		soldadosMax;

	int		agua;
	int		aguaMax;

	int		peixe;
	int		mercadoria;
	int		cargaMax;

public:

	Boat(bool isAmigo);
	virtual ~Boat() = 0;

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