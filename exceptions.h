#pragma once

#include <exception>

class RepositoryDuplicateMedicine : public std::exception{
public:
	const char* what()const noexcept override;
};

class RepositoryNotFoundMedicine : public std::exception {
public:
	const char* what()const noexcept override;
};

class MedicineNameNotValid : public std::exception {
public:
	const char* what()const noexcept override;
};

class MedicineTypeNotValid : public std::exception {
public:
	const char* what()const noexcept override;
};

class MedicinePriceNotValid : public std::exception {
public:
	const char* what()const noexcept override;
};

class MedicineManufacturerNotValid : public std::exception {
public:
	const char* what()const noexcept override;
};

class UndoActionsEmpty : public std::exception{
public:
	const char* what()const noexcept override;
};

class RandomRepositoryError : public std::exception {
public:
	const char* what()const noexcept override;
};