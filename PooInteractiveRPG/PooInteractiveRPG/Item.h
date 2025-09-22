#pragma once
#include <string>
#include <vector>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	Item(int id, string nome, char tipo, float bonus);
	string serialize() const;
	static Item deserialize(const string& data);
	static string findById(int id);
	static vector<Item> findAllByIds(string data);
	int getId() const;
	string getNome() const;
	char getTipo() const;
	float getBonus() const;

private:
	int id;
	string nome;
	char tipo; // A - Armadura, W - Arma
	float bonus; // Se for A - o bonus será de defesa, se for W - o bonus será de ataque
};
