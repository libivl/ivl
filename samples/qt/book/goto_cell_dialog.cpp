#include <ivl/ivl>
#include <ivl/qt>
#include "goto_cell_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	goto_cell_dialog *dialog = new goto_cell_dialog();
	dialog->show();
	return app.exec();
}
