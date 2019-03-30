#include <ivl/ivl>
#include <ivl/qt>
#include "project_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	project_dialog dialog;
	dialog.show();
	return app.exec();
}
