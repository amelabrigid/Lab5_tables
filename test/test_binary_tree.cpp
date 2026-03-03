#include <gtest.h>
#include "Binary_Tree.h"

//template<int N>
class testbinary : public ::testing::Test {
protected:
	BINARY_TREE<char, int> a;

public:
	void SetUp() {

	}

	void TearDown() {

	}
};

TEST(binary_tree, can_create)
{
	BINARY_TREE<char, int> a;
	//ASSERT_NO_THROW(BINARY_TREE<char, int> b);
}

TEST(binary_tree, can_insert)
{
	BINARY_TREE<char, int> a;
	a.Insert('A', 1);
	EXPECT_EQ(a.root->data, std::make_pair('A', 1));
	//EXPECT_EQ(a.Find('A'), 1);
}

TEST(binary_tree, can_insert2)
{
	BINARY_TREE<char, int> a;
	a.Insert('B', 1);
	a.Insert('A', 1);
	a.Insert('D', 1);
	a.Insert('C', 1);
	EXPECT_EQ(a.root->data, std::make_pair('B', 1));
	EXPECT_EQ(a.root->left->data, std::make_pair('A', 1));
	EXPECT_EQ(a.root->right->data, std::make_pair('D', 1));
	EXPECT_EQ(a.root->right->left->data, std::make_pair('C', 1));

	//EXPECT_EQ(a.Find('A'), 1);
}
