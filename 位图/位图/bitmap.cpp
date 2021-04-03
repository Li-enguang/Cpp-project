#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

class Bitmap
{
public:
	Bitmap(size_t range)
	{
		//range 范围 加一防止出现没有比32大的数，计算出来全是0，不能开空间
		_bit.resize(range / 32 + 1);
	}

	//查询操作
	bool Test(size_t num)
	{
		int idx = num / 32;//整数位置
		int bitidx = num % 32;//在哪一位
		return _bit[idx] &(1<<bitidx);
	}

	void Set(size_t num)
	{
		int idx = num / 32;//整数位置
		int bitidx = num % 32;//在哪一位
		_bit[idx] |= (1 << bitidx);
	}

	void Reset(size_t num)
	{
		int idx = num / 32;//整数位置
		int bitidx = num % 32;//在哪一位
		_bit[idx] &= ~(1 << bitidx);
	}
private:
	vector<int> _bit;
};

struct HashStr1
{
	size_t operator()(const string &s)
	{
		size_t ret = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			ret *= 131;
			ret += s[i];
		}
		return ret;
	}
};
struct HashStr2
{
	size_t operator()(const string& s)
	{
		size_t ret = 0;
		size_t magic = 63689;
		for (size_t i = 0; i < s.size(); i++)
		{
			ret *= magic;
			ret += s[i];
			magic *= 378551;
		}
		return ret;
	}
};
struct HashStr3
{
	size_t operator()(const string& s)
	{
		size_t ret = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			ret *= 65599;
			ret += s[i];
		}
		return ret;
	}
};
template<class K , class Hash1 = HashStr1, class Hash2 = HashStr2, class Hash3 = HashStr3>
class bloomfilter
{
public:
	bloomfilter(size_t num)
		:_bs(5 * num)
		, _num(5 * num)
	{}
	void set(K key)
	{
		size_t index1 = Hash1()(key) % _num;
		size_t index2 = Hash2()(key) % _num;
		size_t index3 = Hash3()(key) % _num;
		_bs.Set(index1);
		_bs.Set(index2);
		_bs.Set(index3);
	}
	bool test(K key)
	{
		size_t index1 = Hash1()(key) % _num;
		if (_bs.Test(index1) == false)
			return false;
		size_t index2 = Hash2()(key) % _num;
		if (_bs.Test(index2) == false)
			return false;
		size_t index3 = Hash3()(key) % _num;
		if (_bs.Test(index3) == false)
			return false;
		return true;
	}
private:
	Bitmap _bs;
	size_t _num;
};
int main()
{
	//Bitmap bp(100);
	//bp.Set(10);
	//bp.Set(20);
	//bp.Set(30);
	//cout << bp.Test(20);
	//bp.Reset(20);
	//cout << bp.Test(20);
	bloomfilter<string> bs(50);
	bs.set("aaaabccc");
	bs.set("aaabccc");

	return 0;
}
