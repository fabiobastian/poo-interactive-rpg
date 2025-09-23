#include "Jogador.h"
#include "Inventario.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define FILE_NAME "jogadores.txt"

Jogador::Jogador(){}
Jogador::~Jogador(){}

Jogador::Jogador(int id, string nome, float habilidade, float energia, float sorte, Inventario inventario) 
    : Personagem(id, nome, habilidade, energia, sorte)
{
    this->inventario = inventario;
}

string Jogador::serialize() const
{
    return to_string(this->id) + ";" +
        this->nome + ";" +
        to_string(this->habilidade) + ";" +
        to_string(this->energia) + ";" +
        to_string(this->sorte) + ";" +
        to_string(this->inventario.getId());
}

Jogador Jogador::deserialize(const string& data)
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

    Inventario inventario = Inventario::deserialize(Inventario::findById(stoi(partes[5])));

    return Jogador(
        stoi(partes[0]),    // id
        partes[1],          // nome
        stof(partes[2]),    // habilidade
        stof(partes[3]),    // energia
        stof(partes[4]),    // sorte
        inventario          // inventario
    );
}

string Jogador::findById(int id) {
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

void Jogador::save() const
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

    // Salvar o atributo inventario quando o jogador for salvo
    this->inventario.save();
}

Inventario& Jogador::getInventario()
{
    return this->inventario;
}

int Jogador::getId() const
{
    return this->id;
}

float Jogador::atacar(float multiplicador)
{
    return (this->habilidade + this->inventario.getArmaEquipada().getBonus()) * multiplicador;
}

float Jogador::tomarDano(float danoBruto)
{
    return this->energia -= (this->inventario.getArmaduraEquipada().getBonus() + danoBruto);
}

bool Jogador::testarSorte()
{
    std::srand(std::time(nullptr)); // inicializa a semente com o tempo atual
    int numero = (std::rand() % 8) + 1;
    if (numero > this->sorte)
    {
        return false;
    }
    // Se caso ganhar na sorte, diminui sua sorte
    this->sorte -= 1;
    return true;
}
