#include <ivl/ivl>
#include <ivl/qt>
#include "boolean_window.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    boolean_window window;
    window.show();
    return app.exec();
}
