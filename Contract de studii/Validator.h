#pragma once
#include "Exceptions.h"
#include "Domain.h"

class Validator
{

public:

	void valideaza_denumire(const string);
	void valideaza_profesor(const string);
	void valideaza_disciplina(const Disciplina&);

};

