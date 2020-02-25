#include <typeindex>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <functional>
#include <string>

using namespace std;

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
//struct function_traits : public function_traits<decltype(T)>
{};


// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
	// we specialize for pointers to member function
{
	enum { arity = sizeof...(Args) };
	// arity is the number of arguments.

	typedef ReturnType result_type;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
		// the i-th argument is equivalent to the i-th tuple element of a tuple
		// composed of those arguments.
	};

	typedef std::function<ReturnType(Args...)> FunType;
	typedef std::tuple<Args...> ArgTupleType;
};

int ff(int i,string j) {return i + 1;}

std::function<int(int,string)> ft(ff);


int main()
{
	using T = typename function_traits<decltype(ft)>::arg<1>::type;

    cout << typeid(T).name() << endl;

    return 0;
}





