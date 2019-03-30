#ifndef BOOLEAN_MODEL_HPP
#define BOOLEAN_MODEL_HPP

#include "boolean_parser.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class boolean_model : public abstract_item_model
{
	node* root;

public:

//-----------------------------------------------------------------------------

	boolean_model(QObject *parent = 0) : abstract_item_model(parent), root(0) { }

	~boolean_model() { delete root; }

	void set_root(node* node)
	{
		delete root;
		root = node;
		reset();
	}

	QModelIndex index(int row, int column, const QModelIndex& parent_idx) const
	{
		if (!root || row < 0 || column < 0)
			return QModelIndex();
		node* parent = index2node(parent_idx);
		node* child = parent->children.value(row);
		if (!child)
			return QModelIndex();
		return createIndex(row, column, child);
	}

//-----------------------------------------------------------------------------

	QModelIndex parent(const QModelIndex& child) const
	{
		node* n = index2node(child);
		if (!n)
			return QModelIndex();
		node* parent = n->parent;
		if (!parent)
			return QModelIndex();
		node* grand_parent = parent->parent;
		if (!grand_parent)
			return QModelIndex();

		int row = grand_parent->children.indexOf(parent);
		return createIndex(row, 0, parent);
	}

//-----------------------------------------------------------------------------

	int rowCount(const QModelIndex& parent_idx) const
	{
		if (parent_idx.column() > 0)
			return 0;
		node* parent = index2node(parent_idx);
		if (!parent)
			return 0;
		return parent->children.count();
	}

	int columnCount(const QModelIndex&) const { return 2; }

//-----------------------------------------------------------------------------

	QVariant data(const QModelIndex& index, int role) const
	{
		if (role != Qt::DisplayRole)
			return QVariant();

		node* n = index2node(index);
		if (!n)
			return QVariant();

		static const char* name[] = {
			"unknown", "root", "OR expression", "AND expression", "NOT expression",
			"atom", "identifier", "operator", "punctuator"
		};
		if (index.column() == 0)
			return tr(name[n->type()]);
		else if (index.column() == 1)
			return n->str;

		return QVariant();
	}

//-----------------------------------------------------------------------------

	QVariant headerData(int section, Qt::Orientation orientation, int role)
		const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		{
			if (section == 0)
				return tr("node");
			else if (section == 1)
				return tr("Value");
		}
		return QVariant();
	}

private:

//-----------------------------------------------------------------------------

	node* index2node(const QModelIndex& index) const
	{
		return index.isValid() ?
			static_cast <node*>(index.internalPointer()) : root;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // BOOLEAN_MODEL_HPP
