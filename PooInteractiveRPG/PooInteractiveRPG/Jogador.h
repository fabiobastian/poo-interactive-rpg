#pragma once
#include "Personagem.h"
#include "Inventario.h"

class Jogador : public Personagem
{
public: 
	Jogador();
	~Jogador();
	Jogador(int id, string nome, float habilidade, float energia, float sorte, Inventario inventario);
	string serialize() const;
	static Jogador deserialize(const string& data);
	static string findById(int id);
	void save() const;
	Inventario& getInventario(); // &Inventario retorna a referencia não uma copia 
	int getId() const;
	float atacar(float multiplicador = 1.0f) override;
	float tomarDano(float danoBruto) override;
	bool testarSorte();

private:
	Inventario inventario;
};
