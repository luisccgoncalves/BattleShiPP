#ifndef __BATTLESHIPP_H__
#define __BATTLESHIPP_H__

#include <iostream>
#include <iterator>
#include <ctime>

#include "Map.h"

class UI {

	static const string banner;
	static const vector<string> comandos;
	static const vector<char> boatType;

	int xOffset = 1;
	int yOffset = 1;

	bool isNum(string num);
	int	 toNum(string num);
public:

	UI();

	void	intro();
	void	printInterface(const Map &mapa);
	void	printVars(const Map &mapa);
	void	updateInterface();
	void	updateInterface(const Map &mapa);
	bool	isCmdValid(string linha);
	int		getComandosPos(string cmd);
	void	execCMD(Map &mapa, stringstream &cmdlist);
	void	processCMD(stringstream &buffer, const string &linha);
	void	resetPrompt();
	void	resetLastCmd();
	void	compraNav(Map &mapa, string cmd);
	void	printMap(const Map &printThis);
	void	vaiPara(Map &mapa, string cmd);

};
#endif
