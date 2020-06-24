#include <iostream>
#include <string>
 
class Foo {
 
public:
 std::string s;
 
 // 默认构造函数
 Foo() { std::cout << "default constructor" << std::endl; }
 // 复制构造函数
 Foo(const Foo& foo) { std::cout << "copy constructor" << std::endl; s = foo.s; }
 // 复制赋值运算符
 Foo& operator=(const Foo& foo) { std::cout << "copy assignment operator" << std::endl; s = foo.s; return * this;}
 // 移动构造函数
 Foo(Foo&& foo) { std::cout << "move constructor" << std::endl; s = std::move(foo.s); }
 // 移动赋值运算符
 Foo& operator=(Foo&& foo) { std::cout << "move assignment operator" << std::endl; s = std::move(foo.s); return *this;}
};
 
int main() {
 Foo foo1;
 Foo foo2(foo1);
 foo1 = foo2;
 Foo foo3(std::move(foo1));
 foo2 = std::move(foo3);
}