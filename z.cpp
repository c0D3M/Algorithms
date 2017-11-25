/*
Z Algorithm : aim is to find a longest sibstring which is also a prefix of string.
This help in doing pattern matches as we prefix patter + '$'+ text in a modified string

Time Complexity : O(m+n)
Space Complexity : O(m+n)
*/
#include <bits/stdc++.h>
using namespace std;
#define DEBUG 0
int main(int argc, char*argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >>s;
	int len = s.size();
	//Setup a Z array
	int Z[len]={0};
	Z[0] = 0;
	int Z_l, Z_r;//Left and right index of Z-box
	//Result
	vector <pair<int, int>> result;
	int max_substr_len = 0;
	for (int i=1; i<len; i++)
	{
		if(s[0]!=s[i])
		{
			Z[i] = 0;
			continue;
		}
		int j=0;
		while((i+j<len ) && (s[j]==s[i+j]))
			j++;
		Z[i] = j;if(j>max_substr_len) max_substr_len = j;
		if(j==1)
			continue;
		
		//Form Z box
		Z_l = i; 
		Z_r = (i+j) - 1;
		//Lets try to fill values as much as possible
		int kk=1;//prefix starter index
		for (int k= i+1; k<=Z_r; k++)
		{
			if(k+Z[kk] <= Z_r)
				{Z[k] = Z[kk++];if(Z[k]>max_substr_len) max_substr_len = Z[k];}
			else
			{
				int count =0;
				int prefix_start_index = Z[kk];
				int l;
				for ( l=Z_r+1; l < len;l++)
					if(s[l]!=s[prefix_start_index++])
						break;
					else
						count++;
				Z[k] = count + Z[kk];
				if(Z[k]>max_substr_len) max_substr_len = Z[k];
				//Update Z-box l & r
				Z_l = k;
				Z_r = l-1;
				kk =1;
			}
		}
		i = (i+j)-1;
		
	}
	cout <<max_substr_len<<endl;
if(DEBUG)
{
	for (int i=0; i<len; i++)
	  cout<<"i: "<<i<<" "<<Z[i]<<endl;
}	
	return 0;
}