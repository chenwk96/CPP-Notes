#include <iostream>
#include <string>
//#include <memory>				 //std::allocator  
using namespace std;

//namespace jj02
//{
//
//	class A
//	{
//	public:
//		int id;
//
//		A() : id(0) { cout << "default ctor. this=" << this << " id=" << id << endl; }
//		A(int i) : id(i) { cout << "ctor. this=" << this << " id=" << id << endl; }
//		~A() { cout << "dtor. this=" << this << " id=" << id << endl; }
//	};
//
//	void test_call_ctor_directly()
//	{
//		cout << "\ntest_call_ctor_directly().......... \n";
//
//		string* pstr = new string;
//		cout << "str= " << *pstr << endl;
//		//! pstr->string::string("jjhou");  
//		//[Error] 'class std::basic_string<char>' has no member named 'string'
//		//! pstr->~string();	//crash -- 其語法語意都是正確的, crash 只因為上一行被 remark 起來嘛.  
//		cout << "str= " << *pstr << endl;
//
//
//		//------------
//
//		A* pA = new A(1);         	//ctor. this=000307A8 id=1
//		cout << pA->id << endl;   	//1
//		pA->A::A(3);
//		cout << pA->id << endl;
//		//!	pA->A::A(3);                //in VC6 : ctor. this=000307A8 id=3
//		//in GCC : [Error] cannot call constructor 'jj02::A::A' directly
//
//		A::A(5);
//		//!	A::A(5);	  				//in VC6 : ctor. this=0013FF60 id=5
//		//         dtor. this=0013FF60  	
//		//in GCC : [Error] cannot call constructor 'jj02::A::A' directly
//		//         [Note] for a function-style cast, remove the redundant '::A'
//
//		cout << pA->id << endl;   	//in VC6 : 3
//		//in GCC : 1  	
//
//		delete pA;                	//dtor. this=000307A8 
//
//		//simulate new
//		void* p = ::operator new(sizeof(A));
//		cout << "p=" << p << endl; 	//p=000307A8
//		pA = static_cast<A*>(p);
//		pA->A::A(2);
//		//!	pA->A::A(2);				//in VC6 : ctor. this=000307A8 id=2
//		//in GCC : [Error] cannot call constructor 'jj02::A::A' directly  	
//
//		cout << pA->id << endl;     //in VC6 : 2
//		//in GCC : 0  	
//
//		//simulate delete
//		pA->~A();					//dtor. this=000307A8 
//		::operator delete(pA);		//free()
//	}
//} //namespace
//
//int main(void)
//{
//	jj02::test_call_ctor_directly();
//	return 0;
//}


namespace jj06
{

	class Foo
	{
	public:
		int _id;
		long _data;
		string _str;

	public:
		static void* operator new(size_t size);
		static void  operator delete(void* deadObject, size_t size);
		static void* operator new[](size_t size);
		static void  operator delete[](void* deadObject, size_t size);

		Foo() : _id(0) { cout << "default ctor. this=" << this << " id=" << _id << endl; }
		Foo(int i) : _id(i) { cout << "ctor. this=" << this << " id=" << _id << endl; }
		//virtual 
		~Foo() { cout << "dtor. this=" << this << " id=" << _id << endl; }

		//不加 virtual dtor, sizeof = 12, new Foo[5] => operator new[]() 的 size 參數是 64, 
		//加了 virtual dtor, sizeof = 16, new Foo[5] => operator new[]() 的 size 參數是 84, 
		//上述二例，多出來的 4 可能就是個 size_t 欄位用來放置 array size. 
	};

	void* Foo::operator new(size_t size)
	{
		Foo* p = (Foo*)malloc(size);
		cout << "Foo::operator new(), size=" << size << "\t  return: " << p << endl;

		return p;
	}

	void Foo::operator delete(void* pdead, size_t size)
	{
		cout << "Foo::operator delete(), pdead= " << pdead << "  size= " << size << endl;
		free(pdead);
	}

	void* Foo::operator new[](size_t size)
	{
		Foo* p = (Foo*)malloc(size);  //crash, 問題可能出在這兒 
		cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;

		return p;
	}

		void Foo::operator delete[](void* pdead, size_t size)
	{
		cout << "Foo::operator delete[](), pdead= " << pdead << "  size= " << size << endl;

		free(pdead);
	}

	//-------------	
	void test_overload_operator_new_and_array_new()
	{
		cout << "\ntest_overload_operator_new_and_array_new().......... \n";

		cout << "sizeof(Foo)= " << sizeof(Foo) << endl;

		{
			Foo* p = new Foo(7);
			delete p;

			Foo* pArray = new Foo[5];	//無法給 array elements 以 initializer 
			delete[] pArray;
		}

		{
			cout << "testing global expression ::new and ::new[] \n";
			// 這會繞過 overloaded new(), delete(), new[](), delete[]() 
			// 但當然 ctor, dtor 都會被正常呼叫.  

			Foo* p = ::new Foo(7);
			::delete p;

			Foo* pArray = ::new Foo[5];
			::delete[] pArray;
		}
	}
} //namespace

int main(void)
{	
		cout << sizeof(int) << endl; 
		cout << sizeof(long) << endl;
		cout << sizeof(string) << endl;
	jj06::test_overload_operator_new_and_array_new();
	return 0;
}