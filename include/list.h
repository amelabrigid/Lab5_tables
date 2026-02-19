#pragma once
#include<vector>
template<typename T> class TSinglyList
{
protected:
	struct TNode
	{
		T value;
		TNode* pNext;
		TNode(T data, TNode* n)
		{
			value = data;
			pNext = n;
		}
		TNode& operator=(const TNode& node)
		{
			value = node.value;
			pNext = node.pNext;
		}
	};
	TNode* pCurrent;
	TNode* pFirst;
	TNode* pEnd;
	size_t sz;
public:
	TSinglyList()
	{
		pFirst = nullptr;
		pEnd = nullptr;
		sz = 0;
	}
	TSinglyList(const std::vector<T>& v)
	{
		sz = 0;
		pFirst = nullptr;
		pEnd = nullptr;
		for (size_t i = 0; i < v.size(); i++)
		{
			PushBack(v[i]);
		}
	}
	TSinglyList(const TSinglyList& list)
	{
		sz = 0;
		pFirst = nullptr;
		pEnd = nullptr;
		for (int i = 0; i < list.sz; i++)
		{
			PushBack(list[i]);
		}
	}
	TSinglyList(TSinglyList&& list) noexcept
	{
		pFirst = nullptr;
		pEnd = nullptr;
		sz = 0;
		swap(*this, list);
	}
	TSinglyList& operator=(TSinglyList& list)
	{
		Clean();
		for (int i = 0; i < list.sz; i++)
		{
			PushBack(list[i]);
		}
		return *this;
	}
	void Clean()
	{
		TNode *pCurrent = pFirst;
		while (pCurrent != pEnd)
		{
			TNode* tmp = pCurrent->pNext;
			delete pCurrent;
			pCurrent = tmp;
		}
		
		pFirst = nullptr;
		pEnd = nullptr;
		sz = 0;
	}
	void swap(TSinglyList& hs1, TSinglyList& hs2)
	{
		std::swap(hs1.sz, hs2.sz);
		std::swap(hs1.pFirst, hs2.pFirst);
		std::swap(hs1.pEnd, hs2.pEnd);
	}
	TSinglyList& operator=(const TSinglyList&& list)noexcept
	{
		Clean();
		swap(*this, list);
		return *this;
	}
	~TSinglyList()
	{
		Clean();
	}
	size_t size() const noexcept
	{
		return sz;
	}
	bool IsEmpty() const noexcept
	{
		return(sz == 0);
	}
	T& Front()
	{
		if (pFirst == nullptr)
		{
			throw 10;
		}
		pCurrent = pFirst;
		return pFirst->value;
	}
	T& Next()
	{
		pCurrent = pCurrent->pNext;
		if (pCurrent != nullptr)
		{
			return pCurrent->value;
		}
		throw 10;
	}
	void PushFront(const T& val)
	{
		TNode* t = new TNode(val, pFirst);
		pFirst = t;
		if (pEnd == nullptr)// если 1 элемент в цепочке
		{
			pEnd = t;
		}
		sz++;
	}
	void PushBack(const T& val)
	{
		TNode* t = new TNode(val, nullptr);

		if (pFirst == nullptr)// если 1 элемент в цепочке ( сначала 0)
		{
			pFirst = t;
		}
		if (pEnd == nullptr)
		{
			pEnd = t;
		}
		else
		{
			pEnd->pNext = t;
			pEnd = t;
		}
		sz++;
	}
	void PopFront()noexcept
	{
		if (sz == 0)
		{
			return;
		}
		TNode* tmp = pFirst->pNext;
		delete pFirst;
		pFirst = tmp;
		if (sz == 1)
		{
			pEnd = nullptr;
		}
		sz--;
	}
	T& operator[](size_t pos)
	{
		TNode* tmp = pFirst;
		if (sz == 0 || pos>=sz || pos<0)
		{
			throw 1;
		}
		if (pos ==0)
		{
			return tmp->value;
		}
		for (int i = 0; i < pos; i++)
		{
			tmp = tmp->pNext;
		}
		return tmp->value;
	}

	T operator[](size_t pos) const
	{
		TNode* tmp = pFirst;
		if (sz == 0 || pos >= sz || pos < 0)
		{
			throw 1;
		}
		if (pos == 0)
		{
			return tmp->value;
		}
		for (int i = 0; i < pos; i++)
		{
			tmp = tmp->pNext;
		}
		return tmp->value;
	}


	void PushAfter(size_t pos, const T& val)
	{
		TNode* tmp = pFirst;
		if (pos < 0 || pos >= sz || sz == 0)
		{
			throw 1;
		}
		else
		{

			for (int i = 0; i < pos; i++)
			{
				tmp = tmp->pNext;
			}
			TNode* t = new TNode(val, tmp->pNext);
			tmp->pNext = t;
			if (pos == sz - 1) // последний
			{
				pEnd = t;
			}
			sz++;
		}
	}
	void EraseAfter(size_t pos)
	{
		TNode* tmp = pFirst;
		if (pos < 0 || pos >= sz || sz == 0)
		{
			throw 1;
		}
		else
		{

			for (int i = 0; i < pos; i++)
			{
				tmp = tmp->pNext;
			}
			TNode* t = tmp->pNext->pNext;
			delete tmp->pNext;
			tmp->pNext = t;
			if (pos == sz - 2)// предпоследний
			{
				pEnd = tmp;
			}
			sz--;
		}
	}
	T& LastValue()
	{
		return pEnd->value;
	}
	T& FirstValue()
	{
		return pFirst->value;
	}
};