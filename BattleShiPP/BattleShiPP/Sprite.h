#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <vector>

using std::vector;

class Sprite {

	static const vector<char> cellType;
	
	char spr;
	int clr;

public:
	enum cell {
		AGUA,
		TERRA
	};

	Sprite();
	void	setSpriteType(int sNum);
	void	setSpriteType(char name);
	void	setSpriteColor(int color);
	char	getSprite();
	int		getSpriteColor();
};
#endif