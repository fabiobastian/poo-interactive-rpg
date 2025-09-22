#include "Item.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define FILE_NAME "itens.txt"

using namespace std;

Item::Item(){}
Item::~Item(){}

Item::Item(int id, string nome, char tipo, float bonus)
{
	this->id = id;
	this->nome = nome;
	this->tipo = tipo;
	this->bonus = bonus;
}

// Tem mais não vai ser usado, pois não vamos gravar, itens imutaveis
string Item::serialize() const
{
    return to_string(this->id) + ";" +
        this->nome + ";" +
        this->tipo + ";" +
        to_string(this->bonus);
}

Item Item::deserialize(const string& data)
{
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

int Item::getId() const
{
	return this->id;
}

string Item::getNome() const
{
	return this->nome;
}

char Item::getTipo() const
{
	return this->tipo;
}

float Item::getBonus() const
{
	return this->bonus;
}

string Item::findById(int id) {
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo: " + string(FILE_NAME));
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string idStr;
        getline(iss, idStr, ';'); // pega o primeiro campo separado por ;

        int idLinha = stoi(idStr); // converte para int
        if (idLinha == id) {
            return line; // encontrou, retorna a linha inteira
        }
    }

    return ""; // não encontrou
}

vector<Item> Item::findAllByIds(string data)
{
    vector<Item> items;
    istringstream ss(data);
    string idStr;

    while (getline(ss, idStr, ',')) { // separa por vírgula
        if (idStr.empty()) continue;

        string linha = Item::findById(stoi(idStr));

        if (!linha.empty()) {
            items.push_back(Item::deserialize(linha));
        }
    }

    return items;
}