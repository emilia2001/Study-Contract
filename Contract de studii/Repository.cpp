#include "Repository.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;


const long long Repository::get_nr_elem() noexcept
{
	return lista.size();
}

void Repository::add_repo(const Disciplina& disci)
{
	vector<Disciplina>::iterator it = find(lista.begin(), lista.end(), disci);
	if (it != lista.end())
		throw RepoError("Disciplina existenta!\n");
	lista.push_back(disci);
}

void Repository::delete_repo(string denumire)
{
	bool ok = false;
	for (auto const& disci : lista)
		if (disci.get_denumire() == denumire)
		{
			lista.erase(remove(lista.begin(), lista.end(), disci), lista.end());
			ok = true;
		}
	if (!ok)
		throw RepoError("Disciplina inexistenta!\n");
}

const Disciplina Repository::search_repo(const string denumire)
{
	vector<Disciplina>::iterator it = find_if(lista.begin(), lista.end(), [&](const Disciplina& disci) { return disci.get_denumire() == denumire; });
	if (it != lista.end())
		return *it;
	throw RepoError("Disciplina inexistenta!\n");
}

void Repository::update_repo(const Disciplina& disci, const string profesor_nou)
{
	vector<Disciplina>::iterator it = find(lista.begin(), lista.end(), disci);
	lista.at(it - lista.begin()).set_profesor(profesor_nou);
}

const vector<Disciplina> Repository::get_all()
{
	return lista;
}

Repository::~Repository()
{

}

void RepositoryFile::load_from_file()
{
	ifstream fin(file_name);
	if (!fin.is_open())
		throw RepoError("Eroare la deschiderea fisierului!\n");

	string line, word;
	while (!fin.eof())
	{
		string denumire, tip, prof;
		getline(fin, line);
		if (line.empty())
			break;
		stringstream s(line);
		getline(s, denumire, ';');
		getline(s, word, ';');
		int nr_ore;
		nr_ore = stoi(word);
		getline(s, tip, ';');
		getline(s, prof, ';');
		Disciplina disci{ denumire, nr_ore, tip, prof };
		Repository::add_repo(disci);
	}

	fin.close();
}

void RepositoryFile::store_to_file()
{
	ofstream fout(file_name);
	if (!fout.is_open())
		throw RepoError("Eroare la deschiderea fisierului!\n");
	for (const auto& d : get_all())
	{
		fout << d.get_denumire() << ";";
		fout << d.get_nr_ore() << ";";
		fout << d.get_tip() << ";";
		fout << d.get_profesor() << '\n';
	}

	fout.close();
}

void RepositoryFile::add_repo(const Disciplina& disci)
{
	Repository::add_repo(disci);
	store_to_file();
}

void RepositoryFile::delete_repo(string denumire)
{
	Repository::delete_repo(denumire);
	store_to_file();
}

void RepositoryFile::update_repo(const Disciplina& disci, const string prof)
{
	Repository::update_repo(disci, prof);
	store_to_file();
}

void RepositoryFile::clear_file()
{
	ifstream fin;
	fin.open(file_name, ifstream::out | ifstream::trunc);
	fin.close();
}

void RepositoryMap::jocurile_de_noroc()
{
	mt19937 mt{ std::random_device{}() };
	const uniform_int_distribution<> dist(0, 100);
	const int rndNr = dist(mt);
	const float rndflt = static_cast<float>(rndNr) / 100;
	if (rndflt < this->prob)
		throw RepoError("Mai incearca, n-ai avut noroc..\n");
}

void RepositoryMap::add_repo(const Disciplina& disci)
{
	jocurile_de_noroc();
	string denumire = disci.get_denumire();
	auto it = m.find(denumire);
	if (it != m.end())
		throw RepoError("Disciplina existenta!\n");
	m.insert(make_pair(denumire, disci));
}

void RepositoryMap::delete_repo(string denumire)
{
	jocurile_de_noroc();
	auto it = m.find(denumire);
	if (it == m.end())
		throw RepoError("Disciplina inexistenta!\n");
	m.erase(denumire);
}

const Disciplina RepositoryMap::search_repo(const string denumire)
{
	auto it = m.find(denumire);
	if (it == m.end())
		throw RepoError("Disciplina inexistenta!\n");
	return it->second;
}

void RepositoryMap::update_repo(const Disciplina& disci, const string prof_nou)
{
	jocurile_de_noroc();
	string denumire = disci.get_denumire();
	auto it = m.find(denumire);
	if (it == m.end())
		throw RepoError("Disciplina inexistenta!\n");
	it->second.set_profesor(prof_nou);
}

const long long RepositoryMap::get_nr_elem() noexcept
{
	return m.size();
}

const vector<Disciplina> RepositoryMap::get_all()
{
	vector<Disciplina> all;
	for (auto it = m.begin(); it != m.end(); ++it)
		all.push_back(it->second);
	return all;
}
