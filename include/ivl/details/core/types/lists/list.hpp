/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

/*
Listie: an implementation of the `templist` template language of C++.

Declarations:

The syntax of a list _<n1, n2, ..> is represented as a linked list of
nodes, using node<n1, node<n2, ... > > with the terminator node<null, null>.
Evaluation errors are defined as nat.

Lists are declared as _<n1, n2, ..> or list<n1, n2, ..>.
The declaration ::type of a list is the result of the program.
The declaration ::list of a list is the list recursively converted to node<>.

Evaluation:

Manual evaluation of a list L is done by lists::eval<L>::type, and
when the list is in node<> form it can also be done by lists::run<L>::type.
Conversion to node<> form is done by lists::model<L>::type.

Lists are evaluated recursively, one step at a time.
The execution specifies:

1. (command args...):			runs the command
2. ((lambda ..) args...):		runs lambda command
3. ((define ..) args...):		runs define command
4. (atom|list ...):			evaluates all sublists, if any, 
							and then tests again for any of the above patterns

The lambda and define patterns are actually converted to synonym patterns of
the form (1.)
(lambda (vars) (body) args)
(define f (body) args)

These forms are equally legal calls of lambda and define which are implemented
as commands in the same way as other commands are.

Commands:

Any command of listie has two options.
The first option is the number of parameters. 
This can be either a number or variable.

Declaring a fixed-parameter command for listie is straightforward.
Any template class mapper (that inherits templateclassid) is a valid listie
command.
Any template class of N arguments can be used as a command by defining 
a template-mapper with the t1<>, t2<>, ..., tn<> ivl helper classes.

A N-argument listie command only evaluates when its arguments are
at least N. If less the command does simply not evaluate 
[ could be swapped with an option, to not evaluate or return nat ].

A variable-size command is also declared by a template-mappers
using the tls<> helper-class.
The template class that is used to evaluate the command takes a
single argument L which is the list of all arguments.
Such commands always execute.

The second option of a listie command is auto-evaluation.
Normally a listie command does a single step of evaluating each one of 
its arguments before calling the actual template-mapper command.
This is done automatically.

However some commands such as cond, lambda and define need
to stall, suspend or manually handle the evaluation flow.
In these cases auto-evaluation needs to be disabled for the
actual command. 
This is done by creating a struct that inherits the template-mapper
and the struct lists::lazy_args_id.

Lambda and Define:

((lambda (vars) (body)) args)

((define f (body)) args)
The define command, replicates itself to ensure recursion by creating
a replicated-body, and then does simply an evaluation of 
	(replicated-body args)
making it possible to use define without a following lambda.

*/

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_LIST_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_LIST_HPP

//-----------------------------------------------------------------------------

#include "impl/list.hpp"
#include "impl/list_details.hpp"
#include "impl/seq.hpp"
#include "impl/types.hpp"
#include "impl/tools/list_tools.hpp"
#include "impl/tools/conses.hpp"
#include "impl/tools/syntax.hpp"
#include "impl/tools/substitution.hpp"
//#include "impl/preproc/preproc.hpp"
//#include "impl/preproc/syntaxrules.hpp"
#include "impl/eval.hpp"

//-----------------------------------------------------------------------------

#include "functions/syntaxrules.hpp"
#include "functions/set.hpp"
#include "functions/lambda.hpp"
//#include "functions/letrec.hpp"
#include "functions/funrules.hpp"
#include "functions/cases.hpp"
#include "functions/cond.hpp"

#include "functions/primitive.hpp"

//-----------------------------------------------------------------------------

#include "scheme/macro_start.hpp"

#include "scheme/constants.hpp"
#include "scheme/identifiers.hpp"
#include "scheme/scheme3.hpp"
#include "scheme/sr_tests.hpp"


#include "scheme/macro_end.hpp"

//-----------------------------------------------------------------------------


#endif // IVL_CORE_DETAILS_TYPES_LISTS_LIST_HPP
