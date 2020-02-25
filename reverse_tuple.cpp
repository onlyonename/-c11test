#include <iostream>
#include <tuple>

using namespace std;

template <int...>
struct IndexTuple {};

template <int N, int...Indexs>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexs...>{};

template <int...Indexs>
struct MakeIndexes<0, Indexs...>
{
	typedef IndexTuple<Indexs...> type;
};

template<int I, typename IndexTuple, typename... Types>
struct make_indexes_reverse_impl;

//declare
template<int I, int... Indexes, typename T, typename... Types>
struct make_indexes_reverse_impl<I, IndexTuple<Indexes...>, T, Types...>
{
	using type = typename make_indexes_reverse_impl<I - 1, IndexTuple<Indexes..., I - 1>, Types...>::type;
};

//terminate
template<int I, int... Indexes>
struct make_indexes_reverse_impl<I, IndexTuple<Indexes...>>
{
	using type = IndexTuple<Indexes...>;
};

//type trait
template<typename ... Types>
struct make_reverse_indexes : make_indexes_reverse_impl<sizeof...(Types), IndexTuple<>, Types...>
{};

//·´×ª
template <class...Args, int...Indexes>
auto reverse_impl(tuple<Args...>&& tup, IndexTuple<Indexes...>&&) -> decltype(make_tuple(get<Indexes>(forward<tuple<Args...>>(tup))...))
{
	return make_tuple(get<Indexes>(forward<tuple<Args...>>(tup))...);
}

template <class...Args>
auto Reverse(tuple<Args...>&& tup) -> decltype(reverse_impl(forward<tuple<Args...>>(tup), typename make_reverse_indexes<Args...>::type()))
{
	return reverse_impl(forward<tuple<Args...>>(tup), typename make_reverse_indexes<Args...>::type());
}


template <class Tuple, size_t N>
struct TuplePrinter
{
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		cout << ", " << get<N - 1>(t);
	}
};

template <class Tuple>
struct TuplePrinter<Tuple, 1>
{
	static void print(const Tuple& t)
	{
		cout << get<0>(t);
	}
};

template <class...Args>
void PrintTuple(const tuple<Args...>& t)
{
	cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	cout << ")\n";
}

void TupleReverse()
{
	auto tp1 = make_tuple<int, short, double, char>(1, 2, 2.5, 'a');
	//auto tp2 = Reverse(make_tuple<int, short, double, char>(1, 2, 2.5, 'a'));
	auto tp2 = Reverse(move(tp1));

	PrintTuple(tp1);
	PrintTuple(tp2);
}

int main(void)
{
	TupleReverse();

	return 0;
}