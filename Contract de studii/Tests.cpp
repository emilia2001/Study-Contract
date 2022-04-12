#include <iostream>
#include <sstream>
#include <assert.h>
#include "Domain.h"
#include "Repository.h"
#include "Service.h"
#include "Validator.h"

using namespace std;

void test_domain()
{
	Disciplina d;
	assert(d.get_denumire() == "");
	assert(d.get_nr_ore() == 0);
	assert(d.get_tip() == "");
	assert(d.get_profesor() == "");

	Disciplina d2{ "POO", 4, "Obligatorie", "Istvan Czibula" };
	assert(d2.get_denumire() == "POO");
	assert(d2.get_nr_ore() == 4);
	assert(d2.get_tip() == "Obligatorie");
	assert(d2.get_profesor() == "Istvan Czibula");


	std::ostringstream os;
	os << d2;
	assert(os.str() == "\nDISCIPLINA: POO\nNUMAR DE ORE: 4\nTIP: Obligatorie\nPROFESOR: Istvan Czibula\n");


	d.set_denumire("SDA");
	d.set_nr_ore(2);
	d.set_tip("Obligatorie");
	d.set_profesor("Gabriela Czibula");

	assert(d.get_denumire() == "SDA");
	assert(d.get_nr_ore() == 2);
	assert(d.get_tip() == "Obligatorie");
	assert(d.get_profesor() == "Gabriela Czibula");


	Disciplina d3;
	d3 = d;
	assert(d3.get_denumire() == "SDA");
	assert(d3.get_nr_ore() == 2);
	assert(d3.get_tip() == "Obligatorie");
	assert(d3.get_profesor() == "Gabriela Czibula");

	d3 = d3;
	assert(d3.get_denumire() == "SDA");
	assert(d3.get_nr_ore() == 2);
	assert(d3.get_tip() == "Obligatorie");
	assert(d3.get_profesor() == "Gabriela Czibula");

	assert(d != d2);
	assert(!(d == d2));

	Disciplina d4{ "POO", 0, "Obl", "Istvan" };
	assert(d4 == d2);
	assert(!(d4 != d2));
}

void test_repo()
{
	//Repository repo;
	RepositoryFile repo{ "teste.txt" };
	assert(repo.get_nr_elem() == 0);

	//test add
	Disciplina d{ "POO", 4, "Obligatorie", "Istvan Czibula" };
	repo.add_repo(d);
	assert(repo.get_nr_elem() == 1);
	try
	{
		repo.add_repo(d);
	}
	catch (RepoError& e)
	{
		assert(true);
		assert(e.get_error() == "Disciplina existenta!\n");
	}
	auto all_disci = repo.get_all();
	assert(all_disci.at(0) == d);

	Disciplina d3{ "SDA", 4, "Obligatorie", "Istvan Czibula" };
	Disciplina d4{ "SD", 4, "Obligatorie", "Istvan Czibula" };
	repo.add_repo(d3);
	repo.add_repo(d4);

	//test delete
	repo.delete_repo("SDA");
	all_disci = repo.get_all();
	assert(repo.get_nr_elem() == 2);
	assert(all_disci.at(0) == d);
	assert(all_disci.at(1) == d4);
	try {
		repo.delete_repo("SDA");
	}
	catch (RepoError& err) {
		assert(true);
		assert(err.get_error() == "Disciplina inexistenta!\n");
	}

	//test search
	Disciplina d5 = repo.search_repo("SD");
	assert(d5 == d4);
	try {
		repo.search_repo("SDA");
	}
	catch (RepoError& err) {
		assert(true);
		assert(err.get_error() == "Disciplina inexistenta!\n");
	}

	//test update
	repo.update_repo(d4, "Prof nou");
	d5 = repo.search_repo("SD");
	assert(d5.get_profesor() == "Prof nou");
	try {
		RepositoryFile r2{ "abc" };
	}
	catch (RepoError& err) {
		assert(err.get_error() == "Eroare la deschiderea fisierului!\n");
	}

	repo.clear_file();

}

void test_validator()
{
	Validator valid;
	Disciplina d{ "", 0, "", "" };
	try {
		valid.valideaza_disciplina(d);
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Denumirea nu poate fi vida!\nNumarul de ore trebuie sa apartina intervalului 2, 6!\nTipul trebuie sa fie 'Obligatorie' sau 'Facultativa'!\nNumele profesorului nu poate fi vid!\n");
	}
	d.set_denumire("POO");
	try {
		valid.valideaza_disciplina(d);
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Numarul de ore trebuie sa apartina intervalului 2, 6!\nTipul trebuie sa fie 'Obligatorie' sau 'Facultativa'!\nNumele profesorului nu poate fi vid!\n");
	}
	d.set_nr_ore(3);
	d.set_tip("abc");
	try {
		valid.valideaza_disciplina(d);
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Tipul trebuie sa fie 'Obligatorie' sau 'Facultativa'!\nNumele profesorului nu poate fi vid!\n");
	}
	d.set_tip("Obligatorie");
	try {
		valid.valideaza_disciplina(d);
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Numele profesorului nu poate fi vid!\n");
	}
	d.set_profesor("Prof");
	try {
		valid.valideaza_disciplina(d);
		assert(true);
	}
	catch (ValidatorError) { assert(false); }

	try {
		valid.valideaza_denumire("");
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Denumirea nu poate fi vida!\n");
	}
	try {
		valid.valideaza_profesor("");
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Numele profesorului nu poate fi vid!\n");
	}

}

void test_serv()
{
	//Repository repo;
	RepositoryFile repo{ "teste.txt" };
	Validator valid;
	Contract c(repo);
	Service serv{ repo , valid , c };

	//test undo
	try {
		serv.undo();
	}
	catch (RepoError& err) {
		assert(err.get_error() == "Nu mai exista operatii!\n");
	}

	//test add 
	serv.add_serv("POO", 4, "Obligatorie", "Istvan Czibula");
	assert(serv.get_nr_disci() == 1);
	serv.undo();
	assert(serv.get_nr_disci() == 0);
	serv.add_serv("POO", 4, "Obligatorie", "Istvan Czibula");
	try
	{
		serv.add_serv("POO", 4, "Obligatorie", "Istvan Czibula");
	}
	catch (RepoError& e)
	{
		assert(true);
		assert(e.get_error() == "Disciplina existenta!\n");
	}
	try
	{
		serv.add_serv("", 4, "Obligatorie", "");
	}
	catch (ValidatorError& err) {
		assert(true);
		assert(err.get_error() == "Denumirea nu poate fi vida!\nNumele profesorului nu poate fi vid!\n");
	}

	//test get all
	auto all_disci = serv.get_all();
	assert(all_disci.size() == 1);

	serv.add_serv("SDA", 3, "Facultativa", "Istvan Czibula");
	serv.add_serv("Grafuri", 4, "Obligatorie", "Istvan Czibula");
	serv.add_serv("Geome", 4, "Obligatorie", "Istvan Czibula");
	all_disci = serv.get_all();
	assert(all_disci.size() == 4);

	//test delete
	serv.delete_serv("Grafuri");
	all_disci = serv.get_all();
	assert(all_disci.size() == 3);
	serv.undo();
	all_disci = serv.get_all();
	assert(all_disci.size() == 4);
	serv.delete_serv("Grafuri");
	try {
		serv.delete_serv("Grafuri");
	}
	catch (RepoError& err) {
		assert(true);
		assert(err.get_error() == "Disciplina inexistenta!\n");
	}

	//test search
	Disciplina d1 = serv.search_serv("SDA");
	assert(d1.get_profesor() == "Istvan Czibula");
	assert(d1.get_tip() == "Facultativa");
	assert(d1.get_nr_ore() == 3);
	try {
		serv.search_serv("Grafuri");
	}
	catch (RepoError& err) {
		assert(true);
		assert(err.get_error() == "Disciplina inexistenta!\n");
	}

	//test update
	serv.update_serv("Geome", "Profff");
	d1 = serv.search_serv("Geome");
	assert(d1.get_profesor() == "Profff");
	serv.undo();
	d1 = serv.search_serv("Geome");
	assert(d1.get_profesor() == "Istvan Czibula");
	serv.update_serv("Geome", "Profff");


	//test raport
	auto rap = serv.raport();
	map <string, int> ::iterator it;
	it = rap.find("Istvan Czibula");
	assert(it->first == "Istvan Czibula");
	assert(it->second == 2);
	it = rap.find("Profff");
	assert(it->first == "Profff");
	assert(it->second == 1);

	repo.clear_file();

}

void test_filtrare()
{
	//Repository repo;
	RepositoryFile repo{ "teste.txt" };
	Validator valid;
	Contract c(repo);
	Service serv{ repo , valid , c };
	serv.add_serv("POO", 4, "Obligatorie", "Istvan Czibula");
	serv.add_serv("SDA", 2, "Obligatorie", "Czibula Gabriela");
	serv.add_serv("Fp", 6, "Facultativa", "Istvan Czibula");
	serv.add_serv("ASC", 4, "Obligatorie", "Vancea");


	//filtrare numar ore
	auto filtrate_ore = serv.filtrare_ore(4);
	assert(filtrate_ore.size() == 2);
	assert(filtrate_ore.at(0).get_denumire() == "POO");
	assert(filtrate_ore.at(1).get_denumire() == "ASC");

	filtrate_ore = serv.filtrare_ore(6);
	assert(filtrate_ore.size() == 1);
	assert(filtrate_ore.at(0).get_denumire() == "Fp");

	filtrate_ore = filtrate_ore;

	//filtrare prof
	auto filtrate_prof = serv.filtrare_prof("Istvan Czibula");
	assert(filtrate_prof.size() == 2);
	assert(filtrate_prof.at(0).get_denumire() == "POO");
	assert(filtrate_prof.at(1).get_denumire() == "Fp");

	filtrate_prof = serv.filtrare_prof("Vancea");
	assert(filtrate_prof.size() == 1);
	assert(filtrate_prof.at(0).get_denumire() == "ASC");

	repo.clear_file();
}

void test_sortare()
{
	//Repository repo;
	RepositoryFile repo{ "teste.txt" };
	Validator valid;
	Contract c(repo);
	Service serv{ repo , valid , c };
	serv.add_serv("POO", 4, "Obligatorie", "Istvan Czibula");
	serv.add_serv("SDA", 2, "Obligatorie", "Czibula Gabriela");
	serv.add_serv("Fp", 6, "Facultativa", "Istvan Czibula");
	serv.add_serv("ASC", 4, "Obligatorie", "Vancea");
	//sortare denumire
	auto disci_sortate = serv.sortare_denumire();
	assert(disci_sortate.size() == 4);
	assert(disci_sortate.at(0).get_denumire() == "ASC");
	assert(disci_sortate.at(1).get_denumire() == "Fp");
	assert(disci_sortate.at(2).get_denumire() == "POO");
	assert(disci_sortate.at(3).get_denumire() == "SDA");

	//sortare numar ore
	disci_sortate = serv.sortare_ore();
	assert(disci_sortate.size() == 4);
	assert(disci_sortate.at(0).get_denumire() == "SDA");
	assert(disci_sortate.at(1).get_denumire() == "POO");
	assert(disci_sortate.at(2).get_denumire() == "ASC");
	assert(disci_sortate.at(3).get_denumire() == "Fp");

	//sortare prof + tip
	disci_sortate = serv.sortare_prof_tip();
	assert(disci_sortate.size() == 4);
	assert(disci_sortate.at(0).get_denumire() == "SDA");
	assert(disci_sortate.at(1).get_denumire() == "Fp");
	assert(disci_sortate.at(2).get_denumire() == "POO");
	assert(disci_sortate.at(3).get_denumire() == "ASC");

	repo.clear_file();
}

void test_contract()
{
	//Repository repo;
	RepositoryFile repo{ "teste.txt" };
	Contract serv_c(repo);

	Validator valid;
	Service serv_d(repo, valid, serv_c);
	serv_d.add_serv("Programare orientata obiect", 4, "Obligatorie", "Czibula Istvan");
	serv_d.add_serv("Fundamentele programarii", 6, "Facultativa", "Czibula Istvan");
	serv_d.add_serv("Programare web", 6, "Obligatorie", "Bufnea Darius");
	serv_d.add_serv("Structuri de date si algoritmi", 3, "Obligatorie", "Czibula Gabriela");


	//test adaugare
	serv_c.add("Programare web");
	serv_c.add("Structuri de date si algoritmi");
	serv_c.add("Programare orientata obiect");
	assert(serv_c.get_nr_disci() == 3);
	try {
		serv_c.add("Structuri de date si algoritmi");
	}
	catch (ContractError& err) {
		assert(err.get_error() == "Disciplina existenta!\n");
	}

	//test golire
	serv_c.goleste();
	auto contract = serv_c.get_contract();
	assert(contract.size() == 0);

	//test generare
	serv_c.genereaza(3);
	assert(serv_c.get_nr_disci() == 3);
	try {
		serv_c.genereaza(4);
	}
	catch (ContractError& err) {
		assert(err.get_error() == "Nu exista suficiente discipline!\n");
	}

	repo.clear_file();

	//test export
	serv_c.export_contract("teste2");
	try {
		serv_c.export_contract("teste3");
	}
	catch (ContractError& err) {
		assert(err.get_error() == "Fisierul nu s-a deschis!!\n");
	}

	serv_c.clear_file("teste2");

}

void run_all_tests()
{
	test_domain();
	test_repo();
	test_validator();
	test_serv();
	test_filtrare();
	test_sortare();
	test_contract();
}