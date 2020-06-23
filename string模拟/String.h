#pragma once
//#include<string>
#include<iostream>
using namespace std;

class String
{
public:
	String();//�޲ι���
	String(const char* str);//���εĹ���
	void Swap(String& str);//����
	String(const String& str);//���������ִ�д��
	String& operator=(String str);//��ֵ
	~String();//����
	void push_back(const char& ch);//β��
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
	const size_t size();//����
	const char* c_str();//��ȡ�ַ�
	void insert(size_t pos,const char& ch); 
	void insert(size_t pos, const char* str);//�����ַ���
	void erase(size_t pos, size_t len);//ɾ��
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