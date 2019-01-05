#include <bits/stdc++.h>
#include <algorithm>
//Disjoint Sets using union by rank and path compression Graph Algorithm
using namespace std;

class DisjointSet
{
	private:
	void MakeSet(int n);
	
	public:
	typedef struct Node
	{
		int data;
		int rank;
		struct Node*  parent;
	}N;
	vector<N*> map; //uses to find Node from data

	DisjointSet(int n);
	void Union(int a , int b);
	N* FindSet(N* );
	void display();
};
/*
  * n: number of nodes in graph
 */
DisjointSet::DisjointSet(int n)
{
	for (int i=0; i<n; ++i)
		MakeSet(i);
}
void DisjointSet::MakeSet(int node)
{
	N *n = new N();
	n->data = node;
	n->rank =0;
	n->parent = n;
	map.push_back(n);
}
DisjointSet::N* DisjointSet::FindSet(N* n)
{
	if(n->data == n->parent->data)
		return n;
	FindSet(n->parent);
}
void DisjointSet::Union(int a , int b)
{
	N* pa = FindSet(map[a]); //Find parent
	map[a]->parent = pa; //path compression
	N *pb = FindSet(map[b]); 
	map[b]->parent = pb; //path compression
	
	if(pa->rank == pb->rank) // same rank , choose any one)
	{
		++pa->rank; // a parent
		pb->parent = pa;
	}
	else if(pa->rank >= pb->rank)
		pb->parent =pa;
	else
		pa->parent = pb;
		
}
void DisjointSet::display()
{
	for (int i=0; i<map.size(); i++)
		cout << i << "--->"<< FindSet(map[i])->data<<endl;
}
int main(int argc, char* argv[])
{
	DisjointSet d(7);
	d.Union(0, 1);
	d.Union(1, 2);
	d.Union(3, 4);
	d.Union(5, 6);
	d.Union(4, 5);
	d.Union(2, 6);
	d.display();
}