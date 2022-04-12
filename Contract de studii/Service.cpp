#include "Service.h"
#include<string>
#include <algorithm>
#include <random>
#include <vector>
#include <fstream>
using namespace std;



void Service::add_serv(const string& denumire, const int& nr_ore, const string& tip, const string& profesor)
{
	Disciplina disci(denumire, nr_ore, tip, profesor);
	valid.valideaza_disciplina(disci);
	repo.add_repo(disci);
	actiuni_undo.push_back(new UndoAdauga{ repo, disci });
}

void Service::delete_serv(const string denumire)
{
	valid.valideaza_denumire(denumire);
	auto disci = repo.search_repo(denumire);
	actiuni_undo.push_back(new UndoSterge{ repo, disci });
	repo.delete_repo(denumire);
	contract.delete_disci(denumire);
}

const Disciplina Service::search_serv(const string denumire)
{
	return repo.search_repo(denumire);
}

void Service::update_serv(const string denumire, const string profesor_nou)
{
	auto disci = search_serv(denumire);
	actiuni_undo.push_back(new UndoModifica{ repo, disci });
	valid.valideaza_profesor(profesor_nou);
	repo.update_repo(disci, profesor_nou);
}


vector<Disciplina> Service::filtrare_ore(const int nr_ore)
{
	auto all_disci = get_all();
	vector<Disciplina> filtrate_ore;
	copy_if(all_disci.begin(), all_disci.end(), back_inserter(filtrate_ore), [&](const Disciplina& disci) { return disci.get_nr_ore() == nr_ore; });
	return filtrate_ore;
}

vector<Disciplina> Service::filtrare_prof(const string profesor)
{
	auto all_disci = get_all();
	vector<Disciplina> filtrate_ore;
	copy_if(all_disci.begin(), all_disci.end(), back_inserter(filtrate_ore), [&](const Disciplina& disci) { return disci.get_profesor() == profesor; });
	return filtrate_ore;
}

bool comparare_denumire(const Disciplina& disci1, const Disciplina& disci2)
{
	if (disci1.get_denumire() < disci2.get_denumire())
		return true;
	else return false;
}

bool comparare_ore(const Disciplina& disci1, const Disciplina& disci2)
{
	if (disci1.get_nr_ore() < disci2.get_nr_ore())
		return true;
	else return false;
}

bool comparare_prof_tip(const Disciplina& disci1, const Disciplina& disci2)
{
	if (disci1.get_profesor() == disci2.get_profesor())
	{
		if (disci1.get_tip() < disci2.get_tip())
			return true;
		else return false;
	}
	else if (disci1.get_profesor() < disci2.get_profesor())
		return true;
	else return false;
}

vector<Disciplina> Service::sortare_generala(bool (*comparare) (const Disciplina&, const Disciplina&))
{
	auto all_disci = get_all();
	sort(all_disci.begin(), all_disci.end(), comparare);
	return all_disci;
}

vector<Disciplina> Service::sortare_denumire()
{
	return sortare_generala(comparare_denumire);
}

vector<Disciplina> Service::sortare_ore()
{
	return sortare_generala(comparare_ore);
}

vector<Disciplina> Service::sortare_prof_tip()
{
	return sortare_generala(comparare_prof_tip);
}

const vector<Disciplina> Service::get_all()
{
	return repo.get_all();
}

const long long Service::get_nr_disci() noexcept
{
	return repo.get_nr_elem();
}

map<string, int> Service::raport() const
{
	map <string, int> r;
	auto discis = repo.get_all();
	for (const auto& d : discis)
	{
		string prof = d.get_profesor();
		map<string, int> ::iterator it = r.find(prof);
		if (it == r.end())
			r.insert(make_pair(prof, 1));
		else
			it->second++;
	}
	return r;
}

void Service::undo()
{
	if (actiuni_undo.empty())
		throw RepoError("Nu mai exista operatii!\n");
	ActiuneUndo* actiune = actiuni_undo.back();
	if (actiune != nullptr)
	{
		actiune->do_undo();
		actiuni_undo.pop_back();
		delete actiune;
	}
}

void Contract::add(const string& denumire_disci)
{
	auto disci = repo_disci.search_repo(denumire_disci);
	vector<Disciplina>::iterator it = find(contract.begin(), contract.end(), disci);
	if (it != contract.end())
		throw ContractError("Disciplina existenta!\n");
	contract.push_back(disci);


	notify();
}

const Disciplina Contract::search_disci(const string denumire)
{
	return repo_disci.search_repo(denumire);
}

void Contract::delete_disci(const string denumire)
{
	for (auto const& disci : contract)
		if (disci.get_denumire() == denumire)
			contract.erase(remove(contract.begin(), contract.end(), disci), contract.end());
	notify();
}

void Contract::goleste()
{
	contract.clear();

	notify();
}

void Contract::genereaza(const int nr)
{
	auto discis = repo_disci.get_all();
	//vector<Disciplina> discis = all_disci;
	const long long nr_disci = repo_disci.get_nr_elem();
	if (nr > nr_disci - get_nr_disci())
		throw ContractError("Nu exista suficiente discipline!\n");
	//random_shuffle(discis.begin(), discis.end());
	random_device rd;
	mt19937 g(rd());

	shuffle(discis.begin(), discis.end(), g);
	int n{ 0 };
	int i{ 0 };
	while (n < nr)
	{
		try {
			add(discis.at(i++).get_denumire());
			n++;
		}
		catch (ContractError) {}
	}


	notify();


}

void Contract::export_contract(string fisi)
{
	if (fisi == "")
		throw ContractError("Numele fisierului nu poate fi vid!\n");
	string fisier{ "D:\\" };
	fisier += fisi;
	fisier += ".csv";
	fstream fout(fisier, ios::out);
	fout.close();
	fout.open(fisier, ios::out);
	if (!fout.is_open())
		throw ContractError("Fisierul nu s-a deschis!!\n");
	for (const auto& d : contract)
	{
		fout << d.get_denumire() << ",";
		fout << d.get_nr_ore() << ",";
		fout << d.get_tip() << ",";
		fout << d.get_profesor() << '\n';
	}
}

const vector<Disciplina> Contract::get_contract()
{
	return contract;
}

const long long Contract::get_nr_disci()
{
	return contract.size();
}

void Contract::clear_file(string file_name)
{
	ifstream fin;
	fin.open(file_name, ifstream::out | ifstream::trunc);
	fin.close();
}

const long long Contract::get_nr_disponibile()
{
	return repo_disci.get_nr_elem();
}

Service::~Service()
{
	for (auto& p : actiuni_undo)
		delete p;
}