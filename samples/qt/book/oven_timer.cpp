#include <ivl/ivl>
#include <ivl/qt>
#include "oven_timer.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    oven_timer oven;
    oven.setWindowTitle(QObject::tr("Oven Timer"));
    oven.resize(300, 300);
    oven.show();
    return app.exec();
}
