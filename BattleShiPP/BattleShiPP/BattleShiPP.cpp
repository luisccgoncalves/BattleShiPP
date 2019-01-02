#include "BattleShiPP.h"

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

const vector<char> UI::boatType{
	'V',			//0 - Veleiro
	'G',			//1 - Galeão
	'E',			//2 - Escuna
	'F',			//3 - Fragata
	'S'				//4 - Special
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

	printVars(mapa);
	printMap(mapa);

	Consola::gotoxy(1, 22);
	cout << '>';
}

void UI::printVars(const Map &mapa) {

	Consola::gotoxy(42, 1);
	cout << "\20MOEDAS:" << mapa.getMoedas();
	
	Harbour *mainH=mapa.getMainHarbour();

	Consola::gotoxy(42, 2);
	cout << "\20Porto Principal: " << mainH->getSprite().getSprite();
	Consola::gotoxy(46, 3);
	cout << "\20N\247Barcos PP: " << mainH->getDockedBoats().size();
}

void	UI::updateInterface() {

	Consola::clrspc(42, 20, 37);
	resetPrompt();

};

void	UI::updateInterface(const Map &mapa) {

	printVars(mapa);
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
					for(auto it : boatType)
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
				if (palavras.size() == 3 && isNum(palavras[1]) && !isNum(palavras[2]))
					return true;
				else {
					int numNum = 0;
					for (unsigned int i = 1; i < palavras.size(); i++)
						numNum += isNum(palavras[i]);
					if ((numNum == 3 && palavras.size() == 4))
						return true;
				}
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
		case 0:	 //exec <nomeFicheiro>
			break;
		case 1:  //compranav <T>
			compraNav(mapa, cmd);
			break;
		case 3:	 //lista
			break;
		case 4:	 //compra <N> <M>
			break;
		case 5:  //vende <N>
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
			vaiPara(mapa, cmd);
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

//Clears the last command input
void UI::resetLastCmd() {
	
	Consola::clrspc(42, 20, 37);
}

void UI::compraNav(Map &mapa, string cmd) {

	//discard compranav part
	string param = cmd.substr(cmd.find(" ")+1, cmd.back());

	mapa.buyBoat(param);

}

void UI::printMap(const Map &printThis) {

	Sprite sprite;

	for (int y = 0; y < printThis.getLin(); y++) {
		for (int x = 0; x < printThis.getCol(); x++) {
			sprite=printThis.getCell(x, y)->getSprite();
			for(int ySquare=0;ySquare<2;ySquare++)
				for (int xSquare=0; xSquare < 2; xSquare++) {
					Consola::gotoxy(xOffset + (x*2) + xSquare, yOffset + (y*2) + ySquare);
					Consola::setBackgroundColor(
						((x % 2) && !(y % 2)) || (!(x % 2) && (y % 2))?		//Makes the chess patern
							sprite.getSpriteColor():
							sprite.getSpriteColor() +8);
					putchar(sprite.getSprite());
				}
		}
	}

	Consola::setBackgroundColor(Consola::PRETO);
}

void UI::vaiPara(Map &mapa, string cmd) {
	istringstream iss(cmd);

	vector<string> param{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };

	cout << param.size();
	Sleep(5000);
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