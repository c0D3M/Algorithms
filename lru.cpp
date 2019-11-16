class LRUCache {
    unordered_map<int, int> hash;
    list<int> lru;
    int n;
public:
    void findAndDelete(int key)
    {
            // Find the key in list and delete
            for (auto it = lru.begin(); it != lru.end(); ++it) 
            {
                //cout <<*it<<"\n";
                if(*it==key)
                {
                    lru.erase(it);
                    break;
                }
            }
    }
    LRUCache(int capacity) {
        n = capacity;
    }
    
    int get(int key) {
        
        if(hash.find(key)==hash.end())
            return -1;
        else
        {
            findAndDelete(key);
            //and move to front
            lru.push_front(key);
            
            return hash[key];
        }
            
        
    }
    
    void put(int key, int value) {
        //If existing key is geting inserted
        if(hash.find(key)!=hash.end()) //key present
            findAndDelete(key);
        
        if(hash.find(key)==hash.end())
        {
            if(hash.size()==n)
            {
                // Find tail item from LRU list.
                int indx = lru.back();
                lru.pop_back();
                hash.erase(indx);    
            }
        }
        
            
        hash[key] = value;
        //insert in LRU List;
        lru.push_front(key);        
    }
};
