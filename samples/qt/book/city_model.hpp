#ifndef CITY_MODEL_HPP
#define CITY_MODEL_HPP

#include <algorithm>
#include <vector>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

class city_model : public abstract_table_model
{
	QStringList cities;
	vector <int> distances;

public:
	city_model(QObject *parent = 0) : abstract_table_model(parent) { }

	void set_cities(const QStringList &cities)
	{
		this->cities = cities;
		distances.resize(cities.count() * (cities.count() - 1) / 2, 0);
		reset();
	}

	int rowCount   (const QModelIndex&) const { return cities.count(); }
	int columnCount(const QModelIndex&) const { return cities.count(); }

//-----------------------------------------------------------------------------

	QVariant data(const QModelIndex& index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		if (role == Qt::TextAlignmentRole)
			return int(Qt::AlignRight | Qt::AlignVCenter);
		else if (role == Qt::DisplayRole)
		{
			int row = index.row(), col = index.column();
			if (row == col)
				return 0;
			return distances[offset_of(row, col)];
		}
		return QVariant();
	}

//-----------------------------------------------------------------------------

	bool setData(const QModelIndex& index, const QVariant& value, int role)
	{
		if (index.isValid() && index.row() != index.column()
				&& role == Qt::EditRole)
		{
			int offset = offset_of(index.row(), index.column());
			distances[offset] = value.toInt();

			QModelIndex transpose = createIndex(index.column(), index.row());
			emit dataChanged(index, index);
			emit dataChanged(transpose, transpose);
			return true;
		}
		return false;
	}

//-----------------------------------------------------------------------------

	QVariant headerData(int section, Qt::Orientation, int role) const
	{
		if (role == Qt::DisplayRole)
			return cities[section];
		return QVariant();
	}

//-----------------------------------------------------------------------------

	Qt::ItemFlags flags(const QModelIndex& index) const
	{
		Qt::ItemFlags flags = QAbstractItemModel::flags(index);
		if (index.row() != index.column())
			flags |= Qt::ItemIsEditable;
		return flags;
	}

private:

//-----------------------------------------------------------------------------

	int offset_of(int row, int column) const
	{
		if (row < column)
			std::swap(row, column);
		return (row * (row - 1) / 2) + column;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CITY_MODEL_HPP
