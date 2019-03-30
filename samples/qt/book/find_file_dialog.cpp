#include <ivl/ivl>
#include <ivl/qt>
#include "find_file_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    find_file_dialog dialog;
    dialog.show();
    return app.exec();
}
