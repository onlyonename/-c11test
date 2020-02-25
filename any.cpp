#include <iostream>
#include <memory>
#include <typeindex>
#include <string>

using namespace std;


struct Any
{
	Any(void) : m_tpIndex(type_index(typeid(void))){}
	Any(const Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
	Any(Any && that) : m_ptr(move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}

	//创建智能指针时，对于一般的类型，通过decay来移除引用和cv符，从而获取原始类型
	template<typename U, class = typename enable_if<!is_same<typename decay<U>::type, Any>::value, U>::type>
	Any(U && value) : m_ptr(new Derived < typename decay<U>::type>(forward<U>(value))),
		m_tpIndex(type_index(typeid(typename decay<U>::type))){}

	bool IsNull() const { return !bool(m_ptr); }

	template<class U> bool Is() const
	{
		return m_tpIndex == type_index(typeid(U));
	}

	//将Any转换为实际的类型
	template<class U>
	U& AnyCast()
	{
		if (!Is<U>())
		{
			cout << "can not cast " << typeid(U).name() << " to " << m_tpIndex.name() << endl;
			throw bad_cast();
		}

		auto derived = dynamic_cast<Derived<U>*> (m_ptr.get());
		return derived->m_value;
	}

	Any& operator=(const Any& a)
	{
		if (m_ptr == a.m_ptr)
			return *this;

		m_ptr = a.Clone();
		m_tpIndex = a.m_tpIndex;
		return *this;
	}

private:
	struct Base;
	typedef unique_ptr<Base> BasePtr;

	struct Base
	{
		virtual ~Base() {}
		virtual BasePtr Clone() const = 0;
	};

	template<typename T>
	struct Derived : Base
	{
		template<typename U>
		Derived(U && value) : m_value(forward<U>(value)) { }

		BasePtr Clone() const
		{
			return BasePtr(new Derived<T>(m_value));
		}

		T m_value;
	};

	BasePtr Clone() const
	{
		if (m_ptr != nullptr)
			return m_ptr->Clone();

		return nullptr;
	}

private:

	BasePtr m_ptr;
	type_index m_tpIndex;
};


int main()
{
	Any n;
	auto r = n.IsNull();//true
	std::string s1 = "hello";
	n = s1;
	cout << n.AnyCast<string>() << endl;
	
	n = "world";
	n.AnyCast<int>();  //can not cast int to string
	Any n1 = 1;
	n1.Is<int>(); //true

	return 0;
}




