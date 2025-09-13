#pragma once
#include <string>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	string getNome();
	string getTipo();
	float getBonus();

private:
	int id;
	string nome;
	char tipo; // A - Armadura, W - Arma
	float bonus; // Se for A - o bonus será de defesa, se for W - o bonus será de ataque
};
