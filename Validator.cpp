#include "Validator.h"
#include "exceptions.h"

void Validator::validate_medicine(const Medicine &medicine) const {
	string exceptions = "";
	try {
		validate_name(medicine.get_name());
	}
	catch (std::exception &exception) {
		exceptions += exception.what();
	}

	try {
		validate_type(medicine.get_type());
	}
	catch (std::exception &exception) {
		exceptions += exception.what();
	}

	try {
		validate_price(medicine.get_price());
	}
	catch (std::exception &exception) {
		exceptions += exception.what();
	}

	try {
		validate_manufacturer(medicine.get_manufacturer());
	}
	catch (std::exception &exception) {
		exceptions += exception.what();
	}

	if (exceptions != "") {
		throw std::exception(exceptions.c_str());
	}
}

void Validator::validate_name(const string &name) const {
	if (name == "") {
		throw MedicineNameNotValid();
	}
}

void Validator::validate_type(const string &type) const {
	if (type == "") {
		throw MedicineTypeNotValid();
	}
}

void Validator::validate_price(const double &price) const {
	if (price <= 0){
		throw MedicinePriceNotValid();
	}
}

void Validator::validate_manufacturer(const string &manufacturer) const {
	if (manufacturer == ""){
		throw MedicineManufacturerNotValid();
	}
}

