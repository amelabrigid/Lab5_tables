#include "polinom.h"
#include "arithmetic.h"
/**int main()
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "5x1y1z1+10x2y2z2";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("a+b");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	//EXPECT_EQ(tmp3, X.Calculate());
	Polinom res = X.Calculate();
	if (tmp3 == res)
	{
		cout << "Result true" << endl;
		return true;
	}
	else
	{
		cout << "Result false" << endl;
		return false;
	}
}
*/