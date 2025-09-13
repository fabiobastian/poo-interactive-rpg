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

private:
	int id;
	Jogador jogador;
	vector<Cena> cenasVisitadas; // Cenas que o Jogador passou, quando cenaBatalha, só salva se venceu boss
};

