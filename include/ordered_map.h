#pragma once
#include "basetable.h"

template <typename tskey, typename tsval>
struct line {
	tskey key;
	tsval val;
	line() { 
		key = tskey{}; 
		val = tsval{}; 
	}
	line(tskey k, tsval v)
	{
		key = tskey{ k };
		val = tsval{ v };
	}
	line(line& l) : val{l.val}, key{l.key} {}
	line operator=(line& l)
	{
		val = l.val;
		key = l.key;
		return l;
	}
};

template <typename tkey, typename tval>

class Ordered_map : BaseTable<tkey, tval>
{
private: 
	line<tkey, tval>* data;
	size_t size;
	size_t maxsize;
public:
	Ordered_map() : maxsize{}, size{}
	{
		data = new line<tkey, tval>;
	}
	Ordered_map(tkey key, tval val) : size{ 1 }, maxsize { 2 }
	{
		data = new line<tkey, tval>[2];
		data[0].key = key;
		data[0].val = val;
	}
	bool Insert (const tkey& k, const tval& v) override {
		
		if (size >= maxsize)
		{
			maxsize *= 2;
			line<tkey, tval>* ndata = new line<tkey, tval>[maxsize];
			for (int i = 0; i < size; ++i)
			{
				ndata[i] = data[i];
			}
			delete[] data;
			data = ndata;
			delete[] ndata;
		}
		int i = 0;
		while ((i < size) && (k < data[i].key))
		{
			i++;
		}
		data[i] = line<tkey, tval>(k, v);
		size++;
		return true;
	}
	bool Delete(const tkey& k) override {
		return true;
	}
	tval& Find(const tkey& k) override {
		tval v{};
		return v;
	}

};