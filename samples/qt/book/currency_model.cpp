#include <ivl/ivl>
#include <ivl/qt>
#include "currency_model.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	vector <QString> symbol(13);
	vector <double> currency(13);
	symbol[0]  = "AUD"; currency[0]  = 1.3259;
	symbol[1]  = "CHF"; currency[1]  = 1.2970;
	symbol[2]  = "CZK"; currency[2]  = 24.510;
	symbol[3]  = "DKK"; currency[3]  = 6.2168;
	symbol[4]  = "EUR"; currency[4]  = 0.8333;
	symbol[5]  = "GBP"; currency[5]  = 0.5661;
	symbol[6]  = "HKD"; currency[6]  = 7.7562;
	symbol[7]  = "JPY"; currency[7]  = 112.92;
	symbol[8]  = "NOK"; currency[8]  = 6.5200;
	symbol[9]  = "NZD"; currency[9]  = 1.4697;
	symbol[10] = "SEK"; currency[10] = 7.8180;
	symbol[11] = "SGD"; currency[11] = 1.6901;
	symbol[12] = "USD"; currency[12] = 1.0000;

	currency_model model;
	model.set_currency(symbol, currency);

	table_view view;
	view.setModel(&model);
	view.setAlternatingRowColors(true);

	view.setWindowTitle(QObject::tr("Currencies"));
	view.show();

	return app.exec();
}
