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
	static vector<Cena> findAllByIds(string data);
	int getId() const;

private:
	int id;
	int nivel;
	char tipo; // B - batalha, D - dialogo
	string texto;
	vector<Decisao> decisoes; // Possiveis escolhas
};
