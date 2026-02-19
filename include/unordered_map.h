#pragma once
#include"list.h"
//#include"BaseTable.h"
#include"basetable.h"
const int NOT_FOUND = 15;
const int REPEAT = 25;
template <typename tkey, typename tval>
class Unordered_map : public BaseTable<tkey, tval>, private TSinglyList<std::pair<tkey,tval>>
{
private:


public:
	virtual bool Insert(const tkey& key,const tval& val)override
	{
		try
		{
			Find(key);
		}
		catch (int error)
		{
			TSinglyList<std::pair<tkey, tval>>::PushBack(std::pair<tkey, tval>(key, val));
			return true;
		}
		throw REPEAT;

	}
	virtual bool Delete(const tkey& key) override
	{
		int pos = 0;
		try 
		{
			if (key == TSinglyList<std::pair<tkey, tval>>::Front().first)
			{
				TSinglyList<std::pair<tkey, tval>>::PopFront();
				return true;
			}
			while (TSinglyList<std::pair<tkey, tval>>::Next().first != key)
			{
				pos++;// показывает позицию предыдущего элемента
			}
			TSinglyList<std::pair<tkey, tval>>::EraseAfter(pos);
		}
		catch (int error)
		{

			return false;

		}
		return true;
	}
	virtual	tval& Find(const tkey& key)override
	{
		try
		{
			if (key == TSinglyList<std::pair<tkey, tval>>::Front().first)
			{
				return TSinglyList<std::pair<tkey, tval>>::Front().second;
			}
			while ( true)
			{
				std::pair<tkey, tval>& P = TSinglyList<std::pair<tkey, tval>>::Next();
				if (P.first == key)
				{
					return P.second;
				}
			}
		}
		catch (int error)
		{


		}
		throw NOT_FOUND;
	}
	Unordered_map():
		TSinglyList<std::pair<tkey, tval>>()
	{
		
	}
	Unordered_map(const Unordered_map& x):
		TSinglyList<std::pair<tkey, tval>>(x)
	{
		
	}
	~Unordered_map()
	{

	}
	std::pair<tkey,tval> Last_value()
	{
		return TSinglyList<std::pair<tkey, tval>>::LastValue();
	}
	std::pair<tkey, tval> First_value()
	{
		return TSinglyList<std::pair<tkey, tval>>::FirstValue();
	}
};