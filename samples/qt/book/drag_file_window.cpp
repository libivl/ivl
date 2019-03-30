#include <ivl/ivl>
#include <ivl/qt>
#include "drag_file_window.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    drag_file_window window;
    window.show();
    return app.exec();
}
