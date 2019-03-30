#include <ivl/ivl>
#include <ivl/qt>
#include "city_model.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);

    QStringList cities;
    cities << "Arvika" << "Boden" << "Eskilstuna" << "Falun"
           << "Filipstad" << "Halmstad" << "Helsingborg" << "Karlstad"
           << "Kiruna" << "Kramfors" << "Motala" << "Sandviken"
           << "Skara" << "Stockholm" << "Sundsvall" << "Trelleborg";

    city_model model;
    model.set_cities(cities);

    table_view view;
    view.setModel(&model);
    view.setAlternatingRowColors(true);
    view.setWindowTitle(QObject::tr("Cities"));
    view.show();

    return app.exec();
}
