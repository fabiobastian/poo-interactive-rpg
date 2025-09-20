#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Item.h"

using namespace std;

std::vector<Item> loadItemsFromFile(const std::string& filename);

int main()
{
    vector<Item> itens = loadItemsFromFile("itens.txt");
    cout << itens[0].getNome();
	return 0;
}

std::vector<Item> loadItemsFromFile(const std::string& filename) {
    std::vector<Item> itens;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            itens.push_back(Item::deserialize(line));
        }
    }

    return itens;
}