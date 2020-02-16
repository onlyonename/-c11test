#include <iostream>
#include <string>
#include <stdio.h>



using namespace std;


int foo(int& a) {return ++a;}


int main()
{
	auto f = [] (int a) -> int { return a + 1;};
	cout << f(1) << endl;

	//没有参数时,可以省略参数符号
	auto f1 = []() -> string { return "hello";};
	cout << f1() << endl;
	
	//对于返回值类型明显的函数,可省略返回值类型,甚至参数括号
	auto f2 = []() { return "hello";};
	cout << f2() << endl;

	auto f3 = []{ return "hello";};
	cout << f3() << endl;

	int a = 1, b = 2;
	auto f4 = [&]{return ++a;};
	cout << "f4():" << f4() << ", a:" << a << endl; //注意！！！流的执行,是按从右到左来的,这里输出为2，1
	//cout << "foo:" << foo(a) << ", a:" << a << endl;
	cout << "a:" << a << endl;
	
	//auto f5 = [=]{return ++a;};		//error,=捕获的变量,是readonly类型,即使在lambda内部复制了一份,也不能修改,修改了也不会影响外部的变量.但如果内部实在想修改,可以加mutable关键字,如auto f5 = [=]() mutable {return ++a;};

	auto f6 = [=]{return b;};	
	++b;
	cout << "f6():" << f6() << endl;	//lambda捕获的值,在捕获那一该就定了,后面对b的修改,不影响其值.如果希望lambda即时捕获外面的参数值, 可以用引用方式捕获


	

	


	return 0;
}

