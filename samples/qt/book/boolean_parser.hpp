#ifndef BOOLEAN_PARSER_HPP
#define BOOLEAN_PARSER_HPP

#include "boolean_node.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class boolean_parser
{
	QString expr;
	int pos;

public:

//-----------------------------------------------------------------------------

	node* operator()(const QString& expr)
	{
		this->expr = expr;
		this->expr.replace(" ", "");
		pos = 0;

		node* n = new root_node;
		add_child(n, parse_or());
		return n;
	}

private:

//-----------------------------------------------------------------------------

	node* parse_or()
	{
		node* child = parse_and();
		if (!match_token("||"))
			return child;

		node* n = new or_node;
		add_child(n, child);
		while (match_token("||"))
		{
			add_token <operator_>(n, "||");
			add_child(n, parse_and());
		}
		return n;
	}

//-----------------------------------------------------------------------------

	node* parse_and()
	{
		node* child = parse_not();
		if (!match_token("&&"))
			return child;

		node* n = new and_node;
		add_child(n, child);
		while (match_token("&&"))
		{
			add_token <operator_>(n, "&&");
			add_child(n, parse_not());
		}
		return n;
	}

//-----------------------------------------------------------------------------

	node* parse_not()
	{
		if (!match_token("!"))
			return parse_atom();

		node* n = new not_node;
		while (match_token("!"))
			add_token <operator_>(n, "!");
		add_child(n, parse_atom());
		return n;
	}

//-----------------------------------------------------------------------------

	node* parse_atom()
	{
		if (!match_token("("))
			return parse_identifier();

		node* n = new atom_node;
		add_token <punctuator>(n, "(");
		add_child(n, parse_or());
		add_token <punctuator>(n, ")");
		return n;
	}

//-----------------------------------------------------------------------------

	node* parse_identifier()
	{
		int from = pos;
		while (pos < expr.length() && expr[pos].isLetterOrNumber())
			++pos;

		if (pos > from)
			return new identifier_node(expr.mid(from, pos - from));

		return 0;
	}

//-----------------------------------------------------------------------------

	void add_child(node* parent, node* child)
	{
		if (child)
		{
			parent->children += child;
			parent->str += child->str;
			child->parent = parent;
		}
	}

//-----------------------------------------------------------------------------

	template <node_type T>
	void add_token(node* parent, const QString &str)
	{
		if (match_token(str))
		{
			add_child(parent, new typed_node <T>(str));
			pos += str.length();
		}
	}

//-----------------------------------------------------------------------------

	bool match_token(const QString &str) const
	{
		return expr.mid(pos, str.length()) == str;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // BOOLEAN_PARSER_HPP
