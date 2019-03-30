#include <ivl/ivl>
#include <ivl/qt>

using namespace std;
using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

void g3(int i, const char* c, const array <int>& a)
{
	cout << "g3 : " << i << " : " << c << " : " << a << endl;
}

void h4(int i, const char* c, const array <int>& a, double d)
{
	cout << "h4 : " << i << " : " << c << " : " << a << " : " << d << endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	{
		signal <void (int)> F1;
		signal <void (int, const char*)> F2;
		signal <void (int, const char*, const array <int>&)> F3;
		slot   <void (int, const char*, const array <int>&)> G3;
		signal <void (int, const char*, const array <int>&, double)> F4;
		signal <defaults <
			void (int, const char*, const array <int>&, double),
			c_minus <c_int <8> >, c_string <'lala'>,
			c_struct <array <int> (c_int <3>, c_int_array <int, 3, -5, -6, -7>)>,
			c_double <271, -2>
		> > H4;

		G3.bind <g3>();
		H4.bind <h4>();

		F1.connect(G3);
		F2.connect(G3);
		F3.connect(G3);
		F4.connect(G3);
		H4.connect(G3);

		F1(5);
		F2(5, "hello");
		F3(5, "hello", arr(1,2,3));
		F4(5, "hello", arr(1,2,4), 3.14);
		cout << endl;

		G3.bind <
			g3, c_int <12>, c_string <'koko'>,
			c_struct <array <int> (c_int <2>, c_int_array <int, 2, 0, 9>)>
		>();

		F1(5);
		F2(5, "hello");
		F3(5, "hello", arr(1,2,3));
		F4(5, "hello", arr(1,2,4), 3.14);
		cout << endl;

		H4(5, "hello", arr(1,2,4), 3.14);
		H4(5, "hello", arr(1,2,3));
		H4(5, "hello");
		H4(5);
		H4();
		cout << endl;
	}

//-----------------------------------------------------------------------------

}
