#include <ivl/ivl>
#include <ivl/qt>
#include "preference_dialog.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    preference_dialog dialog;
    dialog.show();
    return app.exec();
}
