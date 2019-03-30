#include <ivl/ivl>
#include <ivl/qt>
#include "color_list.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    color_list dialog;
    dialog.show();
    return app.exec();
}
