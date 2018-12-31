#include "BattleShiPP.h"

//===============================================================================
//================================ CLASS MAP ====================================
//===============================================================================

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

	updateMainHarbour();

	return true;
}

void Map::updateMainHarbour() {

	Harbour *first=nullptr;
	//Searches for a main harbour
	for (int y = 0; y < lin; y++) {
		for (int x = 0; x < col; x++) {
			if(mapa[y][x]->isFriend()){
				//Only harbours return "true", it's safe to cast
				if(first==nullptr)
					first = static_cast<Harbour*>(mapa[y][x]);
				if(static_cast<Harbour*>(mapa[y][x])->isMain())
					return;
			}
		}
	}

	first->isMain() = true;
}


//===============================================================================
//=============================== CLASS UI ======================================
//===============================================================================

UI::UI() {
	Consola::setTextColor(Consola::BRANCO_CLARO);
	
};

const string UI::banner{
	"  ____        _   _   _       _____ _     _ _____  _____  \n"
	" |  _ \\      | | | | | |     / ____| |   (_)  __ \\|  __ \\ \n"
	" | |_) | __ _| |_| |_| | ___| (___ | |__  _| |__) | |__) |\n"
	" |  _ < / _` | __| __| |/ _ \\\\___ \\| '_ \\| |  ___/|  ___/ \n"
	" | |_) | (_| | |_| |_| |  __/____) | | | | | |    | |     \n"
	" |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_|_|lus |_|lus  \n" };

const vector<string> UI::comandos{
	"exec",			//0
	"compranav",	//1
	"vendenav",		//2
	"lista",		//3
	"compra",		//4
	"vende",		//5
	"move",			//6
	"auto",			//7
	"stop",			//8
	"pirata",		//9
	"evpos",		//10
	"evnav",		//11
	"moedas",		//12
	"vaipara",		//13
	"comprasold",	//14
	"saveg",		//15
	"loadg",		//16
	"delg"			//17
};

void UI::intro() {

	for (int i = 14; i >= 0; i--) {
		Consola::gotoxy(0, i);
		cout << banner;
		Sleep(80);
		if (i)Consola::clrscr();
	}
	Sleep(500);
}

void UI::printInterface(const Map &mapa) {

	Consola::clrscr();

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

	printMap(mapa);

	Consola::gotoxy(1, 22);
	cout << '>';
}

void	UI::updateInterface() {

	Consola::clrspc(42, 20, 37);
	resetPrompt();

};

void	UI::updateInterface(const Map &mapa) {

	printMap(mapa);
	updateInterface();

};

bool UI::isCmdValid(string linha) {

	istringstream iss(linha);

	vector<string> palavras{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };
	
	int i = 0;
	for (vector<string>::const_iterator it = comandos.begin(); it != comandos.end(); ++it, i++) {
		if (*it == palavras.front()) {
			switch (i) {
			case 0://exec <nomeFicheiro>
				if (palavras.size() == 2)
					return true;
				break;
			case 1://compranav <T>
				if (palavras.size() == 2 && palavras.at(1).size()==1)
					for(auto it : Sprite::getBoatTypes())
						if(it==palavras.at(1)[0])
							return true;
				break;
			case 2://vendenav <N>
				if (palavras.size() == 2 && isNum(palavras.at(1)))
					return true;
				break;
			case 3:	//lista
				if (palavras.size() == 1)
					return true;
				break;
			case 4:	 //compra <N> <M>
				if (palavras.size() == 3 && 
					isNum(palavras.at(1)) && 
					isNum(palavras.at(2)))
					return true;
				break;
			case 5:	 //vende <N>
				if (palavras.size() == 2 && isNum(palavras.at(1)))
					return true;
				break;
			case 6:	 //move <N> <X>
				break;
			case 7:	 //auto <N>
				break;
			case 8:	 //stop <N>
				break;
			case 9:	 //pirata <x> <y> <t>
				break;
			case 10: //evpos <E> <x> <y>
				break;
			case 11: //evnav <E> <N>
				break;
			case 12: //moedas <N>
				break;
			case 13: //vaipara	<N> <x> <y> || vaipara <N> <P>
				break;
			case 14: //comprasold <N> <s>
				break;
			case 15: //saveg <nome>
				break;
			case 16: //loadg <nome>
				break;
			case 17: //delg <nome>
				break;
			default:
				break;
			}

		}
	}

	return false;
}

int	UI::getComandosPos(string cmd) {

	cmd = cmd.substr(0, cmd.find(" "));
	for (unsigned int i = 0; i < comandos.size(); i++)
		if (comandos[i] == cmd)
			return i;

	return -1;
}

void UI::execCMD(Map &mapa, stringstream &cmdlist) {

	string cmd;

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
	cmdlist.clear();
	updateInterface(mapa);
}

void UI::processCMD(stringstream &buffer, const string &linha) {

	resetLastCmd();

	if (isCmdValid(linha)) {
		buffer << linha << endl;
		Consola::setTextColor(Consola::VERDE_CLARO);
	}
	else {
		Consola::setTextColor(Consola::VERMELHO_CLARO);
	}
	cout << '>' << linha;

	resetPrompt();
}

void UI::resetPrompt() {
	Consola::setTextColor(Consola::BRANCO_CLARO);
	Consola::clrspc(2, 22, 77);
}

void UI::resetLastCmd() {
	Consola::clrspc(42, 20, 37);
}

void UI::compraNav(Map &mapa, string cmd) {

	//discard compranav part
	string param = cmd.substr(cmd.find(" ")+1, cmd.back());
}

void UI::printMap(const Map &printThis) {

	Sprite sprite;

	for (int y = 0; y < printThis.getLin(); y++) {
		for (int x = 0; x < printThis.getCol(); x++) {
			printThis.getCell(x, y)->getSprite(sprite);
			for(int ySquare=0;ySquare<2;ySquare++)
				for (int xSquare=0; xSquare < 2; xSquare++) {
					Consola::gotoxy(xOffset + (x*2) + xSquare, yOffset + (y*2) + ySquare);
					Consola::setBackgroundColor(
						((x % 2) && !(y % 2)) || (!(x % 2) && (y % 2))?		//Makes the chess patern
							(sprite.getSpriteColor()==Consola::VERMELHO?	//Red will always be light
								sprite.getSpriteColor() +8:
								sprite.getSpriteColor()):
							sprite.getSpriteColor() +8);
					putchar(sprite.getSprite());
				}
		}
	}

	Consola::setBackgroundColor(Consola::PRETO);
}

bool UI::isNum(string num) {
	try { stoi(num); }
	catch (...) {
		return false;
	}
	return true;
}

int main() {

	srand((unsigned int)time(NULL));

	Map mapa;
	UI ui;
	//ui.intro();
	mapa.load("map.txt");
		
	ui.printInterface(mapa);

	bool running = true;
	stringstream buffer;

	while (running) {

		string linha;
		
		getline(cin, linha);
		
		if (linha.size()==0 || linha.at(0)==' ') {
			ui.resetPrompt();
		}
		else if (linha == "sair") {
			running = false;
		}
		else if (linha== "prox"){
			ui.execCMD(mapa,buffer);
		}
		else {
			ui.processCMD(buffer, linha);
		}
	}

	return 0;
}