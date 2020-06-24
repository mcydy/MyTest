#include <iostream>
using namespace std;
int main()
{
	try{
		cerr<<"error"<<endl;
		throw "1";
	}
	catch(const char *msg){
	cout<<"catch"<<msg<<endl;
}
}
