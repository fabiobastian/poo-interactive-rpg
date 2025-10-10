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
void continuarJogo(Jogo& jogo);
void carregarCena(int id, Jogo& jogo);
bool jogadorPossuiItem(Jogador& jogador, const Item& itemNecessario);
bool iniciarCombate(Jogador jogador, Inimigo inimigo);
void abrirInventario(Jogador& jogador);
void exibirCreditos();

int main()
{
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
		case 2: {
			cout << "Carregando jogo...\n";
			Jogo jogo = carregarJogo();
			continuarJogo(jogo);
			break;
		}	
		case 3:
			exibirCreditos();
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
	Jogo jogo = Jogo(retornoProximoId(FILE_JOGO), jogador, {});

	jogo.save(); // Deixar comentado por enquanto, não ficar salvando um monte de personagens
	continuarJogo(jogo);
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

void continuarJogo(Jogo& jogo) {
	if (jogo.getCenas().empty()) {
		carregarCena(1, jogo);
	}
	vector<Cena> cenas = jogo.getCenas();
	// Basicamente se já foi visitado as cenas, pega a ultima cena salva
	carregarCena(cenas[cenas.size() - 1].getId(), jogo);
}

void carregarCena(int id, Jogo& jogo) {
	Jogador jogador = jogo.getJogador();
	Cena cena = Cena::deserialize(Cena::findById(id));

	// Cabeçalho dependendo do tipo
	cout << "========================================\n";
	if (cena.getTipoCena() == 'B') {
		cout << "CENA (BATALHA)" << "\n";
		cout << "Nome inimigo: " << cena.getInimigo().getNome() << "\n";
		cout << "Nivel inimigo:" << to_string(cena.getInimigo().getNivel()) << "\n";
	}
	else {
		cout << "CENA (DIALOGO)\n\n";
	}

	// Texto da cena
	cout << cena.getTexto() << "\n\n";

	vector<Decisao> decisoes = cena.getDecisoes();

	if (decisoes.empty()) {
		throw runtime_error("DADOS CORROMPIDOS.\n");
		return;
	}

	// Listar decisões, marcando as bloqueadas por falta de item
	cout << "Escolhas:\n";
	for (size_t i = 0; i < decisoes.size(); ++i) {
		Decisao decisao = decisoes[i];
		bool pode = jogadorPossuiItem(jogador, decisao.getItemNescessario());

		cout << (i + 1) << ") " << decisao.getTexto();
		if (!pode) {
			// Exibe qual item é necessário (se tiver nome)
			if (!decisao.getItemNescessario().getNome().empty()) {
				cout << "  [BLOQUEADO - necessita: " << decisao.getItemNescessario().getNome() << "]";
			}
			else {
				cout << "  [BLOQUEADO - item necessário]";
			}
		}
		cout << "\n";
	}

	// Ler escolha do usuário (apenas números entre 1 a n)
	int escolha = 0;
	while (true) {

		if (!(cin >> escolha)) {
			cout << "Entrada inválida. Digite um número.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (escolha < 1 || escolha > decisoes.size()) {
			cout << "Escolha inválida. Digite um número entre 1 e " << decisoes.size() << ".\n";
			continue;
		}

		const Decisao& decisao = decisoes[escolha - 1];
		if (!jogadorPossuiItem(jogador, decisao.getItemNescessario())) {
			cout << "Você não possui o item necessário para essa escolha.\n";
			// pode permitir tentar outra escolha ou permitir cancelar — aqui pedimos nova escolha
			continue;
		}

		bool venceu = false;
		if (cena.getTipoCena() == 'B') {
			Inimigo inimigo = cena.getInimigo();

			if (decisao.getId() == 5) {
				cout << "Você decidiu iniciar o combate, boa sorte!!.\n\n";
				venceu = iniciarCombate(jogador, inimigo);
			}

			else if (decisao.getId() == 6) {
				if (!cena.getPermiteFugir()) {
					cout << "Você não conseguiu escapar, terá que lutar pela vida.\n\n";
					venceu = iniciarCombate(jogador, inimigo);
				}
			}

			if (venceu) {
				jogador.getInventario().adicionarMantimento(inimigo.getQuantidadeMantimentos());
				jogador.getInventario().adicionarTesouro(100);
				auto itensInimigo = inimigo.getItens();
				for (auto& item : itensInimigo) {
					jogador.getInventario().adicionarItem(item);
				}
			}
			else {
				cout << "Você perdeu o jogo, voltará da última cena conquistada.\n\n";
				continuarJogo(jogo);
			}
		}
		
		jogo.adicionarCenaVisitada(cena);
		jogo.save();

		cout << "Carregando próxima cena: " << to_string(decisao.getIdProximaCena()) << "...\n\n";
		carregarCena(decisao.getIdProximaCena(), jogo); // recursão simples
		break;
	}
}

// Helper para checar se jogador possui o item (verifique sua representação de inventário)
bool jogadorPossuiItem(Jogador& jogador, const Item& itemNecessario) {
	if (itemNecessario.getNome().empty()) {
		return true; // sem item necessário
	}
	vector<Item> itensJogador = jogador.getInventario().getItens();
	for (size_t i = 0; i < itensJogador.size(); ++i) {
		if (itensJogador[i].getId() == itemNecessario.getId()) {
			return true;
		}
	}
	return false;
}

// Retorna true se o jogador venceu, false se perdeu.
bool iniciarCombate(Jogador jogador, Inimigo inimigo) {
	cout << "=== Combate iniciado: " << jogador.getNome()
		<< " vs " << inimigo.getNome() << " ===\n\n";

	while (true) {
		cout << jogador.getNome() << "  |  Energia: " << jogador.getEnergia() << "\n";
		cout << inimigo.getNome() << "  |  Energia: " << inimigo.getEnergia() << "\n\n";

		cout << "Ação do jogador:\n";
		cout << "1) Atacar\n";
		cout << "2) Usar SORTE neste turno\n";
		cout << "3) Abrir inventario\n";
		cout << "Escolha (1/2): ";
		int escolha = 0;
		if (!(cin >> escolha)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			escolha = 1; // em caso de erro Ataca
		}

		if (escolha == 3) {
			abrirInventario(jogador);
			continue;
		}

		bool usouSorte = (escolha == 2);
		bool sorteBemSucedida = false;

		if (usouSorte) {
			sorteBemSucedida = jogador.testarSorte();
			cout << (sorteBemSucedida ? "Sorte funcionou!\n" : "Sorte falhou!\n");
		}

		// Calcula forças de ataque base
		float ataqueJogador = jogador.atacar();
		float ataqueInimigo = inimigo.atacar();

		// Aplica modificadores de sorte
		if (usouSorte && sorteBemSucedida) {
			ataqueJogador *= 2.0f; // sorte dobra dano do jogador
		}
		if (usouSorte && !sorteBemSucedida) {
			ataqueInimigo *= 1.5f; // sorte falha => inimigo causa mais dano recebido pelo jogador
		}

		cout << jogador.getNome() << " ataca com força " << ataqueJogador
			<< " | " << inimigo.getNome() << " ataca com força " << ataqueInimigo << "\n";

		// Decide quem "ataca primeiro" apenas para fins de print/ordem de mensagem
		bool jogadorPrimeiro = ataqueJogador >= ataqueInimigo;

		// Ambos tomam dano neste round (ambos são afetados), mas mostramos quem "acertou" primeiro
		if (jogadorPrimeiro) {
			cout << jogador.getNome() << " acerta primeiro e causa " << inimigo.tomarDano(ataqueJogador) << " de dano!\n";

			cout << inimigo.getNome() << " revida e causa " << jogador.tomarDano(ataqueInimigo) << " de dano!\n";
		}
		else {
			cout << inimigo.getNome() << " acerta primeiro e causa " << jogador.tomarDano(ataqueInimigo) << " de dano!\n";

			cout << jogador.getNome() << " revida e causa " << inimigo.tomarDano(ataqueJogador) << " de dano!\n";
		}

		// Estado após o round
		cout << "\nEstado pós-round:\n";
		cout << jogador.getNome() << " -> Energia: " << jogador.getEnergia() << "\n";
		cout << inimigo.getNome() << " -> Energia: " << inimigo.getEnergia() << "\n\n";

		// Verifica condições de vitória/derrota
		bool jogadorMorreu = jogador.getEnergia() <= 0.0f;
		bool inimigoMorreu = inimigo.getEnergia() <= 0.0f;

		if (inimigoMorreu && !jogadorMorreu) {
			cout << "\n" << inimigo.getNome() << " foi derrotado!\n";
			cout << "Você venceu o combate!\n";
			return true; // jogador venceu
		}
		else if (jogadorMorreu) {
			// Caso o jogador tenha morrido (mesmo se inimigo também morreu), consideramos derrota do jogador
			cout << "\n" << jogador.getNome() << " foi derrotado!\n";
			return false; // jogador perdeu
		}

		cout << "\n--- Próximo round ---\n\n";
	}
}

void abrirInventario(Jogador& jogador) {
	cout << jogador.getInventario().serialize() << "\n\n";
}

void exibirCreditos() {
	cout << "\n=== CREDITOS ===\n";
	cout << "Disciplina: Algoritmos e Programação: Orientação a Objetos\n";
	cout << "Proposta: Interactive eBook\n";
	cout << "Professor: Marcio Garcia Martins\n";
	cout << "Dev: Fábio J. N. Bastian\n";
	cout << "Dev: Luiza Santos de Souza\n";
	cout << "\nDigite ENTER para retornar ao menu inicial...\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
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