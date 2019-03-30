#ifndef HEX_SPIN_BOX_HPP
#define HEX_SPIN_BOX_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class hex_spin_box : public spin_box
{
	QRegExpValidator *validator;

public:

	hex_spin_box(QWidget *parent = 0) : spin_box(parent)
	{
		setRange(0, 255);
		validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,2}"), this);
	}

protected:

//-----------------------------------------------------------------------------

	QValidator::State validate(QString &text, int &pos) const
	{
		return validator->validate(text, pos);
	}

	int valueFromText(const QString &text) const
	{
		bool ok;
		return text.toInt(&ok, 16);
	}

	QString textFromValue(int value) const
	{
		return QString::number(value, 16).toUpper();
	}
};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // HEX_SPIN_BOX_HPP
