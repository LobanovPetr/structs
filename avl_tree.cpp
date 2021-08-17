#include<iostream>

template<typename T>
class avl_tree
{

	struct node
	{
		node * left = nullptr;
		node * right = nullptr;
		node * par = nullptr;
		int hight = 1;
		T val;
	};

	node * root;
	int size;

	avl_tree()
	{
		root = nullptr;
		size = 0;
	}

	node * find(T x)
	{
		node * ptr = root;
		while (ptr)
		{
			if (ptr->val == x)
			{
				return ptr;
			}
			else if (x < ptr->val)
			{
				if (ptr->left == nullptr)
				{
					return ptr;
				}
				ptr = ptr->left;
			}
			else
			{
				if (ptr->right == nullptr)
				{
					return ptr;
				}
				ptr = ptr->right;
			}
		}
		return ptr;
	}

	void increas_hights(node * ptr)
	{
		while(ptr != nullptr)
		{
			ptr->hight++;
			ptr = ptr->par;
		}
	}

	void insert(T x)
	{
		node * ptr = find(x);
		if (ptr == nullptr)
		{
			root = new node();
			root->val = x;
			root->hight = 1;
			return;
		}

		if (x == ptr->val)
		{
			return;
		}

		if (x < ptr->val)
		{
			ptr->left = new node();
			ptr->left->val = x;
			ptr->left->par = ptr;
		}
		else
		{
			ptr->right = new node();
			ptr->right->val = x;
			ptr->right->par = ptr;
		}
		increas_hights(ptr);
		balance(ptr);
	}

	void remove(T x)
	{
		node * ptr = root;

	}






}