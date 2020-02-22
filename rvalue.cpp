#include <iostream>
#include <string>
#include <stdio.h>
#include <typeinfo>



using namespace std;


int g_iConstructCount = 0;
int g_iCopyConstructCount = 0;
int g_iDestructCount = 0;


class A
{
public:
	A(){cout << "construct called:" << ++g_iConstructCount << endl;}
	
	A(const A& a){cout << "copy construct called:" << ++g_iCopyConstructCount << endl;}

	~A(){cout << "destruct called:" << ++g_iDestructCount << endl;}
	
private:

};


A GetA()
{
	return A();
}


void test1()
{
	//为了测试这个例子,要这样编译g++ construction.cpp -fno-elide-constructors,默认情况下,g++已经进行了优化

	/*
		在不开-fno-elide-constructors优化的情况下,下面语句的执行是这样的:
		GetA函数内部,先生成一个对象t1,然后t1返回时,复制给临时对象t2,这时t1析构.
		接着,t1赋值给a,然后t1和a析构.
	*/
	A a = GetA();


	//即使打开-fno-elide-constructors,但是如果用了右值引用,就能减少t2的消亡
	A&& b = GetA();

	//上在的优化,还可以写成这样.const左值引用是个万能引用,可以引用右值,但没const就会报错,A&不能直接引用右值
	const A& c = GetA();
}




int f1(int& i)
{
	cout << "f1" << endl;
}





template<typename T>
void f(T&& param)	//T的类型待推导,T&&为universal reference,param既可为左值引用(被左值初始化,param为左值),也可为右值引用(被右值初始化,param为右值).
{
	cout << typeid(param).name() << " " << param << endl;

    cout << is_lvalue_reference<decltype(param)>::value << endl;
    cout << is_rvalue_reference<decltype(param)>::value << endl;

	f1(forward<T>(param));
}


template<typename T>
void f1(const T&& param)	//和上面的例子不同,加了const后,param只能为右值引用了,不是universal reference
{
	cout << typeid(param).name() << " " << param << endl;

	f(forward<T>(param));
}





int main()
{
	test1();

	int x = 10;
	f(x);

	//f(10);//编译不过,因为此时param为右值引用,即右值,不能传给非const左值引用f1.如果f1改成f1(int&&),那f(x)编译不过
	
	return 0;
}

