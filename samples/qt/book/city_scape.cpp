#include <ivl/ivl>
#include <ivl/qt>
#include "city_scape.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    city_scape city;
    city.show();
    return app.exec();
}
