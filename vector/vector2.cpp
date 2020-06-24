#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef struct _node
{
	int data;
	struct  _node *next;
}node;

class solution{
public:
	vector<int >printListFromEndToHead(node *head){

		vector <int> result;
		stack <int> tmp;
		node *current = head;
		while(current){
			tmp.push(current->data);
			current = current->next;
		}
		int i;

		for(i=0; i<tmp.size(); i++)
		{
			result.push_back(tmp.top());
			tmp.pop();
		}

		return result;
	}
};

int main()
{
	solution example;
}