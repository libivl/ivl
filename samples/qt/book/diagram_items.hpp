#ifndef DIAGRAM_ITEMS_HPP
#define DIAGRAM_ITEMS_HPP

#include <set>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

template <typename N, typename L>
class node_item : public QGraphicsItem
{
	Q_DECLARE_TR_FUNCTIONS(node_item)

	typedef typename set <L*>::iterator I;

	set <L*> links;
	QString node_text;
	QColor node_text_color;
	QColor node_background_color;
	QColor node_outline_color;

public:

//-----------------------------------------------------------------------------

	node_item()
	{
		node_text_color = Qt::darkGreen;
		node_outline_color = Qt::darkBlue;
		node_background_color = Qt::white;

		setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	}

	~node_item()
	{
		set <L*> copy(links);
		for (I i = copy.begin(); i != copy.end(); i++)
			delete *i;
	}

//-----------------------------------------------------------------------------

	QString text() const { return node_text; }
	void set_text(const QString &text)
	{
		prepareGeometryChange();
		node_text = text;
		update();
	}

	QColor text_color() const { return node_text_color; }
	void set_text_color(const QColor &color)
	{
		node_text_color = color;
		update();
	}

	QColor outline_color() const { return node_outline_color; }
	void set_outline_color(const QColor &color)
	{
		node_outline_color = color;
		update();
	}

	QColor background_color() const { return node_background_color; }
	void set_background_color(const QColor &color)
	{
		node_background_color = color;
		update();
	}

//-----------------------------------------------------------------------------

	void add_link(L* link) { links.insert(link); }
	void remove_link(L* link) { links.erase(link); }

//-----------------------------------------------------------------------------

	QRectF boundingRect() const
	{
		const int margin = 1;
		return outline_rect().adjusted(-margin, -margin, +margin, +margin);
	}

	QPainterPath shape() const
	{
		QRectF rect = outline_rect();
		QPainterPath path;
		path.addRoundRect(rect, roundness(rect.width()),
								roundness(rect.height()));
		return path;
	}

//-----------------------------------------------------------------------------

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
				  QWidget* /* widget */)
	{
		QPen pen(node_outline_color);
		if (option->state & QStyle::State_Selected)
		{
			pen.setStyle(Qt::DotLine);
			pen.setWidth(2);
		}
		painter->setPen(pen);
		painter->setBrush(node_background_color);

		QRectF rect = outline_rect();
		painter->drawRoundRect(rect, roundness(rect.width()),
									  roundness(rect.height()));

		painter->setPen(node_text_color);
		painter->drawText(rect, Qt::AlignCenter, node_text);
	}

protected:

//-----------------------------------------------------------------------------

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
	{
		QString text = QInputDialog::getText(event->widget(),
										tr("Edit Text"), tr("Enter new text:"),
										QLineEdit::Normal, node_text);
		if (!text.isEmpty())
			set_text(text);
	}

//-----------------------------------------------------------------------------

	QVariant itemChange(GraphicsItemChange change, const QVariant& value)
	{
		if (change == ItemPositionHasChanged)
		{
			for (I i = links.begin(); i != links.end(); i++)
				(*i)->track_nodes();
		}
		return QGraphicsItem::itemChange(change, value);
	}

private:

//-----------------------------------------------------------------------------

	QRectF outline_rect() const
	{
		const int padding = 8;
		QFontMetricsF metrics = qApp->font();
		QRectF rect = metrics.boundingRect(node_text);
		rect.adjust(-padding, -padding, +padding, +padding);
		rect.translate(-rect.center());
		return rect;
	}

//-----------------------------------------------------------------------------

	int roundness(double size) const
	{
		const int diameter = 12;
		return 100 * diameter / int(size);
	}

};

//-----------------------------------------------------------------------------

template <typename L, typename N>
class link_item : public QGraphicsLineItem
{
	N* from;
	N* to;

	L* derived() { return static_cast <L*>(this); }

public:

//-----------------------------------------------------------------------------

	link_item(N* from_node, N* to_node)
	{
		from = from_node;
		to = to_node;

		from->add_link(derived());
		to->add_link(derived());

		setFlags(QGraphicsItem::ItemIsSelectable);
		setZValue(-1);

		set_color(Qt::darkRed);
		track_nodes();
	}

//-----------------------------------------------------------------------------

	~link_item()
	{
		from->remove_link(derived());
		to->remove_link(derived());
	}

//-----------------------------------------------------------------------------

	N* from_node() const { return from; }
	N* to_node() const { return to; }

	void track_nodes() { setLine(QLineF(from->pos(), to->pos())); }

	void set_color(const QColor& color) { setPen(QPen(color, 1.0)); }
	QColor color() const { return pen().color(); }

};

//-----------------------------------------------------------------------------

struct diagram_link;

struct diagram_node : public node_item <diagram_node, diagram_link> { };

class diagram_link : public link_item <diagram_link, diagram_node>
{
	typedef diagram_node N;
	typedef link_item <diagram_link, diagram_node> B;
public:
	diagram_link(N* from_node, N* to_node) : B(from_node, to_node) { }
};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // DIAGRAM_ITEMS_HPP
