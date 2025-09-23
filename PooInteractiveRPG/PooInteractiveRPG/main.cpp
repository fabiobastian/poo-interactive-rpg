#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventario.h"
#include "Jogador.h"
#include "Inimigo.h"

using namespace std;

int main()
{
	Inventario inventario = Inventario::deserialize(Inventario::findById(2));

	cout << "INVENTARIO\n" + inventario.serialize();
	inventario.adicionarItem(Item::deserialize(Item::findById(1)));
	inventario.equiparArmadura(Item::deserialize(Item::findById(2)));
	inventario.save();
	cout << "\n" + inventario.serialize();

	Jogador jogador = Jogador::deserialize(Jogador::findById(1));

	cout << "\nJOGADOR\n" + jogador.serialize();
	cout << "\n" + jogador.getInventario().serialize();
	//jogador.getInventario().adicionarTesouro(100);
	cout << "\n" + jogador.getInventario().serialize();
	jogador.save();
	cout << "\n" + jogador.serialize();

	Inimigo inimigo = Inimigo::deserialize(Inimigo::findById(1));

	cout << "\nINIMIGO\n" + inimigo.serialize();

	return 0;
}
