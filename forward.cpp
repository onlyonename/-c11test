#include <iostream>

void PrintT(int& t)
{
	std::cout << "lvalue" << std::endl;
}

template <typename T>
void PrintT(T&& t)
{
	std::cout << "rvalue" << std::endl;
}

template <typename T>
void TestForward(T&& v)
{
	PrintT(v);
	PrintT(std::forward<T>(v));
	PrintT(std::move(v));
}

void Test()
{
	TestForward(1);
	
	int x = 1;
	TestForward(x);
	
	TestForward(std::forward<int>(x));	//注意,这里经过forward<int>后为右值,下面的表达式,才是转化为左值
	TestForward(std::forward<int&>(x));	

	cout << is_rvalue_reference<decltype(std::forward<int>(x))>::value << endl;
    cout << is_rvalue_reference<decltype(std::forward<int&>(x))>::value << endl;
}

int main(void)
{
	Test();

	return 0;
}

