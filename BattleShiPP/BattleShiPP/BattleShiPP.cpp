#include <iostream>
#include "consola.h"

using namespace std;

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

int main() {


	Consola::setTextColor(Consola::AZUL_CLARO);

	intro();

	Consola::getch();

	return 0;
}