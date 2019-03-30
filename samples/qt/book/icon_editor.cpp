#include <ivl/ivl>
#include <ivl/qt>
#include "icon_editor.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	icon_editor* editor = new icon_editor;
	editor->set_icon_image(QImage(":/icon_editor_images/mouse.png"));

	QScrollArea area;
	area.setWidget(editor);
	area.setWidgetResizable(true);
	area.setFocusPolicy(Qt::NoFocus);
	area.viewport()->setBackgroundRole(QPalette::Dark);
	area.viewport()->setAutoFillBackground(true);
	area.setWindowTitle(QObject::tr("Icon Editor"));

	editor->setFocus(Qt::OtherFocusReason);  // TODO: simpler way of focusing scroll area's widget?
	area.show();
	return app.exec();
}
