#include <ivl/ivl>
#include <ivl/qt>
#include "editor_window.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    editor_window window;
    window.show();
    return app.exec();
}
