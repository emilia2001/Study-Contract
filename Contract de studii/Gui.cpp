#include "Gui.h"
#include <warning.h>
#include <qmessagebox.h>

void GUI::init_components()
{


	setLayout(main_ly);

	auto* wid = new QWidget;
	auto* lay = new QHBoxLayout;
	wid->setStyleSheet("background-color:    #364F6B");


	QWidget* w_lista = new QWidget;
	w_lista->setStyleSheet("background-color:    #364F6B");
	QVBoxLayout* v_box = new QVBoxLayout;
	w_lista->setLayout(v_box);
	v_box->addWidget(new QLabel{ "DISCIPLINE" });
	//list = new QListWidget;
	//list = new QListView;
	//model = new MyTableView{serv.get_all()};
	//list->setModel(model);
	//list->setStyleSheet("background-color:    #3FC1C9");
	v_box->addWidget(list);
	get_all_btn = new QPushButton{ "Toate disciplinele" };
	get_all_btn->setStyleSheet("background-color:    #FC5185");
	v_box->addWidget(get_all_btn);
	v_box->addWidget(new QLabel{ "" });
	v_box->addWidget(new QLabel{ "SORTARE" });
	QHBoxLayout* s_buttons = new QHBoxLayout;
	sort_denumire_btn = new QPushButton{ "Denumire" };
	sort_denumire_btn->setStyleSheet("background-color:    #FC5185");
	sort_ore_btn = new QPushButton{ "Numar ore" };
	sort_ore_btn->setStyleSheet("background-color:    #FC5185");
	sort_cadru_btn = new QPushButton{ "Profesor si tip" };
	sort_cadru_btn->setStyleSheet("background-color:    #FC5185");
	s_buttons->addWidget(sort_denumire_btn);
	s_buttons->addWidget(sort_ore_btn);
	s_buttons->addWidget(sort_cadru_btn);
	v_box->addLayout(s_buttons);

	v_box->addWidget(new QLabel{ "" });
	v_box->addWidget(new QLabel{ "FILTRARE" });
	filter_ore_btn = new QPushButton{ "Numar ore" };
	filter_ore_btn->setStyleSheet("background-color:    #FC5185");
	filter_prof_btn = new QPushButton{ "Profesor" };
	filter_prof_btn->setStyleSheet("background-color:    #FC5185");
	QHBoxLayout* f_buttons = new QHBoxLayout;
	f_buttons->addWidget(filter_ore_btn);
	f_buttons->addWidget(filter_prof_btn);
	v_box->addLayout(f_buttons);

	//info disci
	auto w_meniu = new QWidget;
	w_meniu->setStyleSheet("background-color:    #364F6B");
	auto info = new QFormLayout;
	w_meniu->setLayout(info);
	info->addWidget(new QLabel{ "INFORMATII DISCIPLINA" });
	txt_denumire = new QLineEdit;
	txt_denumire->setStyleSheet("background-color:    #3FC1C9");
	txt_ore = new QLineEdit;
	txt_ore->setStyleSheet("background-color:    #3FC1C9");
	txt_tip = new QLineEdit;
	txt_tip->setStyleSheet("background-color:    #3FC1C9");
	txt_profesor = new QLineEdit;
	txt_profesor->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Denumire", txt_denumire);
	info->addRow("Numar de ore", txt_ore);
	info->addRow("Tip", txt_tip);
	info->addRow("Profesor", txt_profesor);
	//meniu
	add_btn = new QPushButton{ "Adauga disciplina" };
	add_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(add_btn);
	delete_btn = new QPushButton{ "Sterge disciplina" };
	delete_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(delete_btn);
	update_btn = new QPushButton{ "Modifica disciplina" };
	update_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(update_btn);
	search_btn = new QPushButton{ "Cauta disciplina" };
	search_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(search_btn);
	info->addWidget(new QLabel{ "" });
	undo_btn = new QPushButton{ "Undo" };
	undo_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(undo_btn);
	info->addWidget(new QLabel{ "" });
	info->addWidget(new QLabel{ "MENIU CONTRACT" });
	add_contract_btn = new QPushButton{ "Adaugare disciplina in contract" };
	add_contract_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(add_contract_btn);
	txt_nr_generate = new QLineEdit;
	txt_nr_generate->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Numar discipline", txt_nr_generate);
	generate_contract_btn = new QPushButton{ "Genereaza contract random" };
	generate_contract_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(generate_contract_btn);
	empty_contract_btn = new QPushButton{ "Goleste contractul" };
	empty_contract_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(empty_contract_btn);
	contract_crud_btn = new QPushButton{ "Contract de studii CRUD" };
	contract_crud_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(contract_crud_btn);
	contract_rdonly_btn = new QPushButton{ "Contract de studii ReadOnly" };
	contract_rdonly_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(contract_rdonly_btn);


	lay->addWidget(w_lista);
	lay->addWidget(w_meniu);

	wid->setLayout(lay);


	main_ly->addWidget(wid);

}

void GUI::connect_signals()
{
	QObject::connect(get_all_btn, &QPushButton::clicked, [&]() {reload_list(serv.get_all()); });

	QObject::connect(sort_denumire_btn, &QPushButton::clicked, [&]() {reload_list(serv.sortare_denumire()); });
	QObject::connect(sort_ore_btn, &QPushButton::clicked, [&]() {reload_list(serv.sortare_ore()); });
	QObject::connect(sort_cadru_btn, &QPushButton::clicked, [&]() {reload_list(serv.sortare_prof_tip()); });

	QObject::connect(filter_ore_btn, &QPushButton::clicked, this, &GUI::filtrare_ore);
	QObject::connect(filter_prof_btn, &QPushButton::clicked, this, &GUI::filtrare_prof);

	QObject::connect(add_btn, &QPushButton::clicked, this, &GUI::add_gui);
	QObject::connect(delete_btn, &QPushButton::clicked, this, &GUI::delete_gui);
	QObject::connect(update_btn, &QPushButton::clicked, this, &GUI::update_gui);
	QObject::connect(search_btn, &QPushButton::clicked, this, &GUI::search_gui);
	QObject::connect(undo_btn, &QPushButton::clicked, this, &GUI::undo_gui);


	QObject::connect(add_contract_btn, &QPushButton::clicked, this, &GUI::add_contract_gui);
	QObject::connect(generate_contract_btn, &QPushButton::clicked, this, &GUI::generate_contract_gui);
	QObject::connect(empty_contract_btn, &QPushButton::clicked, this, &GUI::empty_contract_gui);
	QObject::connect(contract_crud_btn, &QPushButton::clicked, [&]() {/*GUIContractCRUD* gui_c = new GUIContractCRUD{ contract }; gui_c->show();*/    GUIContractCRUDModel* gui_c = new GUIContractCRUDModel{ contract }; gui_c->show();});
	QObject::connect(contract_rdonly_btn, &QPushButton::clicked, [&]() { GUIContractReadOnly* gui_c = new GUIContractReadOnly{ contract }; gui_c->show(); });

	QObject::connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		/*
		if(list->selectionModel()->selectedIndexes().isEmpty())
		{
			txt_denumire->setText("");
			txt_ore->setText("");
			txt_tip->setText("");
			txt_profesor->setText("");
			return;
		}
		txt_denumire->clear();
		txt_ore->clear();
		txt_tip->clear();
		txt_profesor->clear();
		auto curr = list->selectionModel()->selectedIndexes().at(0);
		string denumire = curr.data(Qt::DisplayRole).toString().toStdString();
		Disciplina d = serv.search_serv(denumire);
		txt_denumire->setText(QString::fromStdString(denumire));
		txt_ore->setText(QString::number(d.get_nr_ore()));
		txt_tip->setText(QString::fromStdString(d.get_tip()));
		txt_profesor->setText(QString::fromStdString(d.get_profesor()));*/
		});

}

void GUI::load_info(QList<QListWidgetItem*> selected)
{
	if (selected.isEmpty())
	{
		txt_denumire->setText("");
		txt_ore->setText("");
		txt_tip->setText("");
		txt_profesor->setText("");
	}
	else
	{
		auto sel_disci = selected.at(0);
		auto denumire = sel_disci->data(Qt::UserRole).toString();
		txt_denumire->setText(denumire);
		auto disci = serv.search_serv(denumire.toStdString());
		txt_ore->setText(QString::number(disci.get_nr_ore()));
		txt_tip->setText(QString::fromStdString(disci.get_tip()));
		txt_profesor->setText(QString::fromStdString(disci.get_profesor()));
	}
}

void GUI::add_gui()
{
	try {
		serv.add_serv(txt_denumire->text().toStdString(), txt_ore->text().toInt(), txt_tip->text().toStdString(), txt_profesor->text().toStdString());
		reload_list(serv.get_all());
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (ValidatorError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::delete_gui()
{
	try {
		serv.delete_serv(txt_denumire->text().toStdString());
		reload_list(serv.get_all());
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (ValidatorError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::update_gui()
{
	try {
		serv.update_serv(txt_denumire->text().toStdString(), txt_profesor->text().toStdString());
		reload_list(serv.get_all());
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (ValidatorError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::search_gui()
{
	try {
		auto disci = serv.search_serv(txt_denumire->text().toStdString());
		txt_denumire->setText(QString::fromStdString(disci.get_denumire()));
		txt_ore->setText(QString::number(disci.get_nr_ore()));
		txt_tip->setText(QString::fromStdString(disci.get_tip()));
		txt_profesor->setText(QString::fromStdString(disci.get_profesor()));
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (ValidatorError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::undo_gui()
{
	try {
		serv.undo();
		reload_list(serv.get_all());
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::reload_list(const vector<Disciplina> discis)
{
	auto disci = serv.get_all();
	model->set_disci(disci);
	/*
	list->clear();
	for (const auto& d : discis)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.get_denumire()));
		item->setData(Qt::UserRole, QString::fromStdString(d.get_denumire()));
		list->addItem(item);

	}
	*/
}

void GUI::filtrare_ore()
{
	reload_list(serv.filtrare_ore(txt_ore->text().toInt()));
}

void GUI::filtrare_prof()
{
	reload_list(serv.filtrare_prof(txt_profesor->text().toStdString()));
}

void GUI::add_contract_gui()
{
	try {
		contract.add(txt_denumire->text().toStdString());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::generate_contract_gui()
{
	try {
		contract.genereaza(txt_nr_generate->text().toInt());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUI::empty_contract_gui()
{
	contract.goleste();
}




//gui contract CRUD
void GUIContractCRUD::init_components()
{
	contract.addObserver(this);
	setLayout(main_ly);

	auto* wid = new QWidget;
	auto* lay = new QHBoxLayout;
	wid->setStyleSheet("background-color:    #364F6B");

	QWidget* widget_meniu = new QWidget;
	QVBoxLayout* meniu = new QVBoxLayout;
	widget_meniu->setLayout(meniu);
	auto info = new QFormLayout;
	info->addWidget(new QLabel{ "INFORMATII DISCIPLINA" });
	txt_denumire = new QLineEdit;
	txt_denumire->setStyleSheet("background-color:    #3FC1C9");
	txt_ore = new QLineEdit;
	txt_ore->setStyleSheet("background-color:    #3FC1C9");
	txt_tip = new QLineEdit;
	txt_tip->setStyleSheet("background-color:    #3FC1C9");
	txt_profesor = new QLineEdit;
	txt_profesor->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Denumire", txt_denumire);
	info->addRow("Numar de ore", txt_ore);
	info->addRow("Tip", txt_tip);
	info->addRow("Profesor", txt_profesor);

	//meniu
	add_btn = new QPushButton{ "Adauga disciplina" };
	add_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(add_btn);
	info->addWidget(new QLabel{ "" });
	txt_nr_disci = new QLineEdit;
	txt_nr_disci->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Numar discipline", txt_nr_disci);
	generate_btn = new QPushButton{ "Genereaza contract" };
	generate_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(generate_btn);
	info->addWidget(new QLabel{ "" });
	empty_btn = new QPushButton{ "Goleste contract" };
	empty_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(empty_btn);
	info->addWidget(new QLabel{ "" });
	txt_fisier = new QLineEdit;
	txt_fisier->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Fisier export", txt_fisier);
	export_btn = new QPushButton{ "Export contract" };
	export_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(export_btn);

	//lista
	QWidget* w_list = new QWidget;
	QVBoxLayout* lista_c = new QVBoxLayout;
	lista_c->addWidget(new QLabel{ "DISCIPLINELE DIN CONTRACT" });
	w_list->setLayout(lista_c);
	
	table = new QTableWidget;
	table->setStyleSheet("background-color:    #3FC1C9");
	table->setColumnCount(4);
	table->setVerticalHeaderLabels(QStringList{ "Disciplina", "Numar de ore" , "Tip" , "Profesor" });
/*
	table = new QTableView;
	model = new MyTableView{ contract.get_contract() };
	table->setModel(model);
	*/
	lista_c->addWidget(table);
	lista_c->addStretch();
	meniu->addLayout(info);

	lay->addWidget(widget_meniu);
	lay->addWidget(w_list);

	wid->setLayout(lay);

	//main_ly->addWidget(widget_meniu);
	//main_ly->addWidget(w_list);
	//main_ly->addStretch();

	main_ly->addWidget(wid);
}


void GUIContractCRUD::reload_list(const vector<Disciplina> contractt)
{
	
	table->clear();
	table->setRowCount(0);
	int poz{ 0 };
	for (const auto& d : contractt)
	{
		table->insertRow(poz);
		QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(d.get_denumire()));
		item1->setData(Qt::UserRole, QString::fromStdString(d.get_denumire()));
		table->setItem(poz, 0, item1);
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(d.get_nr_ore()));
		item2->setData(Qt::UserRole, QString::fromStdString(d.get_denumire()));
		table->setItem(poz, 1, item2);
		QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(d.get_tip()));
		item3->setData(Qt::UserRole, QString::fromStdString(d.get_denumire()));
		table->setItem(poz, 2, item3);
		QTableWidgetItem* item4 = new QTableWidgetItem(QString::fromStdString(d.get_profesor()));
		item4->setData(Qt::UserRole, QString::fromStdString(d.get_denumire()));
		table->setItem(poz, 3, item4);
		poz++;
	}
}

void GUIContractCRUD::connect_signals()
{

	QObject::connect(add_btn, &QPushButton::clicked, this, &GUIContractCRUD::add_contract_gui);
	QObject::connect(generate_btn, &QPushButton::clicked, this, &GUIContractCRUD::genereaza_gui);
	QObject::connect(empty_btn, &QPushButton::clicked, this, &GUIContractCRUD::goleste_gui);
	QObject::connect(export_btn, &QPushButton::clicked, this, &GUIContractCRUD::export_gui);
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		auto selected = table->selectedItems();
		load_info(selected); });

/*
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		auto selected = table->selectionModel();
		load_info(selected);
		}
	);*/
	

}

void GUIContractCRUD::load_info(QList <QTableWidgetItem*> selected)
{
	if (selected.isEmpty())
	{
		txt_denumire->setText("");
		txt_ore->setText("");
		txt_tip->setText("");
		txt_profesor->setText("");
	}
	else
	{
		auto sel_row = selected.at(0);
		auto denumire = sel_row->data(Qt::UserRole).toString();
		txt_denumire->setText(denumire);
		auto disci = contract.search_disci(denumire.toStdString());
		txt_ore->setText(QString::number(disci.get_nr_ore()));
		txt_tip->setText(QString::fromStdString(disci.get_tip()));
		txt_profesor->setText(QString::fromStdString(disci.get_profesor()));
	}
}

void GUIContractCRUD::add_contract_gui()
{
	try {
		contract.add(txt_denumire->text().toStdString());
		//model->set_disci(contract.get_contract());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUIContractCRUD::genereaza_gui()
{
	try {
		contract.genereaza(txt_nr_disci->text().toInt());
		//model->set_disci(contract.get_contract());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUIContractCRUD::goleste_gui()
{
	contract.goleste();
	//model->set_disci(contract.get_contract());
	reload_list(contract.get_contract());
}

void GUIContractCRUD::export_gui()
{
	try {
		contract.export_contract(txt_fisier->text().toStdString());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}



//viewModel
void GUIContractCRUDModel::init_components()
{
	contract.addObserver(this);
	setLayout(main_ly);

	auto* wid = new QWidget;
	auto* lay = new QHBoxLayout;
	wid->setStyleSheet("background-color:    #364F6B");

	QWidget* widget_meniu = new QWidget;
	QVBoxLayout* meniu = new QVBoxLayout;
	widget_meniu->setLayout(meniu);
	auto info = new QFormLayout;
	info->addWidget(new QLabel{ "INFORMATII DISCIPLINA" });
	txt_denumire = new QLineEdit;
	txt_denumire->setStyleSheet("background-color:    #3FC1C9");
	txt_ore = new QLineEdit;
	txt_ore->setStyleSheet("background-color:    #3FC1C9");
	txt_tip = new QLineEdit;
	txt_tip->setStyleSheet("background-color:    #3FC1C9");
	txt_profesor = new QLineEdit;
	txt_profesor->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Denumire", txt_denumire);
	info->addRow("Numar de ore", txt_ore);
	info->addRow("Tip", txt_tip);
	info->addRow("Profesor", txt_profesor);

	//meniu
	add_btn = new QPushButton{ "Adauga disciplina" };
	add_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(add_btn);
	info->addWidget(new QLabel{ "" });
	txt_nr_disci = new QLineEdit;
	txt_nr_disci->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Numar discipline", txt_nr_disci);
	generate_btn = new QPushButton{ "Genereaza contract" };
	generate_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(generate_btn);
	info->addWidget(new QLabel{ "" });
	empty_btn = new QPushButton{ "Goleste contract" };
	empty_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(empty_btn);
	info->addWidget(new QLabel{ "" });
	txt_fisier = new QLineEdit;
	txt_fisier->setStyleSheet("background-color:    #3FC1C9");
	info->addRow("Fisier export", txt_fisier);
	export_btn = new QPushButton{ "Export contract" };
	export_btn->setStyleSheet("background-color:    #FC5185");
	info->addWidget(export_btn);

	//lista
	QWidget* w_list = new QWidget;
	QVBoxLayout* lista_c = new QVBoxLayout;
	lista_c->addWidget(new QLabel{ "DISCIPLINELE DIN CONTRACT" });
	w_list->setLayout(lista_c);

	//table = new QTableWidget;
	//table->setStyleSheet("background-color:    #3FC1C9");
	//table = new QTableView;

	lista_c->addWidget(table);
	lista_c->addStretch();
	meniu->addLayout(info);

	lay->addWidget(widget_meniu);
	lay->addWidget(w_list);

	wid->setLayout(lay);

	//main_ly->addWidget(widget_meniu);
	//main_ly->addWidget(w_list);
	//main_ly->addStretch();

	main_ly->addWidget(wid);
}

void GUIContractCRUDModel::reload_list(const vector<Disciplina> contractt)
{
	model->set_disci(contractt);
}

void GUIContractCRUDModel::connect_signals()
{

	QObject::connect(add_btn, &QPushButton::clicked, this, &GUIContractCRUDModel::add_contract_gui);
	QObject::connect(generate_btn, &QPushButton::clicked, this, &GUIContractCRUDModel::genereaza_gui);
	QObject::connect(empty_btn, &QPushButton::clicked, this, &GUIContractCRUDModel::goleste_gui);
	QObject::connect(export_btn, &QPushButton::clicked, this, &GUIContractCRUDModel::export_gui);
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			auto selected = table->selectionModel();
			load_info(selected);
			}
		);


}

void GUIContractCRUDModel::load_info(QItemSelectionModel* selected)
{
	if (selected->selectedIndexes().isEmpty())
	{
		txt_denumire->setText("");
		txt_ore->setText("");
		txt_tip->setText("");
		txt_profesor->setText("");
	}
	else
	{
		auto sel_row = selected->selectedIndexes().at(0).row();
		auto cel0idx = table->model()->index(sel_row, 0);
		auto denumire = table->model()->data(cel0idx, Qt::DisplayRole).toString();
		qDebug() << denumire;
		txt_denumire->setText(denumire);
		auto disci = contract.search_disci(denumire.toStdString());
		txt_ore->setText(QString::number(disci.get_nr_ore()));
		txt_tip->setText(QString::fromStdString(disci.get_tip()));
		txt_profesor->setText(QString::fromStdString(disci.get_profesor()));
	}
}

void GUIContractCRUDModel::add_contract_gui()
{
	try {
		contract.add(txt_denumire->text().toStdString());
		//model->set_disci(contract.get_contract());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
	catch (RepoError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUIContractCRUDModel::genereaza_gui()
{
	try {
		contract.genereaza(txt_nr_disci->text().toInt());
		//model->set_disci(contract.get_contract());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}

void GUIContractCRUDModel::goleste_gui()
{
	contract.goleste();
	//model->set_disci(contract.get_contract());
	reload_list(contract.get_contract());
}

void GUIContractCRUDModel::export_gui()
{
	try {
		contract.export_contract(txt_fisier->text().toStdString());
		reload_list(contract.get_contract());
	}
	catch (ContractError& err) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.get_error()));
	}
}
