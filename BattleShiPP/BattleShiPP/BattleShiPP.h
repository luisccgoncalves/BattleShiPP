#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <string>

using namespace std;

class Map {
	int lin, col;
	int moedas;

public:
	bool load(string filename);
};

#endif
