#include <iostream>

using namespace std;

//含有回调函数的接口类
class IinterfaceFloor
{
public:
	virtual void floor() = 0;
	virtual void callback() = 0;
};
 
//一个上层类
class father:public IinterfaceFloor
{
public:
	virtual void floor(){cout<<"floor"<<endl;}
	virtual void callback(){cout<<"floor"<<endl;}
};

//一个底层接口类
class sonInterface
{
public:
	virtual void setvisitor(IinterfaceFloor *visitor) = 0;

public:


};


//一个底层类
class son:public sonInterface
{
public:
	void setvisitor(IinterfaceFloor *visitor){
		visitor_ = visitor;
	};

IinterfaceFloor *visitor_;

};


int main()
{
	//底层模块
	son *s = new son();

	//第一个模块操作
	father *f = new father();
	s->setvisitor(f);


	//底层操作
	s->visitor_->callback();

	// f->callback();

}