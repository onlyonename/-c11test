#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>



using namespace std;



template<typename T>
struct Foo
{
	T t;
};

void test1()
{
	vector<Foo<int>> a;		// >>之间不用空格
}


template<typename T>
using TMap = map<int, T>;		//using 定义类型,可支持模板


template<typename T>
using TFun = T (*)(T);


int fun(int a)
{
	return a;
}



void test2()
{
	TMap<int> a;
	TMap<string> b;

	TFun<int> fun1;	//定义函数指针
	fun1 = fun;
	cout << "fun1:" << fun1(2) << endl;
}



template<typename R = int, typename T>
R foo2(T t)
{
	return t;
}

void test3()
{
	foo2(123);	//模板参数的填充,是从右到左的顺序.因此123对应了T,为int类型,而R为默认类型,也是int。

	foo2<long>(42);	//这个例子中,42对应和T,为int类型.R对应为long
	
}



int main()
{
	test1();
	
	test2();

	test3();


	

	return 0;
}

