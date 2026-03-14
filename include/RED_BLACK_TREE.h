#pragma once
#include "Binary_Tree.h"


template <typename tkey, typename tval>
class RED_BLACK_TREE : public BINARY_TREE<tkey, tval>
{
private:
	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		static Node* nil;
		bool color; // 0 - red, 1 - black
		int bh; // black height
		std::pair<tkey, tval> data;
		/*		Node() :
					parent( nullptr ),
					left(nullptr),
					right (nullptr) {}
		*/
		Node(const tkey& key, const tval& val)
		{
			data.first = key;
			data.second = val;
			parent = nullptr;
			left = nil;
			right = nil;
			color = 0;
			bh = 0;
		}
		Node(int cl) // nil
		{
		//	data.first = tkey{};
		//	data.second = tval{};
		//	parent = nullptr;
		//	left = nil;
		//	right = nil;
			color = 1;
			bh = 0;
		}
		Node(tkey& key, tval& val)
		{
			data.first = key;
			data.second = val;
			parent = nullptr;
			left = nil;
			right = nil;
			color = 0;
			bh = 0;
		}
		Node& operator=(const Node& n)
		{
			parent = n.parent;
			left = n.left;
			right = n.right;
			data = n.data;
			return *this;
		}
	};
	Node* root = nullptr;
	Node* Node::nil = nullptr;
	void right_turn(Node* x)
	{
		int r = 1;
		if (x->parent->left == x) r = 0;  //проверяем, является ли х правым потомком своего родителя

		Node* y = x->left;
		Node* z = y->right;
		y->parent = x->parent;			
		x->parent = y;
		y->right = x;
		z->parent = x;
		x->left = z;		// также необходимо подцепить у к своему новому родителю
		if (x != root)     // если х был рутом, родителя у него нет
		{
			if (r)
			{
				y->parent->right = y;
			}
			else {
				y->parent->left = y;
			}
		}
		else {
			root = y;
		}
	}
	void left_turn(Node* x)
	{
		bool r = 1;
		if (x->parent->left == x) r = 0;  //проверяем, является ли х правым потомком своего родителя

		Node* y = x->right;
		Node* z = y->left;
		y->parent = x->parent;
		x->parent = y;
		y->left = x;
		z->parent = x;
		x->right = z;		// также необходимо подцепить у к своему новому родителю
		if (x != root)     // если х был рутом, родителя у него нет
		{
			if (r)
			{
				y->parent->right = y;
			}
			else {
				y->parent->left = y;
			}
		}
		else {
			root = y;
		}
	}
	void insert_fixup(Node* x) {
		while (!(x->parent.color))
		{
			if (x->parent == x->parent->parent->left)   // если родитель х - левый потомок своего родителя
			{
				y = x->parent->parent->right;   // у - дядя х
				if (y->color) // если дядя чёрный
				{ 
					if (x == x->parent->right)   // если х - правый потомок, тогда передвигаем его налево и идём дальше 
					{
						left_turn(x->parent);
						x = x->left;
					}
					 // если х = левый потомок, тогда правым поворотом поднимаем его наверх
					
					right_turn(x->parent->parent);
					x->parent.color = 1;
					x->parent->right.color = 0;
					
				}
				else  //  если дядя красный
				{
					x->parent.color = 1;
					y.color = 1;
					x->parent->parent.color = 0;
					x = x->parent->parent;
				}
			}
			else //в точности то же, но с заменой левого на правое
			{
				y = x->parent->parent->left;   // у - дядя х
				if (y->color) // если дядя чёрный
				{
					if (x == x->parent->left)   // если х - правый потомок, тогда передвигаем его налево и идём дальше 
					{
						right_turn(x->parent);
						x = x->right;
					}
					// если х = левый потомок, тогда правым поворотом поднимаем его наверх

					left_turn(x->parent->parent);
					x->parent.color = 1;
					x->parent->left.color = 0;

				}
				else  //  если дядя красный
				{
					x->parent.color = 1;
					y.color = 1;
					x->parent->parent.color = 0;
					x = x->parent->parent;
				}
			}
		}
	};
public:
	RED_BLACK_TREE()
	{
		nil = new Node(1);
	}
	tval& Find(const tkey& key) {
		Node* cur = root;
		while ((cur != nil) && (key != cur->data.first))
		{
			if (cur->data.first < key)
			{
				cur = cur->right;
			}
			else
			{
				cur = cur->left;
			}
		}
		if (cur == nil) {
			throw 15;
		}
		return cur->data.second;
	}
	bool Insert(const tkey& key, const tval& val) override
	{
		try
		{
			tval& t = Find(key);
			t = val; // обращаюсь к тому на что указывает ссылка
		}
		catch (int error)
		{
			Node* cur = root;
			Node* pred = root;
			Node* ins = new Node(key, val);
			while (cur != nil)
			{
				pred = cur;
				if (key < cur->data.first)
				{
					cur = cur->left;
				}
				else {
					cur = cur->right;
				}
			}
			ins->parent = pred;
			if (key < pred->data.first)
			{
				pred->left = ins;

			}
			else {
				pred->right = ins;
			}
			insert_fixup(ins);
			return true;
		}
		//случай, когда нашли такой же ключ и нужно заменить значение
	}
};