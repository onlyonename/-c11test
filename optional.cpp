#include <type_traits>
#include <iostream>
#include <string>
#include <map>

using namespace std;


//Optional可判断一个变量是否被赋值过(或初始化过)
template<typename T>
class Optional
{
	using data_t = typename aligned_storage<sizeof(T), alignment_of<T>::value>::type;
	//typedef typename aligned_storage<sizeof(T),
	//                      alignment_of<T>::value>::type data_t;  //这种方式也可以啦
public:
	Optional(){}

	Optional(const T& v)
	{
		Create(v);
	}

	Optional(T&& v)
	{
		Create(move(v));
	}

	~Optional()
	{
		Destroy();
	}

	Optional(const Optional& other)
	{
		if (other.IsInit())
			Assign(other);
	}

	Optional(Optional&& other)
	{
		if (other.IsInit())
		{
			Assign(move(other));
			other.Destroy();
		}
	}

	Optional& operator=(Optional &&other)
	{
		Assign(move(other));
		return *this;
	}

	Optional& operator=(const Optional &other)
	{
		Assign(other);
		return *this;
	}

	template<class... Args>
	void emplace(Args&&... args)
	{
		Destroy();
		Create(forward<Args>(args)...);
	}

	bool IsInit() const { return m_hasInit; }

	explicit operator bool() const
	{
		return IsInit();
	}

	T& operator*()
	{
		return *((T*)(&m_data));
	}

	T const& operator*() const
	{
		if (IsInit())
		{
			return *((T*)(&m_data));
		}

		throw exception("");
	}

	bool operator == (const Optional<T>& rhs) const
	{
		return (!bool(*this)) != (!rhs) ? false : (!bool(*this) ? true : (*(*this)) == (*rhs));
	}

	bool operator < (const Optional<T>& rhs) const
	{
		return !rhs ? false : (!bool(*this) ? true : (*(*this) < (*rhs)));
	}

	bool operator != (const Optional<T>& rhs)
	{
		return !(*this == (rhs));
	}

private:
	template<class... Args>
	void Create(Args&&... args)
	{
		new (&m_data) T(forward<Args>(args)...);
		m_hasInit = true;
	}

	void Destroy()
	{
		if (m_hasInit)
		{
			m_hasInit = false;
			((T*)(&m_data))->~T();
		}
	}

	void Assign(const Optional& other)
	{
		if (other.IsInit())
		{
			Copy(other.m_data);
			m_hasInit = true;
		}
		else
		{
			Destroy();
		}
	}

	void Assign(Optional&& other)
	{
		if (other.IsInit())
		{
			Move(move(other.m_data));
			m_hasInit = true;
			other.Destroy();
		}
		else
		{
			Destroy();
		}
	}

	void Move(data_t&& val)
	{
		Destroy();
		new (&m_data) T(move(*((T*)(&val))));
	}

	void Copy(const data_t& val)
	{
		Destroy();
		new (&m_data) T(*((T*)(&val)));
	}

private:
	bool m_hasInit = false;
	data_t m_data;
};
	
	

struct MyStruct
{
	MyStruct(){}
	MyStruct(int a, int b) : m_a(a), m_b(b){}
	int m_a;
	int m_b;
};

void TestOptional()
{
	Optional<string> a("ok");
	Optional<string> b("ok");
	Optional<string> c("aa");


	cout << a.IsInit() << endl;
	if(a) cout << "a is init!!!" << endl;

	c = a;
	cout << *c << endl;

	Optional<MyStruct> op;
	op.emplace(1, 2);
	MyStruct t; 

	if (op)  //判断op是否被初始化
	{
		t = *op;
		cout << "t content:" << endl;
		cout << t.m_a << " " << t.m_b << endl;
	}

	op.emplace(3, 4);
	t = *op;
	
	cout << "op content:" << endl;
	cout << (*op).m_a << " " << (*op).m_b << endl;
	
	cout << "t content:" << endl;
	cout << t.m_a << " " << t.m_b << endl;
}

int main(void)
{
	TestOptional();

	return 0;
}	
	
	
	
	
	
	
	
	
	
	
	
	
	

