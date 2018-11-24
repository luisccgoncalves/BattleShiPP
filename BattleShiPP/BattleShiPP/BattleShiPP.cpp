#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

#include "BattleShiPP.h"
#include "consola.h"


//===============================================================================
//=============================== CLASS BOAT ====================================
//===============================================================================

Boat::Boat(int x, int y, bool isAmigo, int bType) :x(x), y(y), isAmigo(isAmigo) , tipo(bType){

}

int Boat::getX() const {
	return x;
}

int Boat::getY() const {
	return y;
}

//===============================================================================
//============================= CLASS HARBOUR ===================================
//===============================================================================

Harbour::Harbour(int x, int y, bool isAmigo) :x(x), y(y), isAmigo(isAmigo) {
	isPrincipal = false;
};

int Harbour::getX() const {
	return x;
}

int Harbour::getY() const {
	return y;
}

bool Harbour::isFriend() const {
	return isAmigo;
}

bool &Harbour::isMain(){
	return isPrincipal;
}


//===============================================================================
//=============================== CLASS LAND ====================================
//===============================================================================

Land::Land(int x, int y) : x(x), y(y) {};

int Land::getX() const {
	return x;
}

int Land::getY() const {
	return y;
}

//===============================================================================
//================================ CLASS SEA ====================================
//===============================================================================

Sea::Sea(int x, int y) :x(x), y(y), peixe(0){}

int Sea::getX() const {
	return x;
}

int Sea::getY() const {
	return y;
}

int Sea::getPeixe() const{
	return peixe;
}

//===============================================================================
//================================ CLASS MAP ====================================
//===============================================================================

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

	//get main harbouring coords
	xy free=getFreeCoordsNear(getMainHarbour());

	try {
		barcos.push_back(new Boat(free.x, free.y, true, bType));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

bool Map::addSeaCell(int x, int y) {

	try {
		mar.push_back(new Sea(x, y));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

bool Map::addLandCell(int x, int y) {

	try {
		terra.push_back(new Land(x, y));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

bool Map::addHarbour(int x, int y, char c) {

	try {
		portos.push_back(new Harbour(x, y, c < 'Z'));
	}
	catch (const bad_alloc) {
		return false;
	}

	return true;
}

void Map::storeMapLine(istringstream &iss, int y) {

	char c;

	for (int x = 0; iss >> c; x++) {

		switch (c) {
		case '.':
			addSeaCell(x,y);
			break;
		case '+':
			addLandCell(x, y);
			break;
		default:
			addHarbour(x, y, c);
			break;
		}
	}
}

bool Map::load(string filename) {

	ifstream map(filename);
	string line, buff;

	if (!map.is_open()) {
		return false;
	}

	for (int i = 0, y=0; !map.eof(); i++) {
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
			storeMapLine(iss, y++);
		}
	}

	updateMainHarbour();

	return true;
}

void Map::print(int xOffset, int yOffset) {

	char bFriend='A', bEnemy='a';

	for (auto it:mar) {
		for(int xSquare=0;xSquare<2;xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
					Consola::setBackgroundColor(Consola::AZUL);
				else
					Consola::setBackgroundColor(Consola::AZUL_CLARO);
				cout << ".";
			}
	}

	for (auto it : terra) {
		for (int xSquare = 0; xSquare < 2; xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				if ((it->getX() % 2 && !(it->getY() % 2)) || (it->getY() % 2 && !(it->getX() % 2)))
					Consola::setBackgroundColor(Consola::VERDE);
				else
					Consola::setBackgroundColor(Consola::VERDE_CLARO);
				cout << "+";
			}
	}

	for (auto it : portos) {
		
		Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
		for (int xSquare = 0; xSquare < 2; xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				cout << (it->isFriend() ? bFriend : bEnemy);
			}
		bEnemy++;
		bFriend++;
	}

	for (auto it : barcos) {

		Consola::setBackgroundColor(Consola::AMARELO);
		for (int xSquare = 0; xSquare < 2; xSquare++)
			for (int ySquare = 0; ySquare < 2; ySquare++) {
				Consola::gotoxy(2 * it->getX() + xOffset + xSquare, 2 * it->getY() + yOffset + ySquare);
				cout << "1";
			}
	}
	
	Consola::setBackgroundColor(Consola::PRETO);
}

void Map::updateMainHarbour() {

	for (auto it : portos)
		if (it->isFriend())
			if (it->isMain())
				return;

	for (auto it : portos)
		if (it->isFriend()) {
			it->isMain() = true;
			return;
		}
}

xy Map::getFreeCoordsNear(Harbour porto) {
	xy free;
	int portoX = porto.getX();
	int portoY = porto.getY();
	cout << "(" << portoX << "," << portoY << ")"<<endl;
	for (auto it : mar) {
		if (it->getX() >= portoX-1 && it->getX() <= portoX + 1) {
			if (it->getY() >=portoY-1 && it->getY() <=portoY +1) {
				free.x = it->getX();
				free.y = it->getY();
				cout << "(" << free.x << "," << free.y << ")";
				//Consola::getch();
				return free;
			}
		}
	}


	//free.x = porto.getX()-1;
	//free.y = porto.getY();

	//return free;
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
		//Beep(50*i, 100);
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
			Beep(1000, 1000);
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

int main() {

	Map mapa;

	mapa.load("map.txt");


	Consola::setTextColor(Consola::BRANCO_CLARO);

	//intro();
	Consola::clrscr();
		
	printInterface();
	mapa.print(1,1);
	Consola::gotoxy(1, 22);
	cout << '>';

	bool running = true;
	//string linha;
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
			//actualiza movimentos()
			mapa.print(1, 1);
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