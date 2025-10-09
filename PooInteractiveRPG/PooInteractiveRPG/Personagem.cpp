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

float Personagem::atacar() const
{
    return this->habilidade;
}

float Personagem::atacar()
{
    return this->habilidade;
}

float Personagem::tomarDano(float danoBruto)
{
    if (danoBruto < 0)
    {
        return 0.0f;
    }
    this->energia -= danoBruto;
    return danoBruto;
}

string Personagem::getNome() const
{
    return this->nome;
}

float Personagem::getEnergia() const
{
    return this->energia;
}
