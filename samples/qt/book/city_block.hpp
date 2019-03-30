#ifndef CITY_BLOCK_HPP
#define CITY_BLOCK_HPP

#include <cmath>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using ::rand;

//-----------------------------------------------------------------------------

class city_block : public QGraphicsItem
{
	int kind;
	QColor color;
	QPainterPath shape;

public:

//-----------------------------------------------------------------------------

	enum Kind { Park, SmallBuilding, Hospital, Hall, Building, Tower,
					LShapedBlock, LShapedBlockPlusSmallBlock, TwoBlocks,
					BlockPlusTwoSmallBlocks };

	city_block(Kind kind)
	{
		this->kind = kind;

		int green = 96 + (rand() % 64);
		int red   = 16 + green + (rand() % 64);
		int blue  = 16 + (rand() % green);
		color = QColor(red, green, blue);

		if (kind == Park)
		{
			color = QColor(192 + (rand() % 32), 255,
								192 + (rand() % 16));
			shape.addRect(boundingRect());
		}
		else if (kind == SmallBuilding)
		{
			QRectF block(-7.5, -7.5, 15, 15);
			block.moveBottomLeft(QPointF((rand() % 6) - 3, (rand() % 6) - 3));
			shape.addRect(block);
		}
		else if (kind == Hospital)
		{
			int a = (rand() % 6) + 10;
			int b = (rand() % 6) + 10;
			QPolygonF block;
			block << QPointF(-5, -a) << QPointF(-5, -5) << QPointF(-10, -5)
					<< QPointF(-10, 5) << QPointF(-5, 5)  << QPointF(-5, 10)
					<< QPointF(5, 10)  << QPointF(5, 5)   << QPointF(b, 5)
					<< QPointF(b, -5)  << QPointF(5, -5)  << QPointF(5, -a);
			shape.addPolygon(block);
		}
		else if (kind == Hall)
		{
			int pad1 = (rand() % 8) + 2;
			int pad2 = (rand() % 8) + 2;
			shape.addEllipse(boundingRect().adjusted(+pad1, +pad1, -pad2, -pad2));
		}
		else if (kind == Building)
		{
			shape.addRect(boundingRect());
		}
		else if (kind == Tower)
		{
			int pad1 = (rand() % 8) + 2;
			int pad2 = (rand() % 8) + 2;
			shape.addRect(boundingRect().adjusted(+pad1, +pad1, -pad2, -pad2));
		}
		else if (kind == LShapedBlock || kind == LShapedBlockPlusSmallBlock)
		{
			int a = (rand() % 6) + 10;
			int b = (rand() % 6) + 10;
			int s = qMin(a, b) / 2;
			QPolygonF block;
			block << QPointF(-a, -a) << QPointF(-a, +a) << QPointF(-s, +a)
					<< QPointF(-s, -s) << QPointF(+b, -s) << QPointF(+b, -a);
			shape.addPolygon(block);
			if (kind == LShapedBlockPlusSmallBlock)
			{
					int inset = (rand() % 4) + 4;
					shape.addRect(QRectF(-s + inset, -s + inset, a, b));
			}
		}
		else if (kind == TwoBlocks)
		{
			int w1 = (rand() % 10) + 8;
			int h1 = (rand() % 28) + 8;
			int w2 = (rand() % 10) + 8;
			int h2 = (rand() % 24) + 8;
			shape.addRect(QRectF(-16, -16, w1, h1));
			shape.addRect(QRectF(-16 + w1 + 4, -16 + (rand() % 4), w2, h2));
		}
		else if (kind == BlockPlusTwoSmallBlocks)
		{
			int w1 = (rand() % 10) + 8;
			int h1 = (rand() % 28) + 8;
			int w2 = (rand() % 10) + 8;
			int h2 = (rand() % 10) + 8;
			int w3 = (rand() % 6) + 8;
			int h3 = (rand() % 6) + 8;
			int y = (rand() % 4) - 16;
			shape.addRect(QRectF(-16, -16, w1, h1));
			shape.addRect(QRectF(-16 + w1 + 4, y, w2, h2));
			shape.addRect(QRectF(-16 + w1 + 4, y + h2 + 4 + (rand() % 4), w3, h3));
		}
	}

//-----------------------------------------------------------------------------

	QRectF boundingRect() const { return QRectF(-20, -20, 40, 40); }

//-----------------------------------------------------------------------------

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
				  QWidget* /* widget */)
	{
		qreal level =
			option->levelOfDetailFromTransform(painter->worldTransform());
		if (level < 2.0)
			painter->fillPath(shape, color);
		else
		{
			QLinearGradient gradient(QPoint(-20, -20), QPoint(+20, +20));
			int coeff = 105 + int(10 * std::log(level - 4.0));
			gradient.setColorAt(0.0, color.lighter(coeff));
			gradient.setColorAt(1.0, color.darker(2 * coeff));
			painter->fillPath(shape, gradient);
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CITY_BLOCK_HPP
