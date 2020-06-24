#include <iostream>
using namespace std;

int main(){
	char szTest[] = "abcdef";
	char *p = szTest;

	cout << *p++ <<endl;
	return 0;
}