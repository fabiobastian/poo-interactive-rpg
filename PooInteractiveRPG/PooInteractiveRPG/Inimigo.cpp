#include "Inimigo.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define FILE_NAME "inimigos.txt"

Inimigo::Inimigo(){
    id = 0;
    nome = 'n';
    habilidade = 0.0;
    energia = 0.0;
    sorte = 0.0;
    nivel = 0;
    quantidadeMantimentos = 0;
    itens = {};
}

Inimigo Inimigo::InimigoVazio() {
    Inimigo inimigoVazio = Inimigo();

    return inimigoVazio;
}

Inimigo::~Inimigo(){}

int Inimigo::getId() const
{
    return this->id;
}

int Inimigo::getNivel() const
{
    return this->nivel;
}

int Inimigo::getQuantidadeMantimentos() const
{
    return this->quantidadeMantimentos;
}

vector<Item> Inimigo::getItens() const
{
    return this->itens;
}

Inimigo::Inimigo(int id, string nome, float habilidade, float energia, float sorte, int nivel, int quantidadeMantimentos, vector<Item> itens)
    : Personagem(id, nome, habilidade, energia, sorte)
{
    this->nivel = nivel;
    this->quantidadeMantimentos = quantidadeMantimentos;
    this->itens = itens;
}

string Inimigo::serialize() const
{
    string itensId;

    for (size_t i = 0; i < itens.size(); ++i) {
        itensId += std::to_string(itens[i].getId());
        if (i < itens.size() - 1) {
            itensId += ","; // adiciona o separador, exceto no último
        }
    }

    return to_string(this->id) + ";" +
        this->nome + ";" +
        to_string(this->habilidade) + ";" +
        to_string(this->energia) + ";" +
        to_string(this->sorte) + ";" +
        to_string(this->nivel) + ";" +
        to_string(this->quantidadeMantimentos) + ";" +
        itensId;
}

Inimigo Inimigo::deserialize(const string& data)
{
    vector<string> partes;
    stringstream ss(data);
    string parte;

    while (getline(ss, parte, ';')) {
        partes.push_back(parte);
    }

    if (partes.size() != 8) {
        throw runtime_error("Formato inválido para Inventario::deserialize");
    }

    vector<Item> itens = Item::findAllByIds(partes[7]);

    return Inimigo(
        stoi(partes[0]),    // id
        partes[1],          // nome
        stof(partes[2]),    // habilidade
        stof(partes[3]),    // energia
        stof(partes[4]),    // sorte
        stoi(partes[5]),    // nivel
        stoi(partes[6]),    // quantidadeMantimentos
        itens               // itens
    );
}

string Inimigo::findById(int id) {
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