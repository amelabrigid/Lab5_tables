#include <gtest.h>
#include "ordered_map.h"

TEST(ordered_map, test_of_tests)
{
	EXPECT_TRUE(true);
}

TEST(ordered_map, can_be_created)
{
	Ordered_map<char, int> a;
}

TEST(ordered_map, can_be_parametred)
{
	Ordered_map<char, int> a('a', 0);
}

TEST(ordered_map, can_insert_new_key)
{
	Ordered_map<char, int> a('a', 0);
	a.Insert('b', 1);
	char key = a.get_key(1);
	EXPECT_EQ(key, 'b');
}

TEST(ordered_map, can_insert_existing_key)
{
	Ordered_map<char, int> a('a', 0);
	a.Insert('a', 1);
	int val = a.get_val(0);
	EXPECT_EQ(val, 1);
}

TEST(ordered_map, can_delete)
{
	Ordered_map<char, int> a('a', 0);
	a.Insert('b', 1);
	a.Delete('a');
	char key = a.get_key(0);
	EXPECT_EQ(key, 'b');
}

TEST(ordered_map, can_find)
{
	Ordered_map<char, int> a('a', 0);
	a.Insert('b', 1);
	a.Insert('c', 2);
	std::cout << a.get_key(0) << std::endl;
	std::cout << a.get_key(1) << std::endl;
	std::cout << a.get_key(2) << std::endl;
	int val = a.Find('b');
	EXPECT_EQ(val, 1);
}

