#pragma once
#include <vector>
#include "Personagem.h"
#include "Item.h"

class Inimigo : public Personagem
{
public:
	Inimigo();
	~Inimigo();
	static Inimigo InimigoVazio();
	Inimigo(int id, string nome, float habilidade, float energia, float sorte, int nivel, int quantidadeMantimentos, vector<Item> itens);
	string serialize() const;
	static Inimigo deserialize(const string& data);
	static string findById(int id);
	int getId() const;

private:
	int nivel;
	int quantidadeMantimentos;
	vector<Item> itens;
};
