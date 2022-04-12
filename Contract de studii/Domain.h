#pragma once
#define Domain_h_
#include <string>
using namespace std;


class Disciplina
{
private:

	//denumirea unei discipline
	string denumire;

	//numarul de ore 
	int nr_ore;

	//tipul disciplinei, Obligatorie sau Facultativa
	string tip;

	//numele profesorului care preda cursul
	string profesor;

public:

	//Constructori si destructor

	/*
		Constructor
	*/
	Disciplina() : denumire{ "" }, nr_ore{ 0 }, tip{ "" }, profesor{ "" } {

	}

	/*
		Constructor cu parametri:
			denumire - string
			nr_ore - int
			tip - string
			profesor - string
	*/
	Disciplina(const string&, const int&, const string&, const string&);

	/*
		Constructor de copiere
			other - disciplina de copiat
	*/
	Disciplina(const Disciplina&);

	/*
		Destructor
	*/
	~Disciplina();

	//Getteri

	/*
		Returneaza denumirea unei discpline, un string
	*/
	string get_denumire() const;

	/*
		Returneaza numarul de ore al unei discpline, un intreg
	*/
	int get_nr_ore() const noexcept;

	/*
		Returneaza tipul unei discpline, un string
	*/
	string get_tip() const;

	/*
		Returneaza numele profesorului care preda discplina, un string
	*/
	string get_profesor() const;

	//Setteri

	/*
		Seteaza denumirea unei discpline cu stringul dat ca parametru:
			const string - noua denumire
	*/
	void set_denumire(const string);

	/*
		Seteaza numarul de ore al unei discpline cu numarul de ore dat ca parametru:
			const int - noul numar de ore
	*/
	void set_nr_ore(const int) noexcept;

	/*
		Seteaza tipul unei discpline cu stringul dat ca parametru:
			const string - noul tip
	*/
	void set_tip(const string);

	/*
		Seteaza numele profesorului unei discpline cu stringul dat ca parametru:
			const string - numele noului profesor
	*/
	void set_profesor(const string);

	//Operatori suprascrisi

	/*
		Atribuire
	*/
	Disciplina& operator=(const Disciplina&);

	/*
		Egalitate
	*/
	bool operator==(const Disciplina&);

	/*
		Neegalitate
	*/
	bool operator!=(const Disciplina&);

	/*
		Afisare
	*/
	friend ostream& operator<< (ostream&, const Disciplina&);

	Disciplina(Disciplina&& s) = default;

	//Disciplina& operator=(const Disciplina & s) = default;
};