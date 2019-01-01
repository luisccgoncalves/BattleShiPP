#include "Sprite.h"
#include "consola.h"

Sprite::Sprite() :spr(' '), clr(Consola::BRANCO_CLARO) {};

const vector<char> Sprite::cellType{
	'.',			//0 - Água
	'+',			//1 - Terra
};

void	Sprite::setSpriteType(int sNum) {
	if ((unsigned int)sNum >= cellType.size())
		return;
	else
		spr = cellType[sNum];
};
void	Sprite::setSpriteType(char name) {
		spr = name;
};

void	Sprite::setSpriteColor(int color) {
	if(color<Consola::BRANCO_CLARO&& color>=0)
		clr = color;
};

char	Sprite::getSprite() {
	return spr;
};

int		Sprite::getSpriteColor() {
	return clr;
};
