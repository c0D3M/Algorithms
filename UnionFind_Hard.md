In this chapter we will try to solve solve hard problems using Union Find.  
[2812. Find the Safest Path in a Grid](https://leetcode.com/problems/find-the-safest-path-in-a-grid/)  
Key idea for using union find is first find for all grid manhattan distance to thief.  
Now start with cells which has maximum distance and union with there unvisited neighbors.  
Stop at the moment (0,0) & (n-1, n-1) parent is same and return the distance when this occur.  
Same problem can be solved using bsearch as well as priority heap (Dijkstra).  

[778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/description/)
Put all cells as a separate individual component.
Approach 1:
set t = 0 and then loop entire grid merge cells whose grid value <= t 
Do this until 0 and n^2 in same component.
This approach works but very slow.
Worst case we have to loop n^4 since time can be n^2 and for each time we are looping grid.


Approach 2:
Store co-ordinate value in time vector;
Now iterate this time vector , pick the grid value and mark as visited 
Also see if any lef-right-top-bottom are visited, if yes merge with it.
Do this until 0 and n^2 in same component.
This is much faster as we are not iterating grid every time .
Worst case we have to loop n^2

[1970. Last Day Where You Can Still Cross](https://leetcode.com/problems/last-day-where-you-can-still-cross/description/)  
Key Insight: cells.length == row * col, that means at the end, the whole grid will be full of water (all cell will be 1)
Now we have to find maximum here, so start with end, before this day , this cell would be 0
check 4-way adjacent if anything is 0 , if yes merge in same component using uion find.
Now since we have to din first and last row are in same connected component, create a virtual cell ```0``` for row 0 and virtual cell ```m*n +1 ``` for last row.
If any cell is of this row 0 or m , additonal merge with there virtual node too.
break when virtual node lies in same connected component.

```
class Solution {
    vector<int> parent;
    vector<int> rank;
    void init_union(int n){
        rank.resize(n, 0);
        parent.resize(n);
        iota(begin(parent), end(parent), 0);
    }
    int find(int x){
        if(x!=parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void union_(int x, int y){
        int p_x = find(x);
        int p_y = find(y);
        if(p_x!=p_y){
            if(rank[p_y] > rank[p_x])
                swap(p_x, p_y);
            parent[p_y] = p_x;
            rank[p_x] += rank[p_y];
            if(rank[p_x]==rank[p_y])
                ++rank[p_x];
        }
    }
public:
    int latestDayToCross(int m, int n, vector<vector<int>>& cells) {
        // Point , cells.length == row * col
        // So at the end , everything is water (i.e. 1)
        vector<vector<int>> grid(m, vector<int>(n, 1));
        #define MAX_DIR (4)
        init_union(m*n + 2);
        int dir[MAX_DIR+1] = {-1, 0, 1, 0, -1};
        for(int i = cells.size()-1; i >=0; --i){
            // Take a virtual node which connect the top column
            // Take another virtual node which connect all last column
            int r = cells[i][0]-1;
            int c = cells[i][1]-1;
            grid[r][c] = 0; //beofre this day it was land so mark it
            int idx = r*n +c + 1;
            for(int j =0; j < MAX_DIR; ++j)
            {
                int n_r = r + dir[j];
                int n_c = c + dir[j+1];
                
                if(n_r >=0 and n_r < m and n_c>=0 and n_c < n and !grid[n_r][n_c]){
                    int idx_new = n_r*n +n_c+1;
                    union_(idx, idx_new);
                }
            }
            if(r==0)
                union_(0, c+1);
            if(r==m-1)
                union_(m*n+1, r*n + c+1);

            // if both virtual belongs  to same component we have a connection
            if(find(0) == find(m*n +1))
                return i;
        }
        return 0;
    }
};
```
