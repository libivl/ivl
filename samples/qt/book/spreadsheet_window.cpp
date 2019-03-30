#include <ivl/ivl>
#include <ivl/qt>
#include "spreadsheet_window.hpp"

using namespace ivl;
using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    spreadsheet_window win;
    win.show();
    return app.exec();
}
