#pragma once

#include <QtWidgets>
#include <vector>
#include "LinkedList.h"
#include "Medicine.h"

using std::vector;

class MyTableModel : public QAbstractTableModel
{
	Q_OBJECT
private:
	LinkedList <Medicine> medicines;
public:
	MyTableModel(QObject *parent = Q_NULLPTR);
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	void set_medicines(const LinkedList <Medicine> &_medicines);
};

