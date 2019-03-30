#ifndef BOOLEAN_NODE_HPP
#define BOOLEAN_NODE_HPP

#include <vector>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

enum node_type { base = 0, root, or_, and_, not_, atom,
                 identifier, operator_, punctuator };

template <node_type T = base>
struct typed_node;

//-----------------------------------------------------------------------------

template <>
struct typed_node <>
{
	QString str;
	typed_node* parent;
	QList <typed_node*> children;

//-----------------------------------------------------------------------------

	typed_node(const QString& s = "") : str(s), parent(0) { }
	~typed_node() { qDeleteAll(children); }

	virtual node_type type() { return base; }
};

//-----------------------------------------------------------------------------

template <node_type T>
struct typed_node : public typed_node <>
{
	typed_node(const QString& s = "") : typed_node <>(s) { }
	node_type type() { return T; }
};

//-----------------------------------------------------------------------------

typedef typed_node <>           node;
typedef typed_node <root>       root_node;
typedef typed_node <or_>        or_node;
typedef typed_node <and_>       and_node;
typedef typed_node <not_>       not_node;
typedef typed_node <atom>       atom_node;
typedef typed_node <identifier> identifier_node;
typedef typed_node <operator_>  operator_node;
typedef typed_node <punctuator> punctuator_node;

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // BOOLEAN_NODE_HPP
