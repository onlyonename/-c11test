#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>



using namespace std;


template<typename T>
void print(T t)
{
	cout << t << endl;
}


void test1()
{
	//几种for循环的用法

	vector<int> v {1,2,3,4,5};
	
	for(auto iter = v.begin(); iter != v.end(); ++iter) cout << *iter << endl;

	using vt = decltype(*v.begin());
	for_each(v.begin(), v.end(), print<vt>);

	for(auto i : v) cout << i << endl;

	map<int,int> m {{1,1},{2,2},{3,3}};
	for(auto i : m) cout << i.first << ":" << i.second << endl;

	map<string, string> n {{"a","a"},{"b","b"},{"c","c"}};
	for(auto& i : n) cout << i.first << ":" << i.second << endl;	//i可以为引用

	
}



int main()
{

	test1();

	

	return 0;
}

