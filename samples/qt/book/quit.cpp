#include <ivl/ivl>
#include <ivl/qt>

using namespace ivl;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	push_button* button = new push_button("Quit");
	button->clicked.connect(application::quit);
	button->show();
	return app.exec();
}
