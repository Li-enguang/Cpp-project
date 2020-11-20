#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<string>

using namespace std;
template<class T>
  class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _eos(nullptr)
	{}
	Vector(size_t n,const T& val) //带参构造
		:_start(nullptr)
		, _finish(nullptr)
		, _eos(nullptr)
	{
		resize(n, val);
	}
	Vector(const Vector<T>& v) //拷贝构造
		:_start(nullptr)
		, _finish(nullptr)
		, _eos(nullptr)
	{
		reserve(v.capacity());
		iterator it = begin();
		const_iterator vit = v.begin();
		while (vit != v.end())
		{
			*it++ = *vit++;
			++_finish;
		}
	}
	Vector<T>& operator=(Vector<T> v)
	{
		Swap(v);
		return *this;
	}
	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish,v._finish);
		swap(_eos,v._eos);
	}

	size_t size() const
	{
		return _finish - _start;
	}
	size_t capacity() const
	{
		return _eos - _start;
	}
	void resize(size_t n,const T&val=T())
	{
		if (n > capacity())
		{
			reserve(n);
		}
		if (n > size())
		{
			iterator it = end();
			while (it != _start + n)
			{
				*it = val;
				++it;
			}
		}
		_finish = _start + n;

	}
	void reserve(size_t n)

	{
		size_t oldsize = size();
		if (n > capacity())//开辟空间
		{
			T* tmp = new T[n];

			//拷贝内容
			for (size_t i = 0; i < size(); i++)
			{
				tmp[i] = _start[i];
			}
			//释放原来空间
			delete[] _start;

			_start = tmp;
			_finish = _start + oldsize;
			_eos = _start + n; 
		}
	}
	
	void push_back(const T& val)
	{
		//if (_finish==_eos)
		//{
 	//		size_t newc = (_start == nullptr) ? 1 : 2 * capacity();
		//	reserve(newc);//增容
		//}
		//*_finish = val;
		//++_finish;
		insert(end(), val);
	}
	void pop_back()
	{
		erase(end() - 1);
	}

	iterator begin()
	{
		return _start;
	}
	iterator end()
	{
		return _finish;
	}
	const_iterator begin() const
	{
		return _start;
	}
	const_iterator end() const
	{
		return _finish;
	}

	iterator erase(iterator pos)
	{
		assert(pos >= begin() && pos < end());
		iterator it = pos+1;
		while (it!=end())
		{
			*(it-1) = *(it);
			it++;
		}
		--_finish;
		return pos;
	
	}
	iterator insert(iterator pos, const T& val)
	{
		size_t offset = pos - _start;
		assert(pos >= begin() && pos <= end());
		if (_finish == _eos)
		{
			size_t newc = (_start == nullptr) ? 1 : 2 * capacity();
			reserve(newc);
		}
		pos = _start + offset;
		iterator it = end();
		while(pos != it)
		{
			*it = *(it - 1);
			it--;
		}
		*pos = val;
		_finish++;
		return pos;
	}
	T& operator[](size_t pos)
	{
		assert(pos >= 0 && pos < size());
		return _start[pos];
	}
	const T& operator[](size_t pos) const
	{
		assert(pos >= 0 && pos < size());
		return _start[pos];
	}
	~Vector()
	{
		delete[] _start;
		_start = _finish = _eos = nullptr;
	}
private:
	T* _start;
	T* _finish;
	T* _eos;
};
  template<class T>
  void printfor(const Vector<T>&  v)
  {
	  for (const auto& e: v)
	  {
		  cout << e << " ";
	  }
	  cout << endl;
  }

  void test1()
  {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 1);
	v.insert(v.begin(), 2);
	//v.insert(v.end()-1, 20);
	v.resize(10,1);
	printfor(v);
	Vector<int> ::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it == 1)
			v.erase(it);
		else
			++it;
	}
	printfor(v);
  }

  void test2()
  {
	  Vector<int> v;
	  v.insert(v.begin(), 0);
	  v.insert(v.begin(), 1);
	  v.insert(v.end(),2);
	  printfor(v);

	  Vector<int> b(v);
	  //b = v;
	  printfor(b);

  }
int main()
{
	test2();
	return 0;

}