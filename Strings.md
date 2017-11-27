**Longest Palindromic Substring**
Given a string we have to find a longest substring which is also a palindrome.

1. O(n^3) Algorithm
In this algorithm we basically 
    - iterate each index of a string (Loop #1)
    - For each index, iterate all possible substring(Loop #2)
    - Test for palindrome (Loop #3)

2. O(n^2) Algorithm
Basicallywe will have a 2-D table, row will be index and columns will be sub-string index.  
    - iterate each index of a string (Loop #1)  
    - For each index, iterate all possible substring(Loop #2)  
     - To test palindrome test if 'first' and 'last' characters are same  
         - if yes: then check if inner sub-string is palindromic or not, this information we stored from earlier loops.  
         - if no: continue;  
Example: abaa  
Individual string at index 0,1,2,3 of length 1 are 1-letter palindrome, hence mark [0,0] [1,1] [2,2] [3,3] as true in 2-D array.  
Now lets see for all substring at index i = 0;  
inner loop start from i+1 to 'n'  
  - i=1, s[0] != s[1] continue;  
  - i=2 s[0] == s[2] hence chek inner string which will be at one-row down and one-column earlier. i.e. [1,1] which we know is already palidrome
  hence [0,2]  i.e. aba is palindrome.
  
3. O(n) Algorithm : Palindromic Tree
     Easy to understand , basically each node is palindrome and we test if that node can be extended or not,  
     if yes: extended for that characters  
     if no: follow suffix link , which point to next suffix which is also a palindrome (except not the whole string, because that we already tested at this node)
4. O(n) Algorithm: Manacher algorithm
 
5: O(n log n) : Suffix Array + binary search
 Suffix array is an array of integers giving the starting positions of suffixes of a string in lexicographical order  
- Create a Suffix Array for S+'#'+Reversed(S), this can be done using prefix-doubling algroithm in O(n log n) time or DC3 algorithm in O(n) time  
- Create LCP Array i.e. longest matching prefix between i and i-1 suffixes.
- Now to find longest palindrome look for longest LCP and also corresponding s[i] and s[i-1] would come from different side i.e. s[i] in original string and 
  s[i-1] is in reverse one or vice versa.  
    
