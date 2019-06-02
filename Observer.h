#pragma once

#include <vector>
#include <memory>
#include "LinkedList.h"
#include "Medicine.h"

class ObserverCart{
private:
public:
	virtual void update(const LinkedList <Medicine> &medicines) = 0;
};

class ObservableCart{
private:
	std::vector <ObserverCart*> observers;
public:
	void addObserver(ObserverCart* obs) {
		observers.push_back(obs);
	}
protected:
	void notify(const LinkedList <Medicine> &medicines) {
		for (auto &obs : observers) {
			obs->update(medicines);
		}
	}
};

