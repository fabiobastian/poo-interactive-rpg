#pragma once
#include <string>
#include <vector>
#include "Decisao.h"
#include "Inimigo.h"
 

using namespace std;

class Cena
{
public:
	Cena();
	~Cena();
	Cena(int id, int nivel, char tipo, string texto, Inimigo inimigo, bool permiteFugir, vector<Decisao> decisoes);
	string serialize() const;
	static Cena deserialize(const string& data);
	void adicionarDecisao(const Decisao& item);
	void removerDecisao(const Decisao& item);
	static string findById(int id);
	vector<Cena> findAllByIds(string data);
	//getters
	int getId() const;
	vector<Decisao> getDecisoes() const;
	char getTipoCena();
	string getTexto();
	Inimigo getInimigo() const;
	bool getPermiteFugir();
	
private:
	int id;
	int nivel;
	char tipo; // B - batalha, D - dialogo
	string texto;
	vector<Decisao> decisoes; // Possiveis escolhas
	Inimigo inimigo;
	bool permiteFugir;
};
