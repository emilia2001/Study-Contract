#pragma once
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include "Service.h"
#include <QTableWidget>
#include <QGraphicsView>
#include <qtableview.h>
#include <cstdlib>
#include <ctime>

#include "Observer.h"

class MyTableView : public QAbstractTableModel
{
	vector<Disciplina> disci;

public slots:
	void resetInternalData()
	{
		disci.resize(0);
	}

public:
	MyTableView(vector<Disciplina> discipline) : disci{ discipline } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return disci.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		if (role == Qt::DisplayRole)
		{
			Disciplina d = disci[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(d.get_denumire());
			else if (index.column() == 1)
				return QString::number(d.get_nr_ore());
			else if (index.column() == 2)
				return QString::fromStdString(d.get_tip());
			else if (index.column() == 3)
				return QString::fromStdString(d.get_profesor());
		}
		return QVariant{};
	}

	void set_disci(vector<Disciplina> disci) {
		this->disci = disci;
		qDebug() << "setez" << rowCount() << "  " << columnCount();
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}
};

class GUI :public QWidget
{
private:
	Service& serv;
	Contract& contract;
	QHBoxLayout* main_ly = new QHBoxLayout;
	QListView* list = new QListView;
	MyTableView* model;
	QPushButton* get_all_btn;
	QPushButton* sort_denumire_btn;
	QPushButton* sort_ore_btn;
	QPushButton* sort_cadru_btn;
	QPushButton* filter_ore_btn;
	QPushButton* filter_prof_btn;

	QLineEdit* txt_denumire;
	QLineEdit* txt_ore;
	QLineEdit* txt_tip;
	QLineEdit* txt_profesor;
	QPushButton* add_btn;
	QPushButton* delete_btn;
	QPushButton* update_btn;
	QPushButton* search_btn;
	QPushButton* undo_btn;
	QPushButton* contract_crud_btn;
	QPushButton* contract_rdonly_btn;
	QPushButton* add_contract_btn;
	QLineEdit* txt_nr_generate;
	QPushButton* generate_contract_btn;
	QPushButton* empty_contract_btn;

	void init_components();
	void connect_signals();
	void reload_list(const vector<Disciplina> discis);
	void load_info(QList <QListWidgetItem*>);
	void add_gui();
	void delete_gui();
	void search_gui();
	void update_gui();
	void undo_gui();
	void filtrare_ore();
	void filtrare_prof();
	void add_contract_gui();
	void generate_contract_gui();
	void empty_contract_gui();

public:
	GUI(Service& serv, Contract& contract) : serv{ serv }, contract{ contract }
	{
		model = new MyTableView{ serv.get_all() };
		list->setModel(model);
		init_components();
		connect_signals();
		reload_list(serv.get_all());
	}
};



//clasa cos crud
class GUIContractCRUD :public QWidget, public Observer
{
private:
	Contract& contract;

	QHBoxLayout* main_ly = new QHBoxLayout;
	QTableWidget* table;
	QLineEdit* txt_denumire;
	QLineEdit* txt_ore;
	QLineEdit* txt_tip;
	QLineEdit* txt_profesor;
	QLineEdit* txt_nr_disci;
	QLineEdit* txt_fisier;
	QPushButton* add_btn;
	QPushButton* generate_btn;
	QPushButton* empty_btn;
	QPushButton* export_btn;


	void init_components();
	void connect_signals();
	void reload_list(const vector<Disciplina> contract);
	void load_info(QList <QTableWidgetItem*> selected);
	void add_contract_gui();
	void genereaza_gui();
	void goleste_gui();
	void export_gui();

public:

	GUIContractCRUD(Contract& contract) : contract{ contract }
	{
		init_components();
		connect_signals();
		reload_list(contract.get_contract());
	}

	void update() {
		reload_list(contract.get_contract());
	}
};




//clasa cos read only
class GUIContractReadOnly :public QWidget, public Observer
{
private:
	Contract& contract;


public:
	GUIContractReadOnly(Contract& contract) : contract{ contract }{
		contract.addObserver(this);
	}

	void update() {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		srand((unsigned)time(NULL));
		QPainter p{ this };
		int x = rand()&500;
		int y = rand()%500;
		for (int i = 0; i < contract.get_nr_disci(); i++)
		{
		p.drawRect(x, y, 10, 10);
		//p.drawImage(x, y, QImage("carte2.jpg"));
		x += rand()%100;
		y += rand() % 50;
		}
	}
};





class GUIContractCRUDModel :public QWidget, public Observer
{
private:
	Contract& contract;

	QHBoxLayout* main_ly = new QHBoxLayout;
	QTableView* table = new QTableView;
	MyTableView* model;
	QLineEdit* txt_denumire;
	QLineEdit* txt_ore;
	QLineEdit* txt_tip;
	QLineEdit* txt_profesor;
	QLineEdit* txt_nr_disci;
	QLineEdit* txt_fisier;
	QPushButton* add_btn;
	QPushButton* generate_btn;
	QPushButton* empty_btn;
	QPushButton* export_btn;


	void init_components();
	void connect_signals();
	void reload_list(const vector<Disciplina> contract);
	void load_info(QItemSelectionModel* selected);
	void add_contract_gui();
	void genereaza_gui();
	void goleste_gui();
	void export_gui();

public:

	GUIContractCRUDModel(Contract& contract) : contract{ contract }
	{
		model = new MyTableView{ contract.get_contract() };
		table->setModel(model);
		init_components();
		connect_signals();
		reload_list(contract.get_contract());
	}

	void update() {
		model->set_disci(contract.get_contract());
	}
};