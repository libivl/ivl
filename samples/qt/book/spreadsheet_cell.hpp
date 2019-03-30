#ifndef SPREADSHEET_CELL_HPP
#define SPREADSHEET_CELL_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

const QVariant Invalid;

//-----------------------------------------------------------------------------

class spreadsheet_cell : public QTableWidgetItem
{
	mutable QVariant cached_value;
	mutable bool cache_is_dirty;

public:

	spreadsheet_cell() { set_dirty(); }
	QTableWidgetItem* clone() const { return new spreadsheet_cell(*this); }

	void set_dirty() { cache_is_dirty = true; }
	void set_formula(const QString &formula) { setData(Qt::EditRole, formula); }
	QString formula() const { return data(Qt::EditRole).toString(); }

//-----------------------------------------------------------------------------

	void setData(int role, const QVariant &value)
	{
		QTableWidgetItem::setData(role, value);
		if (role == Qt::EditRole)
			set_dirty();
	}

//-----------------------------------------------------------------------------

	QVariant data(int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (value().isValid())
				return value().toString();
			else
				return "####";
		}
		else if (role == Qt::TextAlignmentRole)
		{
			return value().type() == QVariant::String ?
				int(Qt::AlignLeft | Qt::AlignVCenter) :
				int(Qt::AlignRight | Qt::AlignVCenter);
		}
		else
			return QTableWidgetItem::data(role);
	}

private:

//-----------------------------------------------------------------------------

	QVariant value() const
	{
		if (cache_is_dirty)
		{
			cache_is_dirty = false;

			QString formula_str = formula();
			if (formula_str.startsWith('\''))
				cached_value = formula_str.mid(1);
			else if (formula_str.startsWith('='))
			{
				cached_value = Invalid;
				QString expr = formula_str.mid(1);
				expr.replace(" ", "");
				expr.append(QChar::Null);
				int pos = 0;
				cached_value = eval_expression(expr, pos);
				if (expr[pos] != QChar::Null)
					cached_value = Invalid;
			}
			else
			{
				bool ok;
				double d = formula_str.toDouble(&ok);
				if (ok)
					cached_value = d;
				else
					cached_value = formula_str;
			}
		}
		return cached_value;
	}

//-----------------------------------------------------------------------------

	QVariant eval_expression(const QString &str, int &pos) const
	{
		QVariant result = eval_term(str, pos);
		while (str[pos] != QChar::Null)
		{
			QChar op = str[pos];
			if (op != '+' && op != '-')
				return result;
			++pos;

			QVariant term = eval_term(str, pos);
			if (result.type() == QVariant::Double
				&& term.type() == QVariant::Double)
				result = op == '+' ? result.toDouble() + term.toDouble() :
				                     result.toDouble() - term.toDouble();
			else
				result = Invalid;
		}
		return result;
	}

//-----------------------------------------------------------------------------

	QVariant eval_term(const QString &str, int &pos) const
	{
		QVariant result = eval_factor(str, pos);
		while (str[pos] != QChar::Null)
		{
			QChar op = str[pos];
			if (op != '*' && op != '/')
				return result;
			++pos;

			QVariant factor = eval_factor(str, pos);
			if (result.type() == QVariant::Double
						&& factor.type() == QVariant::Double)
			{
				if (op == '*')
					result = result.toDouble() * factor.toDouble();
				else
				{
					if (factor.toDouble() == 0.0)
						result = Invalid;
					else
						result = result.toDouble() / factor.toDouble();
				}
			}
			else
				result = Invalid;
		}
		return result;
	}

//-----------------------------------------------------------------------------

	QVariant eval_factor(const QString &str, int &pos) const
	{
		QVariant result;
		bool negative = false;

		if (str[pos] == '-')
		{
			negative = true;
			++pos;
		}

		if (str[pos] == '(')
		{
			++pos;
			result = eval_expression(str, pos);
			if (str[pos] != ')')
				result = Invalid;
			++pos;
		}
		else
		{
			QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
			QString token;

			while (str[pos].isLetterOrNumber() || str[pos] == '.')
			{
				token += str[pos];
				++pos;
			}

			if (regExp.exactMatch(token))
			{
				int column = token[0].toUpper().unicode() - 'A';
				int row = token.mid(1).toInt() - 1;

				spreadsheet_cell *c = static_cast <spreadsheet_cell*>(
										tableWidget()->item(row, column));
				if (c)
					result = c->value();
				else
					result = 0.0;
			}
			else
			{
				bool ok;
				result = token.toDouble(&ok);
				if (!ok)
					result = Invalid;
			}
		}

		if (negative)
		{
			if (result.type() == QVariant::Double)
				result = -result.toDouble();
			else
				result = Invalid;
		}
		return result;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // SPREADSHEET_CELL_HPP
