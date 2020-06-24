#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Stack{

private:
	vector<T> elems;
public:
	void push(T &t);
	void pop();
	T top()const;
};

int main()
{
	Stack<int> intStack;
}