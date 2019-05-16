#pragma once

#include "Repository.h"
#include "Validator.h"
#include "UndoAction.h"
#include <vector>

using std::vector;

class Service{
private:
	shared_ptr <Repository> repository;
	Validator validator;
	vector <unique_ptr<UndoAction>> undo_actions;
public:
	Service() = default;
	Service(shared_ptr <Repository> _repository) noexcept;

	/// <summary>
	/// Adds a new medicine
	/// </summary>
	/// <param name="name">Name of the medicine</param>
	/// <param name="type">Type of the medicine</param>
	/// <param name="price">Price of the medicine</param>
	/// <param name="manufacturer">Manufacturer of the medicine</param>
	void add(const string &name, const string &type = "None", const double &price = 0, const string &manufacturer = "None");
	/// <summary>
	/// Removes a medicine with a given name
	/// </summary>
	/// <param name="name">Name of the medicine</param>
	void remove(const string &name);
	/// <summary>
	/// Modifies medicine with a given name to another one given
	/// </summary>
	/// <param name="old_name">Old name of the medicine</param>
	/// <param name="name">New name of the medicine</param>
	/// <param name="type">Type of the medicine</param>
	/// <param name="price">Price of the medicine</param>
	/// <param name="manufacturer">Manufacturer of the medicine</param>
	void modify(const string &old_name, const string &name, const string &type = "None", const double &price = 0, const string &manufacturer = "None");
	/// <summary>
	/// Undo the last operation of add/remove/modify
	/// </summary>
	void undo();
	/// <summary>
	/// Finds medicine by name
	/// </summary>
	/// <param name="name">Name of the medicine</param>
	/// <returns>Medicine found</returns>
	const Medicine& find(const string &name) const;

	/// <summary>
	/// Gets n random medicines from the repository
	/// </summary>
	/// <param name="n">Number of medicines</param>
	/// <returns>Linked list of n random medicines</returns>
	LinkedList <Medicine> get_n_random(const int &n) const;
	int get_count(const string &name) const;
	/// <summary>
	/// Gets medicines in sorted order based on comparison given
	/// </summary>
	/// <param name="sort_comparison">Function by which we sort the list</param>
	/// <returns>Sorted list</returns>
	LinkedList <Medicine> get_sorted(const string &sort_comparison) const;
	/// <summary>
	/// Gets medicines sorted by name
	/// </summary>
	/// <returns>Sorted list by name</returns>
	LinkedList <Medicine> get_sorted_by_name() const;
	/// <summary>
	/// Gets medicines sorted by type
	/// </summary>
	/// <returns>Sorted list by type</returns>
	LinkedList <Medicine> get_sorted_by_type() const;
	/// <summary>
	/// Gets medicines sorted by price
	/// </summary>
	/// <returns>Sorted list by price</returns>
	LinkedList <Medicine> get_sorted_by_price() const;
	/// <summary>
	/// Gets medicines sorted by manufacturer
	/// </summary>
	/// <returns>Sorted list by manufacturer</returns>
	LinkedList <Medicine> get_sorted_by_manufacturer() const;

	/// <summary>
	/// Gets medicines filtered by type
	/// </summary>
	/// <param name="type">Type by which we filter</param>
	/// <returns>Filtered list by type</returns>
	LinkedList <Medicine> get_filtered_by_type(const string &type) const;
	/// <summary>
	/// Gets medicines filtered by price
	/// </summary>
	/// <param name="upper_bound">Maximum price</param>
	/// <returns>Filtered list by price</returns>
	LinkedList <Medicine> get_filtered_by_price(const double &upper_bound) const;
	/// <summary>
	/// Gets medicines filtered by manufacturer
	/// </summary>
	/// <param name="manufacturer">Manufacturer by which we filter</param>
	/// <returns>Filtered list by manufacturer</returns>
	LinkedList <Medicine> get_filtered_by_manufacturer(const string &manufacturer) const;

	/// <summary>
	/// Gets all medicines
	/// </summary>
	/// <returns>List of all medicines</returns>
	const LinkedList <Medicine>& get_all() const noexcept;

	/// <summary>
	/// Groups medicines by type 
	/// </summary>
	/// <returns>List of DTOMedicines with medicine type and number of occurences</returns>
	LinkedList<DTOMedicine> get_types() const;

	Service(const Service&) = default;
	Service(Service&&) = default;
	Service& operator=(const Service&) = default;
	Service& operator=(Service &&) = default;

	~Service() = default;
};

