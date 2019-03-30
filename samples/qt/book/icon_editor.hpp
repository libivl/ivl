#ifndef ICON_EDITOR_HPP
#define ICON_EDITOR_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class icon_editor : public widget, public method_binder <icon_editor>
{
	typedef icon_editor T;
	using method_binder <T>::bind;

	QColor curr_color;
	QImage image;
	int zoom;

//-----------------------------------------------------------------------------

public:

	slot <void ()> zoom_in, zoom_out;

//-----------------------------------------------------------------------------

	icon_editor(QWidget *parent = 0) : widget(parent)
	{
		bind(zoom_in)  .to <&T::zoom_in_>();
		bind(zoom_out) .to <&T::zoom_out_>();

		setAttribute(Qt::WA_StaticContents);
		setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

		curr_color = Qt::black;
		zoom = 8;

		image = QImage(16, 16, QImage::Format_ARGB32);
		image.fill(qRgba(0, 0, 0, 0));
	}

//-----------------------------------------------------------------------------

	QColor pen_color() const { return curr_color; }
	void set_pen_color(const QColor &new_color) { curr_color = new_color; }

	int zoom_factor() const { return zoom; }
	void set_zoom_factor(int new_zoom)
	{
		if (new_zoom < 1)
			new_zoom = 1;

		if (new_zoom != zoom)
		{
			zoom = new_zoom;
			update();
			updateGeometry();
		}
	}

	QImage icon_image() const { return image; }
	void set_icon_image(const QImage &new_image)
	{
		if (new_image != image)
		{
			image = new_image.convertToFormat(QImage::Format_ARGB32);
			update();
			updateGeometry();
		}
	}

	QSize sizeHint() const
	{
		QSize size = zoom * image.size();
		if (zoom >= 3)
			size += QSize(1, 1);
		return size;
	}

protected:

//-----------------------------------------------------------------------------

	void mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
			set_pixel(event->pos(), true);
		else if (event->button() == Qt::RightButton)
			set_pixel(event->pos(), false);
	}

	void mouseMoveEvent(QMouseEvent *event)
	{
		if (event->buttons() & Qt::LeftButton)
			set_pixel(event->pos(), true);
		else if (event->buttons() & Qt::RightButton)
			set_pixel(event->pos(), false);
	}

	void keyPressEvent(QKeyEvent *event)
	{
		switch (event->key())
		{
			case Qt::Key_Plus:   zoom_in();   break;
			case Qt::Key_Minus:  zoom_out();  break;
			default:             QWidget::keyPressEvent(event);
		}
	}

//-----------------------------------------------------------------------------

	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);

		if (zoom >= 3)
		{
			painter.setPen(palette().foreground().color());
			for (int i = 0; i <= image.width(); ++i)
				painter.drawLine(zoom * i, 0, zoom * i, zoom * image.height());
			for (int j = 0; j <= image.height(); ++j)
				painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
		}

		for (int i = 0; i < image.width(); ++i)
			for (int j = 0; j < image.height(); ++j)
			{
				QRect rect = pixel_rect(i, j);
				if (!event->region().intersect(rect).isEmpty())
				{
					QColor color = QColor::fromRgba(image.pixel(i, j));
					if (color.alpha() < 255)
						painter.fillRect(rect, Qt::white);
					painter.fillRect(rect, color);
				}
			}
	}

private:

//-----------------------------------------------------------------------------

	void zoom_out_() { set_zoom_factor(zoom / 1.5); }
	void zoom_in_()  { set_zoom_factor(zoom == 1 ? 2 : zoom * 1.5); }

	void set_pixel(const QPoint &pos, bool opaque)
	{
		int i = pos.x() / zoom;
		int j = pos.y() / zoom;

		if (image.rect().contains(i, j))
		{
			opaque ? image.setPixel(i, j, pen_color().rgba()) :
			         image.setPixel(i, j, qRgba(0, 0, 0, 0));
			update(pixel_rect(i, j));
		}
	}

	QRect pixel_rect(int i, int j) const
	{
		return zoom < 3 ?
			QRect(zoom * i, zoom * j, zoom, zoom) :
		   QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // ICON_EDITOR_HPP
