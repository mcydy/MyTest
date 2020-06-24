#include <iostream>
#include <stack>
using namespace std;

typedef struct _tree
{
	int data;
	struct _tree *leftNode;
	struct _tree *rightNode;	
}tree_t;

void proOrder(tree_t *tree)
{
	if(tree == NULL)
		return;
	proOrder(tree->leftNode);
	proOrder(tree->rightNode);
}

void proOrderStack(tree_t *tree)
{
	if(tree == NULL)
		return;
	tree_t *current = tree;
	stack<tree_t *> tree_stack;

	while(current != NULL || !tree_stack.empty())
	{
		while(current != NULL)
		{
			tree_stack.push(tree);
			current = current->leftNode;
		}
		if(!tree_stack.empty())
		{
			current = tree_stack.top();
			current = current->rightNode;
			tree_stack.pop();
		}

	}
}

int main()
{

}