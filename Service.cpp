#include "Service.h"

#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include "exceptions.h"

using std::sort;
using std::copy_if;
using std::back_inserter;


Service::Service(shared_ptr <Repository> _repository) noexcept{
	repository = _repository;
}

void Service::add(const string &name, const string &type, const double &price, const string &manufacturer) {
	Medicine new_medicine = Medicine(name, type, price, manufacturer);
	validator.validate_medicine(new_medicine);

	undo_actions.push_back(make_unique<UndoAdd>(repository, new_medicine.get_name()));

	repository.get()->add(new_medicine);
}

void Service::remove(const string &name) {
	validator.validate_name(name);

	undo_actions.push_back(make_unique<UndoRemove>(repository, repository.get()->find(name)));

	repository.get()->remove(name);
}

void Service::modify(const string &old_name, const string &name, const string &type, const double &price, const string &manufacturer) {
	Medicine new_medicine = Medicine(name, type, price, manufacturer);
	validator.validate_medicine(new_medicine);
	validator.validate_name(old_name);

	undo_actions.push_back(make_unique<UndoModify>(repository, repository.get()->find(old_name), new_medicine.get_name()));

	repository.get()->modify(old_name, new_medicine);
}

void Service::undo(){
	if(undo_actions.empty()){
		throw UndoActionsEmpty();
	}
	shared_ptr <UndoAction> last_undo = move(undo_actions.back());
	undo_actions.pop_back();
	last_undo.get()->do_undo();
}

const Medicine& Service::find(const string &name) const {
	validator.validate_name(name);

	return repository.get()->find(name);
}


LinkedList <Medicine> Service::get_n_random(const int &n) const {
	std::mt19937 seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));

	const LinkedList <Medicine> &medicines = get_all();
	const std::uniform_int_distribution <int> generator(0, medicines.get_size() - 1);
	
	LinkedList <Medicine> random_medicines;
	for (int i = 0; i < n; i++) {
		random_medicines.append(medicines.get_elem(generator(seed)));
	}
	return random_medicines;
}

int Service::get_count(const string &name) const{
	validator.validate_name(name);
	
	const LinkedList <Medicine> &medicines = get_all();
	int ret = 0;
	for(const auto &medicine : medicines){
		if(medicine == name){
			ret++;
		}
	}
	return ret;
}

LinkedList <Medicine> Service::get_sorted(const string &sort_comparison) const {
	if (sort_comparison == "nume") {
		return get_sorted_by_name();
	}
	if (sort_comparison == "tip") {
		return get_sorted_by_type();
	}
	if (sort_comparison == "pret") {
		return get_sorted_by_price();
	}
	if (sort_comparison == "producator") {
		return get_sorted_by_manufacturer();
	}
	throw std::exception("Criteriul de sortare nu este valid");
}

LinkedList <Medicine> Service::get_sorted_by_name() const {
	LinkedList <Medicine> medicines(repository.get()->get_all());
	medicines.sort([](const Medicine &med1, const Medicine &med2) noexcept {
		return med1.get_name() < med2.get_name();
	});
	/*sort(medicines.begin(), medicines.end(), [](const Medicine &med1, const Medicine &med2) noexcept{
		return med1.get_name() < med2.get_name();
	});*/
	return medicines;
}

LinkedList <Medicine> Service::get_sorted_by_type() const {
	LinkedList <Medicine> medicines(repository.get()->get_all());
	medicines.sort([](const Medicine &med1, const Medicine &med2) noexcept {
		return med1.get_type() < med2.get_type();
	});
	/*sort(medicines.begin(), medicines.end(), [](const Medicine &med1, const Medicine &med2) noexcept{
		return med1.get_type() < med2.get_type();
	});*/
	return medicines;
}

LinkedList <Medicine> Service::get_sorted_by_price() const {
	LinkedList <Medicine> medicines(repository.get()->get_all());
	medicines.sort([](const Medicine &med1, const Medicine &med2) noexcept {
		return med1.get_price() < med2.get_price();
	});
	/*sort(medicines.begin(), medicines.end(), [](const Medicine &med1, const Medicine &med2) noexcept{
		return med1.get_price() < med2.get_price();
	});*/
	return medicines;
}

LinkedList <Medicine> Service::get_sorted_by_manufacturer() const {
	LinkedList <Medicine> medicines(repository.get()->get_all());
	medicines.sort([](const Medicine &med1, const Medicine &med2) noexcept {
		return med1.get_manufacturer() < med2.get_manufacturer();
	});
	/*sort(medicines.begin(), medicines.end(), [](const Medicine &med1, const Medicine &med2) noexcept{
		return med1.get_manufacturer() < med2.get_manufacturer();
	});*/
	return medicines;
}

LinkedList <Medicine> Service::get_filtered_by_type(const string &type) const {
	validator.validate_type(type);

	const LinkedList <Medicine> &medicines = repository.get()->get_all();
	return medicines.filter([type](const Medicine &med) noexcept {
		return med.get_type() == type;
	});
	/*
	LinkedList <Medicine> filtered;
	copy_if(medicines.begin(), medicines.end(), std::back_inserter(filtered), [type](const Medicine &med) noexcept{
		return med.get_type() == type;
	});*/
}

LinkedList <Medicine> Service::get_filtered_by_price(const double &upper_bound) const {
	validator.validate_price(upper_bound);

	const LinkedList <Medicine> &medicines = repository.get()->get_all();
	return medicines.filter([upper_bound](const Medicine &med) noexcept {
		return med.get_price() <= upper_bound;
	});
	/*
	LinkedList <Medicine> filtered;
	copy_if(medicines.begin(), medicines.end(), std::back_inserter(filtered), [upper_bound](const Medicine &med) noexcept{
		return med.get_price() <= upper_bound;
	});*/
}

LinkedList <Medicine> Service::get_filtered_by_manufacturer(const string &manufacturer) const {
	validator.validate_manufacturer(manufacturer);
	
	const LinkedList <Medicine> &medicines = repository.get()->get_all();
	return medicines.filter([manufacturer](const Medicine &med) noexcept {
		return med.get_manufacturer() == manufacturer;
	});
	/*
	LinkedList <Medicine> filtered;
	copy_if(medicines.begin(), medicines.end(), std::back_inserter(filtered), [manufacturer](const Medicine &med) noexcept{
		return med.get_manufacturer() == manufacturer;
	});*/
}

LinkedList<DTOMedicine> Service::get_types() const{
	std::map <string, int> mp;
	const LinkedList <Medicine> &medicines = repository.get()->get_all();
	for(const auto &medicine : medicines){
		mp[medicine.get_type()]++;
	}
	LinkedList <DTOMedicine> result;
	for(const auto &it : mp){
		DTOMedicine dto_medicine(it.first, it.second, it.first);
		result.append(dto_medicine);
	}
	return result;
}

const LinkedList <Medicine>& Service::get_all() const noexcept {
	return repository.get()->get_all();
}
