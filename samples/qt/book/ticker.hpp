#ifndef TICKER_HPP
#define TICKER_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class ticker : public widget
{
	QString message_text;
	int offset;
	int timer_id;

public:

//-----------------------------------------------------------------------------

	ticker(QWidget* parent = 0) : widget(parent)
	{
		offset = 0;
		timer_id = 0;
	}

	void set_text(const QString &text)
	{
		message_text = text;
		update();
		updateGeometry();
	}

	QString text() const { return message_text; }

	QSize sizeHint() const
	{
		return fontMetrics().size(0, text());
	}

protected:

//-----------------------------------------------------------------------------

	void paintEvent(QPaintEvent * /* event */)
	{
		QPainter painter(this);

		int text_width = fontMetrics().width(text());
		if (text_width < 1)
			return;
		int x = -offset;
		while (x < width())
		{
			painter.drawText(x, 0, text_width, height(),
								  Qt::AlignLeft | Qt::AlignVCenter, text());
			x += text_width;
		}
	}

	void timerEvent(QTimerEvent *event)
	{
		if (event->timerId() == timer_id)
		{
			++offset;
			if (offset >= fontMetrics().width(text()))
					offset = 0;
			scroll(-1, 0);
		}
		else
			widget::timerEvent(event);
	}

	void showEvent(QShowEvent * /* event */)
	{
		timer_id = startTimer(30);
	}

	void hideEvent(QHideEvent * /* event */)
	{
		killTimer(timer_id);
		timer_id = 0;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // TICKER_HPP
