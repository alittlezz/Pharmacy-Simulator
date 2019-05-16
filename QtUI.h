#pragma once

#include <QtWidgets>
#include <QVBoxLayout>
#include "Service.h"
#include "ServiceCart.h"

class QtUI : public QWidget{
	Q_OBJECT
public:
	QtUI(shared_ptr <Repository> _repo, QWidget *parent = Q_NULLPTR);
	void run();
private:
	void init();
	void connect();
	void show_lst();
	void show_lst_cart();
	void update_lst(const LinkedList <Medicine> &medicines);
	void color_lst();
	void clear_lst();
	void set_message(const QString &message);
	void set_medicine(int idx, const Medicine &medicine);

	Service service;
	ServiceCart service_cart = ServiceCart("medicines_cart.csv", true);

	QVBoxLayout *layout = new QVBoxLayout(this);
	//QListWidget *lst = new QListWidget(this);
	QTableWidget *table = new QTableWidget(this);

	QPushButton *close_button = new QPushButton("Exit", this);
	QPushButton *add_button = new QPushButton("Add medicine", this);
	QPushButton *remove_button = new QPushButton("Remove selected medicine", this);
	QPushButton *find_button = new QPushButton("Find a medicine", this);
	QPushButton *modify_button = new QPushButton("Modify selected medicine", this);
	QPushButton *undo_button = new QPushButton("Undo", this);

	QPushButton *sort_button = new QPushButton("Sort medicines", this);
	QPushButton *filter_button = new QPushButton("Filter medicines", this);
	QPushButton *clear_filter_button = new QPushButton("Remove filter", this);
	QPushButton *distribution_button = new QPushButton("Check medicines distribution", this);
	QComboBox *criteria = new QComboBox(this);

	QListWidget *lst_cart = new QListWidget(this);
	QPushButton *add_cart_button = new QPushButton("Add to cart", this);
	QPushButton *empty_cart_button = new QPushButton("Empty cart", this);
	QPushButton *generate_cart_button = new QPushButton("Generate cart", this);
	QPushButton *save_cart_button = new QPushButton("Save to cart", this);

	QLabel *footer = new QLabel(this);
};

class FindUI : public QDialog{
	Q_OBJECT
public:
	FindUI(QWidget *parent = Q_NULLPTR);
	QString get_text() const;
private:
	void init();
	void connect();

	QVBoxLayout *layout = new QVBoxLayout(this);
	QLabel *header = new QLabel("Introduceti numele medicamentului:" ,this);
	QTextEdit *text = new QTextEdit(this);
	QPushButton *accept_button = new QPushButton("Accept", this);
};

class MedicineUI : public QDialog{
	Q_OBJECT
public:
	MedicineUI(QWidget *parent = Q_NULLPTR);
	QString get_name() const;
	QString get_type() const;
	QString get_price() const;
	QString get_manufacturer() const;
private:
	void init();
	void connect();

	QVBoxLayout *layout = new QVBoxLayout(this);
	QLabel *header = new QLabel("Introduceti datele medicamentului:", this);
	QTextEdit *name = new QTextEdit(this);
	QTextEdit *type = new QTextEdit(this);
	QTextEdit *price = new QTextEdit(this);
	QTextEdit *manufacturer = new QTextEdit(this);
	QPushButton *accept_button = new QPushButton("Accept", this);
};

class FilterUI : public QDialog{
	Q_OBJECT
public:
	FilterUI(QWidget *parent = Q_NULLPTR);
	QString get_text() const;
private:
	void init();
	void connect();

	QVBoxLayout *layout = new QVBoxLayout(this);
	QLabel *header = new QLabel("Introduceti valoarea de filtrare", this);
	QTextEdit *text = new QTextEdit(this);
	QPushButton *accept_button = new QPushButton("Accept", this);
};