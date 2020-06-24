#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

typedef struct link_
{
	int data;
	struct link_ *next;
}link_t;

//创建链表
link_t *createList(int node_num)
{

	link_t *head = NULL;
	link_t *tmp = NULL;
	link_t *current = NULL;
	int i;
	for(i = 0; i< node_num; i++)
	{
		tmp = (link_t *)malloc(sizeof(link_t));
		if(head == NULL)
		{
			cout<<"head"<<endl;
			tmp->data = 5;
			head = tmp;
			// current = tmp;
		}else{
			cout<<"middle"<<endl;
			tmp->data =10;		
			current->next = tmp;
			// current = tmp;
		}
		current = tmp;

	}
	return head;
}

//显示链表
void showList(link_t *head)
{
	link_t *current;
	current = head;
	while(current!= NULL)
	{
		cout<<current->data<<endl;
		current = current->next;
	}
}

//倒序链表

link_t *reverseList(link_t *head)
{
	link_t *current = head;
	// link_t *head;
	link_t *front_node = NULL;
	link_t *next_node = NULL;

	//原则是先进行后边的
	while(current!= NULL)
	{

		//下一个节点移动赋值
		next_node =current->next; 
		//当前节点的和下一个节点赋值
		current->next = front_node;
		//上一个节点移动赋值
		front_node = current;
		//当前节点向下移动
		current = next_node;

		cout<<"reverse"<<endl;		
	}
	return front_node;

	// return next_node;
	 // link_t *current,*next_node,*front_node;
  //    current=head;
  //    next_node=front_node=NULL;
  //    while(current){
  //        next_node=current->next;
  //        current->next=front_node;
  //        front_node=current;
  //        current=next_node;
  //    }
  //    return front_node;

}


int main()
{

	link_t *head = createList(5);

	showList(head);

	link_t *newList = reverseList(head);
	showList(newList);
	// link_t *p_link = (link_t *)malloc(sizeof(link_t));

}