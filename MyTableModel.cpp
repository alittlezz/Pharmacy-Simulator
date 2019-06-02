#include "MyTableModel.h"

MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent)
{
	
}

int MyTableModel::rowCount(const QModelIndex &parent) const
{
	return medicines.get_size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
	return 4;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
	if(role == Qt::DisplayRole)
	{
		Medicine medicine = medicines.get_elem(index.row());
		if(index.column() == 0)
		{
			return QString::fromStdString(medicine.get_name());
		}else if(index.column() == 1)
		{
			return QString::fromStdString(medicine.get_type());
		}else if(index.column() == 2)
		{
			return QString::number(medicine.get_price());
		}
		else if (index.column() == 3)
		{
			return QString::fromStdString(medicine.get_manufacturer());
		}
	}
	return QVariant();
}

void MyTableModel::set_medicines(const LinkedList <Medicine> &_medicines)
{
	medicines = _medicines;
	auto topLeft = createIndex(0, 0);
	auto bottomR = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomR);
}