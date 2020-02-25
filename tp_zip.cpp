#include <utility>
#include <tuple>
#include <iostream>

using namespace std;

//将两个tuple合起来，前一个tuple中的每个元素为key，后一个tuple中的每个元素为value，组成一个pair集合
namespace details
{
	template<typename Tuple, size_t N>
	struct tuple_print
	{
		static void print(const Tuple& t, std::ostream& os)
		{
			tuple_print<Tuple, N-1>::print(t, os);
			os << ", " << std::get<N-1>(t); 
		}
	};
	
	// 类模板的特化版本
	template<typename Tuple>
	struct tuple_print<Tuple, 1>
	{
		static void print(const Tuple& t, std::ostream& os)
		{
			os << "(" << std::get<0>(t); 
		}
	};
 
	// operator<<
	template<typename... Args>
	std::ostream& operaotr<<(std::ostream& os, const std::tuple<Args...>& t)
	{
		tuple_print<decltype(t), sizeof...(Args)>::print(t, os);
		return os << ")";
	}
	
	
	template <int...>
	struct IndexTuple {};

	template <int N, int...Indexs>
	struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexs...>{};

	template <int...Indexs>
	struct MakeIndexes<0, Indexs...>
	{
		typedef IndexTuple<Indexs...> type;
	};

	template<std::size_t N, typename T1, typename T2>
	using pair_type = std::pair<typename std::tuple_element<N, T1>::type, typename std::tuple_element<N, T2>::type>;

	template<std::size_t N, typename T1, typename T2>
	pair_type<N, T1, T2> pair(const T1& tup1, const T2& tup2)
	{
		//
		return std::make_pair(std::get<N>(tup1), std::get<N>(tup2));
	}

	template<int... Indexes, typename T1, typename T2>
	auto pairs_helper(IndexTuple<Indexes...>, const T1& tup1, const T2& tup2) -> decltype(std::make_tuple(pair<Indexes>(tup1, tup2)...))
	{
		return std::make_tuple(pair<Indexes>(tup1, tup2)...);
	}

} // namespace details

template<typename Tuple1, typename Tuple2>
auto Zip(Tuple1 tup1, Tuple2 tup2) -> decltype(details::pairs_helper(typename details::MakeIndexes<std::tuple_size<Tuple1>::value>::type(), tup1, tup2))
{
	static_assert(std::tuple_size<Tuple1>::value == std::tuple_size<Tuple2>::value,	"tuples should be the same size.");
	
	return details::pairs_helper(typename details::MakeIndexes<std::tuple_size<Tuple1>::value>::type(), tup1, tup2);
}




void TupleZip()
{
    auto tp1 = std::make_tuple<int, short, double, char>(1, 2, 2.5, 'a');
	auto tp2 = std::make_tuple<double, short, double, char>(1.5, 2, 2.5, 'z');
	auto mypairs = Zip(tp1, tp2);

    size_t tp_size = tuple_size<decltype(mypairs)>::value;
}

int main(void)
{
	TupleZip();

	return 0;
}
