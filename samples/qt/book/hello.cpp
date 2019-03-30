#include <ivl/ivl>
#include <ivl/qt>

using namespace ivl;

int main(int argc, char *argv[])
{
	application app(argc, argv);
	label* l = new label("Hello Qt!");
	l->show();
	return app.exec();
}
