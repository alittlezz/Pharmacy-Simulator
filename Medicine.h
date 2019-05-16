#pragma once

#include <string>
using std::string;

class Medicine{
private:
	string name;
	string type;
	double price = 0;
	string manufacturer;
public:
	Medicine() = default;
	Medicine(const string &_name, const string &_type = "None", const double &_price = 0, const string &_manufacturer = "None");
	Medicine(const Medicine &medicine);

	Medicine(Medicine&&) = default;
	Medicine& operator=(const Medicine&) = default;
	Medicine& operator=(Medicine &&) = default;

	const string& get_name() const noexcept;
	const string& get_type() const noexcept;
	const double& get_price() const noexcept;
	const string& get_manufacturer() const noexcept;
	string get_text() const noexcept;

	void set_name(const string &_name);
	void set_type(const string &_type);
	void set_price(const double &_price) noexcept;
	void set_manufacturer(const string &_manufacturer);

	bool operator ==(const Medicine &other) const noexcept{
		return name == other.get_name();
	}

	bool operator !=(const Medicine &other) const noexcept {
		return name != other.get_name();
	}

	bool operator ==(const string &_name) const noexcept {
		return name == _name;
	}

	bool operator !=(const string &_name) const noexcept {
		return name != _name;
	}

	~Medicine() = default;
};

class DTOMedicine: public Medicine{
private:
	int ap;
public:
	DTOMedicine(const string &_name, const int &_ap = 0, const string &_type = "None", const double &_price = 0, const string &_manufacturer = "None");
	void add_ap() noexcept;

	void set_ap(const int &_ap) noexcept;
	const int& get_ap() const noexcept;
};