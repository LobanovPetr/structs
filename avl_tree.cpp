#include<iostream>

template<typename T>
class avl_tree
{

	struct node
	{
		node * left = nullptr;
		node * right = nullptr;
		int hight = 1;
		T val;
	};

	node root;
	int size;

	avl_tree()
	{
		root = nullptr;
		size = 0;
	}

	bool find(T x)
	{
		node * ptr = root;
		while (ptr != nullptr)
		{
			if (ptr->val == x)
			{
				return true;
			}
			else if (x < ptr->val)
			{
				ptr = ptr->left;
			}
			else
			{
				ptr = ptr->right;
			}
		}
		return false;
	}

	




}