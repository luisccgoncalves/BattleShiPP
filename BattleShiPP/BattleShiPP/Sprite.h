#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <vector>

using std::vector;

class Sprite {

	static const vector<char> cellType;
	static const vector<char> boatType;
	char spr;
	int clr;

public:
	enum cell {
		AGUA,
		TERRA
	};
	enum boat {
		VELEIRO,
		GALEAO,
		ESCUNA,
		FRAGATA
	};

	Sprite();
	void	setSpriteType(int sNum);
	void	setSpriteType(char name);
	void	setSpriteColor(int color);
	char	getSprite();
	int		getSpriteColor();
	static const vector<char>  getBoatTypes();
};
#endif