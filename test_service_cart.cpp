#include "test_service_cart.h"
#include "ServiceCart.h"
#include "assert.h"

static void test_add() {
	ServiceCart service("test_cart.csv");
	service.add(Medicine("med1"));
	assert(service.get_all().get_size() == 1);
	assert(service.get_all().get_elem(0) == Medicine("med1"));
	service.add(Medicine("med2"));
	assert(service.get_all().get_size() == 2);
	assert(service.get_all().get_elem(1) == Medicine("med2"));
	service.add(Medicine("med3"));
	assert(service.get_all().get_size() == 3);
	assert(service.get_all().get_elem(2) == Medicine("med3"));
}

static void test_get_total() {
	ServiceCart service("test_cart.csv");
	service.add(Medicine("med1", "tip1", 20));
	assert(service.get_total() == 20);
	service.add(Medicine("med2", "tip2", 40));
	assert(service.get_total() == 60);
	service.add(Medicine("med3", "tip3", 70));
	assert(service.get_total() == 130);
}

static void test_populate() {
	ServiceCart service("test_cart.csv");
	LinkedList <Medicine> lst;
	lst.append(Medicine("med1"));
	lst.append(Medicine("med2"));
	lst.append(Medicine("med3"));
	service.populate(lst);
	assert(service.get_all().get_size() == 3);
	service.save_to_file();
	service.load_from_file();
}

void test_service_cart() {
	test_add();
	test_get_total();
	test_populate();
}
