#include <ivl/ivl>
#include <ivl/qt>
#include "plotter.hpp"

using namespace qt_book;

//-----------------------------------------------------------------------------

template <typename P>
void read_data(plotter& plot, const QString &filename)
{
	typedef vector <P> V;
	const int C = 6;

	V data[C];
	double factor_x = 0.0013;
	double offset_x = 0.0;
	double factor_y[C] = { 0.0008, 0.1, 0.2, 0.2, 0.1, 0.8 };
	double offset_y[C] = { +500, -55, +309, +308, 0, 0 };
	int pos[C] = { 3, 6, 7, 8, 9, 10 };
	QFile file(filename);

	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			QStringList coords = line.split(' ', QString::SkipEmptyParts);
			if (coords.count() >= int(C))
			{
				double x = factor_x * coords[0].toDouble();
				if (data[0].empty())
					offset_x = x;
				for (int c = 0; c < C; ++c)
				{
					double y = coords[pos[c]].toDouble();
					data[c].push_back(P(x - offset_x, factor_y[c] * (y - offset_y[c])));
				}
			}
		}
	}

	for (int c = 0; c < C; ++c)
		plot.set_data(c, data[c]);
}

//-----------------------------------------------------------------------------

template <typename P>
void generate_data(plotter& plot)
{
	typedef vector <P> V;
	const int C = 2, N = 100;

	V data[C];
	for (int c = 0; c < C; ++c)
	{
		data[c].resize(N);
		for (int n = 0; n < N; ++n)
			data[c][n] = P(n, uint(qrand()) % 100);
		plot.set_data(c, data[c]);
	}

	plot.set_plot_settings(plot_settings(0, 100, 0, 100));
}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	typedef QPointF P;

	application app(argc, argv);
	plotter plot;
	plot.setWindowTitle(QObject::tr("plotter"));
	if (true)
		read_data <P>(plot, ":/plotter_data/in1.txt");
	else
		generate_data <P>(plot);
	plot.show();
	return app.exec();
}
