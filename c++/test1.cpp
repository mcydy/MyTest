#include <iostream>
using namespace std;

class soluction
{
public:
	int findSec(int *p, int len){
		if(p == NULL)
		{
			return -1;
		}
		int max1 = p[0];
		int max2 = p[0];
		int i;
		for(i = 0; i < len; i++)
		{
			if(p[i] >max1)
			{
				max2 = max1;
				max1 = p[i];
			}else if(p[i] > max2)
			{
				max2 = p[i];
			}
		}
		return max2;

	}
};

int main()
{
	soluction example;
	int a[4] = {3,6,8,10};
	cout<<"size:"<<sizeof(a)/sizeof(a[0])<<endl;
	int k = example.findSec(a,sizeof(a)/sizeof(a[0]));
	cout<<"size:"<<k<<endl;
}	