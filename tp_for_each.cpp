#include <tuple>
#include <iostream>

template <int...>
struct IndexTuple {};

template <int N, int...Indexs>
struct make_indexes : make_indexes<N - 1, N - 1, Indexs...>{};

template <int...Indexs>
struct make_indexes<0, Indexs...>
{
	typedef IndexTuple<Indexs...> type;
};


namespace details {

	template<typename Func, typename Last>
	void for_each_impl(Func&& f, Last&& last)
	{
		f(last);
	}

	template<typename Func, typename First, typename ... Rest>
	void for_each_impl(Func&& f, First&& first, Rest&&...rest)
	{
		f(first);
		for_each_impl(std::forward<Func>(f), rest...);
	}

	template<typename Func, int ... Indexes, typename ... Args>
	void for_each_helper(Func&& f, IndexTuple<Indexes...>, std::tuple<Args...>&& tup)
	{
		for_each_impl(std::forward<Func>(f), std::forward<Args>(std::get<Indexes>(tup))...);
	}

} // namespace details 

template<typename Func, typename Tuple>
void tp_for_each(Func&& f, Tuple& tup)
{
	using namespace details;
	for_each_helper(std::forward<Func>(f), typename make_indexes<std::tuple_size<Tuple>::value>::type(), tup);
}

template<typename Func, typename Tuple>
void tp_for_each(Func&& f, Tuple&& tup)
{
	using namespace details;
	for_each_helper(std::forward<Func>(f), typename make_indexes<std::tuple_size<Tuple>::value>::type(), std::forward<Tuple>(tup));
}


struct Functor
{
	template <typename T>
	void operator()(T& t) const
	{
		//t.doSomething();
		std::cout << t << std::endl;
	}
};

void TestTupleForeach()
{
	tp_for_each(Functor(), std::make_tuple<int, double, int, std::string>(1, 2.5, 3, std::string("abc")));
}

int main(void)
{
	TestTupleForeach();

	return 0;
}
