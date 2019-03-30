#ifndef TRACK_DELEGATE_HPP
#define TRACK_DELEGATE_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class track_delegate : public item_delegate,
	public method_binder <track_delegate>
{
	typedef track_delegate T;
	using method_binder <T>::bind;

	int duration_column;
	mutable time_edit *edit;  // TODO: sender

	slot <void ()> commit_close_editor;

public:

//-----------------------------------------------------------------------------

	track_delegate(int duration_column, QObject *parent = 0)
		: item_delegate(parent), duration_column(duration_column)
	{
		bind(commit_close_editor).to <&T::commit_close_editor_>();
	}

//-----------------------------------------------------------------------------

	void paint(QPainter* painter, const QStyleOptionViewItem& option,
	           const QModelIndex& index) const
	{
		if (index.column() != duration_column)
			return item_delegate::paint(painter, option, index);

		int secs = get_data(index).toInt();
		QString text = QString("%1:%2").arg(secs / 60, 2, 10, QChar('0'))
		                               .arg(secs % 60, 2, 10, QChar('0'));

		QStyleOptionViewItem opt = option;
		opt.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

		drawDisplay(painter, opt, opt.rect, text);
		drawFocus  (painter, opt, opt.rect);
	}

//-----------------------------------------------------------------------------

	QWidget *createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	                      const QModelIndex& index) const
	{
		if (index.column() != duration_column)
			return item_delegate::createEditor(parent, option, index);

		edit = new time_edit(parent);
		edit->setDisplayFormat("mm:ss");
		edit->editing_finished.connect(commit_close_editor);
		return edit;
	}

//-----------------------------------------------------------------------------

	void setEditorData(QWidget* editor, const QModelIndex& index) const
	{
		if (index.column() != duration_column)
			return item_delegate::setEditorData(editor, index);

		int secs = get_data(index).toInt();
		time_edit* edit = dynamic_cast <time_edit*>(editor);
		edit->setTime(QTime(0, secs / 60, secs % 60));
	}

//-----------------------------------------------------------------------------

	void setModelData(QWidget *editor, QAbstractItemModel *model,
	                  const QModelIndex &index) const
	{
		if (index.column() != duration_column)
			return item_delegate::setModelData(editor, model, index);

		time_edit* edit = dynamic_cast <time_edit*>(editor);
		QTime time = edit->time();
		int secs = (time.minute() * 60) + time.second();
		model->setData(index, secs);
	}

private:

//-----------------------------------------------------------------------------

	void commit_close_editor_()
	{
// 		time_edit* editor = dynamic_cast <time_edit*>(sender());  // TODO: sender
		emit commit_data(edit);
		emit close_editor(edit);
	}

//-----------------------------------------------------------------------------

	QVariant get_data(const QModelIndex &index) const
	{
		return index.model()->data(index, Qt::DisplayRole);
	}
};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // TRACK_DELEGATE_HPP
