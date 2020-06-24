#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <mutex>
#include <memory>
#include <string>

using namespace std;

class IKYSInterface
{
public:
	IKYSInterface(int a,string s):a1(a),s1(s){cout<<"IKSYinterface"<<a1<<s<<endl;}
private:
	int a1;
	string s1;
};

class mcy
{
public:
	mcy();
	// virtual ~mcy();
	int fun();

public:
	std::shared_ptr<IKYSInterface> ksy_;
	IKYSInterface *ksy1_;
};
mcy::mcy()
{
	cout<<"mcy mcy"<<endl;
}

int mcy::fun()
{
	ksy_ = make_shared<IKYSInterface>(1,"aa");
	return 0;
}

int main()
{
	mcy a;
	a.fun();

	shared_ptr<IKYSInterface> b(new IKYSInterface(8,"object"));
	cout<<"b.get()"<<b.use_count()<<endl;
	// mcy b;
	// b(a);
}