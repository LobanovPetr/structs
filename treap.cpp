#include<iostream>
#include<ctime>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>

template<typename ...Ts>
void print_all(const Ts & ...ts){
    ((std::cout << ts << ' '), ...);
    std::cout << std::endl;
}

template<typename T>
class treap
{
public:
    struct node
    {
        T val;
        int key;
        node * left;
        node * right;

        node(T val_, node * left_ = nullptr, node * right_ = nullptr): val(val_), left(left_), right(right_)
        {
            key = rand() % 100;
        }
    };

    node * root;

    std::pair<node*, node*> split_(node * ptr, T x)
    {
        if (ptr == nullptr)
        {
            return std::make_pair(nullptr, nullptr);
        }
        if (ptr->val < x)
        {
            auto p = split_(ptr->right, x);
            ptr->right = p.first;
            return std::make_pair(ptr, p.second);
        }
        else
        {
            auto p = split_(ptr->left, x);
            ptr->left = p.second;
            return std::make_pair(p.first, ptr);
        }
    }

    node * merge_(node *A, node *B)
    {
        if (A == nullptr)
        {
            return B;
        }
        if (B == nullptr)
        {
            return A;
        }

        if (A->key > B->key)
        {
            A->right = merge_(A->right, B);
            return A;
        }
        else
        {
            B->left = merge_(A, B->left);
            return B;
        }
    }

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
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        return ptr;
    }

    treap(node * ptr) :root(ptr)
    {

    }

    node * get_root()
    {
        return root;
    }

    void drop_root()
    {
        root = nullptr;
    }

    node * erase_(node * A, T x)
    {
        if (A->val == x)
        {
            node * B = merge_(A->left, A->right);
            delete A;
            return B;
        }
        if (x < A->val)
        {
            A->left = erase_(A->left, x);
        }
        else
        {
            A->right = erase_(A->right, x);
        }
        return A;
    }

    node * insert_(node * A, node * ptr)
    {
        if (A == nullptr)
        {
            return ptr;
        }
        if (ptr->key > A->key)
        {
            auto p = split_(A, ptr->val);
            ptr->left = p.first;
            ptr->right = p.second;
            return ptr;
        }
        if (ptr->val < A->val)
        {
            A->left = insert_(A->left, ptr);
        }
        else
        {
            A->right = insert_(A->right, ptr);
        }
        return A;
    }




public:
    treap()
    {
        root = nullptr;
        srand(time(NULL));
    }

    void insert(T x)
    {
        if (find_(x) != nullptr)
        {
            return;
        }
        if (root == nullptr)
        {
            root = new node(x);
            print_all(x, root->key);
            std::cout << std::endl;
            return;
        }
        else
        {
            node * ptr = new node(x);
            print_all(x, ptr->key);
            std::cout << std::endl;
            root = insert_(root, ptr);
            return;
        }
    }



    bool find(T x)
    {
        return (find_(x) != nullptr);
    }

    treap & split(T x)
    {
        auto p = split_(root, x);
        root = p.first;
        
        treap * N = new treap(p.second);
        return *N;
    }

    void merge(treap &B)
    {
        merge_(root, B.get_root());
        B.drop_root();
    }

    void erase(T x)
    {
        if (!find(x))
        {
            return;
        }
        else
        {
            root = erase_(root, x);
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

};

int main()
{

    treap<int> t;
    treap<int> p;

    t.insert(5);
    t.insert(6);
    t.insert(7);
    std::cout << std::endl << "display" << std::endl;
    t.display();
    std::cout << std::endl;
    
//     print_all("t find 5", t.find(5), "\nt find 6", t.find(6), "\nt find 7", t.find(7), "\n");
    p = t.split(6);
    std::cout << std::endl << "t display" << std::endl;
//    t.display();
    std::cout << std::endl;
    
    
    std::cout << std::endl << "p display" << std::endl;
//    p.display();
    std::cout << std::endl;
    
    

     print_all("t find 5", t.find(5), "\nt find 6", t.find(6), "\nt find 7", t.find(7), "\n");
     print_all("p find 5", p.find(5), "\np find 6", p.find(6), "\np find 7", p.find(7), "\n");
    
    t.erase(5);
    print_all("t find 5", t.find(5), "\nt find 6", t.find(6), "\nt find 7", t.find(7), "\n");
    
    

}
