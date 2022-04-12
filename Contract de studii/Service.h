#pragma once
#include "Repository.h"
#include "Validator.h"
#include "Exceptions.h"
#include "Undo.h"
#include "Observer.h"
#include<string>
#include <vector>
#include<map>
using namespace std;

class Contract;

class Service
{
private:
	Validator valid;
	RepositoryPure& repo;
	Contract& contract;
	vector <ActiuneUndo*> actiuni_undo;

public:
	Service(RepositoryPure& repo, Validator& valid, Contract& contract) noexcept : repo{ repo }, valid{ valid }, contract{ contract }{
	}

	Service(const Service& other) = delete;

	/*
		Functia de adaugare a unei discipline in lista
			denumire - string, denumirea materiei
			nr_ore - int, numarul de ore
			tip - string, tipul materiei, Obligatorie sau facultativa
			profesor - numele profesorului
		Arunca RepoError daca disciplina exista deja
	*/
	void add_serv(const string&, const int&, const string&, const string&);

	/*
		Functia de stergere a disciplinei cu denumirea data
			denumire - string, denumirea materiei pe care o sterg
		Arunca RepoError daca disciplina cu denumirea data nu exista
	*/
	void delete_serv(const string);

	/*
		Functia de cautare a disciplinei cu denumirea data
			denumire - string, denumirea materiei
		Returneaza disciplina daca exista, sau arunca RepoError in caz contrar
	*/
	const Disciplina search_serv(const string);

	/*
		Functia de modificarea a profesorului disciplinei cu denumirea data
			denumire - string, denumirea materiei pe care o modificam
			profesor - numele profesorului nou
		Arunca RepoError daca disciplina nu exista
	*/
	void update_serv(const string, const string);

	/*
		Functia de filtrare dupa numarul de ore
			nr ore - int, numarul de ore pe care le cautam
		Returneaza vectorul cu toate disciplinele care au numarul de ore dat
	*/
	vector<Disciplina> filtrare_ore(const int);

	/*
		Functia de filtrare dupa profesor
			profesor - string, numele profesorului pe care il cautam
		Returneaza vectorul cu toate disciplinele care au profesorul dat
	*/
	vector<Disciplina> filtrare_prof(const string);

	/*
		Functia de sortare a unui vector de discipline dupa o functie de comparare transmisa ca parametru
			comparare - functia care compara 2 discipline
		Returneaza un vector ordonat dupa functia transmisa ca parametru
	*/
	vector<Disciplina> sortare_generala(bool(*comparare)(const Disciplina&, const Disciplina&));

	/*
		Functia de sortare a unui vector de discipline in ordine alfabetica dupa denumire
		Returneaza un vector ordonat alfabetic dupa denumire
	*/
	vector<Disciplina> sortare_denumire();

	/*
		Functia de sortare a unui vector de discipline in ordine crescatoare dupa numarul de ore
		Returneaza un vector ordonat crescator dupa numarul de ore
	*/
	vector<Disciplina> sortare_ore();

	/*
		Functia de sortare a unui vector de discipline in ordine alfabetica dupa profesor, iar in cadrul celor cu acelasi
			profesor, alfabetic dupa tip
		Returneaza un vector ordonat alfabetic dupa profesor si tip
	*/
	vector<Disciplina> sortare_prof_tip();

	/*
		Returneaza un vector cu toate disciplinele existente
	*/
	const vector<Disciplina> get_all();

	/*
		Returneaza numarul de discipline existente
	*/
	const long long  get_nr_disci() noexcept;

	map<string, int> raport() const;

	void undo();

	~Service();
};

class Contract :public Observable
{
private:
	RepositoryPure& repo_disci;
	vector<Disciplina> contract;

public:
	//constructor
	Contract(RepositoryPure& repo_disci) noexcept : repo_disci{ repo_disci } {
	}

	//constructor de copiere
	Contract(const Contract& other) = delete;

	/*
		Functia de adaugare a unei discipline in contract
			denumire - string, denumirea materiei
		Arunca ContractError daca disciplina exista deja
	*/
	void add(const string&);

	const Disciplina search_disci(const string);

	void delete_disci(const string);

	/*
		Functia de golire a contractului
			sterge toate disciplinele din contract
	*/
	void goleste();

	/*
		Functia de generare a unui contract cu un numar dat de discipline
			nr- int, numarul de discipline care sa fie alease aleator si adaugate in contract
		Arunca ContractError daca nu exista suficiente discipline
	*/
	void genereaza(const int);

	/*
		Functia de export a unui contract intr-un fisier
			fisier - string, denumirea fisierului in care se va efectua exportul
	*/
	void export_contract(string);

	/*
		Returneaza un vector care contine contractul
	*/
	const vector<Disciplina> get_contract();

	/*
		Returneaza numarul de discipline existente in contract
	*/
	const long long  get_nr_disci();

	const long long get_nr_disponibile();

	void clear_file(string);

	//destructor
	~Contract() {};
};