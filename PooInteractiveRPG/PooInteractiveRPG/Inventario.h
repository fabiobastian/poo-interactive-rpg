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
	int id;
	vector<Item> itens; // Prestar aten��o em n�o colocar itens repetidos
	Item armaduraEquipada;
	Item armaEquipada;
	int quantidadeTesouros; // Somente usada para carregar o score do jogador
	int quantidadeMantimentos; // 1 mantimento recarrega 1 ponto de energia
};
