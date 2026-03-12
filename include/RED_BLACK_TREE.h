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
public:
	RED_BLACK_TREE()
	{
		Node* Node::nil = new Node;
	}

};