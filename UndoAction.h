#pragma once

#include "Repository.h"

class UndoAction{
public:
	shared_ptr<Repository> repository;
	UndoAction() = delete;
	UndoAction(shared_ptr<Repository> _repository) noexcept
	{
		repository = move(_repository);
	};
	virtual void do_undo() noexcept;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction{
private:
	string medicine_name;
public:
	UndoAdd(shared_ptr<Repository> _repository, const string &_medicine_name) noexcept;
	void do_undo() noexcept override;
};

class UndoRemove : public UndoAction {
private:
	Medicine removed_medicine;
public:
	UndoRemove(shared_ptr<Repository> _repository, const Medicine &_removed_medicine) noexcept;
	void do_undo() noexcept override;
};

class UndoModify : public UndoAction {
private:
	Medicine old_medicine;
	string new_medicine_name;
public:
	UndoModify(shared_ptr<Repository> _repository, const Medicine &_old_medicine, const string &_new_medicine_name) noexcept;
	void do_undo() noexcept override;
};
