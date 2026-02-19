#pragma once
template <typename tkey, typename tval> 
class BaseTable {
public:
	virtual bool Insert(const tkey&, const tval&) = 0; // возвращает успех/неуспех
	virtual bool Delete(const tkey&) = 0;
	virtual tval& Find(const tkey&) = 0;
};