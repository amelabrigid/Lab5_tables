#include "gtest.h"
#include"Unordered_map.h"
TEST(Test1, ADD)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	std::pair<int, int> para(100, 52);
	EXPECT_EQ(para, map1.Last_value());
}
TEST(Test2, Delete)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Delete(15);
	std::pair<int, int> para(100, 52);
	EXPECT_EQ(para, map1.Last_value());
}
TEST(Test3, NoDelete)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	EXPECT_EQ(map1.Delete(15),0);
}
TEST(Test4, Found)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Insert(52, 13);
	EXPECT_EQ(map1.Find(15), 25);
}
TEST(Test5, NoFound)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Insert(52, 13);
	EXPECT_THROW(map1.Find(32), int);
}
TEST(Test6, DeleteFirst)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	map1.Insert(15, 25);
	map1.Delete(100);
	std::pair<int, int> para(15, 25);
	EXPECT_EQ(para, map1.First_value());
}
TEST(Test7, Insert_REPEAT)
{
	Unordered_map<int, int> map1;
	map1.Insert(100, 52);
	EXPECT_THROW(map1.Insert(100, 25), int);
}