#include<iostream>
#include<vector>
#include<ctime>
#include<queue>
#include<set>

template<typename T>
class avl_tree
{
public:
	struct node
	{
		node * left = nullptr;
		node * right = nullptr;
		node * par = nullptr;
		int hight = 1;
		T val;

		node() : hight(0)
		{
		}
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

	void hights(node * ptr)
	{
		int l, r;
		while(ptr != nullptr)
		{
			if (ptr->right == nullptr && ptr->left == nullptr)
			{
				ptr->hight = 0;
			}
			else
			{
				l = ((ptr->left)?ptr->left->hight:0);
				r = ((ptr->right)?ptr->right->hight:0);
				ptr->hight = ((l > r)?l:r) + 1;
			}
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
		node * tmp;
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
			tmp = ptr->left;
		}
		else
		{
			ptr->right = new node();
			ptr->right->val = x;
			ptr->right->par = ptr;
			tmp = ptr->right;
		}
		size++;
		hights(tmp);
		return;
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
					// std::cout << "we here" << std::endl;
				}
				else
				{
					ptr->par->right = nullptr;
				}
			}
			else
			{
				// std::cout << "we here" << std::endl;
				delete ptr;
				root = nullptr;
				return;
			}
		}
		else if (ptr->right == nullptr)
		{
			if (ptr->par)
			{
				if (ptr->par->right == ptr)
				{
					ptr->par->right = ptr->left;
				}
				else
				{
					ptr->par->left = ptr->left;
				}
				ptr->left->par = ptr->par;
			}
			else
			{
				root = ptr->left;
				ptr->left->par = nullptr;
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
				ptr->right->par = ptr->par;
			}
			else
			{
				root = ptr->right;
				ptr->right->par = nullptr;
			}
		}
		else
		{
			tmp = ptr->left;
			while(tmp->right)
			{
				tmp = tmp->right;
			}
			// std::cout << "tmp val " << tmp->val << std::endl;
			ptr->val = tmp->val;
			ptr = tmp;
			if (ptr->par)
			{
				if (ptr->par->left == ptr)
				{
					ptr->par->left = ptr->left;
				}
				else
				{
					ptr->par->right = ptr->left;
				}
				if (ptr->left)
				{
					ptr->left->par=ptr->par;
				}
			}
		}
		// std::cout <<  "ptr val " << ptr->val << std::endl;
		size--;
		p = ptr->par;
		if (ptr == root)
		{
			root = nullptr;
		}
		else
		{
			delete ptr;
		}
		hights(p);
		// if (!p)
		// {
		// 	std::cout << "no parent " << std::endl;
		// }
		// std::cout << "root val " << root->val << std::endl;

		// decrease_hight(p);
		//balance(p);

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

	void display()
	{
		std::queue<node *> q;
		q.push(root);
		if (root == nullptr)
		{
			return;
		}
		T prev = root->val;


		while(!q.empty())
		{
			if (q.front()->left != nullptr)
			{
				q.push(q.front()->left);
			}
			if (q.front()->right != nullptr)
			{
				q.push(q.front()->right);
			}
			if (q.front()->val < prev)
			{
				std::cout << std::endl;
			}
			prev = q.front()->val;
			std::cout << q.front()->val << ' ';

			q.pop();
		}
	}

	int check_parents(node * ptr = NULL)
	{
		if (ptr == NULL)
		{
			ptr = root;
		}
		if (root == nullptr)
		{
			return 0;
		}
		// std::cout << ptr->val << std::endl;
		if (ptr && ptr->left && ptr->right)
		{
			return check_parents(ptr->left) + check_parents(ptr->right);
		}
		if (ptr->left != nullptr)
		{
			if (ptr->left->par == ptr)
			{
				return check_parents(ptr->left);
			}
			else
			{
				return -1;
			}
		}
		if (ptr->right != nullptr)
		{
			if (ptr->right->par == ptr)
			{
				return check_parents(ptr->right);
			}
			else
			{
				return -1;
			}
		}
		return 0;
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
        const int hight()
        {
        	return ptr->hight;
        }
    };
    
    iterator begin()
    {
        node * ptr = root;
        while (ptr && ptr->left)
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


const int w[] = {33, 76, 62, 0, 4, 35, 27, 41, 47, 86};

int main()
{
	avl_tree<int> t;
	std::vector<int> v;
	srand(time(NULL));
	int tmp;


	// const int n = 10;

	// for (int i = 0; i < n; ++i)
	// {
	// 	tmp = rand() % 100;
	// 	v.push_back(tmp);
	// 	std::cout << tmp << " ";
	// }
	// std::cout << std::endl;


	// for (int i = 0; i < 10; ++i)
	// {
	// 	t.insert(w[i]);
	// }
	// for (auto a = t.begin(); a != t.end(); ++a)
	// {
	// 	std::cout << *a  << " " << a.hight() << std::endl;
	// }

	// std::cout << std::endl;
	// std::cout << "parents = " << t.check_parents() << std::endl;

	// for (auto a : t)
	// {
	// 	std::cout << a << ' ';
	// }
	// std::cout << std::endl;
	// std::cout << std::endl;
	// std::cout << std::endl;
	// std::cout << std::endl;

	// for (int i = 0; i < 10; ++i)
	// {
	// 	std::cout << "delete - "<< w[i] << std::endl;
	// 	t.erase(w[i]);
	// 	for (auto a : t)
	// 	{
	// 		std::cout << a << ' ';
	// 	}
	// 	std::cout << std::endl;
	// 	std::cout << std::endl;
		// std::cout << std::endl;
		// t.display();
		// std::cout << std::endl;
		// std::cout << "parents = " <<  t.check_parents() << std::endl;
		// std::cout << std::endl;
		// std::cout << std::endl;

	// for(auto a : t)
	// {
	// 	std::cout << " a" << std::endl;
	// }

	

	// std::cout << (t.begin() != t.end()) << std::endl;
	// std::cout << (t.begin().ptr) << std::endl;


	// std::cout << "delete - " << w[7] << std::endl;
	// t.erase(w[7]);
	// std::cout << t.root->val << std::endl;
	// std::cout << t.root->right->val << std::endl;
	// std::cout << (t.root->left == nullptr) << std::endl;
	// std::cout << (t.root->right->left == nullptr) << std::endl;
	// std::cout << (t.root->right->right == nullptr) << std::endl;
	// std::cout << (t.root->)

	// for (auto a : t)
	// {
	// 	std::cout << a << ' ';
	// }

	// std::cout << t.root->val << std::endl;
	// std::cout << t.root->left->val << std::endl;
	// std::cout << t.root->left->par->val << std::endl;

	// std::cout << t.root->right->val << std::endl;
	// std::cout << t.root->right->par->val <<std::endl;

	// std::cout << t.find_(41)->val << std::endl;
	// t.erase(41);


	for (int i = 0; i < 100; ++i)
	{
		std::cout << i << std::endl;
		avl_tree<int> t;
		std::set<int> s;
		std::vector<int> v;
		int idx;

		for (int j = 0; j < 100000; ++j)
		{
			tmp = rand() % 100;
			v.push_back(tmp);
			s.insert(tmp);
			t.insert(tmp);


		}

		auto it1 = t.begin();
		auto it2 = s.begin();

		for(;it1 != t.end(); ++it1, ++it2)
		{
			if (*it1 != *it2)
			{
				std::cout << "bad insert" << std::endl;
			}
		}


		for(int j = 0; j < 100000; ++j)
		{
			idx = rand() % 100;
			s.erase(tmp);
			t.erase(tmp);
		}

		it1 = t.begin();
		it2 = s.begin();

		for(;it1 != t.end(); ++it1, ++it2)
		{
			if (*it1 != *it2)
			{
				std::cout << "bad erase" << std::endl;
			}
		}
	}
	





	// std::cout << t.find(0) << std::endl;
	// std::cout << t.find(1) << std::endl;
	// std::cout << t.find(2) << std::endl;
	// std::cout << t.find(3) << std::endl;

	// t.insert(0);
	// std::cout << t.find(0) << std::endl;

	// for(auto a : t)
	// {
	// 	std::cout << a << ' ';
	// }
	// std::cout << std::endl;

	// t.erase(33);

	// for(auto a : t)
	// {
	// 	std::cout << a << ' ';
	// }
	// std::cout << std::endl;



	// for (int i = 0; i < n; ++i)
	// {
	// 	tmp = rand() % n;
	// 	std::cout << "del " << v[tmp] << std::endl;
	// 	t.erase(v[tmp]);
	// 	for (auto a : t)
	// 	{
	// 		std::cout << a << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }

	// t.erase(0);
	// t.erase(1);

	// std::cout << t.find(0) << std::endl;



}


