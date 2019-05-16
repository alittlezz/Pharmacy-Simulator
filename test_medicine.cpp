#include "test_medicine.h"

#include "Medicine.h"
#include <assert.h>


void test_getters() {
	Medicine medicine("nume1", "tip1", 10, "prod1");
	assert(medicine.get_name() == "nume1");
	assert(medicine.get_type() == "tip1");
	assert(medicine.get_price() == 10);
	assert(medicine.get_manufacturer() == "prod1");
}

void test_setters() {
	Medicine medicine("nume1", "tip1", 10, "prod1");
	medicine.set_name("nume2");
	medicine.set_type("tip2");
	medicine.set_price(20);
	medicine.set_manufacturer("prod2");
	assert(medicine.get_name() == "nume2");
	assert(medicine.get_type() == "tip2");
	assert(medicine.get_price() == 20);
	assert(medicine.get_manufacturer() == "prod2");
}

void test_operators() {
	Medicine medicine("nume1", "tip1", 10, "prod1");
	Medicine medicine_same("nume1", "tip2", 40, "prod3");
	assert(medicine == medicine_same);
	Medicine medicine_diff("nume2", "tip1", 10, "prod1");
	assert(medicine != medicine_diff);
	assert(medicine == "nume1");
	assert(medicine_diff == "nume2");
	assert(medicine != "nume2");
}

void test_DTO(){
	DTOMedicine medicine("nume1", 0, "tip1");
	medicine.set_ap(3);
	assert(medicine.get_ap() == 3);
	medicine.add_ap();
	assert(medicine.get_ap() == 4);
}

void test_medicine() {
	test_getters();
	test_setters();
	test_operators();
	test_DTO();
}