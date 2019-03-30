#include <ivl/ivl>
#include <ivl/qt>
#include "settings_viewer.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    settings_viewer viewer;
    viewer.show();
    return app.exec();
}
