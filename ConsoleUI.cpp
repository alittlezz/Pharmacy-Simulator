#include "ConsoleUI.h"

#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
using std::cin;
using std::cout;


void ConsoleUI::finish() noexcept{
	running = false;
}

void ConsoleUI::populate() {
	service.add("med1", "tip1", 10, "prod1");
	service.add("med2", "tip1", 20, "prod1");
	service.add("med3", "tip2", 30, "prod1");
	service.add("med4", "tip2", 40, "prod1");
	service.add("med5", "tip2", 50, "prod1");
	service.add("med6", "tip3", 60, "prod2");
	service.add("med7", "tip3", 70, "prod2");
	service.add("med8", "tip4", 80, "prod2");
	service.add("med9", "tip4", 90, "prod2");
	service.add("med10", "tip4", 100, "prod2");
}


void ConsoleUI::print_medicines(const LinkedList < Medicine > &medicines) const {
	if (medicines.get_size() == 0) {
		cout << "Lista este goala\n";
		return;
	}
	cout << "Nume      Tip      Pret       Producator\n";
	for (auto it :medicines) {
		print_medicine(it);
	}
}

void ConsoleUI::print_medicine(const Medicine &medicine) const {
	cout << medicine.get_name() << ' ' << medicine.get_type() << ' ' << medicine.get_price() << ' ' << medicine.get_manufacturer() << '\n';
}

void ConsoleUI::print_all() const {
	const LinkedList < Medicine > &medicines = service.get_all();
	print_medicines(medicines);
}

void ConsoleUI::add() {
	string name;
	cout << "Introduceti nume: ";
	cin >> name;
	string type;
	cout << "Introduceti tip: ";
	cin >> type;
	float price;
	cout << "Introduceti pret: ";
	cin >> price;
	string manufacturer;
	cout << "Introduceti producator: ";
	cin >> manufacturer;

	service.add(name, type, price, manufacturer);
}

void ConsoleUI::remove() {
	string name;
	cout << "Introduceti nume: ";
	cin >> name;

	service.remove(name);
}

void ConsoleUI::modify() {
	string old_name;
	cout << "Introduceti nume vechi: ";
	cin >> old_name;

	string name;
	cout << "Introduceti nume: ";
	cin >> name;
	string type;
	cout << "Introduceti tip: ";
	cin >> type;
	float price;
	cout << "Introduceti pret: ";
	cin >> price;
	string manufacturer;
	cout << "Introduceti producator: ";
	cin >> manufacturer;

	service.modify(old_name, name, type, price, manufacturer);
}

void ConsoleUI::undo(){
	service.undo();
}

void ConsoleUI::find() const {
	string name;
	cout << "Introduceti nume: ";
	cin >> name;

	const Medicine &medicine = service.find(name);
	print_medicine(medicine);
}

void ConsoleUI::sort() const {
	string sort_comparison;
	cout << "Introduceti dupa ce sa se faca sortarea (nume/tip/pret/producator): ";
	cin >> sort_comparison;
	const LinkedList <Medicine> &medicines = service.get_sorted(sort_comparison);
	print_medicines(medicines);
}

void ConsoleUI::filter_by_type() const {
	string type;
	cout << "Introduceti tipul: ";
	cin >> type;
	const LinkedList < Medicine> &medicines = service.get_filtered_by_type(type);
	print_medicines(medicines);
}

void ConsoleUI::filter_by_price() const {
	double upper_bound;
	cout << "Introduceti pretul maxim: ";
	cin >> upper_bound;
	const LinkedList < Medicine> &medicines = service.get_filtered_by_price(upper_bound);
	print_medicines(medicines);
}

void ConsoleUI::filter_by_manufacturer() const {
	string manufacturer;
	cout << "Introduceti producatorul: ";
	cin >> manufacturer;
	const LinkedList < Medicine> &medicines = service.get_filtered_by_manufacturer(manufacturer);
	print_medicines(medicines);
}

void ConsoleUI::group_by_type() const{
	const LinkedList <DTOMedicine> &medicines = service.get_types();
	for(const auto &medicine : medicines){
		cout << "Tipul " << medicine.get_type() << " apare de " << medicine.get_ap() << '\n';
	}
}

void ConsoleUI::filter() const {
	string filter_comparison;
	cout << "Introduceti dupa ce sa se faca filtrarea (tip/pret/producator): ";
	cin >> filter_comparison;
	if (filter_comparison == "tip") {
		filter_by_type();
	}
	else if (filter_comparison == "pret") {
		filter_by_price();
	}
	else if (filter_comparison == "producator") {
		filter_by_manufacturer();
	}
	else {
		throw std::exception("Criteriul de filtrare nu este valid");
	}
}

void ConsoleUI::add_cart() {
	string name;
	cout << "Introduceti nume: ";
	cin >> name;
	const Medicine &medicine = service.find(name);
	service_cart.add(medicine);
	print_cart_total();
}

void ConsoleUI::empty_cart() {
	service_cart.empty();
	print_cart_total();
}

void ConsoleUI::generate_cart() {
	int n;
	cout << "Introduceti cate medicamente sa fie: ";
	cin >> n;
	service_cart.populate(service.get_n_random(n));
	print_cart_total();
}

void ConsoleUI::print_cart_total() const {
	const double total = service_cart.get_total();
	std::cout << "Pret total: " << total << '\n';
}

void ConsoleUI::print_cart() const {
	const LinkedList <Medicine> &medicines = service_cart.get_all();
	print_medicines(medicines);
	print_cart_total();
}

void ConsoleUI::save_to_file() const{
	service_cart.save_to_file();
}

void ConsoleUI::print_commands() const {
	for (const auto &command : commands) {
		cout << command << '\n';
	}
}

void ConsoleUI::print_delimiter() const {
	for (int i = 0; i < 30; i++) {
		cout << '-';
	}
	cout << '\n';
}

void ConsoleUI::handle_events() {
	string event_name;
	cout << "Introduceti comanda: ";
	cin >> event_name;
	try {
		events[event_name]();
	}
	catch (std::exception &exception) {
		cout << exception.what() << '\n';
	}
}

void ConsoleUI::run() {
	commands.append("0. Afiseaza lista de medicamente");
	commands.append("1. Adauga medicament");
	commands.append("2. Sterge medicament");
	commands.append("3. Modifica medicament");
	commands.append("4. Cauta medicament");
	commands.append("5. Sorteaza medicamentele");
	commands.append("6. Filtreaza medicamentele");
	commands.append("7. Adauga in cos");
	commands.append("8. Goleste cos");
	commands.append("9. Genereaza cos");
	commands.append("10. Afiseaza cos");
	commands.append("11. Salveaza cosul in fisier");
	commands.append("12. Realizeaza raport cu tipuri");
	commands.append("u. Undo la ultima operatie");
	commands.append("x. Exit");
	events["0"] = [this] { this->print_all(); };
	events["1"] = [this] { this->add(); };
	events["2"] = [this] { this->remove(); };
	events["3"] = [this] { this->modify(); };
	events["4"] = [this] { this->find(); };
	events["5"] = [this] { this->sort(); };
	events["6"] = [this] { this->filter(); };
	events["7"] = [this] { this->add_cart(); };
	events["8"] = [this] { this->empty_cart(); };
	events["9"] = [this] { this->generate_cart(); };
	events["10"] = [this] { this->print_cart(); };
	events["11"] = [this] { this->save_to_file(); };
	events["12"] = [this] { this->group_by_type(); };
	events["u"] = [this] { this->undo(); };
	events["x"] = [this] () noexcept { this->finish(); };
	//populate();
	running = true;
	while (running == true) {
		print_commands();
		print_delimiter();
		handle_events();
		print_delimiter();
	}
}
