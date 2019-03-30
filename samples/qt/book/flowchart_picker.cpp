#include <ivl/ivl>
#include <ivl/qt>
#include "flowchart_picker.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	map <int, QString> symbol_map;
	symbol_map[132] = QObject::tr("Data");
	symbol_map[135] = QObject::tr("Decision");
	symbol_map[137] = QObject::tr("Document");
	symbol_map[138] = QObject::tr("Manual Input");
	symbol_map[139] = QObject::tr("Manual Operation");
	symbol_map[141] = QObject::tr("On Page Reference");
	symbol_map[142] = QObject::tr("Predefined Process");
	symbol_map[145] = QObject::tr("Preparation");
	symbol_map[150] = QObject::tr("Printer");
	symbol_map[152] = QObject::tr("Process");

	flowchart_picker picker(symbol_map);
	picker.show();
	return app.exec();
}
