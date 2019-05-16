#include "exceptions.h"

const char* RepositoryDuplicateMedicine::what()const noexcept{
	return "Deja exista medicament cu acest nume";
}

const char* RepositoryNotFoundMedicine::what()const noexcept{
	return "Nu exista medicament cu acest nume";
}

const char* MedicineNameNotValid::what()const noexcept{
	return "Numele nu poate fi vid";
}

const char* MedicineTypeNotValid::what()const noexcept{
	return "Tipul nu poate fi vid";
}

const char* MedicinePriceNotValid::what()const noexcept{
	return "Pretul nu poate fi <= 0";
}

const char* MedicineManufacturerNotValid::what()const noexcept{
	return "Producatorul nu poate fi vid";
}

const char* UndoActionsEmpty::what()const noexcept {
	return "Nu mai exista operatii de undo";
}

const char* RandomRepositoryError::what()const noexcept {
	return "Probabilistic repo a crapat";
}
