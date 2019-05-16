#pragma once

#include "Medicine.h"

class Validator{
public:
	Validator() noexcept {};

	void validate_medicine(const Medicine &medicine) const;
	void validate_name(const string &name) const;
	void validate_type(const string &type) const;
	void validate_price(const double &price) const;
	void validate_manufacturer(const string &manufacturer) const;

	~Validator() = default;
};

