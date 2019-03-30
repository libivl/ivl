#include <ivl/ivl>
#include <ivl/qt>
#include "team_leaders.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	QStringList leaders;
	leaders << "Stooge Viller" << "Littleface" << "B-B Eyes"
		<< "Pruneface" << "Mrs. Pruneface" << "The Brow"
		<< "Vitamin Flintheart" << "Flattop Sr." << "Shakey"
		<< "Breathless Mahoney" << "Mumbles" << "Shoulders"
		<< "Sketch Paree";

	team_leaders_dialog dialog(leaders);
	dialog.show();
	return app.exec();
}
