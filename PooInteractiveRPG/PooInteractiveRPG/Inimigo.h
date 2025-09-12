#pragma once
#include <vector>
#include "Personagem.h"
#include "Item.h"

class Inimigo : public Personagem
{
public:
	Inimigo();
	~Inimigo();

private:
	char nivel; // I - Inicial, M - Médio, D0 - Difícil
	int quantidadeMantimentos;
	vector<Item> itens;
};

