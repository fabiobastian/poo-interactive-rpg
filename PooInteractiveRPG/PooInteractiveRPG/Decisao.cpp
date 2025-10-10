#include "Decisao.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define FILE_NAME "decisoes.txt"

Decisao::Decisao(){}
Decisao::~Decisao(){}

//getters
int Decisao::getId() const
{
    return this->id;
}

string Decisao::getTexto() const
{
    return this->texto;
}

int Decisao::getIdProximaCena() const
{
    return this->idProximaCena;
}

Item Decisao::getItemNescessario() const
{
    return this->itemNecessario;
}

//construtor
Decisao::Decisao(int id, string texto, int idProximaCena, Item itemNecessario)
{
    this->id = id;
    this->texto = texto;
    this->idProximaCena = idProximaCena;
    this->itemNecessario = itemNecessario;
}

string Decisao::findById(int id) {
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

vector<Decisao> Decisao::findAllByIds(string data)
{
    vector<Decisao> decisoes;
    istringstream ss(data);
    string idStr;

    while (getline(ss, idStr, ',')) { // separa por vírgula
        if (idStr.empty()) continue;

        string linha = Decisao::findById(stoi(idStr));

        if (!linha.empty()) {
            decisoes.push_back(Decisao::deserialize(linha));
        }
    }

    return decisoes;
}

// Usar uma forma diferente de retirar os dados por conta de erros com campos vazios
static vector<string> splitPreserveEmpty(const string& s, char delim) {
    vector<string> out;
    size_t start = 0;
    size_t pos;
    while ((pos = s.find(delim, start)) != string::npos) {
        out.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    // último campo (pode ser vazio)
    out.push_back(s.substr(start));
    return out;
}

Decisao Decisao::deserialize(const string& data)
{
    auto partes = splitPreserveEmpty(data, ';');

    if (partes.size() != 4)
    {
        throw runtime_error("Formato inválido para Item::deserialize");
    }

    Item item = Item::Item();
    
    if (!partes[3].empty()) {
        item = Item::deserialize(Item::findById(stoi(partes[3])));
    }

    return Decisao(
        stoi(partes[0]),    // id
        partes[1],          // nome
        stoi(partes[2]),    // idProximaCena
        item                // itemNecessario
    );
}
