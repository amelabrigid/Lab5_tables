#pragma once
#include <gtest.h>
#include <basetable.h>

template <template<double, int> class table>
class testtable : public ::testing::Test {
protected:
	table<double, int> a;
	//BINARY_TREE<char, int>* pointer = &a;
public:
	testtable() {
		a = table();
		a.Insert(5.0, 1);
		a.Insert(3.0, 2);
		a.Insert(7.0, 3);
		a.Insert(6.0, 4);
		a.Insert(5.5, 5);
		a.Insert(6.5, 6);
		a.Insert(8.0, 7);
		a.Insert(2.0, 8);
		a.Insert(1.0, 9);
		a.Insert(4.0, 10);
		a.Insert(5.75, 11);
	}
	~testbinary() {};
	void TestBody() override {};
	void SetUp() override {};
	void TearDown() override {};
};