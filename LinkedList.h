#pragma once

#include <iostream>
#include <functional>
#include <algorithm>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::make_unique;
using std::weak_ptr;
using std::shared_ptr;
using std::make_shared;

template <class TElem>
class IteratorLinkedList;

template <class TElem>
class Node {
public:
	Node(const TElem &_value = 0) noexcept: value(_value){}
	TElem value;
	shared_ptr <Node> next;
	weak_ptr <Node> prev;
};

template <class TElem>
class LinkedList {
private:
	shared_ptr <Node<TElem>> head;
public:
	LinkedList() noexcept;
	LinkedList(const LinkedList &ot) = default;
	LinkedList(LinkedList&& ot) = default;
	~LinkedList() = default;

	LinkedList& operator=(const LinkedList &ot) = default;
	LinkedList& operator=(LinkedList&& ot) = default;

	void append(const TElem &x);
	void remove(const int &idx) noexcept;
	void replace(const int &idx, const TElem &x);
	int find(const TElem &x) const noexcept;
	void print() const;
	TElem get_first() const;
	TElem get_last() const;
	const TElem &get_elem(const int &idx) const noexcept;
	int get_size() const noexcept;

	void sort(std::function <bool(const TElem &x, const TElem &y)> cmp);
	LinkedList filter(std::function <bool(const TElem &x)> crit) const;

	friend class IteratorLinkedList<TElem>;
	IteratorLinkedList<TElem> begin() const noexcept;
	IteratorLinkedList<TElem> end() const noexcept;
};

template <class TElem>
LinkedList<TElem>::LinkedList() noexcept{}

template <class TElem>
void LinkedList<TElem>::append(const TElem &x) {
	shared_ptr <Node<TElem>> node = make_shared<Node<TElem>>(x);
	if (!head) {
		head = node;
		return;
	}
	auto cr = head;
	while (cr->next) {
		cr = cr->next;
	}
	node->prev = cr;
	cr->next = node;
}

template <class TElem>
void LinkedList<TElem>::remove(const int &idx) noexcept{
	if (!head) {
		return;
	}
	auto cr = head;
	for (int i = 0; i < idx; i++) {
		cr = cr->next;
	}
	auto prv = cr->prev;
	auto nxt = cr->next;
	if (nxt)
		nxt->prev = prv;
	if (prv.lock())
		prv.lock()->next = nxt;
	else
		head = nxt;
}

template <class TElem>
void LinkedList<TElem>::replace(const int &idx, const TElem &x) {
	auto cr = head;
	for (int i = 0; i < idx; i++) {
		cr = cr->next;
	}
	cr->value = x;
}

template <class TElem>
int LinkedList<TElem>::find(const TElem &x) const noexcept{
	auto cr = head;
	int ret = 0;
	while(cr) {
		if (cr->value == x) {
			return ret;
		}
		ret++;
		cr = cr->next;
	}
	return -1;
}

template <class TElem>
TElem LinkedList<TElem>::get_first() const {
	return head->value;
}

template <class TElem>
TElem LinkedList<TElem>::get_last() const {
	auto cr = head;
	while (cr->next != nullptr) {
		cr = cr->next;
	}
	return cr->value;
}

template <class TElem>
const TElem& LinkedList<TElem>::get_elem(const int &idx) const noexcept{
	auto cr = head;
	for(int i = 0;i < idx;i++){
		cr = cr->next;
	}
	return cr->value;
}

template <class TElem>
void LinkedList<TElem>::print() const {
	for (IteratorLinkedList <TElem> it = begin(); it != end(); it.next()) {
		std::cout << it.element() << ' ';
	}
	std::cout << '\n';
}

template <class TElem>
int LinkedList<TElem>::get_size() const noexcept {
	int id = 0;
	auto cr = head;
	while (cr != nullptr) {
		cr = cr->next;
		id++;
	}
	return id;
}

template<class TElem>
IteratorLinkedList<TElem> LinkedList<TElem>::begin() const noexcept {
	return IteratorLinkedList<TElem>(*this, 0);
}

template<class TElem>
IteratorLinkedList<TElem> LinkedList<TElem>::end() const noexcept {
	return IteratorLinkedList<TElem>(*this, get_size());
}

template <class TElem>
void LinkedList<TElem>::sort(std::function <bool(const TElem &x, const TElem &y)> cmp) {
	std::vector <TElem> v;
	auto cr = head;
	while (cr != nullptr) {
		v.push_back(cr->value);
		cr = cr->next;
	}
	std::sort(v.begin(), v.end(), cmp);
	for (size_t i = 0; i < v.size(); i++) {
		remove(0);
	}
	for (auto &it : v) {
		append(it);
	}
}

template <class TElem>
LinkedList <TElem> LinkedList<TElem>::filter(std::function <bool(const TElem &x)> crit) const {
	LinkedList <TElem> result;
	for (auto it = begin(); it != end(); ++it) {
		if (crit(*it)) {
			result.append(*it);
		}
	}
	return result;
}

template<class TElem>
class IteratorLinkedList {
private:
	const LinkedList<TElem>& v;
	shared_ptr<Node<TElem>> it;
	int poz;
public:
	IteratorLinkedList(const LinkedList<TElem>& v) noexcept;
	IteratorLinkedList(const LinkedList<TElem>& v, int pos)noexcept;
	bool valid()const;
	TElem& element() const noexcept;
	int position() const;
	void next() noexcept;
	TElem& operator*() noexcept;
	IteratorLinkedList& operator++() noexcept;
	IteratorLinkedList operator++(int) noexcept;
	bool operator==(const IteratorLinkedList& ot)noexcept;
	bool operator!=(const IteratorLinkedList& ot)noexcept;
};

template<class TElem>
IteratorLinkedList<TElem>::IteratorLinkedList(const LinkedList<TElem>& v) noexcept :v{ v }{}

template<class TElem>
IteratorLinkedList<TElem>::IteratorLinkedList(const LinkedList<TElem>& v, int pos)noexcept : v{ v }{
	int id = 0;
	auto cr = v.head;
	while (cr != nullptr && id != pos) {
		cr = cr->next;
		id++;
	}
	it = cr;
	poz = id;
}

template<class TElem>
bool IteratorLinkedList<TElem>::valid()const {
	return it != nullptr;
}

template<class TElem>
TElem& IteratorLinkedList<TElem>::element() const noexcept{
	return it->value;
}

template <class TElem>
int IteratorLinkedList<TElem>::position() const {
	return poz;
}

template<class TElem>
void IteratorLinkedList<TElem>::next() noexcept {
	poz++;
	it = it->next;
}

template<class TElem>
TElem& IteratorLinkedList<TElem>::operator*() noexcept{
	return element();
}

template<class TElem>
IteratorLinkedList<TElem>& IteratorLinkedList<TElem>::operator++() noexcept {
	next();
	return *this;
}

template <class TElem>
IteratorLinkedList<TElem> IteratorLinkedList<TElem>::operator++(int) noexcept {
	IteratorLinkedList cpy(*this);
	cpy.next();
	return cpy;
}

template<class TElem>
bool IteratorLinkedList<TElem>::operator==(const IteratorLinkedList<TElem>& ot) noexcept {
	return poz == ot.poz;
}

template<class TElem>
bool IteratorLinkedList<TElem>::operator!=(const IteratorLinkedList<TElem>& ot)noexcept {
	return !(*this == ot);
}