#ifndef BOOLEAN_WINDOW_HPP
#define BOOLEAN_WINDOW_HPP

#include "boolean_model.hpp"
#include "boolean_parser.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class boolean_window : public widget, public method_binder <boolean_window>
{
	typedef boolean_window T;
	using method_binder <T>::bind;

	label         *exp_label;
	line_edit     *exp_edit;
	boolean_model *model;
	tree_view     *view;

	slot <void (const QString&)> expression_changed;

public:

//-----------------------------------------------------------------------------

	boolean_window()
	{
		bind(expression_changed).to <&T::expression_changed_>();

//-----------------------------------------------------------------------------

		exp_label = new label(tr("Boolean expression:"));
		exp_edit = new line_edit;

		model = new boolean_model(this);
		view = new tree_view;
		view->setModel(model);

		exp_edit->text_changed.connect(expression_changed);

		grid_layout *layout = new grid_layout(this);
		*layout << exp_label << exp_edit << nl
		        << col_span(2)(view);

		setWindowTitle(tr("Boolean Parser"));
	}

private:

//-----------------------------------------------------------------------------

	void expression_changed_(const QString &expr)
	{
		boolean_parser parser;
		node* root = parser(expr);
		model->set_root(root);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // BOOLEAN_WINDOW_HPP
