#pragma once
#define Repository_h_

#include "Domain.h"
#include <string>
#include <vector>
#include <map>
#include "Exceptions.h"
#include "VectorDinamic.h"
using namespace std;


class RepositoryPure
{
public:

	virtual void add_repo(const Disciplina&) = 0;

	virtual void delete_repo(string denumire) = 0;

	virtual const Disciplina search_repo(const string) = 0;

	virtual void update_repo(const Disciplina&, const string) = 0;

	virtual long long const get_nr_elem() noexcept = 0;

	virtual const vector<Disciplina> get_all() = 0;

	virtual ~RepositoryPure() = default;
};


class Repository : public RepositoryPure
{
private:
	vector<Disciplina> lista;

public:
	//constructor
	Repository() noexcept {};

	//constructor copiere
	Repository(const Repository& other) = delete;

	/*
		Functia de adaugare a unei discipline in lista
			Disciplina - disciplina de adaugat
		Arunca exceptie daca disciplina exista deja in lista
	*/
	virtual void add_repo(const Disciplina&);

	/*
		Functia de stergere a disciplinei cu denumirea data ca parametru
			denumire - string, denumirea disciplinei pe care vrem sa o stergem
		Arunca exceptie daca nu exista nicio disciplina cu denumirea data
	*/
	virtual void delete_repo(string denumire);

	/*
		Functia de cautare a disciplinei cu denumirea data ca parametru
			denumire - string, denumirea disciplinei pe care vrem sa o cautam
		Returneaza disciplina daca exista, arunca exceptie in caz contrar
	*/
	const Disciplina search_repo(const string);

	/*
		Functia de modificare a cadrului didactic a disciplinei data ca parametru cu noul cadru didactic dat ca parametru
			disciplina - disciplina pe care o modificam
			profesor - string, numele profesorului nou
	*/
	virtual void update_repo(const Disciplina&, const string);

	//getters
	/*
		Returneaza un vector cu toate disciplinele existente
	*/
	const vector<Disciplina> get_all();

	/*
		Returneaza numarul de discipline existente
	*/
	const long long get_nr_elem() noexcept;

	//destructor
	virtual ~Repository();
};



class RepositoryFile :public Repository
{
private:
	string file_name;
	void load_from_file();
	void store_to_file();

public:
	RepositoryFile(string file_name) : Repository(), file_name{ file_name }
	{
		load_from_file();
	}
	void add_repo(const Disciplina&) override;
	void delete_repo(string denumire) override;
	void update_repo(const Disciplina&, const string) override;
	void clear_file();
};


class RepositoryMap : public RepositoryPure
{
private:
	map<string, Disciplina> m;
	float prob;
public:
	RepositoryMap(float p) : prob{ p } {};

	void jocurile_de_noroc();

	void add_repo(const Disciplina&) override;

	void delete_repo(string denumire) override;

	const Disciplina search_repo(const string) override;

	void update_repo(const Disciplina&, const string) override;

	const long long get_nr_elem() noexcept override;

	const vector<Disciplina> get_all() override;

	~RepositoryMap() = default;
};
