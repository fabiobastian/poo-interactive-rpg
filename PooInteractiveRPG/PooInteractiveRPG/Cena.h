#pragma once
#include <string>
#include <vector>
#include "Decisao.h"

using namespace std;

class Cena
{
public:
	Cena();
	~Cena();

private:
	int id;
	int nivel;
	string texto;
	vector<Decisao> decisoes; // Possiveis escolhas
};
