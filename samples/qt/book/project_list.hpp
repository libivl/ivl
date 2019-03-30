#ifndef PROJECT_LIST_HPP
#define PROJECT_LIST_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class project_list : public list_widget
{
	QPoint start_pos;

public:

//-----------------------------------------------------------------------------

	project_list(QWidget* parent = 0) : list_widget(parent)
		{ setAcceptDrops(true); }

protected:

//-----------------------------------------------------------------------------

	void mousePressEvent(QMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton)
			start_pos = event->pos();
		list_widget::mousePressEvent(event);
	}

	void mouseMoveEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			int distance = (event->pos() - start_pos).manhattanLength();
			if (distance >= application::startDragDistance())
				perform_drag();
		}
		list_widget::mouseMoveEvent(event);
	}

//-----------------------------------------------------------------------------

	void dragEnterEvent(QDragEnterEvent* event)
	{
		project_list* source =
			dynamic_cast <project_list*>(event->source());

		if (source && source != this)
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		project_list* source =
			dynamic_cast <project_list*>(event->source());

		if (source && source != this)
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}

	void dropEvent(QDropEvent* event)
	{
		project_list* source =
			dynamic_cast <project_list*>(event->source());

		if (source && source != this)
		{
			addItem(event->mimeData()->text());
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}

private:

//-----------------------------------------------------------------------------

	void perform_drag()
	{
		QListWidgetItem* item = currentItem();
		if (item)
		{
			QMimeData *mimeData = new QMimeData;
			mimeData->setText(item->text());

			drag *d = new drag(this);
			d->setMimeData(mimeData);
			d->setPixmap(QPixmap(":/project_images/person.png"));
			if (d->exec(Qt::MoveAction) == Qt::MoveAction)
				delete item;
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // PROJECT_LIST_HPP
