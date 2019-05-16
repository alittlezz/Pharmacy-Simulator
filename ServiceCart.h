#pragma once

#include "LinkedList.h"
#include "Medicine.h"
#include "Validator.h"

class ServiceCart{
private:
	LinkedList <Medicine> cart;
	Validator validator;
	string file_name;
public:
	ServiceCart() = default;
	~ServiceCart() = default;

	ServiceCart(const string &_file_name, const int &load = false){
		file_name = _file_name;
		if(load)
			load_from_file();
	}

	ServiceCart(const ServiceCart&) = default;
	ServiceCart(ServiceCart&&) = default;
	ServiceCart& operator=(const ServiceCart&) = default;
	ServiceCart& operator=(ServiceCart &&) = default;

	/// <summary>
	/// Adds a new medicine to the cart
	/// </summary>
	/// <param name="medicine">Medicine to be added</param>
	void add(const Medicine &medicine);
	/// <summary>
	/// Empty the cart
	/// </summary>
	void empty() noexcept;
	/// <summary>
	/// Populate the cart with the given medicines
	/// </summary>
	/// <param name="medicines">List of medicines to populate the cart</param>
	void populate(const LinkedList <Medicine> &medicines);

	/// <summary>
	/// Gets all medicines from cart
	/// </summary>
	/// <returns>List of all medicines from cart</returns>
	const LinkedList<Medicine>& get_all() const noexcept;
	/// <summary>
	/// Gets total price of medicines from cart
	/// </summary>
	/// <returns>Sum of prices of medicines from cart</returns>
	double get_total() const noexcept;
	/// <summary>
	/// Saves cart to file
	/// </summary>
	void save_to_file() const;
	/// <summary>
	/// Load cart from file
	/// </summary>
	void load_from_file();
};

