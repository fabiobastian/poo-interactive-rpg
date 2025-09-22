#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventario.h"

using namespace std;

int main()
{
	Inventario inventario = Inventario::deserialize(Inventario::findById(1));

	cout << "\n" + inventario.serialize();
	inventario.adicionarItem(Item::deserialize(Item::findById(3)));
	inventario.save();
	cout << "\n" + inventario.serialize();

	return 0;
}
