#ifndef COLOR_LIST_HPP
#define COLOR_LIST_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class color_list : public dialog, public method_binder <color_list>
{
	typedef color_list T;
	using method_binder <T>::bind;

	string_list_model *source_model;
	sort_filter_proxy_model *proxy_model;
	list_view *view;
	label *filter_label;
	label *syntax_label;
	line_edit *filter_edit;
	combo_box *syntax_box;

	slot <void()> reapply_filter;

public:

//-----------------------------------------------------------------------------

	color_list(QWidget *parent = 0) : dialog(parent)
	{
		bind(reapply_filter).to <&T::reapply_filter_>();

//-----------------------------------------------------------------------------

		source_model = new string_list_model(this);
		source_model->setStringList(QColor::colorNames());

		proxy_model = new sort_filter_proxy_model(this);
		proxy_model->setSourceModel(source_model);
		proxy_model->setFilterKeyColumn(0);

		view = new list_view;
		view->setModel(proxy_model);
		view->setEditTriggers(QAbstractItemView::NoEditTriggers);

		filter_label = new label(tr("&Filter:"));
		filter_edit = new line_edit;
		filter_label->setBuddy(filter_edit);

		syntax_label = new label(tr("&Pattern syntax:"));
		syntax_box = new combo_box;
		syntax_box->addItem(tr("Regular expression"), QRegExp::RegExp);  // TODO: <<
		syntax_box->addItem(tr("Wildcard"), QRegExp::Wildcard);
		syntax_box->addItem(tr("Fixed string"), QRegExp::FixedString);
		syntax_label->setBuddy(syntax_box);

		filter_edit->text_changed.connect(reapply_filter);
		syntax_box->current_index_changed_0.connect(reapply_filter);  // TODO: overloading

//-----------------------------------------------------------------------------

		grid_layout *layout = new grid_layout(this);
		*layout << col_span(2)(view)           << nl
		        << filter_label << filter_edit << nl
		        << syntax_label << syntax_box;

		setWindowTitle(tr("Color Names"));
	}

private:

//-----------------------------------------------------------------------------

	void reapply_filter_()
	{
		QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax
			(syntax_box->itemData(syntax_box->currentIndex()).toInt());
		QRegExp regExp(filter_edit->text(), Qt::CaseInsensitive, syntax);
		proxy_model->setFilterRegExp(regExp);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // COLOR_LIST_HPP
