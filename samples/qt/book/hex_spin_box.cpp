#include <ivl/ivl>
#include <ivl/qt>
#include "hex_spin_box.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	hex_spin_box spin_box;
	spin_box.setWindowTitle(QObject::tr("Hex Spin Box"));
	spin_box.show();
	return app.exec();
}
