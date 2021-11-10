Hello Everyone,

Learned some hard problem solving technique using Binary Index Tree(BIT) , wanted to share . Feel free to point any mistake and add more problems to this thread.

**Pre-requiste**
You can learn about BIT from wikipedia or these resource
https://www.youtube.com/watch?v=v_wj_mOAlig
https://www.youtube.com/watch?v=uSFzHCZ4E-8

You should also be aware of how to do combination of range update and point queries(check wikipedia) or
https://leetcode.com/discuss/general-discussion/1093346/introduction-to-fenwick-treebinary-indexed-treebit

**Warm-up Problems:**
After reading about basic of BIT, you must solve these 2 problems to get hands dirty on BIT.
Solving these gives confidence in BIT and they are easy but important problems.
Make sure to use long long.

https://www.spoj.com/problems/FENTREE/
https://www.spoj.com/problems/UPDATEIT/

**Hard Problems**:
Real fun starts here.
- Fisrt familirize with what is lower_bound & upper_bound.
1.lower_bound first iterator of value <= 
2.upper_bound return value > 
3.in case in lower_bound you need last index <= (GFG problem requires that) just do upper_bound -1.  in this diagram you get index 6 then.
![image](https://assets.leetcode.com/users/images/d334ec73-4330-4cd1-bccc-26d589cb7da0_1636528111.2083225.png)



- Whether to iterate from begining or end of vector.
Mostly you iterate from begining unless problem ( like LC 315) asked something specific.

**Template:**
1. Copy the input vector into another vector and sort it. Why we need another sorted vector is an important  concept to understand here since this is used in all problem.
   Basically in Step 4 we iterate  the input array  (not the sorted array) and we find its position in sorted array and then see how many element before or after (depend on problem)
   occured and then sum it up. Will explain in detail in the problem.
2. Setup BIT array of 1+n , where n is array size.
3. Iterate from begin/ end.
4. See what the problme is asking for and acording use lower/upper bound We want everything less than current 
5. Update the frequency of this current element in BIT array.

Lets see this template working in this problem.
[LC 315: Smaller Number than Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
Step 1 & 2 is standard.
Step 3 :  This question asked every element smaller on its right side, so start from end.
Step 4: Problem is asking for less than current element so lower_bound is needed.
        Since BIT works on 1 index, increment index by 1.
        Now we want everything less than current value so sum(index -1).
Step 5: Increment index by 1.

Step 4 & 5 in detail
A = [5,2,6,1]
Sorted_A = [1, 2, 5, 6]
BIT = [0, 0, 0, 0, 0]

loop from end 
i = 3
  nums[i] = 1
  its position in Sorted_A is 0 (lower_bound of 1 is 1 itself)
  BIT works on 1 index so index is 1.
  now we want everything less than 1 so sum(0) which gives 0 and we know nothing is less than 1 on right side so res[3] = 0
  update idx=1 in BIT array , we are trying to communicate to all higher index that a smaller number (1) is available. 
  This is a key part in understand which direction to update and which direction to sum, if you see 493 the process(sum and update) is exact reverse.  
  so BIT = [0, 1, 1, 0, 1]  (1st , 2nd and 4th index is incremented by 1)
![image](https://assets.leetcode.com/users/images/128f336e-d9c8-4174-98bb-901db073fabd_1636528162.5162542.png)

i=2 
  nums[i] = 6
  position in sorted_A is 3
  +1 for BIT index = 4
  we want all less than this index so sum(3)
  now since 1 occured in previous iteration and it has updated BIT array so sum(3) gives 1, res[2] = 1
  after update(4) we get BIT = [0, 1, 1, 0, 2]
```
class Solution {
    vector<int> BIT;
    int sum (int idx){
        int ret =0;
        for(; idx > 0; idx -= (idx & -idx))
            ret += BIT[idx];
        return ret;
    }
    void update(int idx){
        for(; idx < BIT.size(); idx += (idx & -idx))
            BIT[idx]++;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted(nums);
        sort(sorted.begin(), sorted.end()); // Step 1
        BIT.resize(1+n); // Step 2
		vector<int> ans(nums.size());
        for(int i =n-1; i>=0; --i){
            int idx = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin();
            ++idx;// since BIT starts with 1
            ans[i] = sum(idx-1);
            update(idx);
        }
        return ans;
    }
```

[LC 493: Reverse Pair](https://leetcode.com/problems/reverse-pairs/)
Exactly same as above but one key difference
Here if we get smaller number , we need to get the count of all the bigger number (2 * x - 1 ) appeared in past iteration .
Now since the smaller number index would be smaller, all the bigger number has to tell to the left of it . that means update should happen toward left.
```
class Solution {
    int n;
    vector<int> BIT;
    int sum(int i){
        int ret = 0;
        for(; i < BIT.size(); i += (i & -i))
            ret += BIT[i];
        return ret;
    }
    void update(int i){
        for(; i >0; i -= (i & -i))
            BIT[i]++;
    }
public:
    int reversePairs(vector<int>& nums) {
        n = nums.size();
        BIT.resize(1+n);
        vector<int> sorted_nums(nums);
        sort(sorted_nums.begin(), sorted_nums.end());
        int ans = 0;
        for(int i =0; i < n; ++i){
            int idx = lower_bound(sorted_nums.begin(), sorted_nums.end() , (long)2*nums[i] + 1) - sorted_nums.begin();
            
            ++idx;
            ans += sum(idx);
            idx = lower_bound(sorted_nums.begin(), sorted_nums.end(), nums[i]) - sorted_nums.begin();
            ++idx;
            update(idx);
        }
        return ans;
    }
};
```

Try solving this problem too, same as above, except lower/upper bound difference.
https://www.spoj.com/problems/INVCNT/

**BIT using Prefix Sum**

Key difference is instead of number , we are asked sub-array whose sum lies in certain range.
Basically the problem involved sub-array instead of array element.

When problem asked for subarray sums, one standard approach come to mind is prefix sum.
1. Generate prefix sum
2. Generate sorted prefix_sum 
These two will replace the nums & sorted_nums in template.
Also assign a unique rank or number to each of the psum, why are we doing it, because we are using this unique number to update the BIT.
remember that psum can be -ve and BIT works on +ve indices
you have 2 option , 
1. either make all the psum +ve 
2. or assign a unique rank to each psum and then use this unique rank to update BIT.
For more details I added another post https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/1547068/binary-index-tree-in-2-different-ways

[327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)

 [-2,5,-1], lower = -2, upper = 2
 Suppose psum[i] is 7 , we are looking if any previous psum  lies in range [5, 9]
 which means [psum[i]-upper , psum[i]-lower]
 so look for this psum in sorted_psum and then do the sum(higher)-sum(lower)
 finally update(rank(psum[i])) ; remember we are dealing BIT index on rank of psum not the psum itself as psum cna be -ve.
```
class Solution {
    vector<int> BIT;
    int n;
    void update(int i){
        for(; i < BIT.size(); i += (i & -i))
            BIT[i]++;
    }
    int sum(int i){
        int ret  =0;
        for(; i > 0; i -= (i& -i))
            ret += BIT[i];
        return ret;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        n = nums.size();
        vector<long> psum(1+n, 0);
        for(int i =0; i <n; ++i)
            psum[i+1] = psum[i] + nums[i];
        vector<long> sorted_psum(psum);
        sort(sorted_psum.begin(), sorted_psum.end());
        // Give a unique id to each psum 
        unordered_map<int, int> rank;
        for(int i =0; i <= n ; ++i)
            rank[sorted_psum[i]] = 1+i;
        BIT.resize(2+n, 0);// WHy 2 because 1 for BIT index starts with 1 index
                           // 2nd one is because our psum array has a 0 sum also
                           // Why we added 0 because psum -lower or upper could be 0.
        int ans =0;
        for(int i =0; i <= n ; ++i){
            long  up = psum[i] - lower;
            long lo = psum[i] - upper;
            // Now check in sorted psum array 
            int lower_idx  =  lower_bound(sorted_psum.begin(), sorted_psum.end(), lo)-sorted_psum.begin();
            int higher_idx  = upper_bound(sorted_psum.begin(), sorted_psum.end(), up)-sorted_psum.begin();
            ans += sum(higher_idx) - sum (lower_idx);
            update(rank[psum[i]]);
        }
        return ans;
    }
};
```
 
[GFG  Count of substrings in a Binary String that contains more 1s than 0s](https://www.geeksforgeeks.org/count-of-substrings-in-a-binary-string-that-contains-more-1s-than-0s/)
The page suggest using merge sort but I did using BIT with same time complexity. Try BIT way.
Will add more problem to this list.

**End Note:**
- Make sure you can now write bug free update and sum routine , its fairly easy after some practice.
- Notice what problem is asking and apply the template.
- If problem involved prefix sum, use rank method and use that array instead.
- Think where to start iterarting from.
- lower_bound/upper_bound what to use
- In general, it problem is asking for some kind of count in array ranges, think if BIT can be applied in some way.

