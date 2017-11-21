#include <bits/stdc++.h>
using namespace std;
#define DEBUG 0
struct N;
struct N
{
	N()
	{
		count =0;
	};
	int len;
	int index;
	int count;
	N * node[26];// 
	N * suffix_link;
};
unsigned int res =0;
string s;
unsigned int longest_palin =0;
unsigned int longest_palin_count =0;
struct N *Node0, *Node1;
/*
 * whenever a sufflink is referred by a node, all the smaller suffix palindromes count are updated
 *
 */
void updateCount (N *node)
{
	if(DEBUG)cout<<"updateCount"<<endl;
    while (node && node != Node1)
    {
        node->count++;
        if(DEBUG)cout<<"updateCount done"<<endl;
        node = node->suffix_link;
    }
}

void display(N *node)
{
    for (int i=0; i<26; i++)
        {
            N * t= node->node[i];
            if(t)
            {
                if(DEBUG)
                {
                    cout <<"index: "<< t->index<<" len: "<<t->len<<" count: "<<t->count<<endl;
                    cout << s.substr(t->index,t->len)<<endl;
                }
                if(t->count)
                    res += t->count;
                if(t->len >= longest_palin)
                    {if(t->len!=longest_palin)longest_palin_count=t->count;else longest_palin_count++; longest_palin = t->len; }
                display(node->node[i]);
            }
        }
}
int main(int argc, char*argv[])
{
	longest_palin = 0;
	longest_palin_count =0;
	cin >> s;
	struct N *current_node =NULL;
	// Setup imaginary node node;
	Node0 = new N;
	memset(Node0, 0, sizeof(N));
	Node0->suffix_link = Node0;
	Node0->len =-1;
	
	//Setup 0 node
	Node1 = new N;
	memset(Node1, 0, sizeof(N));
	Node1->suffix_link = Node0;
	Node1->len =0;
	
	current_node = Node1;
	if(DEBUG)cout<< "Node0: "<<Node0 <<" Node1: "<<Node1<<endl;
	for(int i=0; i<s.size();i++)
	{
		struct N* start = current_node;
		bool found =false;
		if(DEBUG)cout <<"loop "<<i<<endl;
		while(!found)
		{
		    if(DEBUG)cout << "Start: "<<start<< " len: "<<start->len<<" index: "<< start->index<<endl;
		if(start->len ==-1) // imaginary Node, just extend
		{
			if(start->node[s[i] -'a']) // Node already exists
				start->node[s[i] -'a']->count++;
			else // Extend the node to create a new palindromic node
			{
				start->node[s[i] -'a'] = new N;
				memset(start->node[s[i] -'a'], 0, sizeof(N));
				start->node[s[i] -'a']->len =1;
				start->node[s[i] -'a']->index = (i -start->node[s[i] -'a']->len)+1;//+1 is to offset 0 index;
				start->node[s[i] -'a']-> count =1;
			}				
			current_node = start->node[s[i] -'a'];
			//Suffix Link point to 0 length node
			start->node[s[i] -'a']->suffix_link = Node1;
			if(DEBUG)cout << "SF 0: "<<start->node[s[i] -'a']->suffix_link<<endl;
			found =true;
		}
		else if(i-start->len-1 >=0) // some valid node
		{
			if(s[i]== s[i-start->len-1]) // Found node which can be extended
			{
			    if(start->node[s[i] -'a'])
			    {
			        start->node[s[i] -'a']->count++;
			        current_node = start->node[s[i] -'a'];
			                        found =true;
			        continue;
			    }

				start->node[s[i] -'a'] = new N;
				memset(start->node[s[i] -'a'], 0, sizeof(N));
				start->node[s[i] -'a']->len = 2 + start->len;
				start->node[s[i] -'a']->index = (i -start->node[s[i] -'a']->len)+1;//+1 is to offset 0 index
				start->node[s[i] -'a']-> count = 1;
				current_node = start->node[s[i] -'a'];
				found =true;
				// Add Suffix Link
				N *link = start->suffix_link;
				//If suffix link point to itself, first check if a node of that characters exists , if yes use that else use Node0
				if(link->suffix_link==link)
			        if(link->node[s[i]-'a'])
			            {start->node[s[i] -'a']->suffix_link = link->node[s[i]-'a'];updateCount(link->node[s[i]-'a']);}
			        else
			        	start->node[s[i] -'a']->suffix_link = Node1;
				else
				{
					while(s[i] != s[i-link->len-1])
					{
						link = link->suffix_link;
						if(link->suffix_link==link)
						    break;
					}
					if(link->node[s[i]-'a'])
						{link = link->node[s[i]-'a'];updateCount(link);}
					else
						link = Node1;
					start->node[s[i] -'a']->suffix_link=link;
				}
				if(DEBUG)cout << "SF 3:"<<start->node[s[i] -'a']->suffix_link<<endl;
			}
			else //Traverse further
				start = start->suffix_link;
		}
		else //look for next suffix link
		{
			start = start->suffix_link;
		}
		}//While loop ends
	}//For ends here , scan of string
	display(Node0);
	if(DEBUG)cout <<"Zero Node"<<endl;
	display(Node1);
	cout << "Total palindromes are: "<<res<<endl;
	cout <<"Longest Palindrom is of length: "<<longest_palin<<" Count: "<<longest_palin_count<<endl<<endl;
}

/* Sample Test Vectors:
 * eertree
 * aaaaa
 * abaaa
 * abbaab
 * aaba
 * malayalam
 * abatxaba
 * */
