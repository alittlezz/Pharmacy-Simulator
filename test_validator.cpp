#include "test_validator.h"

#include <assert.h>
#include "Validator.h"
#include "Medicine.h"

static void test_validate_medicine() {
	const Validator validator;
	validator.validate_medicine(Medicine("nume1", "a", 10, "B"));
	validator.validate_medicine(Medicine("nume1", "avsd", 1, "vrB"));
	validator.validate_medicine(Medicine("nume1", "ad", 1000, "vfB"));
	validator.validate_medicine(Medicine("nume1", "agf sdfd", 100, "B32  1"));

	try {
		validator.validate_medicine(Medicine("nume1", "agf sdfd", 100, ""));
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	try {
		validator.validate_medicine(Medicine("nume1", "", 100, "asdas"));
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}

	try {
		validator.validate_medicine(Medicine("", "", -5, ""));
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}
}

static void test_validate_name() {
	const Validator validator;
	validator.validate_name("ion");
	validator.validate_name("ion vasile");
	validator.validate_name("ion3 vasile2");

	try {
		validator.validate_name("");
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}
}

static void test_validate_type() {
	const Validator validator;
	validator.validate_type("ion");
	validator.validate_type("ion vasile");
	validator.validate_type("ion3 vasile2");

	try {
		validator.validate_type("");
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}
}

static void test_validate_manufacturer() {
	const Validator validator;
	validator.validate_manufacturer("ion");
	validator.validate_manufacturer("ion vasile");
	validator.validate_manufacturer("ion3 vasile2");

	try {
		validator.validate_manufacturer("");
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}
}

static void test_validate_price() {
	const Validator validator;
	validator.validate_price(3);
	validator.validate_price(1);
	validator.validate_price(300);

	try {
		validator.validate_price(0);
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}

	try {
		validator.validate_price(-5);
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}

	try {
		validator.validate_price(-300);
		assert(false);
	}
	catch (std::exception &) {
		assert(true);
	}
}

void test_validator() {
	test_validate_medicine();
	test_validate_name();
	test_validate_type();
	test_validate_price();
	test_validate_manufacturer();
}