#pragma once
#include <string>
#include "Item.h"

using namespace std;

class Escolha
{
public:
	Escolha();
	~Escolha();

private:
	int id;
	string texto;
	int idProximaCena;
	Item itemNecessario; // Se for null, não precisa de item para realizar a escolha
};
