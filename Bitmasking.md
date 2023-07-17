In this set of problem we explore all possible bit combination to deduce which give us max/min result.
How to identify: The input would have limited size  so that bit combination would also be less.
An alternatiove way to solve this problem is using Backtracking 
DP can also be used as an optimization

[1601. Maximum Number of Achievable Transfer Requests](https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/description/)  
**Backtracking method** :  
For each request : either skip or take it  , when we take it , src node degree is decreased and dst degree is increased  and recursively called 1(because we too the request) + 
when we skip, we dont do anything, take max of it skip or take.
When all requests are done, see if all nodes are balanced ?if yes return 0 else INT_MIN.
```
if (i == requests.size())
        return count(begin(bal), begin(bal) + n, 0) == n ? 0 : INT_MIN;
    --bal[requests[i][0]];
    ++bal[requests[i][1]];
    auto take = 1 + maximumRequests(n, requests, i + 1);
    ++bal[requests[i][0]];
    --bal[requests[i][1]];
    return max(take, maximumRequests(n, requests, i + 1));
```
**Bitmask method** :  
If there are *k* requestst there are total [0 to 2^k -1] combination
1. Generate all this combination in loop.  
2. Now for each mask combination, see if request is set, increase/decrease node count.  
3. At the end see if we are stable(all building is 0)  if yes number of requests in this bitmask can be answer. Take max of it.  
```
int r  = requests.size();
   int ans = 0;
   auto  find=[&](int mask){
       int cnt = 0;
       vector<int> buildings(n, 0);
       for(int i =0; i < r; ++i){
           if( (1<<i) & mask){
               ++cnt;
                buildings[requests[i][0]]--; // indegree decreased
                buildings[requests[i][1]]++;// indegree increase
           }
       }
       return count(buildings.begin(), buildings.end(), 0) == n ? cnt : INT_MIN;
   };

   for(int i = 0; i < (1 << r) ; ++i){
       ans = max(ans, find(i));
   }
   return ans;
```

[2305. Fair Distribution of Cookies](https://leetcode.com/problems/fair-distribution-of-cookies/)  
Each child should have some set of bag, so we have 'k' childs and  1<<n cookie bit set
For each child, he can take either coookies from any bitmask set received,  so we sum those number where bit is set
and then recurse to find (k-1, removed_mask)
Either the current child has got maximum sum or whatever we get as return value from k-1 , take maximum of them and then take minimum of it.

Backtrack method:
This is exact opposite of earlier method.  
Here we loop for bags instead of kid.  
Maintain a child array which store how many cookies child got when bag is assigned to him.  
Each bag , give to either of k kids. 
When you assigned the bag , recurse and after return subtract which means we are not going to assign this bag so other kid.
when bag are done then find max_element in child array.
this is our ans and then try to find global minimum.
This solution works, but we can improve with DP as shown in earlier solution.  
```
class Solution {
    int ans = INT_MAX;
    int n;
    int k;
    vector<int> count;
    void solve(int bag, vector<int>& cookies, vector<int>& count ){
        if(bag < 0){
            int t = *max_element(count.begin(), count.end());
            ans = min(ans, t);
            return;
        }
        for(int i =0 ; i < k; ++i){
            count[i] += cookies[bag];
            solve(bag-1, cookies, count);
            count[i] -= cookies[bag];
        }
    }
public:
    int distributeCookies(vector<int>& cookies, int k) {
        n = cookies.size();
        this->k = k;
        count.resize(k, 0);
        solve(n-1, cookies, count);
        return ans;
    }
};
```
https://leetcode.com/problems/smallest-sufficient-team/description/
