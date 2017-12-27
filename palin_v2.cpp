#include <bits/stdc++.h>
using namespace std;
#define MAX 100000
int main(int argc, char*argv[])
{
	int node [MAX+2][26];
	memset(&node, 0, sizeof(int)*26*(MAX+2));
	int suffix_link [MAX+2]={0}; // Contains index of node
	int len[MAX+2]={0};
	int N;
	cin >> N;
	string s;
	cin >> s;
	//Setup imaginary and 0-node
	int count =0;
	suffix_link[count] = 0; // suffix link of imaginary points to itself
	len [count] = -1;
	count++;
	
	suffix_link[count] = 0;
	len[count] = 0;
	count++;
	int current_node = 0;
	int max_pal = 0;
	for (int i =0; i< s.size(); i++)
	{
		//cout<< i<<" "<<max_pal<<endl;
		if( len[current_node]==-1)
		{
			node[0][s[i]-97] = i+2;
			len[count] = 1;
			suffix_link [count]=1;
		}
		else
		{
			int n = current_node;
			while((len[n]!=-1) && (s[i] != s[i-len[n]-1]) )
				n = suffix_link[n];
            
			// Suffix Link
			int l = suffix_link[n];
			while((len[l] !=-1) && (s[i] != s[i-len[l]-1]))
				l = suffix_link[l];
			//suffix_link[count] = node[l][s[i]-97];
			suffix_link[count] = node[l][s[i]-97]?node[l][s[i]-97]:1;
			//Update the node
			node [n][s[i]-97] = i+2;
			len[count] = 2 + len[n];
		}
		if(len[count] > max_pal)
			max_pal = len[count];
		current_node = count;
		count++;
	}
	cout << max_pal;
	return 0;
}