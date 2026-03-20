#include <gtest.h>
#include "Binary_Tree.h"
#include "fixture.h"
#include"AVL_tree.h"
#include<vector>

TEST_F(AVLTest, insert_check_ll)
{
	a.Insert(6.8, 12);
	a.Insert(6.7, 13);
	a.Insert(6.6, 14);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,8,2,1,4,5.75,6.8,6.7,6.6 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <=1 );
	}
}
TEST_F(AVLTest, insert_check_rr)
{
	a.Insert(5.8,52);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,8,2,1,4,5.75,5.8 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}
TEST_F(AVLTest, insert_check_lr)
{
	a.Insert(6.4, 20);
	a.Insert(6.45, 23);
	a.Insert(6.3, 21);
	a.Insert(6.47, 22);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,8,2,1,4,5.75,6.4,6.45,6.3,6.47 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}
TEST_F(AVLTest, insert_check_rl)
{
	a.Insert(8.2, 20);
	a.Insert(8.1, 21);
	a.Insert(8.05, 22);
	a.Insert(8.3, 23);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,8,2,1,4,5.75,8.2,8.1,8.05,8.3 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}
TEST_F(AVLTest, insert_repeat) // нужно перебилдить cmake
{
	a.draw();
	a.Insert(6, 100);
	//a.draw();
	EXPECT_EQ(a.Find(6), 100);
}
TEST_F(AVLTest, delete_root_check)
{
	a.Delete(5.0);
	a.draw();
	std::vector<double> vec = { 3,7,6,5.5,6.5,8,2,1,4,5.75,};

	ASSERT_ANY_THROW(a.Find(5));

}
TEST_F(AVLTest, delete_root_check_balance)
{
	a.Delete(5.0);
	a.draw();
	std::vector<double> vec = {3,7,6,5.5,6.5,8,2,1,4,5.75 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}

TEST_F(AVLTest, delete_sheet_check_balance)
{
	a.Delete(8.0);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,2,1,4,5.75 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}
TEST_F(AVLTest, delete_one_child_check_balance)
{
	a.Delete(5.5);
	a.draw();
	std::vector<double> vec = { 5,3,7,6,8,6.5,2,1,4,5.75 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}
TEST_F(AVLTest, delete_two_child_check_balance)
{
	a.Delete(6);
	a.draw();
	std::vector<double> vec = { 5,3,7,5.5,8,6.5,2,1,4,5.75 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}