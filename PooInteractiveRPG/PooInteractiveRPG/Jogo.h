#pragma once
#include <vector>
#include "Jogador.h"
#include "Cena.h"

class Jogo
{
public:

private:
	int id;
	Jogador jogador;
	vector<Cena> cenas; // Cenas que o Jogador passou, quando cenaBatalha, só salva se venceu boss
};

