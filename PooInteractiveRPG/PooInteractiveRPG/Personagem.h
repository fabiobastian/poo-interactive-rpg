#pragma once
#include <string> 

using namespace std;

class Personagem
{
public:
	Personagem();
	~Personagem();
	Personagem(int id, string nome, float habilidade, float energia, float sorte);
	float atacar();
	virtual float atacar(float multiplicador = 1.0f);
	virtual float tomarDano(float danoBruto);

protected:
	int id;
	string nome;
	float habilidade;
	float energia;
	float sorte; // Sempre que for usada perde 1 ponto
};
