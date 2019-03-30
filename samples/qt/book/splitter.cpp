#include <ivl/ivl>
#include <ivl/qt>

using namespace ivl;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	text_edit* editor1 = new text_edit;
	text_edit* editor2 = new text_edit;
	text_edit* editor3 = new text_edit;

	splitter split(Qt::Horizontal);
	split.addWidget(editor1);
	split.addWidget(editor2);
	split.addWidget(editor3);

	editor1->setPlainText(
		"Mon enfant, ma soeur,\n"
		"Songe  la douceur\n"
		"D'aller l-bas vivre ensemble,\n"
		"Aimer  loisir,\n"
		"Aimer et mourir\n"
		"Au pays qui te ressemble."
	);
	editor2->setPlainText(
		"My child, my sister,\n"
		"think of the sweetness\n"
		"of going there to live together!\n"
		"To love at leisure,\n"
		"to love and to die\n"
		"in a country that is the image of you!"
	);
	editor3->setPlainText(
		"Mein Kind, meine Schwester,\n"
		"denke an den Traum\n"
		"dort hin(unter) zu gehen um zusammen\n"
		"zu leben und in aller Ruhe zu lieben,\n"
		"Zu lieben und zu sterben\n"
		"in dem Land, das dir gleicht."
	);

	split.setWindowTitle(QObject::tr("Splitter"));
	split.show();
	return app.exec();
}
