#include "Jogo.h"
#include "Jogador.h"
#include "Cena.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define FILE_NAME "jogos.txt"

using namespace std;

Jogo::Jogo(){}
Jogo::~Jogo(){}

Jogo::Jogo(int id, Jogador jogador, vector<Cena> cenasVisitadas)
{
	this->id = id;
	this->jogador = jogador;
	this->cenasVisitadas = cenasVisitadas;
}

string Jogo::serialize() const
{
    string cenasId;

    for (size_t i = 0; i < cenasVisitadas.size(); ++i) {
        cenasId += to_string(cenasVisitadas[i].getId());
        if (i < cenasVisitadas.size() - 1) {
            cenasId += ","; // adiciona o separador, exceto no último
        }
    }

    return to_string(this->id) + ";" +
		to_string(this->jogador.getId()) + ";" +
        cenasId;
}

Jogo Jogo::deserialize(const string& data)
{
    vector<string> partes;
    stringstream ss(data);
    string parte;

    while (getline(ss, parte, ';')) {
        partes.push_back(parte);
    }

    if (partes.size() != 3) {
        throw runtime_error("Formato inválido para Inventario::deserialize");
    }

    Jogador jogador = Jogador::deserialize(Jogador::findById(stoi(partes[1])));
    vector<Cena> cenas = Cena::findAllByIds(partes[2]);

    return Jogo(
        stoi(partes[0]),    // id
        jogador,            // jogador
        cenas               // cenasVisitadas
    );
}

string Jogo::findById(int id) {
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

void Jogo::save() const
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

            // Unica ref do objeto neste trecho de codigo this->id
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

    // Salvar o atributo objeto jogador quando o jogo for salvo
    this->jogador.save();
}

Jogador& Jogo::getJogador()
{
    return this->jogador;
}

vector<Cena> Jogo::getCenas() const
{
    return this->cenasVisitadas;
}