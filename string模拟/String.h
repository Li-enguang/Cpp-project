#pragma once
//#include<string>
#include<iostream>
using namespace std;

class String
{
public:
	String();//无参构造
	String(const char* str);//带参的构造
	void Swap(String& str);//交换
	String(const String& str);//拷贝构造现代写法
	String& operator=(String str);//赋值
	~String();//析构
	void push_back(const char& ch);//尾插
	typedef char* iterator;
	iterator begin();
	iterator end();
	typedef const char* const_iterator;
	const_iterator begin() const;
	const_iterator end() const;
	String operator+(const String& str);
	String& operator+=(const String& str);
	bool operator==(const String& str);
	char& operator[](size_t n);
	const size_t size();//长度
	const char* c_str();//获取字符
	void insert(size_t pos,const char& ch); 
	void insert(size_t pos, const char* str);//输入字符串
	void erase(size_t pos, size_t len);//删除
	void popback();
	size_t find(const char* str);
	const size_t npos=-1;
	//friend istream& getline(istream& in, String& str);
	friend ostream& operator<<(ostream& out,const String& str);
	friend istream& operator>>(istream& in, String& str);
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};