#pragma once
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Inventario
{
public:
	Inventario();
	~Inventario();

private:
	vector<Item> itens;
	Item armaduraEquipada;
	Item armaEquipada;
	int quantidadeTesouros;
	int quantidadeMantimentos;
};

