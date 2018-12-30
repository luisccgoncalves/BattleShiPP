#ifndef __BOAT_H__
#define __BOAT_H__

class Boat {
	//Esta classe pode ser melhorada com herança e polimorfismo
	int		x, y;
	bool	isAmigo;
	bool	justSpawned;
	int		tipo;
	int		preco;
	int		soldados;
	int		agua;
	int		peixe;
	int		peixeMax;

public:

	Boat(int x, int y, bool isAmigo, int bType, bool justSpawned = false);

	int getX() const;
	int getY() const;

	void setX(int newX);
	void setY(int newY);

	void removeSpawnDizziness();
	bool canMove();

};
#endif