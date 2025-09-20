#include "Item.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

Item::Item(){};
Item::~Item(){}

Item::Item(int id, string nome, char tipo, float bonus)
{
	this->id = id;
	this->nome = nome;
	this->tipo = tipo;
	this->bonus = bonus;
}

int Item::getId()
{
	return this->id;
}

string Item::getNome()
{
	return this->nome;
}

char Item::getTipo()
{
	return this->tipo;
}

float Item::getBonus()
{
	return this->bonus;
}

// Tem mais não vai ser usado, pois não vamos gravar, itens imutaveis
string Item::serialize() const
{
	return to_string(this->id) + ";" +
		this->nome + ";" +
		this->tipo + ";" +
		to_string(this->bonus);
}

// const string& data -> recebe a referencia da string data imutavel, somente leitura
Item Item::deserialize(const string& data) {
    vector<string> partes;
    stringstream ss(data);
    string parte;

    while (getline(ss, parte, ';')) {
        partes.push_back(parte);
    }

    if (partes.size() != 4) {
        throw runtime_error("Formato inválido para Item::deserialize");
    }

    return Item(
        stoi(partes[0]),    // id
        partes[1],          // nome
        partes[2][0],       // tipo -> tem que usar [2][0] pois é uma string sendo convertida em char
        stof(partes[3])     // bonus
    );
}
