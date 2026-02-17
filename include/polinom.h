// класс Полином - упорядоченный односвязный список Мономов
// поддерживает операции Печать, Вставка монома, Удаление монома,  
// Поиск монома, Сложение полиномов(слияние упорядоченных списков), 
// Умножение полиномов

#pragma once



using namespace std;
#include "list.h"
#include "monom.h"
#include<string>
#include<stdint.h>
class Polinom : private TSinglyList<Monom>
{
public:
	Polinom(): TSinglyList()
	{
		//PushFront(Monom("0"));//empty
	}

	Polinom(string& str): TSinglyList()
	{
		//PushFront(Monom("0"));
		Parsing(str);
		Sort();
	}
	
	Polinom(const Polinom& pol): TSinglyList(pol)
	{
	}

	void Parsing(string& str)
	{
		int index = 0;
		do
		{
			index = str.find_first_of("+-", index);
			if (index == 0)
			{
				index = str.find_first_of("+-", 1); // 1) избавиться от скобок 2) поменять возвращаемое в +,=+ 3) метод для отсеивания 0
			}
			string stroka = str.substr(0, index);
			Monom mon(stroka);
			if (mon.coeff != 0)
			{
				PushBack(mon);
			}
			//PushBack(Monom(str.substr(0, index)));
			if (index != std::string::npos)
			{
				str.erase(0, index);
				index = 1;
			}
		}
		while (index != std::string::npos);

	}
	void Sort()
	{
		Polinom tmp;
		TNode* current = pFirst;
		while (sz!=0)
		{
			Monom Bigest = pFirst->value;
			int index = -2;
			int big_index = -1;
			TNode* CUR = pFirst;
			while(CUR != nullptr)
			{
				index++;
				if (CUR->value > Bigest)
				{
					Bigest = CUR->value;
					big_index = index;
				}
				CUR = CUR->pNext;
			}
			tmp.PushBack(Bigest);
			if (big_index == -1)
			{
				PopFront();
			}
			else
			{
				EraseAfter(big_index);
			}
		}
		tmp.Zero();
		operator=(tmp);
	}

	size_t size() const noexcept
	{
		return TSinglyList<Monom>::size();
	}
	Monom& operator[](size_t index)
	{
		return TSinglyList<Monom>::operator[](index);
	}
	Polinom& operator=(Polinom& pol) 
	{
		return (Polinom&) TSinglyList<Monom>::operator=(pol);
	}
	Polinom operator*(double con)
	{
		Polinom result;
		TNode* curr = pFirst;
		while (curr != nullptr) {
			Monom tmp_monom = curr->value * con;
			result.PushBack(tmp_monom);
			curr = curr->pNext;
		}
		
		result.Zero();
		return result;
	}
	Polinom operator*(Monom& mon)
	{
		Polinom result;
		TNode* curr = pFirst;
		while (curr != nullptr) {
			Monom tmp_monom = curr->value * mon;
			result.PushBack(tmp_monom);
			curr = curr->pNext;
		}
		result.Zero();

		return result;
	}
	void Zero()
	{
		TNode* tmp = pFirst;
		int index = -2;
		while (tmp != nullptr)
		{
			index++;
			if (tmp->value.coeff == 0)
			{
				if (index == -1)
				{
					tmp = tmp->pNext;
					PopFront();
				}
				else
				{
					tmp = tmp->pNext;
					EraseAfter(index);
				}
			}
			else
			{
				tmp = tmp->pNext;
			}

		}
	}
	Polinom operator+(Polinom& pol)
	{
		Polinom result;
		TNode* tmp1 = pFirst;
		TNode* tmp2 = pol.pFirst;
		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->value > tmp2->value)
			{
				result.PushBack(tmp1->value);
				tmp1 = tmp1->pNext;
			}
			else if (tmp1->value < tmp2->value)
			{
				result.PushBack(tmp2->value);
				tmp2 = tmp2->pNext;
			}
			else
			{
				double sumcoef = tmp1->value.coeff + tmp2->value.coeff;
				if (sumcoef != 0)
				{
					result.PushBack(Monom(sumcoef, tmp1->value.degree));
				}
				tmp1 = tmp1->pNext;
				tmp2 = tmp2->pNext;
			}

		}
		while (tmp1 != nullptr)
		{
			result.PushBack(tmp1->value);
			tmp1 = tmp1->pNext;
		}
		while (tmp2 != nullptr)
		{
			result.PushBack(tmp2->value);
			tmp2 = tmp2->pNext;
		}
		result.Zero();
		return result;
	}
	Polinom operator-(Polinom& pol)
	{
		Polinom result;
		TNode* tmp1 = pFirst;
		TNode* tmp2 = pol.pFirst;
		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->value > tmp2->value)
			{
				result.PushBack(tmp1->value*(-1));
				tmp1 = tmp1->pNext;
			}
			else if (tmp1->value < tmp2->value)
			{
				result.PushBack(tmp2->value*(-1));
				tmp2 = tmp2->pNext;
			}
			else
			{
				double sumcoef = tmp1->value.coeff - tmp2->value.coeff;
				if (sumcoef != 0)
				{
					result.PushBack(Monom(sumcoef, tmp1->value.degree)*(-1));
				}
				tmp1 = tmp1->pNext;
				tmp2 = tmp2->pNext;
			}

		}
		while (tmp1 != nullptr)
		{
			result.PushBack(tmp1->value);
			tmp1 = tmp1->pNext;
		}
		while (tmp2 != nullptr)
		{
			result.PushBack(tmp2->value*(-1));
			tmp2 = tmp2->pNext;
		}
		result.Zero();
		return result;
	}
	Polinom& operator+=(Polinom& pol)
	{
		Polinom result;
		TNode* tmp1 = pFirst;
		TNode* tmp2 = pol.pFirst;
		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->value > tmp2->value)
			{
				result.PushBack(tmp1->value);
				tmp1 = tmp1->pNext;
			}
			else if (tmp1->value < tmp2->value)
			{
				result.PushBack(tmp2->value);
				tmp2 = tmp2->pNext;
			}
			else
			{
				double sumcoef = tmp1->value.coeff + tmp2->value.coeff;
				if (sumcoef != 0)
				{
					result.PushBack(Monom(sumcoef, tmp1->value.degree));
				}
				tmp1 = tmp1->pNext;
				tmp2 = tmp2->pNext;
			}

		}
		while (tmp1 != nullptr)
		{
			result.PushBack(tmp1->value);
			tmp1 = tmp1->pNext;
		}
		while (tmp2 != nullptr)
		{
			result.PushBack(tmp2->value);
			tmp2 = tmp2->pNext;
		}
		result.Zero();
		*this = result;
		return *this;
	}
	Polinom& operator-=(Polinom& pol)
	{
		Polinom result;
		TNode* tmp1 = pFirst;
		TNode* tmp2 = pol.pFirst;
		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->value > tmp2->value)
			{
				result.PushBack(tmp1->value*(-1));
				tmp1 = tmp1->pNext;
			}
			else if (tmp1->value < tmp2->value)
			{
				result.PushBack(tmp2->value*(-1));
				tmp2 = tmp2->pNext;
			}
			else
			{
				double sumcoef = tmp1->value.coeff - tmp2->value.coeff;
				if (sumcoef != 0)
				{
					result.PushBack(Monom(sumcoef, tmp1->value.degree)*(-1));
				}
				tmp1 = tmp1->pNext;
				tmp2 = tmp2->pNext;
			}

		}
		while (tmp1 != nullptr)
		{
			result.PushBack(tmp1->value*(-1));
			tmp1 = tmp1->pNext;
		}
		while (tmp2 != nullptr)
		{
			result.PushBack(tmp2->value*(-1));
			tmp2 = tmp2->pNext;
		}
		result.Zero();
		result.Zero();
		*this = result;
		return *this;
	}
	Polinom operator*(Polinom& pol)
	{
		Polinom result;
		Monom tmp_mon;
		TNode* tmp1 = pFirst;
		while (tmp1 != nullptr)
		{
			TNode* tmp2 = pol.pFirst;
			while (tmp2 != nullptr)
			{
				tmp_mon = tmp1->value * tmp2->value;
				if (tmp_mon.coeff != 0)
				{
					result.PushBack(tmp_mon);
				}
				tmp2 = tmp2->pNext;
			}
			tmp1 = tmp1->pNext;
		}
		result.Sort();
		return result;
		//Polinom tmp;
		//for (int i = 0; i < size(); i++)
		//{
		//	for (int j = 0; j < pol.size(); j++)
		//	{
		//		tmp_mon = operator[](i) * pol[j];
		//		//cout << "mon=" << tmp_mon << endl;
		//		tmp.PushBack(tmp_mon);
		//		//tmp_mon.Clear();
		//	}
		//}
		////tmp.Sort();
		//return tmp;
	}
	~Polinom()
	{
		TSinglyList<Monom>::~TSinglyList();
	}
	bool operator==(const Polinom& pol) const
	{
		if (size() != pol.size())
		{
			return false;
		}
		else
		{
			TNode* tmp1 = pFirst;
			TNode* tmp2 = pol.pFirst;
			while (tmp1 != nullptr)
			{
				if (tmp1->value.compare(tmp2->value) == false)
				{
					return false;
				}
				tmp1 = tmp1->pNext;
				tmp2 = tmp2->pNext;
			}
			
		}
		return true;
	}
};