#pragma once
#include "basetable.h"

template <typename tskey, typename tsval>
struct line {
	tskey key;
	tsval val;
	line() : key{}, val{}
};

template <typename tkey, typename tval>

class Ordered_map : public BaseTable<tkey, tval>
{
private: 
	line<tkey, tval>* data;
	size_t size;
public:
	Ordered_map() : size{}, data{};
	Ordered_map(tkey key, tval val) : size = 1
	{
		data = new line<tkey, tval>[1];
		data[0].key = key;
		data[0].val = val;
	}
	bool Insert(const tkey&, const tval&) {};
	bool Delete(const tkey&) {};
	tval& Find(tkey) {};

};