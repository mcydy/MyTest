#include <iostream>
#include <string>
#include <vector>

using namespace std;

class mcy
{
public:
	int loveHongHong(string input){
		cout<<"string ="<<input <<endl;
		honghong_ = input;
	}
public:
	string honghong_;
};

int main()
{
	vector<mcy> vector_mcy;
	mcy a;
	a.loveHongHong("pipi");
	mcy b;
	b.loveHongHong("love pipi");
	vector_mcy.push_back(a);
	vector_mcy.push_back(b);

	for(auto x:vector_mcy)

	{
		cout<<x.honghong_<<endl;
	}

	std::vector<mcy>::iterator iter;

	for(iter = vector_mcy.begin(); iter !=vector_mcy.end(); iter++)
	{
		cout<<iter->honghong_<<endl;
	}

	cout<<vector_mcy.size()<<endl;
	vector_mcy.pop_back();
	vector_mcy.pop_back();
	cout<<vector_mcy.size()<<endl;

}