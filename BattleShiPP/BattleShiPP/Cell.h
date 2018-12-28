#ifndef __CELL_H__
#define __CELL_H__

class Cell {

	int x, y;
	
public:
	Cell(int x, int y);
	//virtual ~Cell() = 0;
	int getX() const;
	int getY() const;
	virtual bool isFriend() const;
	virtual bool &isMain();

};

class Harbour: public Cell {

	bool isAmigo;
	bool isPrincipal;

public:

	Harbour(int x, int y, bool isAmigo);

	bool isFriend()const;
	bool &isMain();

};

class Land : public Cell {

public:

	Land(int x, int y);

};

class Sea: public Cell {

	int peixe;

public:

	Sea(int x, int y);

	int getPeixe() const;

};
#endif