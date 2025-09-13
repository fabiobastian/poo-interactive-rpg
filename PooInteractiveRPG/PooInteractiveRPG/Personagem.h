#pragma once
#include <string> 

using namespace std;

class Personagem
{
public:
	Personagem();
	~Personagem();

protected:
	int id;
	string nome;
	float habilidade;
	float energia;
	float sorte; // Sempre que for usada perde 1 ponto
};
