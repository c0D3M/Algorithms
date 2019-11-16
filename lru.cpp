class LRUCache {
    
    typedef struct node
    {
        int key;
        int value;
        struct node *prev;
        struct node *next;
    }N;
    unordered_map<int, N*> hash;
    N *pool;
    N *front; //head of list
    N *back;
    
    void insert(N* node, int key, int value)
    {
        //Insert at front of link list
        node->key = key;
        node->value =value;
        node->prev = NULL;
        node->next = front;
        if(front)
            front->prev = node;
        front = node;
        if(!back) // when list is empty
            back = front;
        hash[key] = node;//Insert in hash table
    }
    void update(N *n, int value)
    {
        n->value = value; // update the valie
        if(n==front) // if update the front node, no processing required
            return;
        // re-wire
        if(n->prev)
            n->prev->next = n->next;
        if(n->next)
            n->next->prev = n->prev;
        else//Back pointer is updated when the back node is accessed
            back = n->prev;// update back pointer
        
        //Move to top
        n->next = front;
        n->prev = NULL;
        front->prev = n;
        front = n;
    }
    void remove()
    {
        N * node = back->prev;
        if(node)
            node->next = NULL;
        back = node;
    }
    int n;
    int size;
public:
    LRUCache(int capacity) {
        n = capacity;
        size = 0;
        pool = new N[n];
        front = back = NULL;
    }
    
    int get(int key) {
        
        if(hash.find(key)==hash.end())
            return -1;
        else
        {
            update(hash[key], hash[key]->value);
            return hash[key]->value;
        }
    }
    
    void put(int key, int value) 
    {
        //cout<< value<<"\n";
        N *node;
        //If existing key is geting inserted
        if(hash.find(key)!=hash.end()) //key present
            update(hash[key], value);
        else
        {
            if(hash.size()==n)
            {
                
                node = back;
                hash.erase(back->key);// Remove the entry from  hash table
                remove(); //Remove the back node from LRU List
            }
            else
                node = &pool[size++];
            
            insert(node, key, value);
        }
    }
};
