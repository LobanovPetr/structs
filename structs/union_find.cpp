struct union_find
{
    vector<size_t> parents;
    vector<size_t> ranks;
    size_t size;
    
    union_find(): parents(), ranks(), size(0){};
    union_find(size_t size_): parents(size_), ranks(size_, 0), size(size_)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parents[i] = i;
        }
    }
    void add_new()
    {
        parents.push_back(size);
        ranks.push_back(0);
        size++;
    }
    size_t get(size_t x)
    {
        if (x >= size)
        {
            throw;
        }
        vector<size_t> idx;
        while(parents[x] != x)
        {
            idx.push_back(x);
            x = parents[x];
        }
        
        for (auto &it : idx)
        {
            parents[it] = x;
        }
        
        return x;
    }
    void join(size_t x, size_t y)
    {
        if ( (x = get(x)) ==  (y = get(y)))
        {
            return;
        }
        if (ranks[x] > ranks[y]) // rank[x] < rank[y]
        {
            swap(x, y);
        }
        parents[x] = y;
        if (ranks[x] == ranks[y])
        {
            ranks[y]++;
        }
    }
};
