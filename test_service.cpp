#include "test_service.h"

#include "Service.h"

#include <assert.h>

static void test_find(const Service &service) {

	service.find("nume1");
	try {
		service.find("nume");
		service.find("nume2");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
}

static void test_add() {
	Service service(make_shared<Repository>());
	assert(service.get_all().get_size() == 0);
	service.add("nume1", "a", 10, "A");
	test_find(service);
	assert(service.get_all().get_size() == 1);
	service.add("nume2", "a", 10, "A");
	assert(service.get_all().get_size() == 2);
	try {
		service.add("nume2", "a", 10, "A");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(service.get_all().get_size() == 2);
	const LinkedList <Medicine> &lst = service.get_n_random(10);
	assert(lst.get_size() == 10);
}

static void test_remove() {
	Service service(make_shared<Repository>());
	service.add("nume1", "a", 10, "A");
	service.add("nume2", "a", 10, "A");
	service.add("nume3", "a", 10, "A");
	service.remove("nume2");
	assert(service.get_all().get_size() == 2);
	service.remove("nume1");
	assert(service.get_all().get_size() == 1);
	try {
		service.remove("nume1");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(service.get_all().get_size() == 1);
	try{
		service.find("nume1");
		service.find("nume2");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	service.find("nume3");
}

static void test_modify() {
	Service service(make_shared<Repository>());
	service.add("nume1", "a", 10, "A");
	service.add("nume2", "a", 10, "A");
	service.add("nume3", "a", 10, "A");
	service.modify("nume1", "nume4", "a", 10, "A");
	try {
		service.find("nume1");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	service.find("nume4");
	assert(service.get_all().get_size() == 3);
	try {
		service.remove("nume1");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(service.get_all().get_size() == 3);
	service.remove("nume4");
	assert(service.get_all().get_size() == 2);
	try {
		service.remove("nume4");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
}

static void test_sort() {
	Service service(make_shared<Repository>());
	service.add("nume1", "tip4", 30, "prod3");
	service.add("nume2", "tip3", 20, "prod4");
	service.add("nume3", "tip1", 40, "prod5");
	service.add("nume4", "tip5", 10, "prod2");
	service.add("nume5", "tip2", 50, "prod1");
	LinkedList <Medicine> medicines = service.get_sorted("nume");
	for (int i = 0; i < 5; i++) {
		assert(medicines.get_elem(i).get_name() == "nume" + std::to_string(i + 1));
	}
	medicines = service.get_sorted("tip");
	for (int i = 0; i < 5; i++) {
		assert(medicines.get_elem(i).get_type() == "tip" + std::to_string(i + 1));
	}
	medicines = service.get_sorted("pret");
	for (int i = 0; i < 5; i++) {
		assert(medicines.get_elem(i).get_price() == ((double)i + 1) * 10);
	}
	medicines = service.get_sorted("producator");
	for (int i = 0; i < 5; i++) {
		assert(medicines.get_elem(i).get_manufacturer() == "prod" + std::to_string(i + 1));
	}
	try {
		medicines = service.get_sorted("random");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
}

static void test_filter() {
	Service service(make_shared<Repository>());
	service.add("nume1", "tip1", 10, "prod1");
	service.add("nume2", "tip1", 11, "prod1");
	service.add("nume3", "tip2", 12, "prod3");
	service.add("nume4", "tip2", 13, "prod3");
	service.add("nume5", "tip2", 13, "prod3");
	LinkedList <Medicine> medicines = service.get_filtered_by_type("tip1");
	assert(medicines.get_size() == 2);
	assert(medicines.get_elem(0) == "nume1");
	assert(medicines.get_elem(1) == "nume2");
	medicines = service.get_filtered_by_type("tip2");
	assert(medicines.get_size() == 3);
	assert(medicines.get_elem(0) == "nume3");
	assert(medicines.get_elem(1) == "nume4");
	assert(medicines.get_elem(2) == "nume5");
	medicines = service.get_filtered_by_price(12);
	assert(medicines.get_size() == 3);
	assert(medicines.get_elem(0) == "nume1");
	assert(medicines.get_elem(1) == "nume2");
	assert(medicines.get_elem(2) == "nume3");
	medicines = service.get_filtered_by_price(15);
	assert(medicines.get_size() == 5);
	assert(medicines.get_elem(0) == "nume1");
	assert(medicines.get_elem(1) == "nume2");
	assert(medicines.get_elem(2) == "nume3");
	assert(medicines.get_elem(3) == "nume4");
	assert(medicines.get_elem(4) == "nume5");
	medicines = service.get_filtered_by_manufacturer("prod3");
	assert(medicines.get_size() == 3);
	assert(medicines.get_elem(0) == "nume3");
	assert(medicines.get_elem(1) == "nume4");
	assert(medicines.get_elem(2) == "nume5");
	medicines = service.get_filtered_by_manufacturer("prod2");
	assert(medicines.get_size() == 0);
}

static void test_get_types(){
	Service service(make_shared<Repository>());
	service.add("nume1", "tip1", 5, "prod1");
	service.add("nume2", "tip1", 5, "prod1");
	service.add("nume3", "tip2", 5, "prod1");
	service.add("nume4", "tip3", 5, "prod1");
	service.add("nume5", "tip3", 5, "prod1");
	service.add("nume6", "tip3", 5, "prod1");
	const LinkedList <DTOMedicine> &medicines = service.get_types();
	assert(medicines.get_size() == 3);
	assert(medicines.get_elem(0).get_ap() == 2);
	assert(medicines.get_elem(1).get_ap() == 1);
	assert(medicines.get_elem(2).get_ap() == 3);
}

static void test_undo(){
	Service service(make_shared<Repository>());
	service.add("nume1", "tip1", 5, "prod1");
	service.add("nume2", "tip1", 5, "prod1");
	service.add("nume3", "tip2", 5, "prod1");
	service.undo();
	assert(service.get_all().get_size() == 2);
	service.undo();
	assert(service.get_all().get_size() == 1);
	service.undo();
	assert(service.get_all().get_size() == 0);
	try {
		service.undo();
		assert(false);
	}catch(std::exception&){
		assert(true);
	}
	assert(service.get_all().get_size() == 0);
}

void test_service() {
	test_add();
	test_remove();
	test_modify();
	test_sort();
	test_filter();
	test_get_types();
	test_undo();
}