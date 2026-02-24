#pragma once
#include <utility>
#include"basetable.h"
template <typename tkey, typename tval>
class BINARY_TREE : public BaseTable<tkey, tval>
{
public:
	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		std::pair<tkey, tval> data;
		Node(tkey& key, tval& val)
		{
			data.first = key;
			data.second = val;
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}
	};
	Node* root = nullptr;
	BINARY_TREE()
	{

	}
	virtual bool Insert(const tkey&, const tval&) override
	{
		try
		{
			tval& t = Find(key);
			t = val; // обращаюсь к тому на что указывает ссылка
		}
		catch (int error)
		{
			Node* Current = root;
			Node* Next = root;// пустое дерево
			if (root == nullptr)
			{
				root = new Node(key, val);
				return true;
			}
			else
			{
				while (Next != nullptr)
				{
					Current = Next;
					if (key > Next->data.first) // изменение значения у одинаковых ключей
					{
						Next = Next->right;
					}
					else
					{
						Next = Next->left;
					}
				}
				Node* NEW = new Node(key, val);
				if (Current->data.first < key)
				{
					Current->right = NEW;
					NEW->parent = Current;
				}
				else
				{
					Current->left = NEW;
					NEW->parent = Current;
				}
			}
		}
		return true;
	}
	virtual bool Delete(const tkey&) override // не доделал
	{
		Node* Current = root;
		if (root == nullptr)
		{
			return false;
		}
		else
		{
			while (Current != nullptr && Current->data.first != key)
			{
				//Current = Next;
				if (key > Current->data.first)
				{
					Current = Current->right;
				}
				else
				{
					Current = Current->left;
				}
			}
			if (Current == nullptr)
			{
				return false;
			}
		}
		if (Current->left != nullptr && Current->right != nullptr) // 2 ребенка
		{

		}
		else 	if (Current->left == nullptr && Current->right != nullptr) // 1 ребенка 
		{
			if (Current == Current->parent->left)
			{
				Current->parent->left = Current->right;
				Current->right->parent = Current->parent;
			}
			else
			{
				Current->parent->right = Current->left;
				Current->left->parent = Current->parent;
			}
		}
		else 	if (Current->left != nullptr && Current->right == nullptr) // 1 ребенка
		{
			if (Current == Current->parent->left)
			{
				Current->parent->left = Current->left;
				Current->left->parent = Current->parent;
			}
			else
			{
				Current->parent->right = Current->left;
				Current->left->parent = Current->parent;
			}
		}
		else 	if (Current->left == nullptr && Current->right == nullptr) // 0 ребенка
		{
			if (Current == Current->parent->left)
			{
				Current->parent->left = nullptr;// 
			}
			else
			{
				Current->parent->right = nullptr;// запомнить ноду балансировки
			}
		}
		delete Current;
	}
	virtual tval& Find(const tkey&) override
	{
		Node* Current;
		Current = root;
		while (Current != nullptr && Current->data.first != key)
		{
			if (Current->data.first < key)
			{
				Current = Current->right;

			}
			else
			{
				Current = Current->left;
			}
		}
		if (Current == nullptr)
		{
			throw NOT_FOUND;
		}
		return Current->data.second;
	}
	~BINARY_TREE()
	{
		Node* Current;
		if (root != nullptr)
		{
			if (Current->left != nullptr)
			{
				Current = root->left;
			}
			else
			{
				Current = root;
			}
			while (Current != root) // удаляем левое поддерево
			{
				while (Current->left != nullptr)
				{
					Current = Current->left;
				}
				Current = Current->parent;
				delete Current->left;
				Current->left = nullptr;
				if (Current->right != nullptr)
				{
					Current = Current->right;
				}
				else
				{
					Current = Current->parent;
					delete Current->left;
					Current->left = nullptr;

				}
			}
		}
	}
};