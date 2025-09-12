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
	float getBonusAtaque();
	float getBonusDefesa();

private:
	int id;
	string nome;
	char tipo; // A - Armadura, W - Arma, K - Key
	float bonusAtaque;
	float bonusDefesa;
};
