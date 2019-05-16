#include "ServiceCart.h"
#include <fstream>
#include "my_utility.h"

using std::vector;


void ServiceCart::add(const Medicine &medicine) {
	//validator.validate_medicine(medicine);

	cart.append(medicine);
}

void ServiceCart::empty() noexcept{
	cart = LinkedList <Medicine>();
}

void ServiceCart::populate(const LinkedList <Medicine> &medicines) {
	empty();
	for (const auto &medicine : medicines) {
		//validator.validate_medicine(medicine);
		add(medicine);
	}
}

const LinkedList<Medicine>& ServiceCart::get_all() const noexcept{
	return cart;
}

double ServiceCart::get_total() const noexcept{
	double total = 0;
	for (const auto &it : cart) {
		total += it.get_price();
	}
	return total;
}

void ServiceCart::load_from_file() {
	std::ifstream fin(file_name);
	string line;
	while (fin >> line) {
		vector <string> attrs = my_split(line, ",");
		add(Medicine(attrs.at(0), attrs.at(1), std::stoi(attrs.at(2)), attrs.at(3)));
	}
}

void ServiceCart::save_to_file() const{
	std::ofstream fout(file_name);
	for (const auto &medicine : get_all()) {
		fout << medicine.get_name() << ',' << medicine.get_type() << ',' << medicine.get_price() << ',' << medicine.get_manufacturer() << '\n';
	}
}
