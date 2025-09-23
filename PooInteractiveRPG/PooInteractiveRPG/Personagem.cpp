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
