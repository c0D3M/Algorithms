#include <bits/stdc++.h>
#include <algorithm>
#define MIN(a,b)  (a<b?a:b)
#define MAX(a,b)  (a>b?a:b)
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230

using namespace std;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
int blocksize;
int count_x_x[1000000] = {0};
int a[30000];
typedef struct
{
	int left;
	int right;
	int query_num;
}Q;
bool sortQuery (Q i, Q j) 
{  
	if(i.left/blocksize != j.left/blocksize)
	{
		//sort by left index
		return i.left/blocksize < j.left/blocksize;
	}
	return i.right < j.right;
}
void add(int index, int &answer)
{
	count_x_x[a[index]]++;
	if(count_x_x[a[index]]==1)
		answer++;
}
void remove(int index, int &answer)
{
	//if(count_x_x[a[index]])
	{
		count_x_x[a[index]]--;
		if(count_x_x[a[index]]==0)
			answer--;
	}
}
int main(int argc, char*argv[])
{
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	int N, t;
	scanf("%d",&N);;
	
	for (int i=0;i<N;i++)
		scanf("%d",&a[i]);
	int Qn;
	scanf("%d",&Qn);
	Q q[Qn];
	for (int i=0; i<Qn;i++)
	{
		scanf("%d %d",&q[i].left,&q[i].right);
		q[i].query_num = i;	
		// Comment if using 0 based indexing
		q[i].left--;
		q[i].right--;
	}
	
	blocksize = sqrt(N);
	////cout<<"going to sort"<<blocksize<<endl;
	sort(q, q+Qn, sortQuery);
#if 0	
	for (auto i : q) // access by value, the type of i is int
        std:://cout << i.left << i.right <<i.query_num<<endl;
#endif	
	int answer[Qn] ={0};	
	int currentL = 0;
	int currentR = 0;
	
	for(int i=0; i<Qn;i++)
	{
		cout <<"Index"<<i<<endl;
		if(i!=0)
			answer[q[i].query_num] = answer[q[i-1].query_num];
		while(currentL < q[i].left)
		{
			remove(currentL, answer[q[i].query_num]);
			currentL++;
		}
		cout<<answer[q[i].query_num]<<count_x_x[7]<<endl;
		while(currentL  > q[i].left)
		{
			add(currentL-1, answer[q[i].query_num]);
			currentL--;
		}
		cout<<answer[q[i].query_num]<<count_x_x[7]<<endl;
		while(currentR <= q[i].right)
		{
			add(currentR, answer[q[i].query_num]);
			currentR++;
		}
		cout<<answer[q[i].query_num]<<count_x_x[7]<<endl;
		while(currentR > q[i].right+1)
		{
			remove(currentR-1, answer[q[i].query_num]);
			currentR--;	
		}
		cout<<answer[q[i].query_num]<<count_x_x[7]<<endl;
	}
	for (auto i : answer) // access by value, the type of i is int
        printf("%d\n",i);
}
