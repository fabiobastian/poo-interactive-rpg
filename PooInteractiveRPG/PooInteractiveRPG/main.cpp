#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventario.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Jogo.h"

#define FILE_CENA "cenas.txt"
#define FILE_DECISAO "decisoes.txt"
#define FILE_INIMIGO "inimigos.txt"
#define FILE_INVENTARIO "inventarios.txt"
#define FILE_ITEM "itens.txt"
#define FILE_JOGADOR "jogadores.txt"
#define FILE_JOGO "jogos.txt"

using namespace std;

void telaInicial();
void iniciarNovoJogo();
int retornoProximoId(const string&);
Jogador criarJogador();
Jogo carregarJogo();
void continuarJogo(Jogo jogo);

int main()
{
	Jogo jogo = Jogo::deserialize(Jogo::findById(1));
	cout << "JOGO";
	cout << "\n" + jogo.serialize();

	Jogador jogador = jogo.getJogador();
	cout << "\nJOGADOR";
	cout << "\n" + jogador.serialize();

	Inventario inventario = jogador.getInventario();
	cout << "\nINVENTARIO";
	cout << "\n" + inventario.serialize();

	vector<Item> itens = inventario.getItens();
	cout << "\nQTD";
	cout << "\n" + to_string(itens.size());
	cout << "\n" + itens[0].serialize();
	cout << "\n" + itens[1].serialize();

	telaInicial();

	return 0;
}

void telaInicial()
{
	while (true)
	{
		int teclaMenu;
		cout << "\n0 - Sair\n";
		cout << "1 - Novo Jogo\n";
		cout << "2 - Carregar Jogo\n";
		cout << "3 - Exibir Créditos\n";

		if (!(cin >> teclaMenu)) {
			// se falhar, limpa o erro e descarta entrada inválida
			cout << "Entrada invalida! Digite apenas numeros.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (teclaMenu) {
		case 0:
			cout << "Saindo...\n";
			throw runtime_error("VOCE DECIDIU SAIR");
		case 1:
			cout << "Novo jogo iniciado!\n";
			iniciarNovoJogo();
			break;
		case 2:
			cout << "Carregando jogo...\n";
			continuarJogo(carregarJogo());
			break;
		case 3:
			cout << "Exibindo créditos...\n";
			break;
		default:
			cout << "Opção inválida!\n";
			break;
		}
	}
}


void iniciarNovoJogo()
{
	Jogador jogador = criarJogador();
	Jogo jogo = Jogo(retornoProximoId(FILE_JOGO), jogador, {Cena::deserialize(Cena::findById(1))});

	// jogo.save(); // Deixar comentado por enquanto, não ficar salvando um monte de personagens
}

Jogador criarJogador() {
	cout << "\n=== CRIACAO DO PERSONAGEM ===\n";

	string nome;
	float habilidade = 0, energia = 0, sorte = 0;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Digite o nome do jogador: ";
	getline(cin, nome);

	cout << "\nVoce tem 12 pontos para distribuir entre HABILIDADE, ENERGIA e SORTE.\n";
	cout << "Respeite os limites:\n";
	cout << " - Habilidade: 6 a 12\n";
	cout << " - Energia: 12 a 24\n";
	cout << " - Sorte: 6 a 12\n\n";

	int pontos = 12;
	while (true) {
		cout << "Pontos restantes: " << pontos << "\n";

		cout << "Atribua pontos adicionais para HABILIDADE (base 6): ";
		int addHab;
		cin >> addHab;
		habilidade = 6 + addHab;

		cout << "Atribua pontos adicionais para ENERGIA (base 12): ";
		int addEne;
		cin >> addEne;
		energia = 12 + addEne;

		cout << "Atribua pontos adicionais para SORTE (base 6): ";
		int addSor;
		cin >> addSor;
		sorte = 6 + addSor;

		int totalUsado = addHab + addEne + addSor;
		if (totalUsado > pontos) {
			cout << "\nVoce usou mais que 12 pontos! Tente novamente.\n\n";
		}
		else if (habilidade > 12 || energia > 24 || sorte > 12) {
			cout << "\nUm dos atributos excede o limite máximo! Tente novamente.\n\n";
		}
		else {
			break;
		}
	}

	Item arma = Item::deserialize(Item::findById(1));
	Item armadura = Item::deserialize(Item::findById(2));
	vector<Item> itens = { arma, armadura };
	Inventario inventario = Inventario(retornoProximoId(FILE_INVENTARIO), itens, armadura, arma, 1, 5);

	cout << "\nJogador criado com sucesso!\n";
	cout << "Nome: " << nome << "\n";
	cout << "Habilidade: " << habilidade << "\n";
	cout << "Energia: " << energia << "\n";
	cout << "Sorte: " << sorte << "\n";
	cout << "Arma equipada: " << inventario.getArmaduraEquipada().getNome() << "\n";
	cout << "Armadura equipada: " << inventario.getArmaduraEquipada().getNome() << "\n";
	cout << "Tesouros: " << inventario.getQuantidadeTesouros() << "\n";
	cout << "Mantimentos: " << inventario.getQuantidadeMantimentos() << "\n";

	return Jogador(retornoProximoId(FILE_JOGADOR), nome, habilidade, energia, sorte, inventario);
}

Jogo carregarJogo() {
	vector<Jogo> jogos = Jogo::findAll();


	if (jogos.empty()) {
		cout << "Nenhum jogo salvo encontrado.\n";
		cout << "Retornando ao menu anterior, crie um novo jogo!!\n";
	}

	cout << "\n=== ESCOLHA O JOGO QUE DESEJA CARREGAR ===\n";

	for (size_t i = 0; i < jogos.size(); ++i) {
		cout << "Identificador:  " << jogos[i].getId() << "\n";
		cout << "Jogador: " << jogos[i].getJogador().getNome() << "\n";
		cout << "Quantidade cenas: " << jogos[i].getCenas().size() << "\n";
	}

	int idEscolhido;

	while (true) {
		cout << "Digite o ID do jogo que deseja carregar: ";
		if (!(cin >> idEscolhido)) {
			cout << "Entrada inválida. Digite um número.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		// verifica se o ID existe
		for (size_t i = 0; i < jogos.size(); ++i) {
			if (jogos[i].getId() == idEscolhido) {
				cout << "\nCarregando jogo de " << jogos[i].getJogador().getNome() << "...\n";
				return jogos[i];
			}
		}

		cout << "ID não encontrado. Tente novamente.\n";
	}
	return {};
}

void continuarJogo(Jogo jogo)
{
	cout << jogo.serialize();
	// PAREI AQUI, se quiser continuar, fazer equema para jogar ele na tela 1
	// E após isso ir carregando as proximas telas, batalhar e afins
}

int retornoProximoId(const string& nomeArquivo) {
	ifstream file(nomeArquivo);
	if (!file.is_open()) {
		throw runtime_error("Não foi possível abrir o arquivo: " + nomeArquivo);
	}

	string line;
	while (getline(file, line)) {
		if (line.empty())
			continue;

		istringstream iss(line);
		string idStr;
		getline(iss, idStr, ';');

		return stoi(idStr) + 1; // converte para int

	}

	return 1;
}