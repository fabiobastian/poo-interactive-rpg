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
	string texto;
	int proximaCena;
	Item itemNecessario; // Se for null, n�o precisa de item para realizar a escolha
};

