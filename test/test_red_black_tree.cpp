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
	a.Insert('E', 1);
	a.Insert('A', 2);
	a.Insert('B', 3);
	EXPECT_EQ(a.get_root()->right->data.first, 'E');
	EXPECT_EQ(a.get_root()->left->data.first, 'A');
	EXPECT_EQ(a.get_root()->data.first, 'B');
	EXPECT_EQ(a.get_root()->color, 1);
	EXPECT_EQ(a.get_root()->left->color, 0);
	EXPECT_EQ(a.get_root()->right->color, 0);
}

TEST(red_black_tree, can_insert3)
{
	RED_BLACK_TREE<char, int> a;
	a.Insert('E', 1);
	a.Insert('A', 2);
	a.Insert('B', 3);
	a.Insert('C', 4);
	EXPECT_EQ(a.get_root()->right->left->data.first, 'C');				//					B black
	EXPECT_EQ(a.get_root()->right->data.first, 'E');				//				A black			E black	
	EXPECT_EQ(a.get_root()->left->data.first, 'A');				//								C red	
	EXPECT_EQ(a.get_root()->data.first, 'B');
	EXPECT_EQ(a.get_root()->color, 1);
	EXPECT_EQ(a.get_root()->left->color, 1);
	EXPECT_EQ(a.get_root()->right->color, 1);
	EXPECT_EQ(a.get_root()->right->left->color, 0);
}

TEST(red_black_tree, can_insert4)
{
	RED_BLACK_TREE<char, int> a;
	a.Insert('E', 1);
	a.Insert('A', 2);
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	EXPECT_EQ(a.get_root()->right->right->data.first, 'E');
	EXPECT_EQ(a.get_root()->right->left->data.first, 'C');		//									B black
	EXPECT_EQ(a.get_root()->right->data.first, 'D');			//						A black					D black			
	EXPECT_EQ(a.get_root()->left->data.first, 'A');				//											C red		E red
	EXPECT_EQ(a.get_root()->data.first, 'B');
	EXPECT_EQ(a.get_root()->color, 1);
	EXPECT_EQ(a.get_root()->left->color, 1);
	EXPECT_EQ(a.get_root()->right->color, 1);
	EXPECT_EQ(a.get_root()->right->left->color, 0);
	EXPECT_EQ(a.get_root()->right->right->color, 0);
}

TEST(red_black_tree, can_insert5)
{
	RED_BLACK_TREE<char, int> a;								//									B black
	a.Insert('E', 1);											//						A black					D black
	a.Insert('A', 2);											//											C red		E red
	a.Insert('B', 3);											
	a.Insert('C', 4);
	a.Insert('D', 5);
	EXPECT_EQ(a.get_root()->right->right->data.first, 'E');
	EXPECT_EQ(a.get_root()->right->left->data.first, 'C');											//B1
	EXPECT_EQ(a.get_root()->right->data.first, 'D');
	EXPECT_EQ(a.get_root()->left->data.first, 'A');
	EXPECT_EQ(a.get_root()->data.first, 'B');
	EXPECT_EQ(a.get_root()->color, 1);
	EXPECT_EQ(a.get_root()->left->color, 1);
	EXPECT_EQ(a.get_root()->right->color, 1);
	EXPECT_EQ(a.get_root()->right->left->color, 0);
	EXPECT_EQ(a.get_root()->right->right->color, 0);
}


TEST(red_black_tree, can_find)
{
	RED_BLACK_TREE<char, int> a;
	a.Insert('E', 1);
	a.Insert('A', 2);
	a.Insert('B', 3);
	a.Insert('C', 4);
	EXPECT_EQ(a.Find('C'), 4);
}


TEST(red_black_tree, can_delete)
{
	RED_BLACK_TREE<char, int> a;
	a.Insert('E', 1);
	a.Insert('A', 2);
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	a.Delete('C');
	EXPECT_EQ(a.get_root()->right->data.first, 'D');
}


TEST(red_black_tree, can_delete2)
{
	RED_BLACK_TREE<char, int> a;								//									B black
	a.Insert('E', 1);											//						A black					D black
	a.Insert('A', 2);											//											C red		E red
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	a.Delete('D');
	EXPECT_EQ(a.get_root()->right->data.first, 'D');
}


TEST(red_black_tree, right_turn)
{
	RED_BLACK_TREE<char, int> a;								//									B black
	a.Insert('E', 1);											//						A black					D black
	a.Insert('A', 2);											//											C red		E red
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	a.right_turn(a.get_root());
	EXPECT_EQ('A', a.get_root()->data.first);
	EXPECT_EQ('B', a.get_root()->right->data.first);
	EXPECT_EQ('D', a.get_root()->right->right->data.first);
}

TEST(red_black_tree, left_turn)
{
	RED_BLACK_TREE<char, int> a;								//									B black
	a.Insert('E', 1);											//						A black					D black
	a.Insert('A', 2);											//											C red		E red
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	a.left_turn(a.get_root());
	EXPECT_EQ('D', a.get_root()->data.first);
	EXPECT_EQ('B', a.get_root()->left->data.first);
	EXPECT_EQ('C', a.get_root()->left->right->data.first);
}

TEST(red_black_tree, find_place)
{
	RED_BLACK_TREE<char, int> a;								//									B black
	a.Insert('E', 1);											//						A black					D black
	a.Insert('A', 2);											//											C red		E red
	a.Insert('B', 3);
	a.Insert('C', 4);
	a.Insert('D', 5);
	EXPECT_EQ(a.get_root()->right->left, a.find_place('C'));
}



TEST_F(RedBlackTest, can_delete_get_root)
{
	a.Delete(5.0);
	EXPECT_EQ(a.get_root()->data.first, 5.5);
	EXPECT_EQ(a.get_root()->right->data.first, 7.0);
	EXPECT_EQ(a.get_root()->left->data.first, 3.0);
	EXPECT_EQ(a.get_root()->right->left->left->data.first, 5.75);
}

TEST_F(RedBlackTest, can_delete2)
{
	a.Delete(6.0);
	EXPECT_EQ(a.get_root()->right->left->data.first, 6.5);
}

TEST_F(RedBlackTest, can_delete3)
{
	a.Delete(7.0);
	EXPECT_EQ(a.get_root()->right->data.first, 8.0);
}

TEST_F(RedBlackTest, can_delete4)
{
	a.Delete(6.0);
	EXPECT_EQ(a.get_root()->right->left->data.first, 6.5);
}

TEST_F(RedBlackTest, can_delete5)
{
	a.Delete(5.0);
	EXPECT_EQ(a.get_root()->data.first, 5.5);
}