#include <iostream>

using namespace std;

//一个接口类
class instance
{
public:
	virtual void request(){};
};

//一个目标类
class target
{
public:
	void getrequest(){
		cout<<"hahaha"<<endl;
	}
};

//一个适配器类,多继承
class adaptor:public instance,public target
{
	public:
		void request()
		{
			this->getrequest();
		}
};

int main()
{

	adaptor a;
	a.request();
}