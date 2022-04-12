#include <iostream>
#include <string>
#include "Domain.h"
using namespace std;

//constructors

Disciplina::Disciplina(const string& denumire, const int& nr_ore, const string& tip, const string& profesor)
{
	this->denumire = denumire;
	this->nr_ore = nr_ore;
	this->tip = tip;
	this->profesor = profesor;
}

Disciplina::Disciplina(const Disciplina& other)
{
	this->denumire = other.get_denumire();
	this->nr_ore = other.get_nr_ore();
	this->tip = other.get_tip();
	this->profesor = other.get_profesor();
}


//getters
string Disciplina::get_denumire() const
{
	return this->denumire;
}

int Disciplina::get_nr_ore() const noexcept
{
	return this->nr_ore;
}

string Disciplina::get_tip() const
{
	return this->tip;
}

string Disciplina::get_profesor() const
{
	return this->profesor;
}


//setters
void Disciplina::set_denumire(const string denumire_noua)
{
	this->denumire = denumire_noua;
}

void Disciplina::set_nr_ore(const int nr_ore_nou)  noexcept
{
	this->nr_ore = nr_ore_nou;
}

void Disciplina::set_tip(const string tip_nou)
{
	this->tip = tip_nou;
}

void Disciplina::set_profesor(const string profesor_nou)
{
	this->profesor = profesor_nou;
}


//operators
Disciplina& Disciplina::operator=(const Disciplina& other)
{
	if (this == &other)
		return *this;
	this->denumire = other.get_denumire();
	this->nr_ore = other.get_nr_ore();
	this->tip = other.get_tip();
	this->profesor = other.get_profesor();
	return *this;
}

bool Disciplina::operator==(const Disciplina& other)
{
	if (this->denumire == other.get_denumire())
		return true;
	return false;
}

bool  Disciplina::operator!=(const Disciplina& other)
{
	if (this->denumire != other.get_denumire())
		return true;
	return false;
}

ostream& operator<<(ostream& stream, const Disciplina& disci)
{
	stream << endl << "DISCIPLINA: " << disci.get_denumire() << endl;
	stream << "NUMAR DE ORE: " << disci.get_nr_ore() << endl;
	stream << "TIP: " << disci.get_tip() << endl;
	stream << "PROFESOR: " << disci.get_profesor() << endl;
	return stream;
}

//destructor
Disciplina::~Disciplina()
{

}