#pragma once
#include"basetable.h"
#include"list.h"
#include <functional>
#include<vector>
#include <algorithm>
template <typename tkey, typename tval>
class Hash_Table_chain : public BaseTable<tkey, tval>
{
protected:
	struct chain
	{
		size_t hash;
		std::pair<tkey, tval> data;
		chain()
		{

		}
		chain(tkey k, tval v, int h)
		{
			hash = h;
			data.first = k;
			data.second = v;
		}
	};
public:
	TSinglyList<chain> list;	
protected:																						//index  =  hash(key) % bucket_count
	std::vector <typename TSinglyList<chain>::TNode*> end; // индекс конца карманов								 0     1      2     3 4 5 6 7 8 9
	std::vector <typename TSinglyList<chain>::TNode*> begin;									// end		Node2, Node4, Node5	
	int bucket_count = 8;
public:																							// begin	Node1, Node3, Node5
	Hash_Table_chain()																			// list		Node1 - Node2 - Node3 - Node4 - Node5 ...
	{																							//	bucket	0        0       1        1      2
		begin.resize(bucket_count, nullptr); // сделал векторы фикс размера
		end.resize(bucket_count, nullptr);
	}
	Hash_Table_chain(int size)
	{
		begin.resize(size, nullptr); // сделал векторы фикс размера
		end.resize(size, nullptr);
		bucket_count = size;
	}
	//const std::vector<typename TSinglyList<chain>::TNode*>& Get_end()
	//{
	//	return end;
	//}
	//const std::vector<typename TSinglyList<chain>::TNode*>& Get_begin()
	//{
	//	return begin;
	//}
	int Get_bucket_count()
	{
		return bucket_count;
	}
	typename TSinglyList<chain>::TNode*  Get_first_of_bucket(int index)
	{
		return begin[index];
	}
	typename TSinglyList<chain>::TNode* Get_last_of_bucket(int index)
	{
		return end[index];
	}
	virtual bool Insert(const tkey& key, const tval& val) override
	{
		size_t Hash = std::hash<tkey>{} (key);
		int index = Hash % bucket_count; // с каким карманом работаем
		chain value(key, val, Hash);
		if (begin[index] == nullptr)
		{
			typename TSinglyList<chain>::TNode* last = list.Insert(nullptr, value); /// не обязательно бакет хранить под своим индексом, можно хранить его где хочешь, лишь бы указать правильный конец и начало
			end[index] = last;
			begin[index] = last;
		}
		else
		{
			typename TSinglyList<chain>::TNode* last = list.Insert(end[index], value);
			end[index] = last;
		}
		if (list.getSize() > 0.875 * bucket_count)
		{
			Rehash();
		}
		return true;
	}
	virtual bool Delete(const tkey& key) override
	{
		size_t Hash = std::hash<tkey>{} (key);
		int index = Hash % bucket_count;
		if (index < bucket_count)
		{
			typename TSinglyList<chain>::TNode* current = begin[index];
			//typename TSinglyList<chain>::TNode* new_last = current;
			while (current!= nullptr && current->value.data.first != key)
			{
				//new_last = current;
				current = current->pNext;
			}
			if (current == nullptr)
			{
				return false;
			}
			else if (current == begin[index])
			{
				if (current->pNext!= nullptr && current->pNext->value.hash % bucket_count == index)
				{
					begin[index] = current->pNext;
					list.Delete(current);
				}
				else
				{
					list.Delete(current);
					begin[index] = nullptr;
					end[index] = nullptr;
				}
			}
			else if (current == end[index])
			{
				typename TSinglyList<chain>::TNode* new_last = list.Delete(current);
				if (new_last!=nullptr && new_last->value.hash % bucket_count == index)
				{
					end[index] = new_last;
				}
				else
				{
					begin[index] = nullptr;
					end[index] = nullptr;
				}
			}
			else
			{
				list.Delete(current);
			}
			return true;
		}
		else
		{
			return false;
		}

	}
	virtual tval& Find(const tkey& key) override
	{
		size_t Hash = std::hash<tkey>{} (key);
		int index = Hash % bucket_count; 
		if (begin[index] != nullptr)
		{
			typename TSinglyList<chain>::TNode* current = begin[index];
			while (current != end[index])
			{
				if (current->value.data.first == key)
				{
					return current->value.data.second;
				}
				current = current->pNext;
			}
			if (end[index]->value.data.first == key)
			{
				return end[index]->value.data.second;
			}
		}
		throw 15;
	}
	void Rehash()
	{
		int new_bucket_count = bucket_count * 2; // Создаём новую таблицу
		Hash_Table_chain<tkey, tval> new_table(new_bucket_count);	// Вставляем все элементы из текущей таблицы в новую
		typename TSinglyList<chain>::TNode* current = list.getFirst();
		while (current != nullptr)
		{
			new_table.Insert(current->value.data.first, current->value.data.second);
			current = current->pNext;
		}										
		std::swap(begin, new_table.begin);
		std::swap(end, new_table.end);
		std::swap(bucket_count, new_table.bucket_count);// Меняем данные местами, swap без разницы на размеры векторов, после того как поменяли, локальная таблица уничтожится, а новые данные будут в основной
		list.swap(new_table.list);
	}
	~Hash_Table_chain()
	{

	}
};