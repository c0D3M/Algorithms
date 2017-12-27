#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

long  long curren_p_len, current_palindrome_left=-1, current_palindrome_right=-1;
 long  long max_p =0;
void updateCurrentPalindrome( long  long index,   long  long length)
{
	 long  long offset = (length -1)/2;
	curren_p_len = length;
	current_palindrome_right = index+offset;
	current_palindrome_left =  index-offset;
	
}
 long  long findPalindromeLen( long  long centre,  long  long skip, string a)
{
	 long  long count =0;
	while(centre-skip-count >=0 && (a[centre-skip-count]== a[centre+skip+count]))
		count++;
	if(count)
		count --; //Skip the last offset
	return (2*(skip+count)) +1;
}
 long  long LPS(string a)
{
	 long  long current_index = 0;
	 vector<long  long> len;
	 
	while ( current_index < a.size())
	{
		cout << current_index<<endl;
		if(max_p==a.size())
			break;
		if(current_index <= current_palindrome_right )
		{
			for ( long  long j = current_index -2 ; j>=current_palindrome_left; j--)
			{
				// Look for new centre i.e. Rule #3;left
				 long  long offset = (len[j]-1)/2;
				 long  long myleft = j - offset;
				 long  long myright = current_index + offset;
				if((myleft == current_palindrome_left) && (myright== current_palindrome_right))
				{
					//Found new centre, find palindrome
					len.push_back(findPalindromeLen(current_index, offset, a));
					updateCurrentPalindrome(current_index, len[current_index]);
					break;
				}
				else if ((myleft>= current_palindrome_left) && (myright<= current_palindrome_right))
				{
				
					//Current index totally lies in palindrom boundary ; just copy the palindrom length
					len.push_back(len [j]);
					current_index++;
					//updateCurrentPalindrome(current_index, len[current_index]);
				}
				else
				{
					// Calculate length 
					len.push_back( len[j] - (2* (current_palindrome_left-myleft)));
					current_index++;
				}
			}
		}
		else
		{
			// Do normal
			len.push_back(findPalindromeLen(current_index, 0, a));
			updateCurrentPalindrome(current_index, len[current_index]);
		}
		if(max_p< len[current_index])
			max_p =len[current_index];
		current_index++;
	}// while loop ends
#ifdef DEBUG
	for ( long  long i=0; i<a.size();i++)
		cout << len[i]<<" ";
#endif
   return max_p;
}
int main(int argc, char*argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// long  long l;
	//cin >>l;
	string a;
	cin >>a;
	if(a.size()%2) // Odd len string
		cout <<LPS(a);
    else
	{
		string s;
		for ( long  long i=0; i< (2*a.size())+1;i++)
			s.push_back(i%2?a[i/2]:'$');
		cout << LPS(s)/2;
		
	}
}//$a$a$