#include <iostream>
#include <string>
#include <stdio.h>


using namespace std;


struct Foo
{
	static const int _a = 3;
	decltype(_a) b = 4;	//注意,b为const int类型,static不会保留,static不是变量类型的范畴,auto和decltype,只涉及cv、指针和引用这4个属性
	int c = 4;
};


void test1()
{
    int x = 3;
    const int& i = x;
    decltype(i) j = x;	//j为const int&类型,decltype可以保留cv和引用
    //j = 4;			//error,常量引用

	int y = 4;
	decltype(x + y) m = 5;	//decltype可以接表达式

	decltype(x) z = x;	//int
	decltype(x) *p = &x;	//int*

	decltype(p) *pp = &p;	//int**

	int* q = &x;
	decltype(q) r = &y;
}


void test2()
{
	decltype(Foo::_a) m = 3;	//m为const int类型,static不会保留,decltype只会保留cv、引用和指针
}


void test3()
{
	int& func_int_r(void);    //左值（lvalue，可简单理解为可寻址值）
	int&& func_int_rr(void);  //x值（xvalue，右值引用本身是一个xvalue）
	int func_int(void);       //纯右值（pvalue）

	const int& func_cint_r(void);         //左值
	const int&& func_cint_rr(void);       //x值
	const int func_cint(void);            //纯右值

	class Foo{public:int i;};
	const Foo func_cfoo(void);  //纯右值


	int x = 0;

	//规则2:decltype(exp)中,如果exp是函数调用,则decltype(exp)和exp一致
	decltype(func_int_r()) a1 = x;    //a1 -> int&
	decltype(func_int_rr()) b1 = 0;   //b1 -> int&&
	decltype(func_int()) c1 = 0;      //c1 -> int

	decltype(func_cint_r()) a2 = x;    //a2 -> const int&
	decltype(func_cint_rr()) b2 = 0;   //b2 -> const int&&
	decltype(func_cint()) c2 = 0;      //c2 -> int,注意,这里const丢失了
	c2 = 3;//const丢失了

	decltype(func_cfoo()) ff = Foo();  //ff -> const Foo,这里保留了const
	//ff.i = 5;//error

	/*
		对于函数的纯右值返回,只有类类型可以携带cv,普通类型会丢失cv
	*/
}


void test4()
{
	struct Foo{int x;};

	const Foo a = Foo();

	//规则1:decltype(exp)中,如果exp是标识符、类访问表达式,则decltype(exp)和exp一致
	decltype(a.x) b = 0;	// b为int类型,即使包装它的对象为const.
	b = 1;

	decltype((a.x)) c = b;	// c为const int&类型
	//c = 4;	//error

	int m = 0, n = 0;
	decltype(m + n) k = 4;	//int,此表达式为右值

	//规则3:其它情况,decltype(exp)中,如果exp是左值,则decltype(exp)是左值引用
	//decltype(m += n) w = 4;	//error,w为int&,此表达式为左值,不能引用右值
}


//在main函数之前执行
__attribute__((constructor)) void before_main()
{
    printf("before main\n");
    printf("Foo::_a %d\n", Foo::_a);	//静态变量,在main函数运行前已创建完成
    //printf("Foo::_b %d\n", Foo::_b);	//报错,Foo::_b不是静态变量
}


int main()
{
	test1();

	test2();

	return 0;
}

