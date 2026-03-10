#include <gtest.h>
#include "Binary_Tree.h"
#include "fixture.h"

//template<int N>
//class testbinary : public ::testing::Test {
//protected:
//	BINARY_TREE<double, int> a;
//	//BINARY_TREE<char, int>* pointer = &a;
//public:
//	testbinary() {
//		a = BINARY_TREE<double, int>();
//		a.Insert(5.0, 1);				
//		a.Insert(3.0, 2);
//		a.Insert(7.0, 3);
//		a.Insert(6.0, 4);
//		a.Insert(5.5, 5);
//		a.Insert(6.5, 6);
//		a.Insert(8.0, 7);
//		a.Insert(2.0, 8);
//		a.Insert(1.0, 9);
//		a.Insert(4.0, 10);
//		a.Insert(5.75, 11);
//	}
//	~testbinary() {};
//	void TestBody() override {};
//	void SetUp() override {};
//	void TearDown() override {};
//};

TEST(binary_tree, can_create)
{
	BINARY_TREE<char, int> a;
	//ASSERT_NO_THROW(BINARY_TREE<char, int> b);
}

TEST(binary_tree, can_insert)
{
	BINARY_TREE<char, int> a;
	a.Insert('A', 1);
	EXPECT_EQ(a.get_root()->data, std::make_pair('A', 1));
	//EXPECT_EQ(a.Find('A'), 1);
}

TEST(binary_tree, can_insert2)
{
	BINARY_TREE<char, int> a;
	a.Insert('B', 1);
	a.Insert('A', 1);
	a.Insert('D', 1);
	a.Insert('C', 1);
	EXPECT_EQ(a.get_root()->data, std::make_pair('B', 1));
	EXPECT_EQ(a.get_root()->left->data, std::make_pair('A', 1));
	EXPECT_EQ(a.get_root()->right->data, std::make_pair('D', 1));
	EXPECT_EQ(a.get_root()->right->left->data, std::make_pair('C', 1));

	//EXPECT_EQ(a.Find('A'), 1);
}

//TEST_F(testbinary, can_insert3)
//{
//	//testbinary t;
//	EXPECT_EQ(a.get_root()->data, std::make_pair('B', 2));
//	EXPECT_EQ(a.get_root()->left->data, std::make_pair('A', 1));
//	EXPECT_EQ(a.get_root()->right->data, std::make_pair('D', 4));
//	EXPECT_EQ(a.get_root()->right->left->data, std::make_pair('C', 3));
//
//	//EXPECT_EQ(a.Find('A'), 1);
//}

TEST_F(testtable<BINARY_TREE>, can_delete_get_root)
{
	a.Delete(5.0);
	EXPECT_EQ(a.get_root()->data.first, 5.5);
	EXPECT_EQ(a.get_root()->right->data.first, 7.0);
	EXPECT_EQ(a.get_root()->left->data.first, 3.0);
	EXPECT_EQ(a.get_root()->right->left->left->data.first, 5.75);
}

TEST_F(testbinary, can_delete2)
{
	a.Delete(6.0);
	EXPECT_EQ(a.get_root()->right->left->data.first, 6.5);
}

TEST_F(testbinary, can_delete3)
{
	a.Delete(7.0);
	EXPECT_EQ(a.get_root()->right->data.first, 8.0);
}

TEST_F(testbinary, can_delete4)
{
	a.Delete(7.0);
	EXPECT_EQ(a.get_root()->right->data.first, 8.0);
}

TEST_F(testbinary, can_find)
{
	EXPECT_EQ(a.Find(5.75), 11);
	EXPECT_EQ(a.Find(1), 9);
}


