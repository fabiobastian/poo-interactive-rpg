#pragma once
#include <vector>
#include "Jogador.h"
#include "Cena.h"

using namespace std;

class Jogo
{
public:
	Jogo();
	~Jogo();
	Jogo(int id, Jogador jogador, vector<Cena> cenasVisitadas);
	string serialize() const;
	static Jogo deserialize(const string& data);
	static string findById(int id);
	void save() const;
	Jogador& getJogador();

private:
	int id;
	Jogador jogador;
	vector<Cena> cenasVisitadas; // Cenas que o Jogador passou, quando cenaBatalha, só salva se venceu boss
};

