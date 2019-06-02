#include "QtUI.h"
#include "test_service_cart.h"
#include "MyTableModel.h"


QtUI::QtUI(shared_ptr <Repository> _repo, QWidget *parent) : QWidget(parent), service(_repo){
	init();
	connect();
}

QtUI::~QtUI(){
}

void QtUI::run(){
	this->show();
}

void QtUI::update(const LinkedList <Medicine> &medicines){
	service_cart.populate(service.get_n_random(medicines.get_size()));
	show_lst_cart();
	notify(service_cart.get_all());
}

void QtUI::init() {
	QHBoxLayout *big_menu = new QHBoxLayout(this);

	big_menu->addWidget(table);
	show_lst();

	QVBoxLayout *layout_buttons = new QVBoxLayout(this);
	layout_buttons->addWidget(add_button);
	layout_buttons->addWidget(remove_button);
	layout_buttons->addWidget(find_button);
	layout_buttons->addWidget(modify_button);
	layout_buttons->addWidget(undo_button);

	QVBoxLayout *layout_buttons2 = new QVBoxLayout(this);
	layout_buttons2->addWidget(sort_button);
	layout_buttons2->addWidget(filter_button);
	layout_buttons2->addWidget(clear_filter_button);
	layout_buttons2->addWidget(distribution_button);

	criteria->addItem("Nume");
	criteria->addItem("Tip");
	criteria->addItem("Pret");
	criteria->addItem("Producator");

	layout_buttons2->addWidget(criteria);

	big_menu->addLayout(layout_buttons);
	big_menu->addLayout(layout_buttons2);
	layout->addLayout(big_menu);

	QHBoxLayout *cart_menu = new QHBoxLayout(this);
	lst_cart->setMaximumWidth(this->width() / 2);
	cart_menu->addWidget(lst_cart);
	show_lst_cart();

	QVBoxLayout *cart_buttons = new QVBoxLayout(this);
	cart_buttons->addWidget(add_cart_button);
	cart_buttons->addWidget(empty_cart_button);
	cart_buttons->addWidget(generate_cart_button);
	cart_buttons->addWidget(save_cart_button);

	cart_menu->addLayout(cart_buttons);
	layout->addLayout(cart_menu);

	QHBoxLayout *cart_buttons_GUI = new QHBoxLayout(this);
	cart_buttons_GUI->addWidget(cart_GUI_button);
	cart_buttons_GUI->addWidget(cart_RO_GUI_button);

	layout->addLayout(cart_buttons_GUI);

	layout->addWidget(close_button);
	tbl->setModel(mdl);
	layout->addWidget(tbl);
	layout->addWidget(footer);
}

void QtUI::clear_lst(){
	table->clear();
}

void QtUI::set_medicine(int idx, const Medicine &medicine) {
	table->setItem(idx, 0, new QTableWidgetItem(QString::fromStdString(medicine.get_name())));
	table->setItem(idx, 1, new QTableWidgetItem(QString::fromStdString(medicine.get_type())));
	table->setItem(idx, 2, new QTableWidgetItem(QString::number(medicine.get_price())));
	table->setItem(idx, 3, new QTableWidgetItem(QString::fromStdString(medicine.get_manufacturer())));
	table->setItem(idx, 4, new QTableWidgetItem(QString::number(service.get_filtered_by_type(medicine.get_type()).get_size())));
}

void QtUI::show_lst(){
	clear_lst();
	const LinkedList <Medicine> &medicines = service.get_all();
	mdl->set_medicines(medicines);
	table->setRowCount(medicines.get_size());
	table->setColumnCount(5);
	for (int i = 0; i < medicines.get_size();i++) {
		set_medicine(i, medicines.get_elem(i));
	}
	table->clearSelection();
	table->setHorizontalHeaderLabels(QStringList() << "Nume" << "Tip" << "Pret" << "Producator" << "Acelasi tip");
	color_lst();
}

void QtUI::show_lst_cart() {
	lst_cart->clear();
	const LinkedList <Medicine> &medicines = service_cart.get_all();
	QStringList cr_lst;
	for (const auto &medicine : medicines) {
		cr_lst << QString::fromStdString(medicine.get_name());
	}
	lst_cart->addItems(cr_lst);
	lst_cart->clearSelection();
}

void QtUI::update_lst(const LinkedList <Medicine> &medicines){
	clear_lst();
	mdl->set_medicines(medicines);
	table->setRowCount(medicines.get_size());
	table->setColumnCount(5);
	for (int i = 0; i < medicines.get_size(); i++) {
		set_medicine(i, medicines.get_elem(i));
	}
	table->clearSelection();
	table->setHorizontalHeaderLabels(QStringList() << "Nume" << "Tip" << "Pret" << "Producator" << "Acelasi tip");
	color_lst();
}

void QtUI::color_lst(){
	int id_1 = table->rowCount() * 0.33;
	int id_2 = table->rowCount() * 0.66;
	for(int i = 0;i < id_1;i++){
		for(int j = 0;j < 5;j++){
			table->item(i, j)->setBackground(Qt::red);
		}
	}
	for (int i = id_1; i < id_2; i++) {
		for (int j = 0; j < 5; j++) {
			table->item(i, j)->setBackground(Qt::green);
		}
	}
	for (int i = id_2; i < table->rowCount(); i++) {
		for (int j = 0; j < 5; j++) {
			table->item(i, j)->setBackground(Qt::blue);
		}
	}
}

void QtUI::connect(){
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [this](){
		if(table->currentColumn() != 0)
		{
			return;
		}
		QTableWidgetItem *medicine_name = table->currentItem();
		Medicine medicine = service.find(medicine_name->text().toStdString());
		this->set_message(QString::fromStdString(medicine.get_text()));
	});
	QObject::connect(close_button, &QPushButton::clicked, [this]() {
		this->close();
	});
	QObject::connect(add_button, &QPushButton::clicked, [this](){
		MedicineUI dialog(this);
		if(dialog.exec() == QDialog::Rejected){
			this->set_message("Adaugarea a fost inchisa");
			return;
		}
		QString name = dialog.get_name();
		QString type = dialog.get_type();
		double price = dialog.get_price().toDouble();
		QString manufacturer = dialog.get_manufacturer();

		try {
			service.add(name.toStdString(), type.toStdString(), price, manufacturer.toStdString());
		}catch(std::exception &exception){
			this->set_message(exception.what());
			return;
		}
		clear_lst();
		show_lst();
		this->set_message("S-a adaugat medicamentul " + name);
	});
	QObject::connect(find_button, &QPushButton::clicked, [this](){
		FindUI dialog(this);
		if(dialog.exec() == QDialog::Rejected){
			this->set_message("Cautarea a fost inchisa");
			return;
		}
		QString name = dialog.get_text();


		for(int i = 0;i < table->rowCount();i++){
			if(table->item(i, 0)->text() == name){
				table->setCurrentCell(i, 0);
				this->set_message("S-a gasit medicamentul " + name);
				return;
			}
		}

		this->set_message("Nu s-a gasit medicamentul " + name);
	});
	QObject::connect(remove_button, &QPushButton::clicked, [this](){
		if(table->currentItem() == Q_NULLPTR){
			this->set_message("Nu s-a selectat nici un medicament");
			return;
		}

		QString name = table->currentItem()->text();
		clear_lst();
		service.remove(name.toStdString());
		show_lst();
	});
	QObject::connect(modify_button, &QPushButton::clicked, [this]() {
		if (table->currentItem() == Q_NULLPTR) {
			this->set_message("Nu s-a selectat nici un medicament");
			return;
		}
		
		MedicineUI dialog(this);
		if (dialog.exec() == QDialog::Rejected) {
			this->set_message("Modificarea a fost inchisa");
			return;
		}
		QString old_name = table->currentItem()->text();
		QString name = dialog.get_name();
		QString type = dialog.get_type();
		double price = dialog.get_price().toDouble();
		QString manufacturer = dialog.get_manufacturer();

		clear_lst();
		service.modify(old_name.toStdString(), name.toStdString(), type.toStdString(), price, manufacturer.toStdString());
		show_lst();
		this->set_message("S-a modificat medicamentul " + name);
	});

	QObject::connect(sort_button, &QPushButton::clicked, [this](){
		clear_lst();
		QString current_criteria = criteria->currentText();
		update_lst(service.get_sorted(current_criteria.toLower().toStdString()));
		this->set_message("S-au sortat dupa " + current_criteria);
	});
	QObject::connect(filter_button, &QPushButton::clicked, [this]() {
		QString current_criteria = criteria->currentText();
		if (current_criteria == "Nume") {
			this->set_message("Nu are rost filtrarea dupa nume");
			return;
		}

		FilterUI dialog(this);
		if (dialog.exec() == QDialog::Rejected) {
			this->set_message("Filtrarea a fost inchisa");
			return;
		}

		QString text = dialog.get_text();

		if(current_criteria == "Tip"){
			update_lst(service.get_filtered_by_type(text.toStdString()));
		}else if(current_criteria == "Pret"){
			update_lst(service.get_filtered_by_price(text.toDouble()));
		}else if(current_criteria == "Producator"){
			update_lst(service.get_filtered_by_manufacturer(text.toStdString()));
		}

		this->set_message("S-au filtrat medicamentele dupa atributul " + current_criteria.toLower() + " si valoarea " + text);
	});
	QObject::connect(clear_filter_button, &QPushButton::clicked, [this](){
		show_lst();
	});
	QObject::connect(add_cart_button, &QPushButton::clicked, [this](){
		if (table->currentItem() == Q_NULLPTR) {
			this->set_message("Nu s-a selectat nici un medicament");
			return;
		}

		QString name = table->currentItem()->text();
		service_cart.add(service.find(name.toStdString()));
		show_lst_cart();

		this->notify(service_cart.get_all());

		this->set_message("S-a adaugat medicamentul " + name);
	});
	QObject::connect(empty_cart_button, &QPushButton::clicked, [this](){
		service_cart.empty();
		show_lst_cart();

		this->notify(service_cart.get_all());

		this->set_message("S-a golit cosul");
	});
	QObject::connect(generate_cart_button, &QPushButton::clicked, [this](){
		FilterUI dialog(this);
		if (dialog.exec() == QDialog::Rejected) {
			this->set_message("Generarea a fost inchisa");
			return;
		}

		QString text = dialog.get_text();

		const LinkedList <Medicine> &medicines = service.get_n_random(text.toDouble());
		service_cart.populate(medicines);
		show_lst_cart();

		this->notify(service_cart.get_all());

		this->set_message("S-au generat " + text + " medicamente in cos");
	});
	QObject::connect(save_cart_button, &QPushButton::clicked, [this](){
		service_cart.save_to_file();
		this->set_message("S-a salvat cosul in fisier");
	});
	QObject::connect(cart_GUI_button, &QPushButton::clicked, [this](){
		ObserverCart* nw_window = new CartCRUDGUI(this->service_cart.get_all(), this);
		addObserver(nw_window);
	});
	QObject::connect(cart_RO_GUI_button, &QPushButton::clicked, [this]() {
		ObserverCart* nw_window = new CartReadOnlyGUI(this->service_cart.get_all());
		addObserver(nw_window);
	});
}

void QtUI::set_message(const QString &message){
	footer->setText(message);
}


FindUI::FindUI(QWidget *parent) : QDialog(parent){
	init();
	connect();
}


QString FindUI::get_text() const{
	return text->toPlainText();
}

void FindUI::init(){
	layout->addWidget(header);
	text->setMaximumHeight(50);
	layout->addWidget(text);
	layout->addWidget(accept_button);
}

void FindUI::connect(){
	QObject::connect(accept_button, &QPushButton::clicked, [this](){
		this->accept();
	});
}

MedicineUI::MedicineUI(QWidget *parent) : QDialog(parent) {
	init();
	connect();
}

QString MedicineUI::get_name() const {
	return name->toPlainText();
}

QString MedicineUI::get_type() const {
	return type->toPlainText();
}

QString MedicineUI::get_price() const {
	return price->toPlainText();
}

QString MedicineUI::get_manufacturer() const {
	return manufacturer->toPlainText();
}

void MedicineUI::init() {
	layout->addWidget(header);

	name->setMaximumHeight(50);
	type->setMaximumHeight(25);
	price->setMaximumHeight(25);
	manufacturer->setMaximumHeight(25);

	layout->addWidget(name);
	layout->addWidget(type);
	layout->addWidget(price);
	layout->addWidget(manufacturer);
	layout->addWidget(accept_button);
}

void MedicineUI::connect() {
	QObject::connect(accept_button, &QPushButton::clicked, [this]() {
		this->accept();
	});
}

FilterUI::FilterUI(QWidget *parent) : QDialog(parent){
	init();
	connect();
}

void FilterUI::init(){
	layout->addWidget(header);
	text->setMaximumHeight(25);
	layout->addWidget(text);
	layout->addWidget(accept_button);
}

void FilterUI::connect() {
	QObject::connect(accept_button, &QPushButton::clicked, [this]() {
		this->accept();
	});
}

QString FilterUI::get_text() const{
	return text->toPlainText();
}

CartCRUDGUI::CartCRUDGUI(const LinkedList <Medicine> &medicines, ObserverCart* obs, QWidget *parent) : QWidget(parent) {
	update(medicines);
	addObserver(obs);
	init();
	connect();
}

void CartCRUDGUI::init() {
	layout->addWidget(lst);
	layout->addWidget(generate_button);
	this->show();
}

void CartCRUDGUI::connect() {
	QObject::connect(generate_button, &QPushButton::clicked, [this](){
		FilterUI dialog(this);
		if (dialog.exec() == QDialog::Rejected) {
			return;
		}

		QString text = dialog.get_text();
		int nr = text.toInt();

		LinkedList <Medicine> aux;
		for(int i = 0;i < nr;i++)
		{
			aux.append(Medicine("a"));
		}
		notify(aux);
	});
}

void CartCRUDGUI::update(const LinkedList <Medicine> &medicines) {
	lst->clear();
	QStringList cr_lst;
	for (const auto &medicine : medicines) {
		cr_lst << QString::fromStdString(medicine.get_name());
	}
	lst->addItems(cr_lst);
	lst->clearSelection();
}

CartReadOnlyGUI::CartReadOnlyGUI(const LinkedList <Medicine> &medicines, QWidget *parent) : QWidget(Q_NULLPTR){
	this->show();
	update(medicines);
}

void CartReadOnlyGUI::paintEvent(QPaintEvent *ev){
	QPainter canvas(this);
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> rndx(0, this->width() - 30);
	std::uniform_int_distribution<int> rndy(0, this->height() - 30);
	for (int i = 0; i < no_shapes; i++) {
		int x = rndx(rng);
		int y = rndy(rng);
		QRect rect(x, y, 30, 30);
		canvas.drawRect(rect);
	}
}

void CartReadOnlyGUI::update(const LinkedList <Medicine> &medicines) {
	no_shapes = medicines.get_size();
	repaint();
}