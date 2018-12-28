#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <ctime>

using namespace std;

#include "BattleShiPP.h"
#include "consola.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

Boat::Boat(int x, int y, bool isAmigo, int bType, bool justSpawned) :
			x(x), y(y), isAmigo(isAmigo) , tipo(bType), justSpawned(justSpawned){

}

int Boat::getX() const {
	return x;
}

int Boat::getY() const {
	return y;
}

void Boat::setX(int newX) {
	x = newX;
}

void Boat::setY(int newY) {
	y = newY;
}

void Boat::removeSpawnDizziness() {

	justSpawned = false;
}

bool Boat::canMove() {

	if (justSpawned) {
		removeSpawnDizziness();
		return false;
	}
	else
		return true;
}




//===============================================================================
//================================ CLASS MAP ====================================
//===============================================================================

Map::~Map() {

	for (auto it : mar) {
		delete it;
	}

	for (auto it : terra) {
		delete it;
	}

	for (auto it : portos) {
		delete it;
	}

	for (auto it : barcos) {
		delete it;
	}
}

vector<Sea*> Map::getMar() const {
	return mar;
}

vector<Land*> Map::getTerra() const {
	return terra;
}

vector<Harbour*> Map::getPortos() const {
	return portos;
}

vector<Boat*> Map::getBarcos() const {
	return barcos;
}

Harbour Map::getMainHarbour() {

	for (auto it : portos)
		if (it->isMain())
			return *it;

	return *portos.at(0);
}

bool Map::addBoat(string param) {

	//check boat type
	int bType=getBoatType(param);
	if (bType == -1)
		return false;

	//check if player has enough money

	//get main harbouring coords
	xy free=getFreeCoordsNear(getMainHarbour());

	if (free.x == -1)
		return false;
		
	try {
		barcos.push_back(new Boat(free.x, free.y, true, bType, true));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

//bool Map::addSeaCell(int x, int y) {
//
//	try {
//		mar.push_back(new Sea(x, y));
//	}
//	catch (const bad_alloc) {
//		return false;
//	}
//
//	return true;
//}

//bool Map::addLandCell(int x, int y) {
//
//	try {
//		terra.push_back(new Land(x, y));
//	}
//	catch (const bad_alloc) {
//		return false;
//	}
//
//	return true;
//}

//bool Map::addHarbour(int x, int y, char c) {
//
//	try {
//		portos.push_back(new Harbour(x, y, c < 'Z'));
//	}
//	catch (const bad_alloc) {
//		return false;
//	}
//
//	return true;
//}

bool Map::load(string filename) {

	ifstream map(filename);
	string line, buff;

	if (!map.is_open()) {
		return false;
	}

	for (int i = 0; i < 2; i++) {
		getline(map, line);
		istringstream iss(line);
		if(i==0)
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
				mapa[y].push_back(new Harbour(x, y, line[x]<='Z'));
				break;
			}
		}
	}
	
	for (int i = 0; !map.eof(); i++) {
		getline(map, line);
		istringstream iss(line);

		switch (i) {
		case 0:
			iss >> buff >> lin;
			break;
		case 1:
			iss >> buff >> col;
			break;
		case 2:
			iss >> buff >> moedas;
			break;
		case 3:
			iss >> buff >> probpirata;
			break;
		case 4:
			iss >> buff >> preconavio;
			break;
		case 5:
			iss >> buff >> precosoldado;
			break;
		case 6:
			iss >> buff >> precovendpeixe;
			break;
		case 7:
			iss >> buff >> precocompmercad;
			break;
		case 8:
			iss >> buff >> precovendmercad;
			break;
		case 9:
			iss >> buff >> soldadosporto;
			break;
		case 10:
			iss >> buff >> probevento;
			break;
		case 11:
			iss >> buff >> probtempestade;
			break;
		case 12:
			iss >> buff >> probsereias;
			break;
		case 13:
			iss >> buff >> prombotim;
			break;			
		default:
			break;
		}
	}

	updateMainHarbour();

	return true;
}

void Map::updateMainHarbour() {

	//Searches for a main harbour
	for (int y = 0; y < lin; y++) {
		for (int x = 0; x < col; x++) {
			if (mapa[y][x]->isFriend())
				if (mapa[y][x]->isMain())
					return;						//If one is found, returns
		}
	}

	//Searches for a friendly harbour
	for (int y = 0; y < lin; y++) {
		for (int x = 0; x < col; x++) {
			if (mapa[y][x]->isFriend()) {
				mapa[y][x]->isMain() = true;	//The first one found is promoted to main harbour
				return;
			}
		}
	}
}

void Map::update() {

	for (auto it : barcos) {
		if (it->canMove()) {
			bool moved = false;
			int tries = 0;
			while (!moved) {
				switch (Direction(rand() % (int)Direction::ENUM_SIZE)) {
				case Direction::North:
					if (isWater(it->getX(), it->getY() - 1))
						if (!hasBoat(it->getX(), it->getY() - 1)) {
							it->setY(it->getY() - 1);
							moved = true;
						}
					break;
				case Direction::East:
					if (isWater(it->getX() + 1, it->getY()))
						if (!hasBoat(it->getX() + 1, it->getY())){
							it->setX(it->getX() + 1);
							moved = true;
						}
					break;
				case Direction::South:
					if (isWater(it->getX(), it->getY() + 1))
						if (!hasBoat(it->getX(), it->getY() + 1)){
							it->setY(it->getY() + 1);
							moved = true;
						}
					break;
				case Direction::West:
					if (isWater(it->getX() - 1, it->getY()))
						if (!hasBoat(it->getX() - 1, it->getY())){
							it->setX(it->getX() - 1);
							moved = true;
						}
					break;
				default:
					break;
				}
				if (tries++>10) //quits moving after 10 tries
					moved = true;
			}
		}
	}
}

bool Map::isWater(int x, int y) {

	for (auto it : mar) {
		if (it->getX() == x && it->getY() == y)
			return true;
	}

	return false;
}

bool Map::hasBoat(int x, int y) {

	for (auto it : barcos) {
		if (it->getX() == x && it->getY() == y)
			return true;
	}

	return false;
}

xy Map::getFreeCoordsNear(Harbour porto) {
	xy free{-1,-1};
	int portoX = porto.getX();
	int portoY = porto.getY();

	for (auto marIt : mar) {
		if (marIt->getX() >= portoX-1 && marIt->getX() <= portoX + 1) {
			if (marIt->getY() >=portoY-1 && marIt->getY() <=portoY +1) {
				if (marIt->getY() == portoY|| marIt->getX()==portoX) { //needed to go from neighbors8 to neighbors4
					if (barcos.size()) {
						for (auto barcoIt : barcos) {
							if (marIt->getX() != barcoIt->getX() || marIt->getY() != barcoIt->getY()) {
								free.x = marIt->getX();
								free.y = marIt->getY();
								return free;
							}
						}
					}
					else {
						free.x = marIt->getX();
						free.y = marIt->getY();
						return free;
					}
				}
			}
		}
	}

	return free;
}

//===============================================================================
//============================== FUNCTIONS ======================================
//===============================================================================

void printBanner() {

	cout << "  ____        _   _   _       _____ _     _ _____  _____  " << endl;
	cout << " |  _ \\      | | | | | |     / ____| |   (_)  __ \\|  __ \\ " << endl;
	cout << " | |_) | __ _| |_| |_| | ___| (___ | |__  _| |__) | |__) |" << endl;
	cout << " |  _ < / _` | __| __| |/ _ \\\\___ \\| '_ \\| |  ___/|  ___/ " << endl;
	cout << " | |_) | (_| | |_| |_| |  __/____) | | | | | |    | |     " << endl;
	cout << " |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_|_|lus |_|lus  " << endl;

}

void intro() {

	for (int i = 14; i >= 0; i--) {
		Consola::gotoxy(0, i);
		printBanner();
		Sleep(80);
		if (i)Consola::clrscr();
	}
	
}

void printInterface() {

	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 24; y++) {
			Consola::gotoxy(x, y);

			//Primeira linha
			if (y == 0) {
				if (x == 0)
					cout << (char)201;
				else if (x == 79)
					cout << (char)187;
				else if (x==41)
					cout << (char)203;
				else
					cout << (char)205;
			}//Prompt
			else if (y == 21) {
				if (x == 0)
					cout << (char)204;
				else if (x == 79)
					cout << (char)185;
				else if (x == 41)
					cout << (char)202;
				else
					cout << (char)205;
			}//Ultima linha
			else if(y==23){
				if (x == 0)
					cout << (char)200;
				else if (x == 79)
					cout << (char)188;
				else
					cout << (char)205;
			}//Linhas restantes
			else {
				if (x == 0||x == 79||(x == 41 && y < 21))
					cout << (char)186;
			}

		}
	}
}

bool isCmdValid(string linha) {

	istringstream iss(linha);

	vector<string> palavras{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };

	for (auto it : Comandos)
		if (it == palavras.front())
			return true;

	return false;
}

int getBoatType(string param) {
	for (unsigned int i = 0; i < boatType.size(); i++)
		if (boatType[i] == param.at(0))
			return i;

	return -1;
}

int	getComandosPos(string cmd) {

	cmd = cmd.substr(0, cmd.find(" "));
	for (unsigned int i = 0; i < Comandos.size(); i++)
		if (Comandos[i] == cmd)
			return i;

	return -1;
}

void execCMD(Map &mapa, stringstream &cmdlist) {

	string cmd;
	//cout << cmdlist.str();
	while (getline(cmdlist, cmd, '\n')) {
		switch (getComandosPos(cmd)) {
		case 0:
			break;
		case 1:
			compraNav(mapa, cmd);
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}

void compraNav(Map &mapa, string cmd) {

	//discard compranav part
	string param = cmd.substr(cmd.find(" ")+1, cmd.back());

	mapa.addBoat(param);
}

void printMap(int xOffset, int yOffset, const Map &printThis) {

	//char bFriend = 'A', bEnemy = 'a';
	//for (auto it : printThis.getMar()) {
	//	for (int xSquare = 0; xSquare < 2; xSquare++)
	//		for (int ySquare = 0; ySquare < 2; ySquare++) {
	//			Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
	//			if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
	//				Consola::setBackgroundColor(Consola::AZUL);
	//			else
	//				Consola::setBackgroundColor(Consola::AZUL_CLARO);
	//			cout << ".";
	//		}
	//}
	//for (auto it : printThis.getTerra()) {
	//	for (int xSquare = 0; xSquare < 2; xSquare++)
	//		for (int ySquare = 0; ySquare < 2; ySquare++) {
	//			Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
	//			if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
	//				Consola::setBackgroundColor(Consola::VERDE);
	//			else
	//				Consola::setBackgroundColor(Consola::VERDE_CLARO);
	//			cout << "+";
	//		}
	//}
	//for (auto it : printThis.getPortos()) {
	//	Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
	//	for (int xSquare = 0; xSquare < 2; xSquare++)
	//		for (int ySquare = 0; ySquare < 2; ySquare++) {
	//			Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
	//			cout << (it->isFriend() ? bFriend : bEnemy);
	//		}
	//	bEnemy++;
	//	bFriend++;
	//}
	//for (auto it : printThis.getBarcos()) {
	//	Consola::setBackgroundColor(Consola::AMARELO);
	//	for (int xSquare = 0; xSquare < 2; xSquare++)
	//		for (int ySquare = 0; ySquare < 2; ySquare++) {
	//			Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
	//			cout << "1";
	//		}
	//}

	Consola::setBackgroundColor(Consola::PRETO);
}

int main() {

	srand((unsigned int)time(NULL));

	Map mapa;

	mapa.load("map.txt");


	Consola::setTextColor(Consola::BRANCO_CLARO);

	//intro();
	Consola::clrscr();
		
	printInterface();
	printMap(1,1,mapa);
	Consola::gotoxy(1, 22);
	cout << '>';

	bool running = true;
	stringstream buffer;

	while (running) {

		string linha;
		
		getline(cin, linha);
		
		if (linha.size()==0 || linha.at(0)==' ') {
			Consola::clrspc(2, 22, 77);
		}
		else if (linha == "sair") {
			running = false;
		}
		else if (linha== "prox"){
			execCMD(mapa,buffer);
			buffer.clear();
			mapa.update();
			printMap(1, 1, mapa);
			Consola::clrspc(42, 20, 37);
			Consola::clrspc(2, 22, 77);
		}
		else {

			Consola::clrspc(42, 20, 37);

			if (isCmdValid(linha)) {
				buffer << linha << endl;
				Consola::setTextColor(Consola::VERDE_CLARO);
			}
			else {
				Consola::setTextColor(Consola::VERMELHO_CLARO);
			}

			cout << '>' << linha;
			Consola::setTextColor(Consola::BRANCO_CLARO);
			Consola::clrspc(2, 22, 77);
		}
	}

	return 0;
}