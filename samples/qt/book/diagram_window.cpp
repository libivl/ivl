#include <ivl/ivl>
#include <ivl/qt>
#include "diagram_window.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	diagram_window view;
	view.show();
	return app.exec();
}
