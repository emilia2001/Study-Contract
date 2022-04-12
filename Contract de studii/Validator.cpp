#include "Validator.h"

using namespace std;

void Validator::valideaza_denumire(const string sir)
{
	if (sir == "")
		throw ValidatorError("Denumirea nu poate fi vida!\n");
}

void Validator::valideaza_profesor(const string sir)
{
	if (sir == "")
		throw ValidatorError("Numele profesorului nu poate fi vid!\n");
}

void Validator::valideaza_disciplina(const Disciplina& disci)
{
	string error{ "" };
	if (disci.get_denumire() == "")
		error += "Denumirea nu poate fi vida!\n";
	if (disci.get_nr_ore() < 2 || disci.get_nr_ore() > 6)
		error += "Numarul de ore trebuie sa apartina intervalului 2, 6!\n";
	if (disci.get_tip() != "Obligatorie" && disci.get_tip() != "Facultativa")
		error += "Tipul trebuie sa fie 'Obligatorie' sau 'Facultativa'!\n";
	if (disci.get_profesor() == "")
		error += "Numele profesorului nu poate fi vid!\n";
	if (error != "")
		throw ValidatorError(error);
}