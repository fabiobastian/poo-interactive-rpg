#pragma once
#include <string>
#include "Item.h"

using namespace std;

class Decisao
{
public:
	Decisao();
	~Decisao();

private:
	int id;
	string texto;
	int idProximaCena;
	Item itemNecessario; // Se for null, n�o precisa de item para realizar a escolha
};
