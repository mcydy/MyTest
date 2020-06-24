#include <iostream>

using namespace std;

/************************************************字符串********************************************************/

//实现strcpy()
char *myStrcpy(char *pDes, char *pSrc)
{
	if(pDes == NULL || pDes == NULL )
		return NULL;

	if(pDes == pSrc)
		return pDes;

	while((*pDes++ = *pSrc++) != '\0'){}

	return pDes;
}

//实现strcat
char *myStrcat(char *pDes, char *pSrc)
{
	if(pDes == NULL || pSrc == NULL)
		return NULL;

	char *pIter = *pDes +strlen(pDes);
	while((*pIter++ = *pSrc++)!= '\0'){}

	return pDes;
}

//实现字符串的逆序
char *myInverted(char *pDes)
{
	if(!pDes)
		return NULL;

	int len = strlen(pDes);
	int i;
	char tmp;
	for(i=0; i<len/2; i++)
	{
		tmp = pDes[i]
		pDes[i] =pDes[len-i-1];
		pDes[len-i-1] = tmp;
	}
	return pDes;
}


//将字符串中的所有大写字母转化为小写字母
char *myUpper(char *pDes)
{
	if(!pDes)
		return NULL;
	
	for(char *i=pDes; *i!='\0'; i++)
	{
		*i -= "A" - "a";
	}

	return pDes;
}

/*************************************************查找算法*******************************************************/

//不使用第三个数交换两个值
void transInt(int &one, int &two)
{
	if(one == two)
		return;
	one = one + two;
	two = one - two;
	one　＝　one - two;
}

//实现二分法查找
int binary(int value, int *arry, int length)
{
	int left = 0;
	int right = length -1;
	int index = (right - left)/2;
	while(left<right && arry[index] != value)
	{
		if( arry[index] < value){
			left = index;
		}else if (arry[index] > value ){
			right = index;
		}
		index = (right - left)/2;
	}
	if(arry[index] == value)
		return value;

	return -1;
}

/************************************************链表算法********************************************************/
typedef struct _node
{
	int data;
	struct _node *next;

}node;

//实现链表的逆序
int rerverse(node *head)
{
	node *current = head;
	node *front = NULL;
	node *behind　= NULL;

	while(current != NULL)
	{
		//后节点移动且赋值
		behind = current->next;
		//修改本节点指向
		current->next = front;
		//前节点移动且赋值
		front = current;
		//当前节点移动
		current = behind;
		//最后一个current已经变成空,所以最后返回front
	}

	return front;
}
//删除链表中值为value的元素
void findValue(node *head,int value)
{
	node　*current = head;
	node *front;
	while(current != NULL)
	{	
		if(current->data == value)
		{
			//删除节点
			//修改本节点指向
			front->next = current->next;
		}
		//前一个节点指针赋值
		front = current;
		//开始下一论论询
		current = front->next;

	}
}

//在index中插入值为value的元素
void indexNode(node *head, int index, int value)
{
	node *current = head;
	node *behind;
	int i = 0;
	while(i != index)
	{
		current = current->next;
		i++;
	}
	//下一个几点赋值
	behind = current->next;
	//创建新节点
	node *inserted_node = malloc(sizeof(node));
	inserted_node->data = value;
	//修改指向
	current->next = inserted_node;
	inserted_node->next　＝　behind;
}

//判断链表是否有环
bool judgeCircle(node *head)
{
	node *fast = head->next;
	node *slow = head->next->next;
	//通过快慢指针判断是否有环
	while(fast && fast->next && fast->next->next)
	{
		fast = head->next;
		slow = head->next->next;

		if(fast->value == slow->value)
			return true;
	}
	return false;
}

/**************************************************排序算法*******************************************************/
//实现冒泡排序,大到小,挨着的比较，换位
int bubbleSort(int *array, int length)
{
	int i,j,tmp;
	for(i = 0; i < length; i++)
	{
		for(j = i; j < length-1; j++)
		{
			if(array[j]　>array[j+1])
			{
				tmp = array[j];
				array[j] = array[];
				array[] = tmp;
			}
		}
	}
}

//实现选择排序，大到小，一个所有的比较，换位
int selectSort(int *array, int len)
{
	int i,j,tmp;
	for(i = 0; i < len; i++)
	{
		for(j = i+1; j < len; j++)
		{
			if(array[i]　< array[j])
			{
				tmp = array[j];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}


int main()
{
	char src[20] = "abcdefghijkl";
	char dsc[20];
	myStrcpy(dsc,src);
	cout<<dsc<<endl;

}