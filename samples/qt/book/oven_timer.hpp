#ifndef OVEN_TIMER_HPP
#define OVEN_TIMER_HPP

#include <cmath>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

const double pi = 3.14159265359;
const double degrees_per_minute = 7.0;
const double degrees_per_second = degrees_per_minute / 60;
const int max_minutes = 45;
const int max_seconds = max_minutes * 60;
const int update_interval = 5;

//-----------------------------------------------------------------------------

class oven_timer : public widget, public method_binder <oven_timer>
{
	typedef oven_timer T;
	using method_binder <T>::bind;

	QDateTime finish_time;
	qtimer *update_timer;
	qtimer *finish_timer;

	signal <void ()> timeout;

public:

//-----------------------------------------------------------------------------

	oven_timer(QWidget* parent = 0) : widget(parent)
	{
		finish_time = QDateTime::currentDateTime();

		update_timer = new qtimer(this);
		update_timer->timeout.connect(update);

		finish_timer = new qtimer(this);
		finish_timer->setSingleShot(true);
		finish_timer->timeout.connect(timeout);
		finish_timer->timeout.connect(update_timer->stop);

		QFont font;
		font.setPointSize(8);
		setFont(font);
	}

//-----------------------------------------------------------------------------

	void setDuration(int secs)
	{
		secs = qBound(0, secs, max_seconds);

		finish_time = QDateTime::currentDateTime().addSecs(secs);

		if (secs > 0)
		{
			update_timer->start(update_interval * 1000);
			finish_timer->start(secs * 1000);
		}
		else
		{
			update_timer->stop();
			finish_timer->stop();
		}
		update();
	}

	int duration() const
	{
		int secs = QDateTime::currentDateTime().secsTo(finish_time);
		if (secs < 0)
			secs = 0;
		return secs;
	}

//-----------------------------------------------------------------------------

	void draw(QPainter *painter)
	{
		static const int triangle[3][2] = {
			{ -2, -49 }, { +2, -49 }, { 0, -47 }
		};
		QPen thickPen(palette().foreground(), 1.5);
		QPen thinPen(palette().foreground(), 0.5);
		QColor niceBlue(150, 150, 200);

		painter->setPen(thinPen);
		painter->setBrush(palette().foreground());
		painter->drawPolygon(QPolygon(3, &triangle[0][0]));

		QConicalGradient cone_gradient(0, 0, -90.0);
		cone_gradient.setColorAt(0.0, Qt::darkGray);
		cone_gradient.setColorAt(0.2, niceBlue);
		cone_gradient.setColorAt(0.5, Qt::white);
		cone_gradient.setColorAt(1.0, Qt::darkGray);

		painter->setBrush(cone_gradient);
		painter->drawEllipse(-46, -46, 92, 92);

		QRadialGradient halo_gradient(0, 0, 20, 0, 0);
		halo_gradient.setColorAt(0.0, Qt::lightGray);
		halo_gradient.setColorAt(0.8, Qt::darkGray);
		halo_gradient.setColorAt(0.9, Qt::white);
		halo_gradient.setColorAt(1.0, Qt::black);

		painter->setPen(Qt::NoPen);
		painter->setBrush(halo_gradient);
		painter->drawEllipse(-20, -20, 40, 40);

		QLinearGradient knob_gradient(-7, -25, 7, -25);
		knob_gradient.setColorAt(0.0, Qt::black);
		knob_gradient.setColorAt(0.2, niceBlue);
		knob_gradient.setColorAt(0.3, Qt::lightGray);
		knob_gradient.setColorAt(0.8, Qt::white);
		knob_gradient.setColorAt(1.0, Qt::black);

		painter->rotate(duration() * degrees_per_second);
		painter->setBrush(knob_gradient);
		painter->setPen(thinPen);
		painter->drawRoundRect(-7, -25, 14, 50, 99, 49);

		for (int i = 0; i <= max_minutes; ++i)
		{
			if (i % 5 == 0) {
				painter->setPen(thickPen);
				painter->drawLine(0, -41, 0, -44);
				painter->drawText(-15, -41, 30, 30,
					Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
			} else
			{
					painter->setPen(thinPen);
					painter->drawLine(0, -42, 0, -44);
			}
			painter->rotate(-degrees_per_minute);
		}
	}

protected:

//-----------------------------------------------------------------------------

	void mousePressEvent(QMouseEvent *event)
	{
		QPointF point = event->pos() - rect().center();
		double theta = std::atan2(-point.x(), -point.y()) * 180.0 / pi;
		setDuration(duration() + int(theta / degrees_per_second));
		update();
	}

	void paintEvent(QPaintEvent * /* event */)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);
		int side = std::min(width(), height());
		painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
		painter.setWindow(-50, -50, 100, 100);
		draw(&painter);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // OVEN_TIMER_HPP
