#pragma once

#include "Medicine.h"

#include "LinkedList.h"
#include "exceptions.h"
#include <fstream>
#include <map>
#include <chrono>
#include <random>

class Repository{
private:
	LinkedList <Medicine> medicines;
public:
	Repository() noexcept;

	/// <summary>
	/// Adds a new medicine to the repository
	/// </summary>
	/// <param name="medicine">Medicine to be added</param>
	virtual void add(const Medicine &medicine);
	/// <summary>
	/// Removes medicine with a given name from repository
	/// </summary>
	/// <param name="name"></param>
	virtual void remove(const string &name);
	/// <summary>
	/// Modifies medicine with a given name to a new one
	/// </summary>
	/// <param name="name"></param>
	/// <param name="new_medicine"></param>
	virtual void modify(const string &name, const Medicine &new_medicine);
	/// <summary>
	/// Finds medicine that is equal to a another given one
	/// </summary>
	/// <param name="medicine"></param>
	/// <returns></returns>
	virtual const Medicine& find(const Medicine &medicine) const;
	/// <summary>
	/// Finds medicine with a given name
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	virtual const Medicine& find(const string &name) const;
	/// <summary>
	/// Gets all the medicines from repository
	/// </summary>
	/// <returns></returns>
	virtual const LinkedList <Medicine>& get_all() const;

	/// <summary>
	/// Checks if medicine already exists
	/// </summary>
	/// <param name="medicine">Medicine to be searched</param>
	/// <returns>True if medicine is in repo, False otherwise</returns>
	virtual bool is_duplicate(const Medicine &medicine) const;
	/// <summary>
	/// Checks if medicine with given name already exists
	/// </summary>
	/// <param name="name">Name of the medicine</param>
	/// <returns>True if medicine is in repo, False otherwise</returns>
	virtual bool is_duplicate(const string &name) const;

	Repository(const Repository&) = default;
	Repository(Repository&&) = default;
	Repository& operator=(const Repository&) = default;
	Repository& operator=(Repository &&) = default;

	~Repository() = default;
};

class FileRepository : public Repository{
private:
	string file_name;
	void save_to_file() const;
	void load_from_file();
public:
	FileRepository(const string &_file_name) noexcept;
	/// <summary>
	/// Adds a new medicine to the repository
	/// </summary>
	/// <param name="medicine">Medicine to be added</param>
	void add(const Medicine &medicine) override;
	/// <summary>
	/// Removes medicine with a given name from repository
	/// </summary>
	/// <param name="name"></param>
	void remove(const string &name) override;
	/// <summary>
	/// Modifies medicine with a given name to a new one
	/// </summary>
	/// <param name="name"></param>
	/// <param name="new_medicine"></param>
	void modify(const string &name, const Medicine &new_medicine) override;

	FileRepository(const FileRepository&) = default;
	FileRepository(FileRepository&&) = default;
	FileRepository& operator=(const FileRepository&) = default;
	FileRepository& operator=(FileRepository &&) = default;

	~FileRepository() = default;
};

class ProbabilisticRepo : public Repository{
private:
	std::map <string, Medicine> medicines_mp;
	double probability;
	std::uniform_real_distribution <double> generator{0, 1};
public:
	ProbabilisticRepo(const double &_probability) noexcept;

	/// <summary>
	/// Adds a new medicine to the repository
	/// </summary>
	/// <param name="medicine">Medicine to be added</param>
	void add(const Medicine &medicine);
	/// <summary>
	/// Removes medicine with a given name from repository
	/// </summary>
	/// <param name="name"></param>
	void remove(const string &name);
	/// <summary>
	/// Modifies medicine with a given name to a new one
	/// </summary>
	/// <param name="name"></param>
	/// <param name="new_medicine"></param>
	void modify(const string &name, const Medicine &new_medicine);
	/// <summary>
	/// Finds medicine that is equal to a another given one
	/// </summary>
	/// <param name="medicine"></param>
	/// <returns></returns>
	const Medicine& find(const Medicine &medicine) const;
	/// <summary>
	/// Finds medicine with a given name
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const Medicine& find(const string &name) const;
	/// <summary>
	/// Gets all the medicines from repository
	/// </summary>
	/// <returns></returns>
	const LinkedList <Medicine>& get_all() const;

	/// <summary>
	/// Checks if medicine already exists
	/// </summary>
	/// <param name="medicine">Medicine to be searched</param>
	/// <returns>True if medicine is in repo, False otherwise</returns>
	bool is_duplicate(const Medicine &medicine) const;
	/// <summary>
	/// Checks if medicine with given name already exists
	/// </summary>
	/// <param name="name">Name of the medicine</param>
	/// <returns>True if medicine is in repo, False otherwise</returns>
	bool is_duplicate(const string &name) const;
};

