#include <ivl/ivl>
#include <ivl/qt>

using namespace ivl;

int main(int argc, char *argv[])
{
	application app(argc, argv);

	spin_box* spin = new spin_box;
	slider* slide = new slider(Qt::Horizontal);

	spin->setRange(0, 130);
	slide->setRange(0, 130);

	spin->value_changed_0.connect(slide->set_value);  // TODO: overloading
	slide->value_changed.connect(spin->set_value);

	spin->set_value(35);

	row_layout* layout = new row_layout;
	*layout << spin << slide;

	widget* window = new widget;
	window->setWindowTitle("Enter Your Age");
	window->setLayout(layout);
	window->show();

	return app.exec();
}
