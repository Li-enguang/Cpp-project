#define _CRT_SECURE_NO_WARNINGS 1

#include"String.h"

String::String()//无参构造
	:_str(new char[16])
	, _size(0)
	, _capacity(0)
{
	_str[_size] = '\0';
	_capacity = 15;
}

String::String(const char* str)//带参的构造
{
	_size = strlen(str);
	_capacity = _size;
	_str = new char[_capacity + 1];
	strcpy(_str, str);
}

void String::Swap(String& str)//交换内容
{
	swap(_str, str._str);
	swap(_size, str._size);
	swap(_capacity, str._capacity);
}

String::String(const String& str)//拷贝构造现代写法
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	String tmp(str._str);//构造一个临时变量
	Swap(tmp); //再进行交换
}

/*
String::String(const String& str)// 拷贝构造
	:_str(new char[str._capacity])
	,_size(str._size)
	,_capacity(str._capacity)
{
	strcpy(_str, str._str);
}*/

/*String& String::operator=(const String& str)//赋值
	{
		if (this != &str)
		{
			char* tmp=new char[str._capacity];  //开空间
			strcpy(tmp, str._str);  //拷贝内容
			delete[] _str; //释放原空间

			_str = tmp;
			_size = str._size;
			_capacity =str._capacity;
			
			return *this;
		}
		
	}*/

String& String::operator=(String str)//赋值 ：调用拷贝构造 拷贝出一个str 在进行交换
{
	Swap(str);
	return *this;
}

String::~String()//析构
{
	delete[_capacity + 1] _str;
	_size = _capacity = 0;
}

void String::push_back(const char& ch)
{
	if (_size == _capacity)
	{
		_capacity *= 2;
		char* tmp = new char[_capacity + 1];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
	_str[_size] = ch;
	_size++;
	_str[_size] = '\0';

}

 char* String::begin()
{
	return _str;

}
 char* String::end()
 {
	 return _str +_size;

 }

 const char* String::begin() const
 {
	 return _str;

 }
 
 const char* String::end() const
 {
	 return _str+_size;

 }
void String::insert(size_t pos,const char& ch)
{
	size_t end = _size+1;
	if (_size == _capacity)
	{
		_capacity *= 2;
		char* tmp = new char[_capacity + 1];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
	//delete[] _str;
	while (end > pos)
	{
		_str[end] = _str[end-1];
		--end;
	}
	_str[pos] = ch;
}

void String::insert(size_t pos, const char* str)
{
	size_t len = strlen(str);
	if (len + _size > _capacity)
	{
		char* tmp = new char[len + _size + 1];
		strcpy(tmp, _str);
		delete[]_str;
		_str = tmp;
	}
	_size += len;
	_capacity += len;
	size_t end = _size;
	while (end > pos+len-1)
	{
		_str[end] = _str[end - len];
		--end;
	}
	for (size_t i = 0; i < len; i++)
	{
		_str[i + pos] = str[i];
	}

}

void String::erase(size_t pos, size_t len)
{
	if (pos < _size)
	{
		if (pos + len >= _size)
		{
			_str[pos] = '\0';
			_size =pos;
		}
		else
		{
			for (size_t i = 0; i < len; i++)
			{
			_str[pos+i] = _str[pos + len+i];
			}
			_str[pos + len] = '\0';		
			_size -= len;
		}
	}
}

size_t String::find(const char* str)
{
	char* cur = strstr(_str, str);
	if (cur)
	{
		return cur - _str;
	}
	else
		return npos;
}

String String::operator+(const String& str)
{
	String newstr;
	newstr._size += str._size;
	newstr._capacity += str._capacity;
	newstr._str = new char[newstr._capacity + 1];
	strcpy(newstr._str,_str);
	strcat(newstr._str, str._str);
	return newstr;
}

String& String::operator+=(const String& str)
{
	_size += str._size;
	_capacity += str._capacity;
	char* newstr = new char[_size + 1];
	strcpy(newstr,_str);
	strcat(newstr, str._str);
	delete[]_str;
	_str = newstr;
	return *this;
}

bool String::operator==(const String& str)
{
	if (_size != str._size)return false;
	return strcmp(_str, str._str) ? true : false;
}
char& String::operator[](size_t n)
{
	if (n > _size)
	{
		return _str[_size-1];
	}
	return _str[n];

}

const size_t String::size()
{
	return _size;
}
const char* String::c_str()
{
	return _str;
}

void String::popback()
{
	if (_size)
	{
	_str[_size - 1] = '\0';
	_size--;
	}

}


istream& operator>>(istream& in, String& str)
{
	char tmp[1000];
	in >> tmp;
	str._capacity=str._size = strlen(tmp);
	str._str = new char[str._size + 1];
	strcpy(str._str, tmp);
	return in;
}

ostream& operator<<(ostream& out, const String& str)
{
	//out << str._str<<endl;
	for (const auto& ch : str)
	{
		out << ch << ' ';
	}
	return out;
}