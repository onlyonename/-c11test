#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>
#include <type_traits>


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


struct AA : integral_constant<int, 1>
{

};

struct BB : integral_constant<char, 'b'>
{

};


/*
编译错误,double不属于integral
struct CC : integral_constant<double, 1.23>
{

};
*/

struct DD : integral_constant<bool, true>
{

};




void test4()
{
	cout << "AA::value:" << AA::value << endl;
	cout << "BB::value:" << BB::value << endl;
	cout << "DD::value:" << boolalpha << DD::value << endl;
}


template<typename Fun>
struct FunWrapper
{
	using FunPointer = typename std::decay<Fun>::type;

	FunWrapper(Fun* p)
	{
		_fp = p;
	}

	void Run() { _fp(); }

	FunPointer _fp;
};


void f5() 
{
	cout << "f5" << endl;
}


void test5()
{
	using fun_type = decltype(f5);
	fun_type* fp = f5;
	
	FunWrapper<fun_type> fw(fp);
	
    fw.Run();
}


//可变参数函数
template<typename...T>
void f(T... args)
{
	cout << sizeof...(args) << endl;
}

void test6()
{
	f(1);
	f(1,2);
	f(1,2,3);
}


void print()
{
	cout << "empty" << endl;
}


template<typename T, typename ...Args>
void print(T head, Args... rest)
{
	cout << head << endl;
	print(rest...);	//当变参作为变量用时,...是放在后面的
}


void test7()
{
	print(1,2,3,4,5,6);	//打印可变参数
}



template<size_t i = 0, typename Tuple>
typename enable_if<i == tuple_size<Tuple>::value>::type printtp(Tuple t)
{

}


template<size_t i = 0, typename Tuple>
typename enable_if<i < tuple_size<Tuple>::value>::type printtp(Tuple t)
{
	cout << get<i>(t) << endl;
	printtp<i + 1>(t);
}

template<typename ...Args>
void print(Args... args)
{
	printtp(make_tuple<args...>);	
}


void test8()
{
	print(4,3,2,1);
}



template<typename T>
void printArg(T t)
{
	cout << "printArg" << t << endl;;	
}


template<typename ...Args>
void expand(Args... args)
{
	int a[] = {(printArg(args), 0)...};
}



template<typename T>
int printArg1(T t)
{
	cout << "printArg1" << t << endl;
	return 0;
}

template<typename ...Args>
void expand1(Args... args)
{
	int a[] = {printArg1(args)...};	//还可以这样写.当初始化列表中执行的函数是可变参数时，会全部自动展开
}



void test9()
{
	expand(1,2,3,4);
	expand1(1,2,3,4);
}




int main()
{
	test1();
	test2();
	test3();
	test4();
    test5();
	test6();
	test7();
	test8();
	test9();

	return 0;
}

