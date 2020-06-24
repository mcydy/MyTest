//created by mcy 2020/4/28

// #ifndef OPERATOR_H_
// #define OPERAtor_H

#include <iostream>
#include <memory>
#include <list>
#include <queue>
#include <deque>

using namespace std;

class mcy{
public:
	mcy operator+(mcy &mcy_baker);
	mcy operator-(mcy &mcy_later);
	bool setLength(int length1){
		length = length1;
	}
public:
	int length;
};
mcy mcy::operator+(mcy &mcy_baker)
{
	mcy a;
	a.length = this->length + mcy_baker.length;
	return a;
}

mcy mcy::operator-(mcy &mcy_later)
{
	mcy b;
	b.length = this->length + mcy_later.length;
	return b;
}

int main()
{

	mcy instance;
	mcy instance1;
	instance1.length = 5;
	mcy instance2;
	instance2.length = 5;
	instance = instance1+instance2;
	cout<<instance.length<<endl;

	mcy *instance4 = new mcy();

	// shared_ptr<mcy> c = make_shared<mcy>();

	shared_ptr<mcy> ksy_ = make_shared<mcy>();
	ksy_->setLength(100);

	cout<<ksy_->length<<endl;
}	


// #endif
