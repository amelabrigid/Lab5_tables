#pragma once



// класс или структура Монома (double коэффициент, целая свернутая степень)
using namespace std;
#include<stdint.h>
#include<string>
#include <iostream>
struct Monom
{
	double coeff;
	uint16_t degree;
	Monom(double c, uint16_t x)
	{
		coeff = c;
		degree = x;
		if (degree >= 1000)
		{
			throw 1;
		}
	}
	Monom()
	{
		coeff = 0;
		degree = 0;
	}
	Monom(const string& str)
	{
		coeff = 0;
		degree = 0;
		int index = str.find_first_of("xyz");
		string tmp = str.substr(0, index);
		coeff = stod(tmp);
		if (index != std::string::npos)
		{
			for (int i = index; i < str.size(); i++)
			{
				if (str[i] == 'x')
				{
					string stroka(1, str[i + 1]);
					degree += 100 * stod(stroka);
				}
				if (str[i] == 'y')
				{
					string stroka(1, str[i + 1]);
					degree += 10 * stod(stroka); // deg <=9
				}
				if (str[i] == 'z')
				{
					string stroka(1, str[i + 1]);
					degree += stod(stroka);
				}
			}
		}

	}


	bool operator<(const Monom& m) const
	{
		if (m.degree > degree)
		{
			return true;
		}
		return false;
	}
	bool operator>(const Monom& m) const
	{
		if (m.degree < degree)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Monom& m) const
	{
		if (m.degree == degree)
		{
			return true;
		}
		return false;
	}
	bool compare(const Monom& x) const
	{
		if (x.degree == degree && x.coeff==coeff)
		{
			return true;
		}
		return false;
	}
	Monom& operator=(const Monom& mon)
	{
		degree = mon.degree;
		coeff = mon.coeff;
		return *this;
	}
	Monom& operator*=(double con)
	{
		coeff *=con;
		return *this;
	}
//	a *= b *= c;


	Monom operator*(double con)
	{
		return Monom(coeff * con, degree);
	}
	
	Monom& operator*=(Monom& mon) 
	{
		degree = mon.degree + degree;
		coeff *= mon.coeff;
		return *this;
	}




	Monom& operator+=(Monom& mon)
	{
		if (mon.degree == degree)
		{
			coeff += mon.coeff;
		}
		return *this;
	}
	Monom& operator-=(Monom& mon)
	{
		if (mon.degree == degree)
		{
			coeff -= mon.coeff;
		}
		return *this;
	}
	Monom operator*(Monom& mon)
	{
		Monom tmp(*this);
		tmp.degree = mon.degree+degree;
		tmp.coeff = mon.coeff*coeff;
		return tmp;

	}
	void Clear()
	{
		degree = 0;
		coeff = 0;
	}
	friend ostream& operator<<(ostream& os, const Monom& obj)
	{
		os << obj.coeff << " " << obj.degree;
		return os;
	}
};