#include <ivl/ivl>

using namespace std;
using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

struct A { void operator()() { cout << "A "; } };
struct B : public A { void operator()() { cout << "B "; } };

A aa;
B bb;

int a[6] = {4, 9, -2, 0, 1, 7};

int main(int argc, char *argv[])
{
	{
		cout << c_float <359, 1>() << endl;
		cout << c_float <-359, 7>() << endl;
		cout << c_float <359, -7>() << endl;
		cout << endl;

		cout << c_norm_double <359, 1>() << endl;
		cout << c_norm_double <-359, 7>() << endl;
		cout << c_norm_double <359, -7>() << endl;
		cout << endl;

		cout << c_norm_float  <359, -50>() << endl;
		cout << c_norm_double <359, -50>() << endl;
		cout << endl;

		cout << c_struct <array <int> (c_unsigned <12>, c_int <-4>)>() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		const bool big = multi_char::big();
		cout << (big ? "big" : "little") << " endian" << endl;
		cout << "abcd : " << multi_char('abcd') << endl;
		cout << "abc  : " << multi_char('abc') << endl;
		cout << "ab   : " << multi_char('ab') << endl;
		cout << "a    : " << multi_char('a') << endl;
		cout << "     : " << multi_char(0) << endl;
		cout << "abcd : " << c_multi_char <'abcd'>() << endl;
		cout << "abc  : " << c_multi_char <'abc'>() << endl;
		cout << "ab   : " << c_multi_char <'ab'>() << endl;
		cout << "a    : " << c_multi_char <'a'>() << endl;
		cout << "     : " << c_multi_char <0>() << endl;
		cout << endl;

		cout << c_string <'Hell','o, w','orld','!'>() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		typedef c_string <
			'Lore','m ip','sum ','dolo','r si','t am','et, ','cons','ecte','tur ','adip','isic','ing ','elit',', se','d do',' eiu','smod',' tem','por ','inci','didu','nt u','t la','bore',' et ','dolo','re m','agna',' ali','qua.',' Ut ','enim',' ad ','mini','m ve','niam',', qu','is n','ostr','ud e','xerc','itat','ion ','ulla','mco ','labo','ris ','nisi',' ut ','aliq','uip ','ex e','a co','mmod','o co','nseq','uat.',' Dui','s au','te i','rure',' dol','or i','n re','preh','ende','rit ','in v','olup','tate',' vel','it e','sse ','cill','um d','olor','e eu',' fug','iat ','null','a pa','riat','ur.'
		> str;
		cout << str() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "inf = " << c_inf <>() << endl;
		cout << "-inf = " << c_minus <c_inf <> >() << endl;
		cout << "nan = " << c_nan <>() << endl;
		cout << "e = " << c_e <>() << endl;
		cout << "pi = " << c_pi <>() << endl;
		cout << "i = " << c_i <>() << endl;
		cout << "j = " << c_j <>() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		array <double>* a = c_new <array <double> (c_unsigned <4>, c_int <-18>)>();
		cout << *a << endl;
		cout << "at : " << c_at <int, ::a, c_int <2> >() << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
		cout << "sizeof : " << c_sizeof <array <double> >() << endl;

		cout << "static_cast : ";
		aa(); bb();
		c_static_cast <A, B, bb>()()();
		cout << endl;
		cout << endl;
	}

//-----------------------------------------------------------------------------

	{
/*		using delegate_details::at;
		using delegate_details::tuple;
		typedef tuple <c_inf <>, c_pi <>, c_i <> > N;

		cout << "N <0> : " << typename at <0, N>::type() << endl;
		cout << "N <1> : " << typename at <1, N>::type() << endl;
		cout << "N <2> : " << typename at <2, N>::type() << endl;
		cout << endl;*/
	}

}
