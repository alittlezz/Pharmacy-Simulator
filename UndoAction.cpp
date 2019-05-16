#include "UndoAction.h"

void UndoAction::do_undo() noexcept{}

UndoAdd::UndoAdd(shared_ptr<Repository> _repository, const string &_medicine_name) noexcept : UndoAction(_repository){
	medicine_name = _medicine_name;
}

void UndoAdd::do_undo()noexcept{
	repository.get()->remove(medicine_name);
}

UndoRemove::UndoRemove(shared_ptr<Repository> _repository, const Medicine &_removed_medicine) noexcept : UndoAction(_repository) {
	removed_medicine = _removed_medicine;
}

void UndoRemove::do_undo() noexcept {
	repository.get()->add(removed_medicine);
}

UndoModify::UndoModify(shared_ptr<Repository> _repository, const Medicine &_old_medicine, const string &_new_medicine_name) noexcept : UndoAction(_repository) {
	old_medicine = _old_medicine;
	new_medicine_name = _new_medicine_name;
}

void UndoModify::do_undo() noexcept {
	repository.get()->modify(new_medicine_name, old_medicine);
}
