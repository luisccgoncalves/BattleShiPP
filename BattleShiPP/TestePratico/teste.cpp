#include <iostream>
#include <string>

using namespace std;

class Computador {



public:
	const string marca;
	const string processador;

	int ram;
	int freq;

	Computador(string marca, int ram, int freq, string processador = "Intel"):
		marca(marca), ram(ram), freq(freq), processador(processador) {
	
		if (ram < 0)this->ram = 2048;
		if (freq < 0)this->freq = 2000;
	};


};

int main() {

	Computador PC("hp",-1,-1,"AMD");

	//PC.marca = "batatas";
	cout << PC.freq << endl;
	//PC.freq = -1;

	cout << PC.freq << endl;

	return 0;
}
