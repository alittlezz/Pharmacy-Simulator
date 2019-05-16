#include "Medicine.h"
#include <iostream>

Medicine::Medicine(const string &_name, const string &_type, const double &_price, const string &_manufacturer){
	name = _name;
	type = _type;
	price = _price;
	manufacturer = _manufacturer;
}

Medicine::Medicine(const Medicine &medicine) {
	name = medicine.get_name();
	type = medicine.get_type();
	price = medicine.get_price();
	manufacturer = medicine.get_manufacturer();
	//std::cout << "Copy\n";
}


const string& Medicine::get_name() const noexcept {
	return name;
}
const string& Medicine::get_type() const noexcept {
	return type;
}
const double& Medicine::get_price() const noexcept {
	return price;
}
const string& Medicine::get_manufacturer() const noexcept {
	return manufacturer;
}

string Medicine::get_text() const noexcept{
	return "Medicamentul " + name + " este de tipul " + type + ", are pretul " + std::to_string(price) + " si este produs de " + manufacturer;
}

void Medicine::set_name(const string &_name) {
	name = _name;
}
void Medicine::set_type(const string &_type) {
	type = _type;
}
void Medicine::set_price(const double &_price) noexcept{
	price = _price;
}
void Medicine::set_manufacturer(const string &_manufacturer) {
	manufacturer = _manufacturer;
}

DTOMedicine::DTOMedicine(const string &_name, const int &_ap, const string &_type, const double &_price, const string &_manufacturer):Medicine(_name, _type, _price, _manufacturer){
	ap = _ap;
}
void DTOMedicine::add_ap() noexcept{
	ap++;
}

void DTOMedicine::set_ap(const int &_ap) noexcept{
	ap = _ap;
}

const int& DTOMedicine::get_ap() const noexcept{
	return ap;
}