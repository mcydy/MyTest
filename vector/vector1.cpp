#include <iostream>
#include <vector>
using namespace std;

class solution{
public:
	bool find(int target, vector<vector<int>> array)
	{
		if(array.size() == 0)
			return false;
		for(auto &iter:array)
		{
			for(auto &element:iter)
			{
				if(element == target)
				{
					cout<<"find target"<<endl;
					return true;
				}else{
					static int i = 0;
					cout<<"find "<<i<<endl;
					i++;
				}
			}
		}
		return false;
	}
};

int main()
{
	vector<vector<int>> array1 = {{1,2,4,5},{3,4,5,6}};
	solution example;
	example.find(6,array1);
}