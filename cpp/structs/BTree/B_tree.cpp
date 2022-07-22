#include "B_tree.hpp"

std::pair<bool, size_t> BNode::lower_bound(const char * s)
{
    if (size == 0)                                          //it is root
    {
        return std::pair<bool, size_t>(false, 0);
    }
    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(s, keys[i]) == 0)
        {
            return std::pair<bool, size_t>(true, i);    // found, i + 1 does not matter
        }
        if (strcmp(s, keys[i]) < 0)
        {
            return std::pair<bool, size_t>(false, i);   // not found, probably at the i children
        }
    }
    return std::pair<bool, size_t>(false, size);               // not found, probably at the 0 children
}

void BNode::print()
{
    printf("keys ");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%s ", keys[i]);
    }
    printf("\n");
}

/*
 erase from the leaf
*/
void BNode::erase(size_t idx)
{
    free(keys[idx]);
    for (size_t i = idx; i < size - 1; ++i)
    {
        keys[i] = keys[i + 1];
    }
    keys[size - 1] = nullptr;
    size--;
}

void BNode::print_whole()
{
//    printf("keys\n");
    for (int i = 0; i < size; ++i)
    {
        if (keys[i] == nullptr)
        {
            printf("null ");
            continue;
        }
        printf("%s ", keys[i]);
    }
}
/*
 we know that s isn't here
 change size
 need to place new children to children[]
*/
void BNode::insert(const char * s)
{
    auto x = lower_bound(s);
    if (x.first)
    {
        throw std::logic_error("there is string!!!");
    }
    size_t idx = x.second;
    for (size_t i = size; i > idx; i--)
    {
        keys[i] = keys[i - 1];
        if (!is_leaf)
        {
            children[i + 1] = children[i];
        };
    }
    
    keys[idx] = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(keys[idx], s);
    size++;
    return;
}

/*
 move all elements left
 we guarantee ptr->size >= M
 
 ptr->size becomes ptr->size - 1
 return left children of ptr and separator
 */
std::pair<BNode *, char *> BTree::moveLeft(BNode * ptr)
{
    std::pair<BNode *, char*> toReturn;
    if (ptr->is_leaf)
    {
        toReturn.first = nullptr;
    }
    else
    {
        toReturn.first = ptr->children[0];
    }
    toReturn.second = ptr->keys[0];
    for (size_t i = 0; i < ptr->size - 1; ++i)
    {
        ptr->keys[i] = ptr->keys[i + 1];
        if(!ptr->is_leaf)
        {
            ptr->children[i] = ptr->children[i + 1];
        };
    }
    if(!ptr->is_leaf)
    {
        ptr->children[ptr->size - 1] = ptr->children[ptr->size];
        ptr->children[ptr->size] = nullptr;
    };
    ptr->keys[ptr->size - 1] = nullptr;
    ptr->size--;
    return toReturn;
}

std::pair<BNode *, char *> BTree::moveRight(BNode * ptr)
{
    std::pair<BNode *, char *> toReturn;
    if (ptr->is_leaf)
    {
        toReturn.first = nullptr;
    }
    else
    {
        toReturn.first = ptr->children[ptr->size];
        ptr->children[ptr->size] = nullptr;
    }
    toReturn.second = ptr->keys[ptr->size - 1];
    ptr->keys[ptr->size - 1] = nullptr;
    ptr->size--;
    return toReturn;
}

/*
 for node that has M - 1 keys
*/
void BTree::pushRight(BNode * ptr)
{
    if(!ptr->is_leaf)
    {
        ptr->children[ptr->size + 1] = ptr->children[ptr->size];
        
    };
    for (size_t i = ptr->size; i > 0; --i)
    {
        ptr->keys[i] = ptr->keys[i - 1];
        if (!ptr->is_leaf)
        {
            ptr->children[i] = ptr->children[i - 1];
        };
    }
    ptr->keys[0] = nullptr;
    if (!ptr->is_leaf)
    {
        ptr->children[0] = nullptr;
    }
    
    ptr->size++;
}




/*
 ptr->children[idx] has M - 1 keys
 ptr->children[idx + 1] has M - 1 keys
 
 merge ptr->children[idx] and ptr->children[idx + 1]
 ptr->children[idx]->keys + ptr->keys[idx] + ptr->children[idx + 1]->keys
 
*/
void BTree::mergeChildren(BNode * ptr, size_t idx)
{
    ptr->children[idx]->keys[M - 1] = ptr->keys[idx];
    
    
    for (size_t i = 0; i < M - 1; ++i)
    {
        ptr->children[idx]->keys[M + i] = ptr->children[idx + 1]->keys[i];
        ptr->children[idx + 1]->keys[i] = nullptr;
        if(!ptr->children[idx]->is_leaf)
        {
            ptr->children[idx]->children[M + i] = ptr->children[idx + 1]->children[i];
            ptr->children[idx + 1]->children[i]->parent = ptr->children[idx];
            ptr->children[idx + 1]->children[i] = nullptr;
        }
    }
    if(!ptr->children[idx]->is_leaf)
    {
        ptr->children[idx]->children[2 * M - 1] = ptr->children[idx + 1]->children[M - 1];
        ptr->children[idx + 1]->children[M - 1]->parent = ptr->children[idx];
        ptr->children[idx + 1]->children[M - 1]= nullptr;
    }
    ptr->children[idx]->size = 2 * M - 1;
    
    
    
    free(ptr->children[idx + 1]->keys);
    
    if(!ptr->children[idx]->is_leaf)
    {
        free(ptr->children[idx + 1]->children);
    }
    free(ptr->children[idx + 1]);
    ptr->children[idx + 1] = nullptr;
    
    for (size_t i = idx ; i < ptr->size - 1; ++i)
    {
        ptr->keys[i] = ptr->keys[i + 1];
        ptr->children[i + 1] = ptr->children[i + 2];
    }
    ptr->keys[ptr->size - 1] = nullptr;
    ptr->children[ptr->size] = nullptr;
    
    ptr->size--;
    
}


BNode * BTree::initializeNode()
{
    BNode * toReturn = (BNode *)calloc(1, sizeof(BNode));
    toReturn->keys = (char **)calloc((2 * M - 1), sizeof(char *));
    toReturn->children = (BNode **)calloc((2 * M), sizeof(BNode*));
    toReturn->is_leaf = false;
    toReturn->size = 0;
    toReturn->parent = nullptr;
    return toReturn;
}
BNode * BTree::initializeLeaf()
{
    BNode * toReturn = (BNode *)malloc(sizeof(BNode));
    toReturn->keys = (char **)calloc((2 * M - 1), sizeof(char *) );
    toReturn->is_leaf = true;
    toReturn->size = 0;
    toReturn->parent = nullptr;
    return toReturn;
}

/*
 we know that ptr has 2 * M - 1 keys
 change size of ptr
 first argument of return value - right node, second - key
*/
std::pair<BNode *, char *> BTree::splitNode(BNode * ptr)
{
    if (ptr->size != 2 * M - 1)
    {
        throw std::logic_error("not enough keys to split");
    }
    BNode * right;
    char * value;
    size_t idx;
    idx = M;
    if (ptr->is_leaf)
    {
        right = initializeLeaf();
    }
    else
    {
        right = initializeNode();
    }
    for (size_t i = M; i < 2 * M - 1; ++i)
    {
        right->keys[i - M] = ptr->keys[i];
        ptr->keys[i] = nullptr;
        if (!ptr->is_leaf)
        {
            right->children[i - M] = ptr->children[i];
            ptr->children[i]->parent = right;
            ptr->children[i] = nullptr;
        }
    }
    if (!ptr->is_leaf) {
        right->children[M - 1] = ptr->children[2 * M - 1];
        ptr->children[2 * M - 1]->parent = right;
        ptr->children[2 * M - 1] = nullptr;
    };
//    right->parent = ptr->parent;
    value = ptr->keys[M - 1];
    ptr->keys[M - 1] = nullptr;
    ptr->size = M - 1;
    right->size = M - 1;
    
    return std::pair<BNode *, char *>(right, value);
}
/*
 we know that children[idx] has 2 * M - 1 keys
 split children[idx] of parent
 par gets new key
 par changes size
 right and left children have size M - 1
 return key
*/
char * BTree::splitChildren(BNode * par, size_t idx)
{
    auto x = splitNode(par->children[idx]);
    
    for (size_t i = par->size; i > idx; i--)
    {
        par->keys[i] = par->keys[i - 1];
        par->children[i + 1] = par->children[i];
    }
    
    par->keys[idx]= x.second;
    par->children[idx + 1] = x.first;
    par->size++;
    x.first->parent = par;
    return x.second;
}


void BTree::insert(const char * s)
{
    BNode * ptr = root;
    size_t idx;
    std::pair<BNode *, char *> x;
    std::pair<bool, size_t> y;      // for lower bound
    char * str;
    if (ptr->size == 2 * M - 1)
    {
        BNode * tmp = initializeNode(); // new root
        x = splitNode(ptr);
        tmp->keys[0] = x.second;
        tmp->children[0] = root;
        tmp->children[1] = x.first;
        tmp->children[0]->parent = tmp;
        tmp->children[1]->parent = tmp;
        tmp->size++;
        root = tmp;
        ptr = root;
        tmp = nullptr;
    }
    while(true)
    {
        y = ptr->lower_bound(s);
        if (y.first) // found
        {
            return;
        }
        if (ptr->is_leaf)
        {
            ptr->insert(s);
            SIZE++;
            return;
        }
        idx = y.second;
        if (ptr->children[idx]->size == 2 * M - 1)  // children is full
        {
            str = splitChildren(ptr, idx);
            if (strcmp(str, s) == 0)                // key to separete is equal to s
            {
                return;                             // found
            }
            if (strcmp(str, s) < 0)                 // new key is less than s
            {
                idx++;
            }
        }
        ptr = ptr->children[idx];
    }
}

void BTree::remove(const char * s)
{
    BNode * ptr = root;
    std::pair<bool, size_t> x;      //for lower bound
    std::pair<BNode *, char *> y;   // for moves
    bool need_to_go_left = false;
    bool need_to_go_right = false;
    BNode * next = nullptr;
    char ** toReplace;
    
    if (root->is_leaf)
    {
        x = ptr->lower_bound(s);
        if (x.first)
        {
            SIZE--;
            ptr->erase(x.second);
            return;
        }
        else
        {
            return;
        }
    }
    
    // we need to check if root has keys size 1
    // and both left and right children have size M - 1
    // then we need to change root
    
    if (ptr->size == 1 && (ptr->children[0]->size == M - 1) && (ptr->children[1]->size == M - 1))
    {
        mergeChildren(ptr, 0);      // ptr is empty
        root = ptr->children[0];    // new root
        free(ptr->children);
        free(ptr->keys);
        free(ptr);
        root->parent = nullptr;
        ptr = root;
    }
    
    while(true)
    {
        if (need_to_go_left)
        {
            if (ptr->is_leaf)
            {
                *toReplace = ptr->keys[0];
                moveLeft(ptr);
                SIZE--;
                return;
            }
            else
            {
                x = std::pair<bool, size_t>(false, 0);
            }
        }
        else if (need_to_go_right)
        {
            if (ptr->is_leaf)
            {
                *toReplace = ptr->keys[ptr->size - 1];
                moveRight(ptr);
                SIZE--;
                return;
            }
            else
            {
                x = std::pair<bool, size_t>(false, ptr->size);
            }
        }
        else
        {
            x = ptr->lower_bound(s);
        }
        
        if (ptr->is_leaf)   //need just to delete
        {
            if (x.first)
            {
                ptr->erase(x.second);    // need just to delete
                SIZE--;
                return;
            }
            else                            // not found
            {
                return;
            }
        }
        else    // not leaf
        {
            if (x.first) // element found
            {
                if (ptr->children[x.second + 1]->size >= M) // it's okey go right and then left
                {
                    free(ptr->keys[x.second]);
                    toReplace = &(ptr->keys[x.second]);
                    need_to_go_left = true;
                    ptr = ptr->children[x.second + 1];
                    continue;
                }
                if (ptr->children[x.second]->size >= M) // it's okey go left and then right
                {
                    free(ptr->keys[x.second]);
                    toReplace = &(ptr->keys[x.second]);
                    need_to_go_right = true;
                    ptr = ptr->children[x.second];
                    continue;
                }
                mergeChildren(ptr, x.second);
                ptr = ptr->children[x.second];
                continue;
            }
        }
        
        
        if (ptr->children[x.second]->size >= M)     // it's okey
        {
            next = ptr->children[x.second];
        }
        else if (x.second > 0 && (ptr->children[x.second - 1]->size >= M)) // take from left brother
        {
            y = moveRight(ptr->children[x.second - 1]);
            pushRight(ptr->children[x.second]);
            ptr->children[x.second]->keys[0] = ptr->keys[x.second - 1];
            if (!ptr->children[x.second]->is_leaf)
            {
                ptr->children[x.second]->children[0] = y.first;
                y.first->parent = ptr->children[x.second];
            }
            ptr->keys[x.second - 1] = y.second;
            next = ptr->children[x.second];
        }
        else if (x.second < ptr->size && (ptr->children[x.second + 1]->size >= M)) // take from right brother
        {
            
            y = moveLeft(ptr->children[x.second + 1]);
            (ptr->children[x.second]->size)++;
            ptr->children[x.second]->keys[M - 1] = ptr->keys[x.second];
            if (!ptr->children[x.second]->is_leaf)
            {
                ptr->children[x.second]->children[M] = y.first;
                y.first->parent = ptr->children[x.second];
            }
            ptr->keys[x.second] = y.second;
            next = ptr->children[x.second];
        }
        else if (x.second < ptr->size)
        {
            mergeChildren(ptr, x.second); // merge with right children
            next = ptr->children[x.second];
        }
        else
        {
            mergeChildren(ptr, x.second - 1); // merge with left children
            next = ptr->children[x.second - 1];
        }
        ptr = next;
    }
}

BTree::iterator BTree::find(const char * s)
{
    BNode * ptr = root;
    iterator toReturn;
    std::pair<bool, size_t> x;
    while (!ptr->is_leaf)
    {
        x = ptr->lower_bound(s);
        if (x.first)
        {
            toReturn.node = ptr;
            toReturn.value = ptr->keys[x.second];
            return toReturn;
        }
        ptr = ptr->children[x.second];
    }
    x = ptr->lower_bound(s);
    if (x.first)
    {
        toReturn.node = ptr;
        toReturn.value = ptr->keys[x.second];
        return toReturn;
    }
    toReturn.node = nullptr;
    toReturn.value = "1";
    return toReturn;
}

bool BTree::contain(const char * s)
{
    auto it = find(s);
    if (it != end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

BTree::iterator BTree::begin()
{
    BTree::iterator toReturn;
    BNode * ptr = root;
    
    if (SIZE == 0)
    {
        toReturn.node = nullptr;
        toReturn.value = "=";
        return toReturn;
    }
    
    while (!ptr->is_leaf)
    {
        ptr = ptr->children[0];
    }
    
    toReturn.node = ptr;
    toReturn.value = ptr->keys[0];
    
    return toReturn;
}

BTree::iterator BTree::rbegin()
{
    iterator toReturn;
    BNode * ptr = root;
    if (SIZE == 0)
    {
        toReturn.node = nullptr;
        toReturn.value = "=";
        return toReturn;
    }
    while (!ptr->is_leaf)
    {
        ptr = ptr->children[ptr->size];
    }
    toReturn.node = ptr;
    toReturn.value = ptr->keys[ptr->size - 1];
    return toReturn;
}

BTree::iterator BTree::rend()
{
    iterator toReturn;
    toReturn.node = nullptr;
    toReturn.value = "0";
    return toReturn;
}

BTree::iterator BTree::end()
{
    BTree::iterator toReturn;
    toReturn.node = nullptr;
    toReturn.value = "1";
    
    return toReturn;
}



bool BTree::iterator::operator<(const iterator & it) const
{
    if (node == nullptr && strcmp(value, "=") == 0)  // tree is empty
    {
        return false;
    }
    if (it.node == nullptr && strcmp(it.value, "=") == 0)
    {
        return false;
    }
        
    if (node == nullptr && strcmp(value, "0") == 0)  // this is rend
    {
        if (it.node != nullptr)                      // it is normal iterator
        {
            return true;
        }
        if (strcmp(it.value, "1") == 0)              // it is end
        {
            return true;
        }
        return false;                                // it is rend
    }
    if (node == nullptr)                             // this is end
    {
        return false;
    }
    //this is normal iterator
    if (it.node == nullptr && (strcmp(it.value, "0") == 0)) // it is rend
    {
        return false;
    }
    if (it.node == nullptr) // it is end
    {
        return true;
    }
    if (strcmp(value, it.value) < 0)
    {
        return true;
    }
    return false;
}

bool BTree::iterator::operator!=(const iterator & it)
{
    return !((!operator<(it)) and !(it < *this));
}

void BTree::iterator::operator++()
{
    auto x = node->lower_bound(value);
    if (node->is_leaf)
    {
        if (x.second < node->size - 1)
        {
            value = node->keys[x.second + 1];
            return;
        }
        node = node->parent;
        while (node != nullptr)
        {
            x = node->lower_bound(value);
            if (x.second < node->size)
            {
                value = node->keys[x.second];
                return;
            }
            node = node->parent;
        }
        value = "1";
        return;
    }
    node = node->children[x.second + 1];
    while (!node->is_leaf)
    {
        node = node->children[0];
    }
    value = node->keys[0];
}

void BTree::iterator::operator--()
{
    auto x = node->lower_bound(value);
    if (node->is_leaf)
    {
        if (x.second > 0)
        {
            value = node->keys[x.second - 1];
            return;
        }
        node = node->parent;
        while (node != nullptr)
        {
            x = node->lower_bound(value);
            if (x.second > 0)
            {
                value = node->keys[x.second - 1];
                return;
            }
            node = node->parent;
        }
        value = "0";
        return;
    }
    node = node->children[x.second];
    while (!node->is_leaf)
    {
        node = node->children[node->size];
    }
    value = node->keys[node->size - 1];
}

const char * BTree::iterator::operator*()
{
    return value;
}

void BTree::rec_clear(BNode * ptr)
{
    if (ptr->is_leaf)
    {
        for (size_t i = 0; i < ptr->size; ++i)
        {
            free(ptr->keys[i]);
        }
        free(ptr->keys);
        free(ptr);
        return;
    }
    for (size_t i = 0; i <= ptr->size; ++i)
    {
        rec_clear(ptr->children[i]);
    }
    
    for (size_t i = 0; i < ptr->size; ++i)
    {
        free(ptr->keys[i]);
    }
    free(ptr->keys);
    free(ptr->children);
    free(ptr);
    return;
}

void BTree::clear()
{
    rec_clear(root);
    root = initializeLeaf();
    SIZE = 0;
    return;
}

void BTree::print_struct()
{
    std::queue<std::pair<BNode *, int> > queue;
    
    queue.push(std::pair<BNode *, int> (root, 1));
    printf("     ");
    while(queue.size())
    {
//        printf("\t\t");
        queue.front().first->print_whole();
        printf("    ");
        if (queue.front().second)
        {
            printf("\n");
        }
        if (!queue.front().first->is_leaf)
        {
            for (size_t i = 0; i < queue.front().first->size; ++i)
            {
                queue.push(std::pair<BNode *, int>(queue.front().first->children[i], 0));
            }
            if (queue.front().second)
            {
            queue.push(std::pair<BNode *, int>(queue.front().first->children[queue.front().first->size], 1));
            }
            else
            {
                queue.push(std::pair<BNode *, int>(queue.front().first->children[queue.front().first->size], 0));
            }
        }
        queue.pop();
    }
}

BTree::~BTree()
{
    clear();
    free(root->keys);
    free(root);
    return;
}


