#include <ivl/ivl>
#include <ivl/qt>
#include "coordinate_setter.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	vector <QPointF> coordinates;
	coordinates.push_back(QPointF(0.0, 0.9));
	coordinates.push_back(QPointF(0.2, 11.0));
	coordinates.push_back(QPointF(0.4, 15.4));
	coordinates.push_back(QPointF(0.6, 12.9));
	coordinates.push_back(QPointF(0.8, 8.5));
	coordinates.push_back(QPointF(1.0, 7.1));
	coordinates.push_back(QPointF(1.2, 4.0));
	coordinates.push_back(QPointF(1.4, 13.6));
	coordinates.push_back(QPointF(1.6, 22.2));
	coordinates.push_back(QPointF(1.8, 22.2));

	coordinate_setter setter(&coordinates);
	setter.show();
	return app.exec();
}
