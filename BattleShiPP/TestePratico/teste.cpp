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

class Aluno {

	string nome; // nome do aluno
	string & escola; // nome da escola
	const int numero; // numero do aluno
public:
	// Construtor
	Aluno(string s, string & es, int num): nome(s), escola(es), numero(num){	};
};

class Motor{

	int cilind, pot;

 public:

	Motor(int cil, int p) { 
		cilind = cil; 
		pot = p; 
	}

	int getCil() { 
		return cilind; 
	} 
	
	int getPot() { 
		return pot; 
	}

};

class Aviao {
	Motor esquerdo, direito;
public:
	Aviao(int cilind, int pot) : esquerdo { cilind, pot }, direito{ cilind, pot }{

	};
	// ...
};

class Autocarro {
	const string marca;
	int numpass;
public:

	Autocarro(string brand, int num) :marca(brand),numpass(num){};
	string getMarca() const{ return marca; }
	int &passageiros() { return numpass; }
};



int main() {

	const Autocarro a("MBW", 30);
	Autocarro b("VW", 40);
	cout << "marca: " << a.getMarca();
	// muda número de passageiros
	b.passageiros() = 20;


	string esc = "ISEC";

	Aluno eu("manel", esc, 21260);
	Aluno coiso("Zé",esc,123123);

	Aviao boing(1,1);

	//cout << eu.nome << endl << eu.escola << endl << eu.numero;

	Computador PC("hp",-1,-1,"AMD");

	//PC.marca = "batatas";
	cout << PC.freq << endl;
	//PC.freq = -1;

	cout << PC.freq << endl;

	return 0;
}
