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


[1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/)  
[1542. Find Longest Awesome Substring](https://leetcode.com/problems/find-longest-awesome-substring/description/)  
