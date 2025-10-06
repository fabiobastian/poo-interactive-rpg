#include "Inventario.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define FILE_NAME "inventarios.txt"

Inventario::Inventario(){}
Inventario::~Inventario(){}

Inventario::Inventario(int id, vector<Item> itens, Item armaduraEquipada, Item armaEquipada, int quantidadeTesouros, int quantidadeMantimentos)
{
	this->id = id;
	this->itens = itens;
	this->armaduraEquipada = armaduraEquipada;
	this->armaEquipada = armaEquipada;
	this->quantidadeTesouros = quantidadeTesouros;
	this->quantidadeMantimentos = quantidadeMantimentos;
}

string Inventario::serialize() const
{
    string itensId;

    for (size_t i = 0; i < itens.size(); ++i) {
        itensId += std::to_string(itens[i].getId());
        if (i < itens.size() - 1) {
            itensId += ","; // adiciona o separador, exceto no últimoa
        }
    }

    return to_string(this->id) + ";" +
        itensId + ";" +
        to_string(this->armaduraEquipada.getId()) + ";" +
        to_string(this->armaEquipada.getId()) + ";" +
        to_string(this->quantidadeTesouros) + ";" +
        to_string(this->quantidadeMantimentos);
}

Inventario Inventario::deserialize(const string& data)
{
    vector<string> partes;
    stringstream ss(data);
    string parte;

    while (getline(ss, parte, ';')) {
        partes.push_back(parte);
    }

    if (partes.size() != 6) {
        throw runtime_error("Formato inválido para Inventario::deserialize");
    }

    vector<Item> itens = Item::findAllByIds(partes[1]);
    Item armaduraEquipada = Item::deserialize(Item::findById(stoi(partes[2])));
    Item armaEquipada = Item::deserialize(Item::findById(stoi(partes[3])));

    return Inventario(
        stoi(partes[0]),    // id
        itens,              // itens
        armaduraEquipada,   // armaduraEquipada
        armaEquipada,       // armaEquipada
        stoi(partes[4]),    // quantidadeTesouros
        stoi(partes[5])     // quantidadeMantimentos
    );
}

void Inventario::adicionarItem(const Item& item)
{
    for (const auto& it : this->itens) {
        if (it.getId() == item.getId()) {
            return;
        }
    }
    this->itens.push_back(item);
}


void Inventario::removerItem(const Item& item)
{
    auto it = std::remove_if(itens.begin(), itens.end(),
        [&item](const Item& i) { return i.getId() == item.getId(); });
    itens.erase(it, itens.end());
}

void Inventario::equiparArmadura(const Item& item)
{
    if (item.getTipo() != 'A')
    {
        return;
    }
    for (const auto& it : this->itens) {
        if (it.getId() == item.getId()) {
            this->armaduraEquipada = item;
            return;
        }
    }
}

void Inventario::equiparArma(const Item& item)
{
    if (item.getTipo() != 'W')
    {
        return;
    }
    for (const auto& it : this->itens) {
        if (it.getId() == item.getId()) {
            this->armaEquipada = item;
            return;
        }
    }
}

void Inventario::adicionarTesouro(int quantidade)
{
    if (quantidade < 0)
    {
        return;
    }
    this->quantidadeTesouros += quantidade;
}

void Inventario::adicionarMantimento(int quantidade)
{
    if (quantidade < 0)
    {
        return;
    }
    this->quantidadeMantimentos += quantidade;
}

void Inventario::usarMantimento(int quantidade)
{
    if (quantidade < 0 or this->quantidadeMantimentos < quantidade)
    {
        return;
    }
    this->quantidadeMantimentos -= quantidade;
}

int Inventario::getId() const
{
    return this->id;
}

vector<Item> Inventario::getItens() const
{
    return this->itens;
}

Item Inventario::getArmaduraEquipada() const
{
    return this->armaduraEquipada;
}

Item Inventario::getArmaEquipada() const
{
    return this->armaEquipada;
}

string Inventario::findById(int id) {
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

void Inventario::save() const
{
    // 1. Ler todas as linhas do arquivo
    std::ifstream infile(FILE_NAME);
    std::vector<std::string> linhas;
    std::string linha;

    bool atualizado = false;

    if (infile.is_open()) {
        while (std::getline(infile, linha)) {
            if (linha.empty()) continue;

            // Pega o id da linha
            std::istringstream ss(linha);
            std::string idStr;
            std::getline(ss, idStr, ';');

            int idLinha = std::stoi(idStr);

            if (idLinha == this->id) {
                // Substitui a linha pelo serialize
                linhas.push_back(this->serialize());
                atualizado = true;
            }
            else {
                linhas.push_back(linha);
            }
        }
        infile.close();
    }

    // Se não encontrou o id, adiciona no final
    if (!atualizado) {
        linhas.push_back(this->serialize());
    }

    // 2. Regravar o arquivo inteiro
    std::ofstream outfile(FILE_NAME, std::ios::trunc);
    if (!outfile.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + std::string(FILE_NAME));
    }

    for (const auto& l : linhas) {
        outfile << l << "\n";
    }

    outfile.close();
}