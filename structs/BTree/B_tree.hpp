#ifndef B_tree_hpp
#define B_tree_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>
#include <queue>
#include <stdexcept>



struct BNode
{
    char ** keys;       // array of strings
    BNode * parent;     // pointer for parent
    BNode ** children;  // pointer for children
    bool is_leaf;
    size_t size;        // number of units
    
    std::pair<bool, size_t> lower_bound(const char * s); // is found?, idx of children
    void insert(const char * s);
    void erase(size_t idx);
    void print();
    void print_whole();
};


class BTree
{
    BNode * root;
    
    size_t M;           // min keys = M - 1 max keys = 2 * M - 1
                        // M = 3 min = 2 max = 5
    
    size_t SIZE;        // num of elements
    
    BNode * initializeNode();
    BNode * initializeLeaf();
    std::pair<BNode *, char *> splitNode(BNode *);  // right and key
    char * splitChildren(BNode *, size_t);          // split children return key
    std::pair<BNode *, char *> moveLeft(BNode *);
    std::pair<BNode *, char *> moveRight(BNode *);
    void pushRight(BNode *);
    void mergeChildren(BNode *, size_t idx);
    void rec_clear(BNode *);
public:
    
    class iterator
    {
        BNode * node;
        const char * value;
    public:
        friend class BTree;
        void operator++();
        void operator--();
        bool operator<(const iterator&) const;
        bool operator!=(const iterator&);
        const char * operator*();
    };
    
    
    
    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();
    
    void print_struct();
    
    BTree(size_t M_ = 3){M = M_; root = initializeLeaf(); SIZE = 0;};
    void insert(const char *);
    bool contain(const char *);
    void remove(const char *);
    iterator find(const char *);
    void clear();
    size_t size(){return SIZE;};
    
    
    ~BTree();
    
    
};


#endif
