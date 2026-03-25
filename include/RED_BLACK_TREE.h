#pragma once
#include "Binary_Tree.h"


template <typename tkey, typename tval>
class RED_BLACK_TREE : public BINARY_TREE<tkey, tval>
{
public:
	struct RBNode
	{
		RBNode* parent;
		RBNode* left;
		RBNode* right;
		bool color; // 0 - red, 1 - black
		int bh; // black height
		std::pair<tkey, tval> data;
		RBNode(const tkey& key, const tval& val, RBNode* n) 
		{
			data.first = key;
			data.second = val;
			parent = n;
			left = n;
			right = n;
			color = 0;
			bh = 1;
		}
		RBNode(int cl) // nil
		{
		//	data.first = tkey{};
		//	data.second = tval{};
			parent = nullptr;
			left = nullptr;
			right = nullptr;
			color = 1;
			bh = 0;
		}
		RBNode(tkey& key, tval& val, RBNode* n) 
		{
			data.first = key;
			data.second = val;
			parent = n;
			left = n;
			right = n;
			color = 0;
			bh = 1;
		}
		RBNode& operator=(const RBNode& n)
		{
			parent = n.parent;
			left = n.left;
			right = n.right;
			data = n.data;
			return *this;
		}
	};
	RBNode* nil = nullptr;
	RBNode* root = nullptr;
	
	
	void insert_fixup(RBNode* x) {
		
		while (!(x->parent->color))
		{
				if (x->parent == x->parent->parent->left)   // если родитель х - левый потомок своего родителя
				{
					RBNode* y = x->parent->parent->right;   // у - дядя х
					if (y->color) // если дядя чёрный
					{
						if (x == x->parent->right)   // если х - правый потомок, тогда передвигаем его налево и идём дальше 
						{
							left_turn(x->parent);
							x = x->left;
						}
						// если х = левый потомок, тогда правым поворотом поднимаем его наверх

						right_turn(x->parent->parent);
						x->parent->color = 1;
						x->parent->right->color = 0;

					}
					else  //  если дядя красный
					{
						x->parent->color = 1;
						y->color = 1;
						x->parent->parent->color = 0;
						x = x->parent->parent;
					}
				}
				else //в точности то же, но с заменой левого на правое
				{
					RBNode* y = x->parent->parent->left;   // у - дядя х
					if (y->color) // если дядя чёрный
					{
						if (x == x->parent->left)   // если х - левый потомок, тогда передвигаем его направо и идём дальше 
						{
							right_turn(x->parent);
							x = x->right;
						}
						// если х - правый потомок, тогда левым поворотом поднимаем его наверх

						left_turn(x->parent->parent);
						x->parent->color = 1;
						x->parent->left->color = 0;

					}
					else  //  если дядя красный
					{
						x->parent->color = 1;
						y->color = 1;
						x->parent->parent->color = 0;
						x = x->parent->parent;
					}
				}
				if (x == root)
				{
					x->color = 1;
					return;
				}
		}
		
	}
	void delete_fixup(RBNode* x)
	{
		RBNode* w = nullptr;
		while ((x != root) && (x->color))
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (!(w->color))
				{
					w->color = 1;
					x->parent->color = 0;
					left_turn(x->parent);
					w = x->parent->right;
				}
				if ((w->left->color) && (w->right->color))
				{
					w->color = 0;
					x = x->parent;
				}
				else {
					if (w->right->color)
					{
						w->left->color = 1;
						w->color = 0;
						right_turn(w);
						w = x->parent->right;
					}
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->right->color = 1;
				left_turn(x->parent);
				x = root;
			}
			else
			{
				w = x->parent->left;
				if (!(w->color))
				{
					w->color = 1;
					x->parent->color = 0;
					right_turn(x->parent);
					w = x->parent->left;
				}
				if ((w->right->color) && (w->left->color))
				{
					w->color = 0;
					x = x->parent;
				}
				else {
					if (w->left->color)
					{
						w->right->color = 1;
						w->color = 0;
						left_turn(w);
						w = x->parent->left;
					}
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->left->color = 1;
				right_turn(x->parent);
				x = root;
			}
		}
		x->color = 1;
	}
	RED_BLACK_TREE()
	{
		nil = new RBNode(1);
	}
	void right_turn(RBNode* x)
	{
		int r = 1;
		if (x->parent->left == x) r = 0;  //проверяем, является ли х правым потомком своего родителя

		RBNode* y = x->left;
		RBNode* z = y->right;
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
	void left_turn(RBNode* x)
	{
		bool r = 1;
		if (x->parent->left == x) r = 0;  //проверяем, является ли х правым потомком своего родителя

		RBNode* y = x->right;
		RBNode* z = y->left;
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
	RBNode* find_place(const tkey& key)
	{
		RBNode* cur = root;
		//RBNode* pred = root;
		while (key != cur->data.first)
		{
			//pred = cur;
			if (cur->data.first > key)
			{
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}
		return cur;
	}
	tval& Find(const tkey& key) {
		if (root) {
			RBNode* cur = root;
			while ((cur != nil) && (key != cur->data.first))
			{
				if (cur->data.first > key)
				{
					cur = cur->left;
				}
				else {
					cur = cur->right;
				}
			}
			if (cur == nil) {
				throw 15;
			}
			return cur->data.second;
		}
		else {
			throw 15;
		}
	}
	bool Insert(const tkey& key, const tval& val) override // можно переиспользовать из binary tree
	{
		if (root != nullptr)
		{
			try
			{
				tval& t = Find(key);
				t = val; // обращаюсь к тому на что указывает ссылка
			}
			catch (int error)
			{
				RBNode* cur = root;
				RBNode* pred = root;
				RBNode* ins = new RBNode(key, val, nil);
				ins->left = nil;
				ins->right = nil;
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
				insert_fixup(ins); // ПРОБЛЕМА ЗДЕСЬ
				return true;
			}
			//случай, когда нашли такой же ключ и нужно заменить значение
			RBNode* cur = find_place(key);
			cur->data.second = val;
			return false;
		}
		else {
			root = new RBNode(key, val, nil);
			root->color = 1;
		}
	}
	RBNode* Tree_Successor(RBNode* n)
	{
		RBNode* n2 = n->right;
		while (n2->left != nil)
		{
			n2 = n2->left;
		}
		return n2;
	}
	RBNode* get_root()
	{
		return root;
	}
	bool Delete(const tkey& key)
	{		
		if (root == nullptr) return false;			// проверка на пустое дерево
		try {
			tval t = Find(key);							// проверка на наличие ключа
		}
		catch (int error)
		{
			return false;
		}
		RBNode* z = find_place(key);
		RBNode* y = z;
		RBNode* x = z;

		if ((z->left == nil) || (z->right == nil)) y = z;	//определяем, оба ли потомка имеет z
		else y = Tree_Successor(z);
		
		if (y->left != nil) x = y->left;		//всегда выполняется, если потомка было два, именно х мы 
												//вставляем вместо z
		else x = y->right;
		
		x->parent = y->parent;		//присоединили х к родителю у
		
		if (y->parent == nil) root = x;						// случай, если удаляем корень
		else if (y == y->parent->left) y->parent->left = x;
			else y->parent->right = x;
		
		if (y != z) z->data = y->data;		//
		if (y->color) delete_fixup(x);
		delete y;
		return true;
	}
};