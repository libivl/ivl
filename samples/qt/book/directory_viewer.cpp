#include <ivl/ivl>
#include <ivl/qt>
#include "directory_viewer.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    directory_viewer viewer;
    viewer.show();
    return app.exec();
}
