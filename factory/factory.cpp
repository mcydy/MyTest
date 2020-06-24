#include <iostream>
#include <list>
#include <memory>
#include <vector>

using namespace std;

class algo
{
public:
	virtual void getResult()
	{}
		
};

class cubic:public algo
{
public:
	void getResult()
	{
		cout<<"cubic"<<endl;
	}


};

class sharpen:public algo
{
public:
	void getResult()
	{
		cout<<"algo"<<endl;
	
	}

};

class factory
{
public:
	static algo * createInstance(string s){
		algo *p = NULL;
		if(s == "cu")
			p = new cubic();
		if(s == "sh")
			p =new sharpen();
		return p;
	}

};

int main()
{
	
	algo *a =factory::createInstance("cu");
	a->getResult();

	factory b;
	algo *c =b.createInstance("sh");
	c->getResult();

}