#include "Personagem.h"

using namespace std;

Personagem::Personagem(){}
Personagem::~Personagem(){}
Personagem::Personagem(int id, string nome, float habilidade, float energia, float sorte)
{
    this->id = id;
    this->nome = nome;
    this->habilidade = habilidade;
    this->energia = energia;
    this->sorte = sorte;
}

float Personagem::atacar()
{
    return this->habilidade;
}

float Personagem::atacar(float multiplicador)
{
    return this->habilidade * multiplicador;
}

float Personagem::tomarDano(float danoBruto)
{
    if (danoBruto < 0)
    {
        return 0.0f;
    }
    return this->energia - danoBruto;
}
