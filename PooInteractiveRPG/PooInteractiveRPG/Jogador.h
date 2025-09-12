#pragma once
#include "Personagem.h"
#include "Inventario.h"

class Jogador : public Personagem
{
public: 
	Jogador();
	~Jogador();

private:
	Inventario inventario;
};

