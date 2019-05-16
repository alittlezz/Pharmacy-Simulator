#include "Pet.h"
#include "LinkedList.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include "test_medicine.h"
#include "test_repository.h"
#include "test_service.h"
#include "test_validator.h"
#include "test_service_cart.h"
#include "ConsoleUI.h"
#include "QtUI.h"

/*
Functie folosit in teste
primeste vector prin valoare -> copy constructor
returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	double totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.getPrice();
	}
	Pet p{ "total","tt",totalPrice };
	v.append(p);
	return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
	for (int i = 0; i<cate; i++) {
		Pet p{ std::to_string(i) + "_type",std::to_string(i) + "_spec",i + 10.0 };
		v.append(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addPets(v, 100);
	assert(v.get_size() == 100);
	assert(v.get_elem(50).getType() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.get_size() == 100);
	assert(v2.get_elem(50).getType() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.get_size() == 100);
	assert(v3.get_elem(50).getType() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.get_size() == 101);
	assert(v4.get_elem(50).getType() == "50_type");
}

/*
Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addPets(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.get_size() == 0);

}
template <typename MyVector>
void testAll() {
	test_medicine();
	test_repository();
	test_service();
	test_validator();
	test_service_cart();
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}

bool start_app(int argc, char **argv) {
	shared_ptr<Repository> repo = make_shared <FileRepository>("medicines.csv");
	//ConsoleUI ui(repo);
	QApplication a(argc, argv);
	QtUI ui(repo);
	ui.run();
	return a.exec();
}




int main(int argc, char **argv) {
	//testAll<LinkedList<Pet>>();
	start_app(argc, argv);
	//_CrtDumpMemoryLeaks();
	//QApplication a(argc, argv);
	return 0;
}