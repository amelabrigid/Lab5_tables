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
	Ordered_map() : maxsize{1}, size{0}
	{
		data = new line<tkey, tval>;
	}
	Ordered_map(tkey key, tval val) : size{ 1 }, maxsize { 2 }
	{
		data = new line<tkey, tval>[2];
		data[0].key = key;
		data[0].val = val;
	}
	bool Insert (const tkey& k, const tval& v) override { // O(n) 
		
		try
		{
			tval& t = this->Find(k);
		}
		catch (int error)
		{
			if (size >= maxsize) //перепаковка
				{
				maxsize *= 2;
				line<tkey, tval>* ndata = new line<tkey, tval>[maxsize];
				for (int i = 0; i < size; ++i)
				{
					ndata[i] = data[i];
				}
				delete[] data;
				data = ndata;
			}
			int i = 0;
			while ((i < size) && (k > data[i].key)) i++;
			for (int j = size - 1; j >= i; --j)
			{
				data[j + 1] = data[j];
			}
			data[i] = line<tkey, tval>(k, v);
			size++;	
			return true;
		}
		int j{};
		while (data[j].key != k) j++;
		data[j].val = v;
		return true;
	}
	bool Delete(const tkey& k) override {
		if (size) {
			try
			{
				tval& t = this->Find(k);
			}
			catch (int error)
			{
				return false;
			}
			int i{};
			while (data[i].key != k) i++;
			while (i < size - 1)
			{
				data[i] = data[i + 1];
				i++;
			}
			size--;
			return true;
		}
		else
		{
			throw "map is empty";
			return false;
		}
	}
	tval& Find(const tkey& k) override {
		if (size) {
			for (int i = 0; i < size; ++i)
			{
				if (data[i].key == k) return data[i].val;
			}
			int error{ 15 };
			throw error;
			tval r{};
			return r;
		}
		else {
			throw "map is empty";
			tval r{};
			return r;
		}
	}
	tval& get_val(int k)
	{
		return data[k].val;
	}
	tkey& get_key(int k)
	{
		return data[k].key;
	}
};