#pragma once
#include <gtest.h>
#include <basetable.h>
#include "Binary_Tree.h"
#include "AVL_tree.h"
template <typename T1, typename T2, template<typename, typename> class Table >
class testtable : public ::testing::Test {
protected:
	Table<T1, T2> a;
public:
	testtable() {
		a = Table<T1, T2>();
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
	~testtable() {};
	void TestBody() override {};
	void SetUp() override 
	{

	};
	void TearDown() override {};
};
class BynaryTest : public testtable<double, int, BINARY_TREE> {};
class AvlTest: public testtable<double, int, AVL_TREE> {};
//class RedBlackTest : public testtable<double, int, RED_BLACK_TREE> {};
