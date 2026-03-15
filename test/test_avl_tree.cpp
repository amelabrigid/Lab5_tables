#include <gtest.h>
#include "Binary_Tree.h"
#include "fixture.h"
#include"AVL_tree.h"
#include<vector>

TEST_F(AvlTest, insert_check_ll)
{
	a.Insert(6.8, 12);
	a.Insert(6.7, 13);
	a.Insert(6.6, 14);
	a.draw();
	//std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
	//std::cout << a.get_balance(6.8);
	//EXPECT_EQ(a.get_balance(6.8), 0);
	std::vector<double> vec = { 5,3,7,6,5.5,6.5,8,2,1,4,5.75,6.8,6.7,6.6 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <=1 );
	}
}
TEST_F(AvlTest, delete_check)
{
	a.Delete(5.0);
	a.draw();
	std::vector<double> vec = { 3,7,6,5.5,6.5,8,2,1,4,5.75,};

	ASSERT_ANY_THROW(a.Find(5));

}
TEST_F(AvlTest, delete_check_balance)
{
	a.Delete(5.0);
	a.draw();
	std::vector<double> vec = {3,7,6,5.5,6.5,8,2,1,4,5.75 };
	for (const auto& v : vec)
	{
		EXPECT_TRUE(abs(a.get_balance(v)) <= 1);
	}
}