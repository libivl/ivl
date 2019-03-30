#include <ivl/ivl>
#include <ivl/qt>
#include "mail_client.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);
    mail_client client;
    client.show();
    return app.exec();
}
