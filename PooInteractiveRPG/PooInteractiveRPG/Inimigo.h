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
	int nivel;
	int quantidadeMantimentos;
	vector<Item> itens;
};
