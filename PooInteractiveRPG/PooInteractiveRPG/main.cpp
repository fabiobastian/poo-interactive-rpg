#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventario.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Jogo.h"
#include "Cena.h"

using namespace std;

int main()
{
	//start
	void carregarDecisaoDoArquivo(int id, string texto, int idProximaCena, Item itemNecessario);

	std::cout << "Hello World" << std::endl;

	//stop
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

	Cena cena = Cena::deserialize(Cena::findById(1));
	cout << "\nCENA";
	cout << "\n" + cena.serialize();

	return 0;
} 
