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
	char nivel; // I - Inicial, M - M�dio, D - Dif�cil
	int quantidadeMantimentos;
	vector<Item> itens;
};
