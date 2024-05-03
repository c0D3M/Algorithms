[1915. Number of Wonderful Substrings](https://leetcode.com/problems/number-of-wonderful-substrings/description/)  

This is related to prefix sum problem, solve  any of it like 
[325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)  
 
 Lets dry run an example with the approach , expected answer is 9.
 We will tak a map and initialize with ```countMap[0] = 1```  
 The reason we do this is same in all other prefix sum problem, i.e. when entire sub-array counted upto ith index is met with condition , we add that as answer, here we are counting odd/even (using XOR)
 So if XORSum(XOR of all chars a-j) is 0  that is also ans answer.
 Next we maintain a ```mask=0``` , also each character ```a``` is marked as ```1 << 0``` ,   ```b``` as ```1 <<1```  and so on  

 1. Count even count subarray  :  How do we do this? So generate mask with current character ```mask ^= 1 << (c - 'a') ```
    and check in map, if the same exist earlier ``` at poisition j ``` what does it mean  ? it means that  subarray between  j to i contains even elements which cancel out each other and hence ```countMap[mask]``` is an answer, add to answer.
 2. Atmost 1 character with odd count , so what ever ```mask``` we have now, XOR 1 for each a-j characters , this is actually saying that we are allowing 1 odd sum of character , and does the same mask exist , if yes, that mean same thing i.e.  i to j , is even element

  Lets run through an example:
  
String = a<sub>0</sub>a<sub>1</sub>b<sub>0</sub>b<sub>1</sub>

![image](https://github.com/c0D3M/Algorithms/assets/20656683/41ff07d5-d9d2-4a0e-9e8e-a19933315f30)
```
long long wonderfulSubstrings(string word) {
        vector<int> count(1024);
        long long res = 0, cur = 0;
        count[0] = 1L; // when XOR is 0 that means all char is occuring even times 
        // so that is 1 substring

        for (char& c: word) {
            cur ^= 1 << (c - 'a');
            res += count[cur]++;
            for (int i = 0; i < 10; ++i)
                res += count[cur ^ (1 << i)];
        }
        return res;
    }
```

Similar XOR and prefixSum kind of problem
[1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/)  
[1542. Find Longest Awesome Substring](https://leetcode.com/problems/find-longest-awesome-substring/description/)  

Problem Similar to counting & prefix Sum/HashMap  
[523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/description/)  
[974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/)  


[560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/description/)  
[2090. K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/description/)  
[713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/description/)  
[2364. Count Number of Bad Pairs](https://leetcode.com/problems/count-number-of-bad-pairs/description/)  
[1590. Make Sum Divisible by P](https://leetcode.com/problems/make-sum-divisible-by-p/description/)  
Here we are trying to find smallest subarray of size remainder i.e. ```k = totalSum  % p ```
psum<sub>i</sub> - psum<sub>j</sub> = k   
if we remove this smallest subarray of k that means entire subarray sum excluding that will be divisible of p.  
So we go and find the ```smallest subarray of size k``` 

[2845. Count of Interesting Subarrays](https://leetcode.com/problems/count-of-interesting-subarrays/description/)  

First insight : ```nums[i] % modulo == k``` , only those numbers are considered in any given subarray , so convert input array 
to binary array with this condition.
```
       for(int i =0; i < n ; ++i){
            nums[i] = (nums[i] % modulo) == k;
        }
```

Second Insight: 
``` cnt % modulo == k ``` , cnt is subarray sum such that this condition hold true.  
**psum<sub>i</sub>** be the subarray sum upto **i<sup>th</sup>** index.  
**psum<sub>i</sub>** - **psum<sub>j</sub>** % modulo == k , this can be rearranged as  
**psum<sub>i</sub>** - **psum<sub>j</sub>** - k = q * modulo  
put q =0 and rearrange of psum<sub>j</sub> will yield  
**psum<sub>j</sub>** = (**psum<sub>i</sub>** - k  ) % modulo
So look if this exists in our map or not ?  
Since we are dealing with modulo and it can be negative we can add an extra  modulo , which wont hurt in result.   

```
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        // Step 1: convert input array such that for each
        // i : nums[i] % modulo == k
        int n = nums.size();
        for(int i =0; i < n ; ++i){
            nums[i] = (nums[i] % modulo) == k;
        }
        // After above conversion array will have 1 or 0 only

        //Step 2:
        // count the 1's
        long long cnt = 0;
        unordered_map<long long, long long> countMap;
        countMap[0] = 1;
        long long ans = 0;
        for(int i =0; i < n ; ++i){
            cnt += nums[i];
            cnt %= modulo;
            if(countMap.find(((cnt - k + modulo)%modulo)) != countMap.end())
                ans += countMap[((cnt - k + modulo)%modulo)];
            countMap[cnt]++;
        }
        return ans;
    }
```

[1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/description/)  
Same as above , we are interested in only odd number, so again convert to binary array and apply the template.  
```
int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> countMap;
        countMap[0] = 1;
        // Step 1: Only odd numbers are considered
        for(int i = 0; i < n ;++i){
            nums[i] &= 1;
        }
        int sum = 0;
        int ans = 0;
        for(int i = 0; i < n ; ++i){
            sum += nums[i];
            if(countMap.find(sum - k) != countMap.end()){
                ans += countMap[sum-k];
            }
            countMap[sum]++;
        }
        return ans;
    }
```
[930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/description/)  
```
int numSubarraysWithSum(vector<int>& nums, int goal) {
        int sum = 0;
        int ans = 0;
        unordered_map<int, int> countMap;
        countMap[0] = 1;
        for(int i =0; i < nums.size(); ++i){
            sum += nums[i];
            if(countMap.find(sum -goal)!=countMap.end()){
                ans += countMap[sum-goal];
            }
            countMap[sum]++;
        }
        return ans;
    }
```
