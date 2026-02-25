#pragma once
#include <utility>
#include"basetable.h"
template <typename tkey, typename tval>
class BINARY_TREE : public BaseTable<tkey, tval>
{
private:
	void insert_sort(const std::vector<std::pair<tkey, tval>>& vec, int left_index, int right_index)
	{
		if (left_index > right_index)
		{
			return;
		}
		std::pair<tkey, tval> middle = vec[(left_index + right_index) / 2];
		Insert(middle.first, middle.second);
		insert_sort(vec, left_index, (left_index + right_index) / 2 - 1);
		insert_sort(vec, (left_index + right_index) / 2 + 1, right_index);
	}
	bool compare_key(std::pair<tkey, tval> par1, std::pair<tkey, tval> par2)
	{
		return par1.first < par2.first;
	}

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
	BINARY_TREE(const std::vector<std::pair<tkey, tval>>& vec)
	{
		std::sort(vec.begin(), vec.end(), compare_key());
		insert_sort(vec, vec.begin(), vec.size() - 1);
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
	virtual bool Delete(const tkey& key) override  // максимально зверский код, возможно с чем то перемудрил
	{
		Node* Current = root;
		if (root == nullptr) /// проверка на пустое дерево
		{
			return false;
		}
		else
		{
			while (Current != nullptr && Current->data.first != key)  /// поиск места удаления
			{
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
			Node* replacement = Current->right;
			if (Current->parent != nullptr) // проверка на то что удаляемое не корень
			{
				if (Current->right->left == nullptr) // правый ребеное удаляемого сам является минимальным
				{
					replacement->parent = Current->parent;
					Current->left->parent = replacement;
					replacement->left = Current->left;
					if (Current == Current->parent->left)
					{
						Current->parent->left = replacement;
					}
					else
					{
						Current->parent->right = replacement;
					}
				}
				else
				{
					while (replacement->left != nullptr) // поиск минимального правого
					{
						replacement = replacement->left;
					}
					if (replacement->right != nullptr) // есть правый ребенок у замены, нужно его переприсоединить
					{
						replacement->right->parent = replacement->parent;
						replacement->parent->left = replacement->right;
					}
					else
					{
						replacement->parent->left = nullptr;
					}
					Current->left->parent = replacement;
					Current->right->parent = replacement;
					replacement->left = Current->left;
					replacement->right = Current->right;
					replacement->parent = Current->parent;
					if (Current == Current->parent->left)
					{
						Current->parent->left = replacement;
					}
					else
					{
						Current->parent->right = replacement;
					}
				}
			}
			else// Current == root // удаляемое является корнем
			{
				if (Current->right->left == nullptr) // правый ребенок минимальный
				{
					replacement->parent = Current->parent;
					Current->left->parent = replacement;
					replacement->left = Current->left;
					root = replacement;
				}
				else
				{
					while (replacement->left != nullptr)
					{
						replacement = replacement->left;
					}
					if (replacement->right != nullptr) // есть правый ребенок у замены
					{
						replacement->right->parent = replacement->parent;
						replacement->parent->left = replacement->right;
					}
					else
					{
						replacement->parent->left = nullptr;
					}
					Current->left->parent = replacement;
					Current->right->parent = replacement;
					replacement->left = Current->left;
					replacement->right = Current->right;
					replacement->parent = Current->parent;
					root = replacement;
				}
			}

		}
		else 	if (Current->left == nullptr && Current->right != nullptr) // 1 ребенок (правый)
		{
			if (Current->parent != nullptr)// проверка на корень
			{
				if (Current == Current->parent->left)
				{
					Current->parent->left = Current->right;
					Current->right->parent = Current->parent;
				}
				else
				{
					Current->parent->right = Current->right;
					Current->right->parent = Current->parent;
				}
			}
			else
			{
				root = Current->right;
				root->parent = nullptr;
			}
		}
		else 	if (Current->left != nullptr && Current->right == nullptr) // 1 ребенок (левый)
		{
			if (Current->parent != nullptr) // проверка на корень
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
			else
			{
				root = Current->left;
				root->parent = nullptr;
			}

		}
		else 	if (Current->left == nullptr && Current->right == nullptr) // 0 детей
		{
			if (Current != root)// проверка на корень
			{	
				if (Current == Current->parent->left)
				{
					Current->parent->left = nullptr;// 
				}
				else
				{
					Current->parent->right = nullptr;// запомнить ноду балансировки для авл
				}
			}
			else
			{
				root = nullptr;
			}

		}
		delete Current;
		return true;
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
	void delete_node(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		delete_node(node->left);
		delete_node(node->right);
		delete node;
	}
	~BINARY_TREE()
	{
		delete_node(root);
	}
};