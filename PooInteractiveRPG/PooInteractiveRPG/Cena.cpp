#include "Cena.h"
#include "Decisao.h"
#include "Inimigo.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#define FILE_NAME "cenas.txt"

Cena::Cena() {}
Cena::~Cena() {}


//construtor
Cena::Cena(int id, int nivel, char tipo, string texto, Inimigo inimigo, bool permiteFugir, vector<Decisao> decisoes)
{
    this->id = id;
    this->nivel = nivel;
    this->tipo = tipo;
    this->texto = texto;
    this->inimigo = inimigo;
    this->permiteFugir = permiteFugir;
    this->decisoes = decisoes;
}

//monta arquivo
string Cena::serialize() const
{
    string decisoesId;

    for (size_t i = 0; i < decisoes.size(); ++i) {
        decisoesId += std::to_string(decisoes[i].getId());
        if (i < decisoes.size() - 1) {
            decisoesId += ","; // adiciona o separador, exceto no últimoa
        }
    }

    return to_string(this->id) + ";" +decisoesId + ";" +to_string(this->inimigo.getId());
}

//le arquivo e retorna cena
Cena Cena::deserialize(const string& data)
{
    vector<string> partes;
    stringstream ss(data);
    string parte;

    //le o arquivo
    while (getline(ss, parte, ';')) {
        partes.push_back(parte);
    }

    if (partes.size() != 7) {// nao lembro se size == 8, eh 7 mesmo
        throw runtime_error("Formato inválido para Cena::deserialize");
    }

    //inicializa inimigo
    Inimigo inimigo = Inimigo::Inimigo();
;
    if (!partes[5].empty()) {
        Inimigo inimigo = Inimigo::deserialize(Inimigo::findById(stoi(partes[5])));
    }

    vector<Decisao> decisoes = Decisao::findAllByIds(partes[4]);;

    //em caso de bool pode-fugir vazio
    bool permiteFugir = partes[5] == "1" ? true : false;


    //retorna objeto do arquivo
    return Cena(
        stoi(partes[0]),    // id
        stoi(partes[1]),    //nivel
        partes[2][0],          //tipo -> errado
        partes[3],          //texto
        inimigo,            
        permiteFugir,
        decisoes /*stoi(partes[6])*/
        // exemplo 15;8;B;Dragão adulto guarda o castelo final.;14,20,25;18;0
 
    );
}


//adicionar decisao
void Cena::adicionarDecisao(const Decisao& decisao)
{
    for (const auto& decisa : this->decisoes) {
        if (decisa.getId() == decisao.getId()) {
            return;
        }
    }
    this->decisoes.push_back(decisao);
}

//remover decisao
void Cena::removerDecisao(const Decisao& decisao)
{
    auto it = std::remove_if(decisoes.begin(), decisoes.end(),
        [&decisao](const Decisao& decisa) { return decisa.getId() == decisao.getId(); });
    decisoes.erase(it, decisoes.end());
}

//getters

// Getters

int Cena::getId() const
{
    return this->id;
}

string Cena::getTexto() { return this->texto; }

//const -> constante -> nao sera alterado
vector<Decisao> Cena::getDecisoes() const{ return this->decisoes; }

//findbyid
string Cena::findById(int id) {
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

vector<Cena> Cena::findAllByIds(string data)
{
    vector<Cena> cenas;
    istringstream ss(data);
    string idStr;

    while (getline(ss, idStr, ',')) { // separa por vírgula
        if (idStr.empty()) continue;

        string linha = Cena::findById(stoi(idStr));

        if (!linha.empty()) {
            cenas.push_back(Cena::deserialize(linha));
        }
    }

    return cenas;
}


/*
void Cena::carregarCenaDoArquivo(const std::string& txtCena) {
    std::ifstream file(txtCena);
    if (!file) {
        std::cerr << "Erro: não consegui abrir " << txtCena << std::endl;
        return;
    }

    std::string line;
    texto = "";
    decisoes.clear();

    while (std::getline(file, line)) {
        if (line.rfind("#", 0) == 0) {
            // linha de decisão (#2: texto)
            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                int idDecisao = std::stoi(line.substr(1, colon - 1));
                int idProximaCena = std::stoi(line.substr(1, colon - 1));
                std::string texto = line.substr(colon + 1);
                Decisao carregarDecisaoDoArquivo(idDecisao, texto, idProximaCena);
                decisoes.push_back(carregarDecisaoDoArquivo);
            }
            else {
                id = std::stoi(line.substr(1));
            }
        }
        else if (line.rfind("I:", 0) == 0) {
            // linha de item: I: chave;c;0;0;0
            std::stringstream ss(line.substr(2));
            std::string chave;
            char tipo;
            int a, b, c;
            char sep;


        }
        else {
            // linha de descrição
            texto += line + "\n";
        }
    }
}
*/