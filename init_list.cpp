#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>




using namespace std;


class Foo
{
public:
	Foo(int j){i = j; cout << "call construct" << endl;}

private:
	Foo(const Foo& foo);
	
private:

	int i;

};



int main()
{
	Foo a(123);	//构造函数

	//Foo a1 = 123;	//error,拷贝构造函数是私有的

	//下面是新的初始化方式,即通过初始化列表进行.本质上还是会调用构造函数,如果没有构造函数则会报错
	Foo a2 = {123};	
	Foo a3 {123};	//没有等号也行

	int a4{1};
	int a5[3]{1,2,3};
	
	int* a6 = new int{6};
	int* a7 = new int[3]{1,2,3};

	//{}初始化列表,还可以防止类型收窄
	int a = 1.1;	//a为1,系统会自动进行转换,把float类型降为int
	//int b{1.1};	//error,{}不允许类型收窄,这里编译不过
	
	

	return 0;
}

