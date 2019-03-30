#include <ivl/ivl>
#include <ivl/qt>
#include <limits>

using namespace std;
using namespace ivl;
using namespace ivl::types;
using ivl::_;

//-----------------------------------------------------------------------------

void print(const char* c)
{
	cout << "string : " << c << endl;
}

void print(float x, const char* c)
{
	cout << "two args : " << x << " : " << c << endl;
}

template <typename T>
void print_array(unsigned n, const T* a)
{
	cout << "array : ";
	for (unsigned i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

//-----------------------------------------------------------------------------

struct scope
{
	typedef ret <int, int> R;

	       int i, j;
	static int a, b;

	scope(int i = a, int j = b) : i(i), j(j) { }

	       R    tup()  const { return (ivl::_, i, j); }
	static R    tub()        { return (ivl::_, a, b); }
	       void swap()       { std::swap(i, j); }
	static void zwap()       { std::swap(a, b); }
}
s(7, -1);

int a = 0, b = 3;
int scope::a = 10, scope::b = 13;

ret <int, int> tub()  { return (ivl::_, a, b); }
void           zwap() { std::swap(a, b); }

//-----------------------------------------------------------------------------

template <typename T>
void print_ref(T x, T &r, T const &s)
{
	T y = r;
	r = x;
	cout << "ref : " << y << " " << r << " " << s << endl;
}

template <typename T>
void print_ptr(T x, T *p, T const *q)
{
	T y = *p;
	*p = x;
	cout << "ptr : " << y << " " << *p << " " << *q << endl;
}

template <typename T, typename C>
void print_member(C& c, T x, T C::*p, T const C::*q)
{
	T y = c.*p;
	c.*p = x;
	cout << "member : " << y << " " << c.*p << " " << c.*q << endl;
}

template <typename T>
void print_ref_member(T x, T &r, T const &s)  // just like print_ref
{
	T y = r;
	r = x;
	cout << "ref_member : " << y << " " << r << " " << s << endl;
}

template <typename T>
void print_ptr_member(T x, T &r, T const &s)  // just like print_ref
{
	T y = r;
	r = x;
	cout << "ptr_member : " << y << " " << r << " " << s << endl;
}

//-----------------------------------------------------------------------------

template <typename R>
void print_function(R (*f)(), void (*g)())
{
	cout << "function : " << f();
	g();
	cout << " " << f() << endl;
}

template <typename C, typename R>
void print_method(C& c, R (C::*f)() const, void (C::*g)())
{
	cout << "method : " << (c.*f)();
	(c.*g)();
	cout << " " << (c.*f)() << endl;
}

template <typename R>
void print_ref_method(R (*f)(), void (*g)())  // just like print_function
{
	cout << "ref_method : " << f();
	g();
	cout << " " << f() << endl;
}

//-----------------------------------------------------------------------------

template <typename F, typename G>
void print_method_call(const F& f, const G& g)
{
	cout << "method call : " << f();
	g();
	cout << f() << endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	cout << endl;

	{
		// two args

		delegate <void (float, const char*)> f;

		f.bind <print, c_float <-359, 7>, c_string <'Hell','o, w','orld','!'> >();
		f(5, "hello");
		f(5);
		f();
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// long string

		typedef c_string <
			'Lore','m ip','sum ','dolo','r si','t am','et, ','cons','ecte','tur ','adip','isic','ing ','elit',', se','d do',' eiu','smod',' tem','por ','inci','didu','nt u','t la','bore',' et ','dolo','re m','agna',' ali','qua.',' Ut ','enim',' ad ','mini','m ve','niam',', qu','is n','ostr','ud e','xerc','itat','ion ','ulla','mco ','labo','ris ','nisi',' ut ','aliq','uip ','ex e','a co','mmod','o co','nseq','uat.',' Dui','s au','te i','rure',' dol','or i','n re','preh','ende','rit ','in v','olup','tate',' vel','it e','sse ','cill','um d','olor','e eu',' fug','iat ','null','a pa','riat','ur.'
		> lorem_ipsum;

		delegate <void (const char*)> f;

		f.bind <print, lorem_ipsum>();
		f();
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// int array

		typedef c_int_array <int, 10, 1, 2, 3, -5, 0, 5, 1, 9, 0, 15, 18, 19>
			arr;

		delegate <void (unsigned, const int*)> f;

		f.bind <print_array <int>, arr>();
		f(10);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// double array

		typedef c_array <
			double,
			c_double <30, 2>, c_double <-7>, c_double <>, c_double <3, -19>
		> arr;

		delegate <void (unsigned, const double*)> f;

		f.bind <print_array <double>, arr>();
		f(4);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// generic array

		typedef array <int> A;
		typedef c_array <
			A,
			c_struct <A (c_unsigned <4>, c_int <2>)>,
			c_struct <A (c_unsigned <6>, c_int_array <int, 6, 49, -52, 0, 8, -2, 1>)>
		> arr;

		delegate <void (unsigned, const A*)> f;

		f.bind <print_array <A>, arr>();
		f(2);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// reference

		typedef void S(int, int&, int const&);
		delegate <S> f, g;

		f.bind <
			print_ref <int>,
			c_ref       <int, ::a>,
			c_const_ref <int, ::b>
		>();

		g.bind <
			print_ref <int>,
			c_ref       <int, scope::a>,
			c_const_ref <int, scope::b>
		>();

		f(8);
		g(8);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// pointer

		delegate <void (int, int*, int const*)> f, g;

		f.bind <
			print_ptr <int>,
			c_ptr       <int, &::a>,
			c_const_ptr <int, &::b>
		>();

		g.bind <
			print_ptr <int>,
			c_ptr       <int, &scope::a>,
			c_const_ptr <int, &scope::b>
		>();

		f(4);
		g(14);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// pointer to member

		delegate <void (scope&, int, int scope::*, int const scope::*)> f;

		f.bind <
			print_member <int, scope>,
			c_member       <int, scope, &scope::i>,
			c_const_member <int, scope, &scope::j>
		>();

		scope s(-2, 9);
		f(s, 5);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// object ref + pointer to member

		delegate <void (int, int&, int const&)> f;

		f.bind <
			print_ref_member <int>,
			c_ref_member       <int, scope, ::s, &scope::i>,
			c_const_ref_member <int, scope, ::s, &scope::j>
		>();

		f(-3);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// object pointer + pointer to member

		delegate <void (int, int&, int const&)> f;

		f.bind <
			print_ptr_member <int>,
			c_ptr_member       <int, scope, &::s, &scope::i>,
			c_const_ptr_member <int, scope, &::s, &scope::j>
		>();

		f(-3);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// pointer to function

		typedef ret <int, int> R;
		delegate <void (R (*)(), void (*)())> f, g;

		f.bind <
			print_function <R>,
			c_sig <R ()>   ::function < ::tub>,
			c_sig <void ()>::function < ::zwap>  // <:: symbol reserved
		>();

		g.bind <
			print_function <R>,
			c_sig <R ()>   ::function <&scope::tub>,
			c_sig <void ()>::function <&scope::zwap>
		>();

		f();
		g();
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// pointer to method

		typedef ret <int, int> R;
		delegate <void (scope&, R (scope::*)() const, void (scope::*)())> f;

		f.bind <
			print_method <scope, R>,
			c_sig <R ()>   ::const_method <scope, &scope::tup>,
			c_sig <void ()>::method       <scope, &scope::swap>
		>();

		scope s(-2, 9);
		f(s);
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// object ref + pointer to method
		// or, new instance + pointer to method

		typedef ret <int, int> R;
		delegate <void (R (*)(), void (*)())> f, g;

		f.bind <
			print_ref_method <R>,
			c_sig <R ()>   ::const_ref_method <scope, ::s, &scope::tup>,
			c_sig <void ()>::ref_method       <scope, ::s, &scope::swap>
		>();

		g.bind <
			print_ref_method <R>,
			c_sig <R ()>   ::fun_method <scope,      &scope::tup>,
			c_sig <void ()>::ref_method  <scope, ::s, &scope::swap>
		>();

		f();
		g();
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		// call by object ref + pointer to method
		// or, by new instance + pointer to method

		typedef ret <int, int> R;
		typedef void S(R (*)(), void (*)());

		typedef c_sig <void ()>::ref_call       <scope, ::s, &scope::swap> s_swap;
		typedef c_sig <R ()>   ::const_ref_call <scope, ::s, &scope::tup>  s_tup;
		typedef c_sig <R ()>   ::fun_call       <scope,      &scope::tup>  scope_tup;

		print_method_call(s_tup(),     s_swap());
		print_method_call(scope_tup(), s_swap());
		cout << endl;
	}

}
