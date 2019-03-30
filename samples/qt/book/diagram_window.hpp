#ifndef DIAGRAM_WINDOW_HPP
#define DIAGRAM_WINDOW_HPP

#include "diagram_items.hpp"
#include "diagram_properties_dialog.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class diagram_window : public main_window,
	public method_binder <diagram_window>
{
	typedef diagram_window T;
	using method_binder <T>::bind;

	typedef std::pair <diagram_node*, diagram_node*> pair;

	menu *file_menu, *edit_menu;
	tool_bar *edit_bar;
	action *exit_action, *add_node_action, *add_link_action,
	       *delete_action, *cut_action, *copy_action, *paste_action,
	       *bring2front_action, *send2back_action, *properties_action;

	graphics_scene *scene;
	graphics_view *view;

	int min_z, max_z, seq_number;

	slot <void ()> add_node, add_link, del, cut, copy, paste,
	               bring2front, send2back, properties, update_actions;

public:

//-----------------------------------------------------------------------------

	diagram_window()
	{
		bind(add_node)       .to <&T::add_node_>();
		bind(add_link)       .to <&T::add_link_>();
		bind(del)            .to <&T::del_>();
		bind(cut)            .to <&T::cut_>();
		bind(copy)           .to <&T::copy_>();
		bind(paste)          .to <&T::paste_>();
		bind(bring2front)    .to <&T::bring2front_>();
		bind(send2back)      .to <&T::send2back_>();
		bind(properties)     .to <&T::properties_>();
		bind(update_actions) .to <&T::update_actions_>();

		scene = new graphics_scene(0, 0, 600, 500);
		scene->selection_changed.connect(update_actions);

		view = new graphics_view;
		view->setScene(scene);
		view->setDragMode(graphics_view::RubberBandDrag);
		view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
		view->setContextMenuPolicy(Qt::ActionsContextMenu);
		setCentralWidget(view);

		min_z = max_z = seq_number = 0;

		create_actions();
		create_menus();
		create_tool_bars();

		setWindowTitle(tr("Diagram"));
		update_actions();
	}

private:

//-----------------------------------------------------------------------------

	void add_node_()
	{
		diagram_node *node = new diagram_node;
		node->set_text(tr("node %1").arg(seq_number + 1));
		setup_node(node);
	}

//-----------------------------------------------------------------------------

	void add_link_()
	{
		pair nodes = selected_node_pair();
		if (nodes == pair())
			return;

		scene->addItem(new diagram_link(nodes.first, nodes.second));
	}

//-----------------------------------------------------------------------------

	void del_()
	{
		QList <QGraphicsItem*> items = scene->selectedItems();
		QMutableListIterator <QGraphicsItem*> i(items);
		while (i.hasNext())
		{
			diagram_link *link = dynamic_cast <diagram_link*>(i.next());
			if (link)
			{
				delete link;
				i.remove();
			}
		}
		qDeleteAll(items);
	}

//-----------------------------------------------------------------------------

	void cut_()
	{
		diagram_node *node = selected_node();
		if (!node)
			return;

		copy();
		delete node;
	}

//-----------------------------------------------------------------------------

	void copy_()
	{
		diagram_node *node = selected_node();
		if (!node)
			return;

		QString str = QString("node %1 %2 %3 %4")
						.arg(node->text_color().name())
						.arg(node->outline_color().name())
						.arg(node->background_color().name())
						.arg(node->text());
		application::clipboard()->setText(str);
	}

//-----------------------------------------------------------------------------

	void paste_()
	{
		QString str = application::clipboard()->text();
		QStringList parts = str.split(" ");

		if (parts.count() >= 5 && parts.first() == "node")
		{
			diagram_node *node = new diagram_node;
			node->set_text(QStringList(parts.mid(4)).join(" "));
			node->set_text_color(QColor(parts[1]));
			node->set_outline_color(QColor(parts[2]));
			node->set_background_color(QColor(parts[3]));
			setup_node(node);
		}
	}

//-----------------------------------------------------------------------------

	void bring2front_() { set_z(++max_z); }
	void send2back_() { set_z(--min_z); }

//-----------------------------------------------------------------------------

	void properties_()
	{
		diagram_node *node = selected_node();
		diagram_link *link = selected_link();

		if (node)
		{
			properties_dialog dialog(node, this);
			dialog.exec();
		}
		else if (link)
		{
			QColor color = QColorDialog::getColor(link->color(), this);
			if (color.isValid())
				link->set_color(color);
		}
	}

//-----------------------------------------------------------------------------

	void update_actions_()
	{
		bool has_selection = !scene->selectedItems().isEmpty();
		bool is_node = (selected_node() != 0);
		bool is_node_pair = (selected_node_pair() != pair());

		cut_action         -> setEnabled(is_node);
		copy_action        -> setEnabled(is_node);
		add_link_action    -> setEnabled(is_node_pair);
		delete_action      -> setEnabled(has_selection);
		bring2front_action -> setEnabled(is_node);
		send2back_action   -> setEnabled(is_node);
		properties_action  -> setEnabled(is_node);

		foreach (QAction* action, view->actions())
			view->removeAction(action);

		foreach (QAction* action, edit_menu->actions())
		{
			if (action->isEnabled())
				view->addAction(action);
		}
	}

//-----------------------------------------------------------------------------

	void create_actions()
	{
		exit_action = new action(tr("E&xit"), this);
		exit_action->setShortcut(tr("Ctrl+Q"));
		exit_action->triggered.connect(close);

		add_node_action = new action(tr("Add &diagram_node"), this);
		add_node_action->setIcon(QIcon(":/diagram_images/node.png"));
		add_node_action->setShortcut(tr("Ctrl+N"));
		add_node_action->triggered.connect(add_node);

		add_link_action = new action(tr("Add &diagram_link"), this);
		add_link_action->setIcon(QIcon(":/diagram_images/link.png"));
		add_link_action->setShortcut(tr("Ctrl+L"));
		add_link_action->triggered.connect(add_link);

		delete_action = new action(tr("&Delete"), this);
		delete_action->setIcon(QIcon(":/diagram_images/delete.png"));
		delete_action->setShortcut(tr("Del"));
		delete_action->triggered.connect(del);

		cut_action = new action(tr("Cu&t"), this);
		cut_action->setIcon(QIcon(":/diagram_images/cut.png"));
		cut_action->setShortcut(tr("Ctrl+X"));
		cut_action->triggered.connect(cut);

		copy_action = new action(tr("&Copy"), this);
		copy_action->setIcon(QIcon(":/diagram_images/copy.png"));
		copy_action->setShortcut(tr("Ctrl+C"));
		copy_action->triggered.connect(copy);

		paste_action = new action(tr("&Paste"), this);
		paste_action->setIcon(QIcon(":/diagram_images/paste.png"));
		paste_action->setShortcut(tr("Ctrl+V"));
		paste_action->triggered.connect(paste);

		bring2front_action = new action(tr("Bring to &Front"), this);
		bring2front_action->setIcon(QIcon(":/diagram_images/bringtofront.png"));
		bring2front_action->triggered.connect(bring2front);

		send2back_action = new action(tr("&Send to Back"), this);
		send2back_action->setIcon(QIcon(":/diagram_images/sendtoback.png"));
		send2back_action->triggered.connect(send2back);

		properties_action = new action(tr("P&roperties..."), this);
		properties_action->triggered.connect(properties);
	}

//-----------------------------------------------------------------------------

	void create_menus()
	{
		file_menu = new menu(tr("&File"));
		*file_menu << exit_action;

		edit_menu = new menu(tr("&Edit"));
		*edit_menu << add_node_action << add_link_action << delete_action
		           << separator << cut_action << copy_action << paste_action
		           << separator << bring2front_action << send2back_action
		           << separator << properties_action;

		*menuBar() << file_menu << edit_menu;
	}

//-----------------------------------------------------------------------------

	void create_tool_bars()
	{
		edit_bar = new tool_bar(tr("Edit"));
		*edit_bar << add_node_action << add_link_action << delete_action
		          << separator << cut_action << copy_action << paste_action
		          << separator << bring2front_action << send2back_action;

		*this << edit_bar;
	}

//-----------------------------------------------------------------------------

	void set_z(int z)
	{
		diagram_node *node = selected_node();
		if (node)
			node->setZValue(z);
	}

//-----------------------------------------------------------------------------

	void setup_node(diagram_node *node)
	{
		node->setPos(QPoint(80 + (100 * (seq_number % 5)),
								  80 + (50 * ((seq_number / 5) % 7))));
		scene->addItem(node);
		++seq_number;

		scene->clearSelection();
		node->setSelected(true);
		bring2front();
	}

//-----------------------------------------------------------------------------

	diagram_node *selected_node() const
	{
		QList <QGraphicsItem*> items = scene->selectedItems();
		return items.count() == 1 ?
			dynamic_cast <diagram_node*>(items.first()) : 0;
	}

//-----------------------------------------------------------------------------

	diagram_link *selected_link() const
	{
		QList <QGraphicsItem*> items = scene->selectedItems();
		return items.count() == 1 ?
			dynamic_cast <diagram_link*>(items.first()) : 0;
	}

//-----------------------------------------------------------------------------

	pair selected_node_pair() const
	{
		QList <QGraphicsItem*> items = scene->selectedItems();
		if (items.count() == 2)
		{
			diagram_node *first = dynamic_cast <diagram_node*>(items.first());
			diagram_node *second = dynamic_cast <diagram_node*>(items.last());
			if (first && second)
				return pair(first, second);
		}
		return pair();
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // DIAGRAM_WINDOW_HPP
