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
	float habilidade;
	float energia;
	float sorte;
};
