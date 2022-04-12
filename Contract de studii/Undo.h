#pragma once
#include "Domain.h"
#include "Repository.h"

class ActiuneUndo
{
public:
	virtual void do_undo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
	Disciplina disci_adaugata;
	RepositoryPure& repo;

public:
	UndoAdauga(RepositoryPure& repo, const Disciplina& disci) : repo{ repo }, disci_adaugata{ disci } {}
	void do_undo() override
	{
		repo.delete_repo(disci_adaugata.get_denumire());
	}
};

class UndoSterge : public ActiuneUndo
{
	Disciplina disci_stearsa;
	RepositoryPure& repo;

public:
	UndoSterge(RepositoryPure& repo, const Disciplina& disci) : repo{ repo }, disci_stearsa{ disci } {}
	void do_undo() override
	{
		repo.add_repo(disci_stearsa);
	}
};

class UndoModifica : public ActiuneUndo
{
	Disciplina disci_modif;
	RepositoryPure& repo;

public:
	UndoModifica(RepositoryPure& repo, const Disciplina& disci) : repo{ repo }, disci_modif{ disci } {}
	void do_undo() override
	{
		repo.update_repo(disci_modif, disci_modif.get_profesor());
	}
};
