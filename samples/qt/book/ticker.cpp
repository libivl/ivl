#include <ivl/ivl>
#include <ivl/qt>
#include "ticker.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    ticker tick;
    tick.setWindowTitle(QObject::tr("Ticker"));
    tick.set_text(QObject::tr("How long it lasted was impossible to say ++ "));
    tick.show();
    return app.exec();
}
