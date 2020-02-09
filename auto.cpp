#include <iostream>
#include <string>
#include <stdio.h>


using namespace std;


void test1()
{
    auto i = 5;
    auto j = new auto(1);	//auto可自动推导出类型int
    auto p = &i;	//p为int*,还有一种写法是auto* p = &i,这样会更显式一点,指明p是个指针
    cout << i << "," << *j << "," << *p << endl;

    auto &a = i;	//a为int&
    cout << a << endl;
    a = 8;
    cout << i << "," << a << endl;	
   
    const auto& b = i;	//常量引用

	//b = 7; //error,常量引用不能更改

	//auto c; //error,不可定义没有值的auto,类似的情况还有函数参数,因为这样编译器不知给c设置哪种类型

	const int k = 9;
    auto *q = &k;//const int*
    //*q = 4; //error, q会被推导为const int* 类型

	const auto& v = k;	//const int&
    auto &w = k;	//const int&
    //w = 9; //error,常量引用

    auto m = k;	//m为int类型
    m = 8;

	int arr[10] = {0};
	auto r = arr;	//r为int*,而不是int[10]

	/*	
		总结:
		当auto不带上指针和引用时,相当于定义一个普通变量,会忽略右边表达式的cv类型
		当auto带上指针和引用时,会保留右边表达式的cv类型
	*/
}


void test2(auto a = 1){}	//编译错误,auto不可用于函数参数,即使有默认值也不可以


struct Foo
{
	auto _a = 1;				//error,auto不可用于非静态成员变量
	static const auto _b = 2;	//ok,成员变量只可以是静态常量
	static auto _c = 3;			//error,非静态常量不可以
	int b = 4;					//ok
};







int main()
{
	test1();

	return 0;
}

