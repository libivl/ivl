#ifndef DIAGRAM_PROPERTIES_DIALOG_HPP
#define DIAGRAM_PROPERTIES_DIALOG_HPP

#include "diagram_items.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class properties_dialog : public dialog,
	public method_binder <properties_dialog>
{
	typedef properties_dialog T;
	using method_binder <T>::bind;

	label     *x_label, *y_label;
	spin_box  *x_spin,  *y_spin;

	label       *text_label;
	line_edit   *text_edit;
	label       *text_color_label,  *line_color_label,  *back_color_label;
	label       *text_color_panel,  *line_color_panel,  *back_color_panel;
	push_button *text_color_button, *line_color_button, *back_color_button;

	dialog_button_box *button_box;

	diagram_node *node;
	QColor text_color;
	QColor line_color;
	QColor back_color;

	slot <void ()> accept, choose_text_color, choose_line_color, choose_back_color;

public:

//-----------------------------------------------------------------------------

	properties_dialog(diagram_node *node, QWidget *parent = 0) : dialog(parent)
	{
		bind(accept)            .to <&T::accept_>();
		bind(choose_text_color) .to <&T::choose_text_color_>();
		bind(choose_line_color) .to <&T::choose_line_color_>();
		bind(choose_back_color) .to <&T::choose_back_color_>();

		init_dialog();

		this->node = node;
		x_spin->setValue(int(node->x()));
		y_spin->setValue(int(node->y()));
		text_edit->setText(node->text());

		text_color = node->text_color();
		line_color = node->outline_color();
		back_color = node->background_color();

		update_color_label(text_color_panel, text_color);
		update_color_label(line_color_panel, line_color);
		update_color_label(back_color_panel, back_color);
	}

private:

//-----------------------------------------------------------------------------

	void accept_()
	{
		node->setPos(x_spin->value(), y_spin->value());
		node->set_text(text_edit->text());
		node->set_outline_color(line_color);
		node->set_background_color(back_color);
		node->set_text_color(text_color);
		node->update();
		dialog::accept();
	}

//-----------------------------------------------------------------------------

	void choose_text_color_() { choose_color(text_color_panel, &text_color); }
	void choose_line_color_() { choose_color(line_color_panel, &line_color); }
	void choose_back_color_() { choose_color(back_color_panel, &back_color); }

//-----------------------------------------------------------------------------

	void init_dialog()
	{
		x_label = new label("&X:");
		y_label = new label("&Y:");

		x_spin = make_spin();
		y_spin = make_spin();

//-----------------------------------------------------------------------------

		text_label = new label(tr("&Text:"));
		text_edit = new line_edit;

		text_color_label = new label(tr("Text Color:"));
		line_color_label = new label(tr("Outline Color:"));
		back_color_label = new label(tr("Background Color:"));

		text_color_button = new push_button(tr("Choose..."));
		line_color_button = new push_button(tr("Choose..."));
		back_color_button = new push_button(tr("Choose..."));

		text_color_panel = make_panel();
		line_color_panel = make_panel();
		back_color_panel = make_panel();

//-----------------------------------------------------------------------------

		button_box = new dialog_button_box(this);
		button_box->setOrientation(Qt::Horizontal);
		button_box->setStandardButtons(dialog_button_box::Cancel |
			dialog_button_box::NoButton | dialog_button_box::Ok);

//-----------------------------------------------------------------------------

#ifndef QT_NO_SHORTCUT
		x_label->setBuddy(x_spin);
		y_label->setBuddy(y_spin);
		text_label->setBuddy(text_edit);
#endif  // QT_NO_SHORTCUT

		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);

		text_color_button->clicked.connect(choose_text_color);
		line_color_button->clicked.connect(choose_line_color);
		back_color_button->clicked.connect(choose_back_color);

//-----------------------------------------------------------------------------

		group_box *position_box = new group_box(tr("Position"));
		row_layout *position_layout = new row_layout(position_box);
		*position_layout << stretch << x_label << x_spin
		                 << stretch << y_label << y_spin << stretch;

		group_box *attr_box = new group_box(tr("Attributes"));
		grid_layout *attr_layout = new grid_layout(attr_box);
		*attr_layout << tab        << col_stretch(1)         << nl
		             << text_label << col_span(2)(text_edit) << nl
		             << text_color_label << text_color_panel << text_color_button << nl
		             << line_color_label << line_color_panel << line_color_button << nl
		             << back_color_label << back_color_panel << back_color_button;

		col_layout* main_layout = new col_layout(this);
		*main_layout << position_box << attr_box << stretch << button_box;

		setWindowTitle(tr("Edit Properties"));
	}

//-----------------------------------------------------------------------------

	spin_box* make_spin()
	{
		spin_box* s = new spin_box();
		s->setAlignment(Qt::AlignRight);
		s->setMinimum(-1000);
		s->setMaximum(1000);
		return s;
	}

	label* make_panel()
	{
		label* p = new label;
		p->setFrameShape(QFrame::StyledPanel);
		p->setFrameShadow(QFrame::Raised);
		p->setScaledContents(true);
		return p;
	}

//-----------------------------------------------------------------------------

	void update_color_label(label *x_label, const QColor &color)
	{
		QPixmap pixmap(16, 16);
		pixmap.fill(color);
		x_label->setPixmap(pixmap);
	}

	void choose_color(label *x_label, QColor *color)
	{
		QColor new_color = QColorDialog::getColor(*color, this);
		if (new_color.isValid()) {
			*color = new_color;
			update_color_label(x_label, *color);
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // DIAGRAM_PROPERTIES_DIALOG_HPP
