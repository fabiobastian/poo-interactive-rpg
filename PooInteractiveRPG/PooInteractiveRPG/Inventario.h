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
	Inventario(int id, vector<Item> itens, Item armaduraEquipada, Item armaEquipada, int quantidadeTesouros, int quantidadeMantimentos);
	string serialize() const;
	static Inventario deserialize(const string& data);
	static string findById(int id);
	void save() const;
	void adicionarItem(const Item& item);
	void removerItem(const Item& item);
	void equiparArmadura(const Item& item);
	void equiparArma(const Item& item);
	void adicionarTesouro(int quantidade);
	void adicionarMantimento(int quantidade);
	void usarMantimento(int quantidade);

private:
	int id;
	vector<Item> itens; // Prestar atenção em não colocar itens repetidos
	Item armaduraEquipada; // A partir que tem equipado, não desequipa mais, apenas troca
	Item armaEquipada; // A partir que tem equipado, não desequipa mais, apenas troca
	int quantidadeTesouros; // Somente usada para carregar o score do jogador
	int quantidadeMantimentos; // 1 mantimento recarrega 1 ponto de energia
};
