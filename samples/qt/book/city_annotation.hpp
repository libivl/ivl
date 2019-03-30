#ifndef CITY_ANNOTATION_HPP
#define CITY_ANNOTATION_HPP

#include <cmath>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using ::rand;

//-----------------------------------------------------------------------------

class annotation : public QGraphicsItem
{
	QFont font;
	QString str;
	bool major;
	double threshold;
	int y;

public:

//-----------------------------------------------------------------------------

	annotation(const QString& text, bool major = false)
	{
		font = qApp->font();
		font.setBold(true);
		if (major)
		{
			font.setPointSize(font.pointSize() + 2);
			font.setStretch(QFont::SemiExpanded);
		}

		threshold = major ?
			0.01 * (40 + (rand() % 40)) :
			0.01 * (100 + (rand() % 100));

		str = text;
		this->major = major;
		y = 20 - (rand() % 40);

		setZValue(1000);
		setFlag(ItemIgnoresTransformations, true);
	}

//-----------------------------------------------------------------------------

	QString text() const { return str; }
	void setText(const QString& text)
	{
		prepareGeometryChange();
		str = text;
		update();
	}

//-----------------------------------------------------------------------------

	QRectF boundingRect() const
	{
		QFontMetricsF metrics(font);
		QRectF rect = metrics.boundingRect(str);
		rect.moveCenter(QPointF(0, y));
		rect.adjust(-4, 0, +4, 0);
		return rect;
	}

//-----------------------------------------------------------------------------

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
				  QWidget* /* widget */)
	{
		qreal level = // TODO: always 1 due to ItemIgnoresTransformations flag
			option->levelOfDetailFromTransform(painter->worldTransform());
		if (level <= threshold)
			return;

		painter->setFont(font);
		QRectF rect = boundingRect();

		int alpha = int(30 * std::log(level));
		if (alpha >= 32)
			painter->fillRect(rect, QColor(255, 255, 255, qMin(alpha, 63)));

		painter->setPen(Qt::white);
		painter->drawText(rect.translated(+1, +1), str,
								QTextOption(Qt::AlignCenter));
		painter->setPen(Qt::blue);
		painter->drawText(rect, str, QTextOption(Qt::AlignCenter));
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CITY_ANNOTATION_HPP
