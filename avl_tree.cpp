#include<iostream>
#include<vector>
#include<ctime>

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

	node * find_(T x)
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
public:

	avl_tree()
	{
		root = nullptr;
		size = 0;
	}

	void insert(T x)
	{
		node * ptr = find_(x);
		if (ptr == nullptr)
		{
			root = new node();
			root->val = x;
			root->hight = 1;
			size++;
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
		size++;
		increas_hights(ptr);
		// balance(ptr);
	}

	void erase(T x)
	{
		node * ptr = find_(x);
		node * p, *tmp;

		if (ptr == nullptr || ptr->val != x)
		{
			return;
		}
		if (ptr->left == nullptr && ptr->right == nullptr)
		{
			if (ptr->par)
			{
				if (ptr->par->left == ptr)
				{
					ptr->par->left = nullptr;
				}
				else
				{
					ptr->par->right = nullptr;
				}
			}
		}
		else if (ptr->left == nullptr)
		{
			if (ptr->par)
			{
				if (ptr->par->left == ptr)
				{
					ptr->par->left = ptr->right;
				}
				else
				{
					ptr->par->right = ptr->right;
				}
			}
		}
		else
		{
			tmp = ptr->left;
			while(tmp->right)
			{
				tmp = tmp->right;
			}
			ptr->val = tmp->val;
			ptr = tmp;
			if (ptr->par)
			{
				if (ptr->par->left == ptr)
				{
					ptr->par->left = nullptr;
				}
				else
				{
					ptr->par->right = nullptr;
				}
			}
		}

		p = ptr->par;
		delete ptr;

		//decrease_hight(p)
		balance(p);

	}

	bool find(T x)
	{
		node * ptr = find_(x);
		if (ptr == nullptr)
		{
			return 0;
		}
		if (ptr->val == x)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	struct iterator
    {
        node * ptr;
        
        bool operator!=(const iterator & x)
        {
            return ptr != x.ptr;
        }
        
        iterator &operator++()
        {
            if (ptr ->right)
            {
                ptr = ptr -> right;
                
                while (ptr->left)
                {
                    ptr = ptr->left;
                }
                return *this;
            }
            while(ptr->par != nullptr)
            {
                if (ptr -> par -> left == ptr)
                {
                    ptr = ptr->par;
                    return *this;
                }
                ptr = ptr -> par;
            }
            ptr = nullptr;
            return *this;
        }
        const T& operator*()
        {
            return ptr->val;
        }
    };
    
    iterator begin()
    {
        node * ptr = root;
        while (ptr->left)
        {
            ptr = ptr -> left;
        }
        iterator res;
        res.ptr = ptr;
        return res;
    }
    iterator end()
    {
        iterator res;
        res.ptr = nullptr;
        return res;
    }
};

int main()
{
	avl_tree<int> t;
	std::vector<int> v;
	srand(time(NULL));
	int tmp;


	const int n = 10;


	// for (int i = 0; i < n; ++i)
	// {
	// 	tmp = rand() % 1000;
	// 	v.push_back(rand() % 1000);

	// }

	std::cout << t.find(0) << std::endl;
	std::cout << t.find(1) << std::endl;
	std::cout << t.find(2) << std::endl;
	std::cout << t.find(3) << std::endl;

	t.insert(0);
	std::cout << t.find(0) << std::endl;

	for(auto a : t)
	{
		std::cout << a << ' ';
	}
	std::cout << std::endl;



}


