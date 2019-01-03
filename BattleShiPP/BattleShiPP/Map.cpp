#include "Map.h"

const vector<string> Map::direccao{
		"D",
		"E",
		"C",
		"B",
		"CE",
		"CD",
		"BE",
		"BD"
};

Cell* Map::getCell(int x, int y) const {
	return mapa[y][x];
}

int Map::getLin() const {
	return lin;
}

int Map::getCol() const {
	return col;
}

int Map::getMoedas() const {
	return moedas;
}

vector<vector<Cell*>> Map::getMapa() {
	return mapa;
}

bool Map::load(string filename) {

	ifstream map(filename);
	string line, buff;

	if (!map.is_open()) {
		return false;
	}

	for (int i = 0; i < 2; i++) {
		getline(map, line);
		istringstream iss(line);
		if (i == 0)
			iss >> buff >> lin;
		else
			iss >> buff >> col;
	}

	for (int y = 0; y < lin; y++) {
		mapa.push_back(vector<Cell*>());
		getline(map, line);

		for (int x = 0; x < col; x++) {
			switch (line[x]) {
			case '.':
				mapa[y].push_back(new Sea(x, y));
				break;
			case '+':
				mapa[y].push_back(new Land(x, y));
				break;
			default:
				mapa[y].push_back(new Harbour(x, y, line[x] <= 'Z'));
				break;
			}
		}
	}

	for (int i = 0; !map.eof(); i++) {
		getline(map, line);
		istringstream iss(line);

		switch (i) {
		case 0:
			iss >> buff >> moedas;
			break;
		case 1:
			iss >> buff >> probpirata;
			break;
		case 2:
			iss >> buff >> preconavio;
			break;
		case 3:
			iss >> buff >> precosoldado;
			break;
		case 4:
			iss >> buff >> precovendpeixe;
			break;
		case 5:
			iss >> buff >> precocompmercad;
			break;
		case 6:
			iss >> buff >> precovendmercad;
			break;
		case 7:
			iss >> buff >> soldadosporto;
			break;
		case 8:
			iss >> buff >> probevento;
			break;
		case 9:
			iss >> buff >> probtempestade;
			break;
		case 10:
			iss >> buff >> probsereias;
			break;
		case 11:
			iss >> buff >> prombotim;
			break;
		default:
			break;
		}
	}

	getMainHarbour();

	return true;
}

Harbour* Map::getMainHarbour() const{

	Harbour *first = nullptr;
	//Searches for a main harbour
	for (int y = 0; y < lin; y++) {
		for (int x = 0; x < col; x++) {
			if (mapa[y][x]->isFriend()) {
				//Only harbours return "true", it's safe to cast
				if (first == nullptr)
					first = static_cast<Harbour*>(mapa[y][x]);
				if (static_cast<Harbour*>(mapa[y][x])->isMain())
					return static_cast<Harbour*>(mapa[y][x]);
			}
		}
	}

	//If no mainHarbour is found, turn the first harbour found into one
	first->isMain() = true;

	return first;
}

bool	Map::setMoedas(int incdec) {

	if (moedas + incdec >= 0) {
		moedas += incdec;
		return true;
	}
	else
		return false;
}

bool Map::buyBoat(string boatType) {

	if (setMoedas(-preconavio)) {
		getMainHarbour()->newBoat(true, boatType, this);
		return true;
	}
	else
		return false;
}

Boat* Map::findBoat(int boatNr)const {

	for (int y = 0; y < lin; y++)
		for (int x = 0; x < col; x++)
			if (mapa[y][x]->canHaveBoat())
				if(mapa[y][x]->hasBoat(boatNr)!=nullptr)
					return mapa[y][x]->hasBoat(boatNr);	

	return nullptr;
}