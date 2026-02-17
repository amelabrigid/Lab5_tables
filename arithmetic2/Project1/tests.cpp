#include "polinom.h"
#include "arithmetic.h"
#include "gtest.h"

TEST(str, tets1)
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
	EXPECT_EQ(tmp3, X.Calculate());
}
TEST(str, tets2)
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "5x1y1z1-10x2y2z2";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("a-b");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	Polinom res = X.Calculate();
	EXPECT_EQ(tmp3, res);
}
TEST(str, tets3)
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "50x3y3z3";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("a*b");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	EXPECT_EQ(tmp3, X.Calculate());
}
TEST(str, tets4)
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "50x3y3z3+5x1y1z1";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("a*b+a");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	EXPECT_EQ(tmp3, X.Calculate());
}
TEST(str, tets5)
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "25x2y2z2+50x3y3z3";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("(a+b)*a");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	Polinom res = X.Calculate();
	EXPECT_EQ(tmp3,res );
}
TEST(str, tets6)
{
	string str1 = "5x1y1z1";
	string str2 = "10x2y2z2";
	string str3 = "50x1y1z1";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("a*10");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	Polinom res = X.Calculate();
	EXPECT_EQ(tmp3, res);
}
TEST(str, tets7)
{
	string str1 = "5";
	string str2 = "10";
	string str3 = "10";
	Polinom tmp1(str1);
	Polinom tmp2(str2);
	Polinom tmp3(str3);
	map<char, Polinom> values =
	{
		{'a',tmp1},{'b', tmp2}
	};
	TArithmeticExpression X("5+5");
	X.Parse2();
	X.ToPostfix();
	X.Variable(values);
	Polinom res = X.Calculate();
	EXPECT_EQ(tmp3, res);
}