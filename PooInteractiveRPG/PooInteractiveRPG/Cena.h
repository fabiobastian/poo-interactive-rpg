#pragma once
#include <string>
#include <vector>
#include "Decisao.h"

class Cena
{
public:

private:
	int id;
	int nivel;
	string texto;
	vector<Decisao> decisoes; // Possiveis escolhas
};
