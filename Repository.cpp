#include "Repository.h"
#include <algorithm>
#include <exception>
#include "exceptions.h"
#include <vector>
#include "my_utility.h"

using std::vector;


Repository::Repository() noexcept{
}

void Repository::add(const Medicine &medicine) {
	if (is_duplicate(medicine)) {
		throw RepositoryDuplicateMedicine();
	}
	medicines.append(medicine);
}

void Repository::remove(const string &name) {
	if (!is_duplicate(name)) {
		throw RepositoryNotFoundMedicine();
	}
	const auto idx = medicines.find(Medicine(name));
	medicines.remove(idx);
}

void Repository::modify(const string &name, const Medicine &new_medicine) {
	if (!is_duplicate(name)) {
		throw RepositoryNotFoundMedicine();
	}
	const auto idx = medicines.find(Medicine(name));
	medicines.replace(idx, new_medicine);
}


bool Repository::is_duplicate(const Medicine &medicine) const {
	try {
		find(medicine);
		return true;
	}
	catch (std::exception&) {}
	return false;
}

bool Repository::is_duplicate(const string &name) const{
	return is_duplicate(Medicine(name));
}

const Medicine& Repository::find(const string &name) const{
	const Medicine searched_medicine(name);
	return find(searched_medicine);
}

const Medicine& Repository::find(const Medicine &searched_medicine) const{
	const auto index = medicines.find(searched_medicine);
	if (index == -1) {
		throw RepositoryNotFoundMedicine();
	}
	return medicines.get_elem(index);
}

const LinkedList <Medicine>& Repository::get_all() const{
	return medicines;
}


FileRepository::FileRepository(const string &_file_name) noexcept{
	file_name = _file_name;
	load_from_file();
}

void FileRepository::save_to_file() const{
	std::ofstream fout(file_name);
	for(const auto &medicine : get_all()){
		fout << medicine.get_name() << ',' << medicine.get_type() << ',' << medicine.get_price() << ',' << medicine.get_manufacturer() << '\n';
	}
}

void FileRepository::load_from_file(){
	std::ifstream fin(file_name);
	string line;
	while(fin >> line){
		vector <string> attrs = my_split(line, ",");
		Repository::add(Medicine(attrs.at(0), attrs.at(1), std::stoi(attrs.at(2)), attrs.at(3)));
	}
}

void FileRepository::add(const Medicine &medicine){
	Repository::add(medicine);
	save_to_file();
}

void FileRepository::remove(const string &name){
	Repository::remove(name);
	save_to_file();
}

void FileRepository::modify(const string &name, const Medicine &new_medicine){
	Repository::modify(name, new_medicine);
	save_to_file();
}

ProbabilisticRepo::ProbabilisticRepo(const double &_probability) noexcept {
	probability = _probability;
}

void ProbabilisticRepo::add(const Medicine &medicine) {
	std::mt19937 seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	if (generator(seed) <= probability) {
		throw RandomRepositoryError();
	}
	Repository::add(medicine);
	if (is_duplicate(medicine)) {
		throw RepositoryDuplicateMedicine();
	}
	medicines_mp[medicine.get_name()] = medicine;
}

void ProbabilisticRepo::remove(const string &name) {
	std::mt19937 seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	if (generator(seed) <= probability) {
		throw RandomRepositoryError();
	}
	Repository::remove(name);
	if (!is_duplicate(name)) {
		throw RepositoryNotFoundMedicine();
	}
	medicines_mp.erase(name);
}

void ProbabilisticRepo::modify(const string &name, const Medicine &new_medicine) {
	std::mt19937 seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	if (generator(seed) <= probability) {
		throw RandomRepositoryError();
	}
	Repository::modify(name, new_medicine);
	if (!is_duplicate(name)) {
		throw RepositoryNotFoundMedicine();
	}
	medicines_mp[name] = new_medicine;
}


bool ProbabilisticRepo::is_duplicate(const Medicine &medicine) const {
	try {
		find(medicine);
		return true;
	}
	catch (std::exception&) {}
	return false;
}

bool ProbabilisticRepo::is_duplicate(const string &name) const {
	return is_duplicate(Medicine(name));
}

const Medicine& ProbabilisticRepo::find(const string &name) const {
	const Medicine searched_medicine(name);
	return find(searched_medicine);
}

const Medicine& ProbabilisticRepo::find(const Medicine &searched_medicine) const {
	if (medicines_mp.find(searched_medicine.get_name()) == medicines_mp.end()) {
		throw RepositoryNotFoundMedicine();
	}
	string name = searched_medicine.get_name();
	return medicines_mp.at(name);
}

const LinkedList <Medicine> &ProbabilisticRepo::get_all() const{
	std::mt19937 seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	if (generator(seed) <= probability) {
		std::cout << "Get all a crapat";
		//throw RandomRepositoryError();
	}
	return Repository::get_all();
}