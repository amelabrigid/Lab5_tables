#pragma once
#include <utility>
#include"basetable.h"
#include <vector>
const int NOT_FOUND = 15;
const int REPEAT = 25;
template <typename tkey, typename tval> 
class AVL_TREE: public BaseTable<tkey, tval>
{
private:
	struct Node
	{
		std::pair<tkey, tval> data;
		Node* parent;
		Node* left;
		Node* right;
		int height;// соблюдение баланса -1 0 1 
		Node(tkey& key, tval& val)
		{
			data.first = key;
			data.second = val;
			parent = nullptr;
			left = nullptr;
			right = nullptr;
			height = 0;// считаем каждое звено изначально листом
		}
	};
	Node* root = nullptr; // высота nullptr = -1 высота листа =0, считаем по ребрам
	void Update_Height(Node* node)
	{
		int left_height = 0;
		int right_height = 0;
		if (node->left != nullptr)
		{
			left_height = node->left->height + 1; // balance = left->height - right->height
		}
		if (node->right != nullptr)
		{
			right_height = node->right->height + 1;
		}
		if (left_heigth > right_height)
		{
			node->height =  left_height;
		}
		else
		{
			node->height = right_height;
		}
	}
	Node* RIGHT_TURN(node* problem) // изначально был левый, возникла путаница с пониманием и названием, реализован вроде верно
	{
		Node* tmp3 = problem->right;
		Node* tmp2 = problem->right->left;
		Node* tmp = problem;				
		if (problem == root)					
		{
			tmp->right = tmp2;
			if (tmp2 != nullptr)
			{
				tmp2->parent = tmp;// иначе происходит разыменование nullptr
			}
			tmp3->parent = nullptr;
			tmp3->left = tmp;
		}
		else
		{
			tmp->right = tmp2;
			if (tmp2 != nullptr)
			{
				tmp2->parent = tmp;// иначе происходит разыменование nullptr
			}
			tmp3->parent = problem->parent;
			if (problem == problem->parent->left)
			{
				problem->parent->left = tmp3;
			}
			else
			{
				problem->parent->right = tmp3;
			}
			tmp->parent = tmp3;
			tmp3->left = tmp;
		}
		tmp->height =Update_Height(tmp);
		tmp3->height = Update_Height(tmp3);// tmp2 не мен€ет высоту
		return tmp3;
	}
	Node* LEFT_TURN(node* problem) // изначально был правый, возникла путаница с пониманием и названием, реализован вроде верно
	{
		Node* tmp = problem;
		Node* tmp2 = problem->left->right;
		Node* tmp3 = problem->left;			
		if (problem == root)					
		{
			tmp3->right = tmp;
			tmp->parent = tmp3;
			tmp3->parent = nullptr;
			if (tmp2 != nullptr)
			{
				tmp2->parent = tmp;
			}
			tmp->left = tmp2;
		}
		else
		{
			tmp3->right = tmp;
			tmp->parent = tmp3;
			tmp3->parent = problem->parent;
			if (tmp3 == problem->parent->left)
			{
				problem->parent->left = tmp3;
			}
			else
			{
				problem->parent->right = tmp3;
			}
			if (tmp2 != nullptr)
			{
				tmp2->parent = tmp;
			}
			tmp->left = tmp2;
		}
		tmp->height = Update_Height(tmp);
		tmp3->height = Update_Height(tmp3);
		return tmp3;
	}
	int get_balance(Node* node) 
	{
		int left_h = -1;
		if (node->left!=nullptr)
		{
			left_h = node->left->height;
		}
		int right_h = -1;
		if (node->right!=nullptr) 
		{
			right_h = node->right->height;
		}
		return left_h - right_h;
	}
	void MAD_BALANCE(Node* node)// 
	{
		Node* balancer = node;
		while (balancer != nullptr) 
		{
			int balance = get_balance(balancer);

			if (balance > 1) 
			{                    // Ћевое т€жЄлое LL/LR
				if (get_balance(balancer->left) < 0) 
				{     // LR
					balancer->left = RIGHT_TURN(balancer->left);
				}
				balancer = LEFT_TURN(balancer);    // LL или после LR
				balancer = balancer->parent;
			}
			else if (balance < -1) 
			{              // ѕравое т€жЄлое RL/RR
				if (get_balance(balancer->right) > 0) 
				{  // RL
					balancer->right = LEFT_TURN(balancer->right);
				}
				balancer = RIGHT_TURN(balancer);   // RR или после RL
				balancer = balancer->parent;
			}
			else 
			{                                // Ќормальный баланс 0 -1 1
				Update_Height(balancer);
				balancer = balancer->parent;
			}

			// ѕроверка корн€
			if (balancer == nullptr || balancer->parent == nullptr) 
			{
				if (root != balancer)
				{
					root = balancer;
				}
				//return;
			}
		}
	}
	void draw_tree(Node* node, std::vector<std::string>& lines, int level, int x, int y) const {
		if (node == nullptr) return;

		// –исуем узел
		lines[y] += "  ";
		for (int i = 0; i < x - 1; ++i) lines[y] += " ";
		lines[y] += "O(" + std::to_string(node->data.first) + ")";

		// –исуем правую ветку
		if (node->right) {
			lines[y + 1] += "  ";
			for (int i = 0; i < x - 1; ++i) lines[y + 1] += " ";
			lines[y + 1][x * 3 - 1] = '/';  // /
			draw_tree(node->right, lines, level + 1, x * 2, y + 2);
		}

		// –исуем левую ветку
		if (node->left) {
			lines[y + 1] += "  ";
			for (int i = 0; i < x - 1; ++i) lines[y + 1] += " ";
			lines[y + 1][x * 3 + 1] = '\\';  
			 draw_tree(node->left, lines, level+1, x/2, y+2);
		}
	}
	int get_height(Node* node) const {
		return node ? node->height + 1 : 0;
	}

public:
	AVL_TREE()
	{

	}
	AVL_TREE(const std::vector<std::pair<tkey,tval>>&vec)
	{

	}
	virtual bool Insert(const tkey& key, const tval& val) override
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
					if (key > Next->data.first) // изменение значени€ у одинаковых ключей
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
			MAD_BALANCE(NEW);
		}
		return true;
	}
	virtual bool Delete(const tkey& key)override // 2 детей Ќаходим минимальный узел в правом поддереве
	{
		Node* Current = root;
		//Node* Next = root;// пустое дерево
		if (root == nullptr)
		{
			return false;
		}
		else
		{
			while (Current != nullptr && Current->data.first != key )
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
	virtual tval& Find(const tkey& key)override
	{
		Node* Current;
		Current = root;
		while (Current != nullptr && Current->data.first!=key )
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
	void draw() const {
		if (root == nullptr) {
			std::cout << "ƒерево пустое\n";
			return;
		}

		// ¬ычисл€ем размеры
		int height = get_height(root);
		int width = 1 << height;  // 2^высота
		std::vector<std::string> lines(height * 3, std::string(width * 6, ' '));

		// –исуем дерево
		draw_tree(root, lines, 0, width / 2, height);

		// ¬ыводим
		for (const auto& line : lines) {
			std::cout << line.substr(0, width * 4) << std::endl;  // ќбрезаем лишнее
		}
	}
	~AVL_TREE()// пробежатьс€ по дереву и удалить все ноды, начина€ с концов и заканчива€ корнем
	{

	}
};