#include <gtest.h>
#include "fixture.h"
#include "RED_BLACK_TREE.h"

TEST(red_black_tree, can_create)
{
	RED_BLACK_TREE<char, int> a;
	//ASSERT_NO_THROW(BINARY_TREE<char, int> b);
}

TEST(red_black_tree, can_insert)
{
	RED_BLACK_TREE<char, int> a;
	a.Insert('A', 1);
	EXPECT_EQ(a.get_root()->data, std::make_pair('A', 1));
	//EXPECT_EQ(a.Find('A'), 1);
}

TEST(red_black_tree, can_insert2)
{
	RED_BLACK_TREE<char, int> a;
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
