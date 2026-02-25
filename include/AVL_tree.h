#pragma once
#include <utility>
#include"basetable.h"
#include <vector>
#include"Binary_Tree.h"
const int NOT_FOUND = 15;
const int REPEAT = 25;
template <typename tkey, typename tval> 
class AVL_TREE: public BINARY_TREE<tkey, tval>
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
		tmp3->height = Update_Height(tmp3);// tmp2 не меняет высоту
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

			if (balance > 1) // левое тяжелее
			{                   
				if (get_balance(balancer->left) < 0) 
				{										// LR
					balancer->left = RIGHT_TURN(balancer->left);
				}
				balancer = LEFT_TURN(balancer);    // LL 
				balancer = balancer->parent;
			}
			else if (balance < -1) // правое тяжелее
			{              
				if (get_balance(balancer->right) > 0) 
				{										// RL
					balancer->right = LEFT_TURN(balancer->right);
				}
				balancer = RIGHT_TURN(balancer);   // RR 
				balancer = balancer->parent;
			}
			else 
			{                                // Нормальный баланс 0 -1 1
				Update_Height(balancer);
				balancer = balancer->parent;
			}

			// Проверка корня
			if (balancer == nullptr || balancer->parent == nullptr) 
			{
				if (root != balancer)
				{
					root = balancer;
				}
			}
		}
	}
	void draw_tree(Node* node, std::vector<std::string>& lines, int level, int x, int y) const {
		if (node == nullptr) return;

		lines[y] += "  ";
		for (int i = 0; i < x - 1; ++i) lines[y] += " ";
		lines[y] += "O(" + std::to_string(node->data.first) + ")";

		if (node->right) {
			lines[y + 1] += "  ";
			for (int i = 0; i < x - 1; ++i) lines[y + 1] += " ";
			lines[y + 1][x * 3 - 1] = '/';  // /
			draw_tree(node->right, lines, level + 1, x * 2, y + 2);
		}

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
	//void insert_sort(const std::vector<std::pair<tkey, tval>>& vec, int left_index, int right_index)
	//{
	//	if (left_index > right_index)
	//	{
	//		return;
	//	}
	//	std::pair<tkey, tval> middle = vec[(left_index + right_index) / 2];
	//	Insert(middle.first, middle.second);
	//	insert_sort(vec, left_index, (left_index + right_index) / 2 - 1);
	//	insert_sort(vec, (left_index + right_index) / 2 + 1, right_index);
	//}
	//bool compare_key(std::pair<tkey, tval> par1, std::pair<tkey, tval> par2)
	//{
	//	return par1.first < par2.first;
	//}
public:
	AVL_TREE()
	{

	}

	AVL_TREE(const std::vector<std::pair<tkey,tval>>&vec)
	:BINARY_TREE<tkey, tval>(vec);
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
			//bool res = BINARY_TREE<tkey, tval>::Insert(key);
			MAD_BALANCE(NEW);
		}
		return true;
	}
	virtual bool Delete(const tkey& key)override // 2 детей Находим минимальный узел в правом поддереве
	{
		//bool res = BINARY_TREE<tkey, tval>::Delete(key);
		Node* balance_node;
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
			balance_node = replacement;

		}
		else 	if (Current->left == nullptr && Current->right != nullptr) // 1 ребенок (правый)
		{
			balance_node = Current->right;
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
			balance_node = Current->left;
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
			balance_node = Current->parent;
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
		MAD_BALANCE(balance_node);
		return true;
	}
	virtual tval& Find(const tkey& key)override
	{
		return BINARY_TREE<tkey, tval>::Find(key);
	}
	void draw() const {
		if (root == nullptr) {
			std::cout << "Дерево пустое\n";
			return;
		}

		int height = get_height(root);
		int width = 1 << height; 
		std::vector<std::string> lines(height * 3, std::string(width * 6, ' '));

		draw_tree(root, lines, 0, width / 2, height);

		for (const auto& line : lines) {
			std::cout << line.substr(0, width * 4) << std::endl;
		}
	}
	~AVL_TREE()// пробежаться по дереву и удалить все ноды, начиная с концов и заканчивая корнем
	{

	}// родительский диструктор вызовется сам
};