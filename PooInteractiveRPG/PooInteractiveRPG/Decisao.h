#pragma once
#include <string>
#include "Item.h"

using namespace std;

class Decisao
{
public:
	Decisao();
	~Decisao();
	Decisao(int id, string texto, int idProximaCena, Item itemNecessario);

	string serialize() const;
	static vector<Decisao> findAllByIds(string data);
	static Decisao deserialize(const string& data);
	static string findById(int id);

	//getters
	int getId() const;
	string getTexto() const;
	int getIdProximaCena() const;
	Item getItemNescessario() const;

private:
	int id;
	string texto;
	int idProximaCena;
	Item itemNecessario; // Se for null, não precisa de item para realizar a escolha
};
