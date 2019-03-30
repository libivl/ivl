#include <ivl/ivl>
#include <ivl/qt>
#include "find_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	find_dialog *dialog = new find_dialog();
	dialog->show();
	return app.exec();
}
