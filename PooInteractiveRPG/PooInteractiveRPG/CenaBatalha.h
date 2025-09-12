#pragma once
#include "Cena.h"
#include "Inimigo.h"

class CenaBatalha : public Cena
{
public:
	CenaBatalha();
	~CenaBatalha();

private:
	Inimigo inimigo;
	bool permiteFugir;
};

