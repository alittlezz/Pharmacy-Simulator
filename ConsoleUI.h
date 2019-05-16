#pragma once

#include "Service.h"
#include "ServiceCart.h"

#include <unordered_map>
#include <functional>

class ConsoleUI{
private:
	Service service;
	ServiceCart service_cart = ServiceCart("medicines_cart.csv", true);
	LinkedList < string > commands;
	std::unordered_map < string, std::function<void()> > events;
	bool running;
	
	void handle_events();
	void populate();
	void finish() noexcept;

	void add();
	void remove();
	void modify();
	void undo();
	
	void find() const;
	void sort() const;
	void filter() const;
	void filter_by_type() const;
	void filter_by_price() const;
	void filter_by_manufacturer() const;
	void group_by_type() const;

	void add_cart();
	void empty_cart();
	void generate_cart();
	void save_to_file() const;

	void print_cart() const;
	void print_cart_total() const;
	void print_commands() const;
	void print_delimiter() const;
	void print_all() const;
	void print_medicines(const LinkedList < Medicine > &medicines) const;
	void print_medicine(const Medicine &medicine) const;
public:
	ConsoleUI(shared_ptr <Repository> _repo) noexcept { running = false; service = Service(_repo); };

	ConsoleUI(const ConsoleUI&) = default;
	ConsoleUI(ConsoleUI&&) = default;
	ConsoleUI& operator=(const ConsoleUI&) = default;
	ConsoleUI& operator=(ConsoleUI &&) = default;

	void run();

	~ConsoleUI() noexcept {};
};

