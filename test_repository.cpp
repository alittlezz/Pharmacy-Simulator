#include "test_repository.h"

#include "Repository.h"

#include <assert.h>
#include <exception>

static void test_find(const Repository &repo) {
	assert(repo.is_duplicate("nume1") == true);
	assert(repo.is_duplicate("nume") == false);
	assert(repo.is_duplicate("nume2") == false);
}

static void test_add() {
	Repository repo;
	assert(repo.get_all().get_size() == 0);
	repo.add(Medicine("nume1"));
	test_find(repo);
	assert(repo.get_all().get_size() == 1);
	repo.add(Medicine("nume2"));
	assert(repo.get_all().get_size() == 2);
	try {
		repo.add(Medicine("nume2"));
		assert(false);
	}catch(std::exception&) {
		assert(true);
	}
	assert(repo.get_all().get_size() == 2);
}

static void test_remove() {
	Repository repo;
	repo.add(Medicine("nume1"));
	repo.add(Medicine("nume2"));
	repo.add(Medicine("nume3"));
	repo.remove("nume2");
	assert(repo.get_all().get_size() == 2);
	repo.remove("nume1");
	assert(repo.get_all().get_size() == 1);
	try {
		repo.remove("nume1");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(repo.get_all().get_size() == 1);
	assert(repo.is_duplicate("nume1") == false);
	assert(repo.is_duplicate("nume2") == false);
	assert(repo.is_duplicate("nume3") == true);
}

static void test_modify() {
	Repository repo;
	repo.add(Medicine("nume1"));
	repo.add(Medicine("nume2"));
	repo.add(Medicine("nume3"));
	repo.modify("nume1", Medicine("nume4"));
	repo.modify("nume3", Medicine("nume6"));
	assert(repo.is_duplicate("nume1") == false);
	assert(repo.is_duplicate("nume4") == true);
	assert(repo.get_all().get_size() == 3);
	try {
		repo.remove("nume1");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	try {
		repo.modify("nume1", Medicine("nume5"));
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(repo.get_all().get_size() == 3);
	repo.remove("nume4");
	assert(repo.get_all().get_size() == 2);
	assert(repo.is_duplicate("nume4") == false);
}

static void test_file_repo() {
	std::ofstream fout("test.csv");
	fout.close();
	FileRepository repo("test.csv");
	repo.add(Medicine("nume1"));
	repo.add(Medicine("nume2"));
	repo.add(Medicine("nume3"));
	assert(repo.get_all().get_size() == 3);
	repo.remove("nume1");
	assert(repo.get_all().get_size() == 2);
	repo.modify("nume2", Medicine("nume1"));
}

void test_repository() {
	test_add();
	test_remove();
	test_modify();
	test_file_repo();
}
