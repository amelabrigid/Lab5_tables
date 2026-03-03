#include "gtest.h"
#include"Unordered_map.h"
TEST(unordered_map, ADD)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	std::pair<int, int> para(100, 52);
	EXPECT_EQ(para, map1.Last_value());
}
TEST(unordered_map, Delete)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Delete(15);
	std::pair<int, int> para(100, 52);
	EXPECT_EQ(para, map1.Last_value());
}
TEST(unordered_map, NoDelete)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	EXPECT_EQ(map1.Delete(15),0);
}
TEST(unordered_map, Found)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Insert(52, 13);
	EXPECT_EQ(map1.Find(15), 25);
}
TEST(unordered_map, NoFound)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Insert(52, 13);
	EXPECT_THROW(map1.Find(32), int);
}
TEST(unordered_map, DeleteFirst)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Delete(100);
	std::pair<int, int> para(15, 25);
	EXPECT_EQ(para, map1.First_value());
}
TEST(unordered_map, Insert_REPEAT)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	std::pair<int, int> para1(100, 52);
	EXPECT_EQ(map1.First_value(), para1);
	map1.Insert(100, 53);
	std::pair<int, int> para2(100, 53);
	EXPECT_EQ(para2, map1.First_value());
}