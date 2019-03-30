#ifndef CURRENCY_MODEL_HPP
#define CURRENCY_MODEL_HPP

#include <vector>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

class currency_model : public abstract_table_model
{
	vector <QString> symbol;
	vector <double> currency;

public:

//-----------------------------------------------------------------------------

	currency_model(QObject *parent = 0) : abstract_table_model(parent) { }

	void set_currency(const vector <QString>& symbol,
	                  const vector <double>& currency)
	{
		this->symbol = symbol;
		this->currency = currency;
		reset();
	}

	int rowCount   (const QModelIndex&) const { return currency.size(); }
	int columnCount(const QModelIndex&) const { return currency.size(); }

//-----------------------------------------------------------------------------

	QVariant data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		if (role == Qt::TextAlignmentRole)
			return int(Qt::AlignRight | Qt::AlignVCenter);
		else if (role == Qt::DisplayRole)
		{
			int row = index.row(), col = index.column();

			if (currency[row] == 0.0)
				return "####";

			double amount = currency[col] / currency[row];
			return QString("%1").arg(amount, 0, 'f', 4);
		}

		return QVariant();
	}

//-----------------------------------------------------------------------------

	QVariant headerData(int section, Qt::Orientation, int role) const
	{
		if (role != Qt::DisplayRole)
			return QVariant();
		return symbol[section];
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CURRENCY_MODEL_HPP
