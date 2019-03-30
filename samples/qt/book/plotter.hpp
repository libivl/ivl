#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <map>
#include <vector>
#include <cmath>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace std;
using namespace ivl;

//-----------------------------------------------------------------------------

struct plot_settings
{
	double min_x;
	double max_x;
	double min_y;
	double max_y;
	int x_ticks;
	int y_ticks;

	plot_settings(double min_x = 0,   double max_x = 10,
					  double min_y = 0,   double max_y = 10,
					  double x_ticks = 5, double y_ticks = 5) :
		min_x(min_x),     max_x(max_x),
		min_y(min_y),     max_y(max_y),
		x_ticks(x_ticks), y_ticks(y_ticks)
		{ }

	double span_x() const { return max_x - min_x; }
	double span_y() const { return max_y - min_y; }

	void scroll(int dx, int dy)
	{
		double step_x = span_x() / x_ticks;
		min_x += dx * step_x;
		max_x += dx * step_x;

		double step_y = span_y() / y_ticks;
		min_y += dy * step_y;
		max_y += dy * step_y;
	}

	void adjust()
	{
		adjust_axis(min_x, max_x, x_ticks);
		adjust_axis(min_y, max_y, y_ticks);
	}

private:

//-----------------------------------------------------------------------------

	static void adjust_axis(double &min, double &max, int &ticks)
	{
		const int min_ticks = 4;
		double gross_step = (max - min) / min_ticks;
		double step = pow(10.0, floor(log10(gross_step)));

		if (5 * step < gross_step)
			step *= 5;
		else if (2 * step < gross_step)
			step *= 2;

		ticks = int(ceil(max / step) - floor(min / step));
		if (ticks < min_ticks)
			ticks = min_ticks;
		min = floor(min / step) * step;
		max = ceil(max / step) * step;
	}

};

//-----------------------------------------------------------------------------

class plotter : public widget, public method_binder <plotter>
{
	typedef plotter T;
	using method_binder <T>::bind;

	typedef QPointF P;
	typedef vector <P> V;
	typedef map <int, V> M;

	enum { margin = 50 };

	tool_button *zoom_in_button;
	tool_button *zoom_out_button;
	M curve_map;
	vector <plot_settings> zoom_stack;
	int curr_zoom;
	bool band_shown;
	QRect band_rect;
	QPixmap pixmap;

	slot <void ()> zoom_in, zoom_out;

//-----------------------------------------------------------------------------

public:

	plotter(QWidget *parent = 0) : widget(parent)
	{
		bind(zoom_in)  .to <&T::zoom_in_>();
		bind(zoom_out) .to <&T::zoom_out_>();

		setBackgroundRole(QPalette::Dark);
		setAutoFillBackground(true);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setFocusPolicy(Qt::StrongFocus);
		band_shown = false;

		zoom_in_button = new tool_button(this);
		zoom_in_button->setIcon(QIcon(":/plotter_images/zoomin.png"));
		zoom_in_button->adjustSize();
		zoom_in_button->clicked.connect(zoom_in);

		zoom_out_button = new tool_button(this);
		zoom_out_button->setIcon(QIcon(":/plotter_images/zoomout.png"));
		zoom_out_button->adjustSize();
		zoom_out_button->clicked.connect(zoom_out);

		set_plot_settings(plot_settings());
	}

//-----------------------------------------------------------------------------

	QSize minimumSizeHint() const { return QSize(6 * margin, 4 * margin); }
	QSize sizeHint()        const { return QSize(12 * margin, 8 * margin); }

	void set_plot_settings(const plot_settings &settings)
	{
		zoom_stack.clear();
		zoom_stack.push_back(settings);
		curr_zoom = 0;
		zoom_in_button->hide();
		zoom_out_button->hide();
		refresh_pixmap();
	}

	void set_data(int id, const V& data)
	{
		curve_map[id] = data;
		refresh_pixmap();
	}

	void clear(int id)
	{
		curve_map.erase(id);
		refresh_pixmap();
	}

protected:

//-----------------------------------------------------------------------------

	void paintEvent(QPaintEvent * /* event */)
	{
		QStylePainter painter(this);
		painter.drawPixmap(0, 0, pixmap);

		if (band_shown)
		{
			painter.setPen(palette().light().color());
			painter.drawRect(band_rect.normalized()
														.adjusted(0, 0, -1, -1));
		}

		if (hasFocus())
		{
			QStyleOptionFocusRect option;
			option.initFrom(this);
			option.backgroundColor = palette().dark().color();
			painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
		}
	}

	void resizeEvent(QResizeEvent * /* event */)
	{
		int x = width() - (zoom_in_button->width()
		                + zoom_out_button->width() + 10);
		zoom_in_button->move(x, 5);
		zoom_out_button->move(x + zoom_in_button->width() + 5, 5);
		refresh_pixmap();
	}

//-----------------------------------------------------------------------------

	void mousePressEvent(QMouseEvent *event)
	{
		QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);

		if (event->button() == Qt::LeftButton && rect.contains(event->pos()))
		{
			band_shown = true;
			band_rect.setTopLeft(event->pos());
			band_rect.setBottomRight(event->pos());
			update_band_region();
			setCursor(Qt::CrossCursor);
		}
	}

	void mouseMoveEvent(QMouseEvent *event)
	{
		if (band_shown)
		{
			update_band_region();
			band_rect.setBottomRight(event->pos());
			update_band_region();
		}
	}

	void mouseReleaseEvent(QMouseEvent *event)
	{
		if ((event->button() == Qt::LeftButton) && band_shown)
		{
			band_shown = false;
			update_band_region();
			unsetCursor();

			QRect rect = band_rect.normalized();
			if (rect.width() < 4 || rect.height() < 4)
				return;
			rect.translate(-margin, -margin);

			plot_settings prev_settings = zoom_stack[curr_zoom];
			plot_settings settings;
			double dx = prev_settings.span_x() / (width() - 2 * margin);
			double dy = prev_settings.span_y() / (height() - 2 * margin);
			settings.min_x = prev_settings.min_x + dx * rect.left();
			settings.max_x = prev_settings.min_x + dx * rect.right();
			settings.min_y = prev_settings.max_y - dy * rect.bottom();
			settings.max_y = prev_settings.max_y - dy * rect.top();
			settings.adjust();

			zoom_stack.resize(curr_zoom + 1);
			zoom_stack.push_back(settings);
			zoom_in();
		}
	}

//-----------------------------------------------------------------------------

	void wheelEvent(QWheelEvent *event)
	{
		int degrees = event->delta() / 8;
		int ticks = degrees / 15;

		event->orientation() == Qt::Horizontal ?
			zoom_stack[curr_zoom].scroll(ticks, 0) :
			zoom_stack[curr_zoom].scroll(0, ticks);
		refresh_pixmap();
	}

//-----------------------------------------------------------------------------

	void keyPressEvent(QKeyEvent *event)
	{
		switch (event->key())
		{
			case Qt::Key_Plus:   zoom_in();    break;
			case Qt::Key_Minus:  zoom_out();   break;
			case Qt::Key_Left:   move(-1, 0);  break;
			case Qt::Key_Right:  move(+1, 0);  break;
			case Qt::Key_Down:   move(0, -1);  break;
			case Qt::Key_Up:     move(0, +1);  break;
			default:             QWidget::keyPressEvent(event);
		}
	}

private:

//-----------------------------------------------------------------------------

	void zoom_in_()
	{
		if (curr_zoom < int(zoom_stack.size()) - 1)
		{
			++curr_zoom;
			zoom_in_button->setEnabled(curr_zoom < int(zoom_stack.size()) - 1);
			zoom_out_button->setEnabled(true);
			zoom_out_button->show();
			refresh_pixmap();
		}
	}

	void zoom_out_()
	{
		if (curr_zoom > 0)
		{
			--curr_zoom;
			zoom_out_button->setEnabled(curr_zoom > 0);
			zoom_in_button->setEnabled(true);
			zoom_in_button->show();
			refresh_pixmap();
		}
	}

//-----------------------------------------------------------------------------

	void move(int x, int y)
	{
		zoom_stack[curr_zoom].scroll(x, y);
		refresh_pixmap();
	}

//-----------------------------------------------------------------------------

	void update_band_region()
	{
		QRect rect = band_rect.normalized();
		update(rect.left(), rect.top(), rect.width(), 1);
		update(rect.left(), rect.top(), 1, rect.height());
		update(rect.left(), rect.bottom(), rect.width(), 1);
		update(rect.right(), rect.top(), 1, rect.height());
	}

	void refresh_pixmap()
	{
		pixmap = QPixmap(size());
		pixmap.fill(this, 0, 0);

		QPainter painter(&pixmap);
		painter.initFrom(this);
		draw_grid(&painter);
		draw_curves(&painter);
		update();
	}

//-----------------------------------------------------------------------------

	void draw_grid(QPainter *painter)
	{
		QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);
		if (!rect.isValid())
			return;

		plot_settings settings = zoom_stack[curr_zoom];
		QPen quite_dark = palette().dark().color().light();
		QPen light = palette().light().color();

		for (int i = 0; i <= settings.x_ticks; ++i)
		{
			int x = rect.left() + (i * (rect.width() - 1)
												/ settings.x_ticks);
			double label = settings.min_x + (i * settings.span_x()
															/ settings.x_ticks);
			painter->setPen(quite_dark);
			painter->drawLine(x, rect.top(), x, rect.bottom());
			painter->setPen(light);
			painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
			painter->drawText(x - 50, rect.bottom() + 5, 100, 20,
									Qt::AlignHCenter | Qt::AlignTop,
									QString::number(label));
		}

		for (int j = 0; j <= settings.y_ticks; ++j)
		{
			int y = rect.bottom() - (j * (rect.height() - 1)
			        / settings.y_ticks);
			double label = settings.min_y + (j * settings.span_y()
			               / settings.y_ticks);
			painter->setPen(quite_dark);
			painter->drawLine(rect.left(), y, rect.right(), y);
			painter->setPen(light);
			painter->drawLine(rect.left() - 5, y, rect.left(), y);
			painter->drawText(rect.left() - margin, y - 10, margin - 5, 20,
			                  Qt::AlignRight | Qt::AlignVCenter,
			                  QString::number(label));
		}

		painter->drawRect(rect.adjusted(0, 0, -1, -1));
	}

//-----------------------------------------------------------------------------

	void draw_curves(QPainter *painter)
	{
		static const QColor id_colors[6] =
		{
			Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow
		};
		plot_settings settings = zoom_stack[curr_zoom];
		QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);
		if (!rect.isValid())
			return;

		painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

		for (M::const_iterator i = curve_map.begin(); i != curve_map.end(); i++)
		{
			int id = i->first;
			const V& data = i->second;
			QPolygonF polyline(int(data.size()));

			for (unsigned n = 0; n < data.size(); ++n)
			{
				double dx = data[n].x() - settings.min_x;
				double dy = data[n].y() - settings.min_y;
				double x = rect.left() + (dx * (rect.width() - 1)
				           / settings.span_x());
				double y = rect.bottom() - (dy * (rect.height() - 1)
				           / settings.span_y());
				polyline[int(n)] = P(x, y);
			}
			painter->setPen(id_colors[uint(id) % 6]);
			painter->drawPolyline(polyline);
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // PLOTTER_HPP