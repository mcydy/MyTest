#include<iostream>
#include <stdio.h>
using namespace std;
/*
这是一个拷贝函数验证的demo，根据以下程序可以验证拷贝构造函数的调用时机
*/
class CExample
{
private:
    int a;
public:
    CExample(){
         printf("无参构造函数 is called\n");
    }
    //构造函数
    CExample(int b)
    {
        a=b;
        printf("有参构造函数 is called\n");
    }
    //拷贝构造函数
    CExample(const CExample & c)
    {
        a=c.a;
        printf("拷贝构造 is called\n");
    }
    //析构函数
    ~CExample()
    {
        cout<<"析构函数 is called\n";
    }

    CExample& operator=(const CExample& CExample) 
    {
        cout << "拷贝赋值运算符 operator\n";
    }

    void Show()
    {
        cout<<a<<endl;
    }
    static int z;

};
int main()
{

    CExample foo1;
    cout<<"-----------------------\n";
    CExample foo2(100);
    cout<<"-----------------------\n";
    foo1 = CExample(100);

    CExample A(100); 
    cout<<"-----------------------\n";
    CExample B=A;
    cout<<"-----------------------\n";
    CExample C(A);
    
    return 0;
}