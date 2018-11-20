#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <string>

using namespace std;

class Boat {

};

class Port {

};

class Land {

};

class Sea {

};

class Map {
	int lin, col;
	int moedas;

	void storeMapLine(istringstream &iss);
public:
	bool load(string filename);
};

#endif
