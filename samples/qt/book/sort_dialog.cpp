#include <ivl/ivl>
#include <ivl/qt>
#include "sort_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	sort_dialog* dialog = new sort_dialog;
	dialog->set_column_range('C', 'F');
	dialog->show();
	return app.exec();
}
