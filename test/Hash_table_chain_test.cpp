#include <gtest.h>
#include"Hash_table_chain.h"
#include"list.h"
#include <functional>
TEST(hash_table_chain, create)
{
	Hash_Table_chain<double,int> a;

}
TEST(hash_table_chain, insert)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	EXPECT_EQ(a.list.getFirst()->value.data.first, 100);
}
TEST(hash_table_chain, find)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	EXPECT_EQ(a.Find(100), 100);
}
TEST(hash_table_chain, can_delete)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	a.Insert(200, 200);
	a.Delete(200);
	EXPECT_EQ(a.list.getFirst()->value.data.first, 100);
	EXPECT_EQ(a.list.getLast()->value.data.first, 100);
}
TEST(hash_table_chain, insert_repeat)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	a.Insert(222, 200);
	a.Insert(100, 150);
	a.Insert(100, 140);
	size_t index = std::hash<double>{} (100);
	index = index % 8;
	EXPECT_EQ(a.Get_first_of_bucket(index)->value.data.second, 100);
	EXPECT_EQ(a.Get_first_of_bucket(index)->pNext->value.data.second,150);
	EXPECT_EQ(a.Get_last_of_bucket(index)->value.data.second, 140);
}
TEST(hash_table_chain, delete_repeat)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	a.Insert(222, 200);
	a.Insert(100, 150);
	a.Insert(100, 140);
	size_t index = std::hash<double>{} (100);
	index = index % 8;
	a.Delete(100);
	EXPECT_EQ(a.Get_first_of_bucket(index)->value.data.second, 150);
}
TEST(hash_table_chain, rehash)
{
	Hash_Table_chain<double, int> a;
	a.Insert(100, 100);
	a.Insert(222, 200);
	a.Insert(100, 150);
	a.Insert(100, 140);
	a.Insert(300, 400);
	a.Insert(350, 410);
	a.Insert(322, 440);
	a.Insert(320, 470);
	EXPECT_EQ(a.Get_bucket_count(), 16);
}