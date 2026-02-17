// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once


#include<iostream>
#include<string>
#include<vector>
#include<map>
#include"stack.h"
#include"polinom.h"
using namespace std;

enum LEXEM_TYPE {
	OPERAND,
	OPERATION,
	BRACKET,
	VARIABLE
};

struct Lexema
{
	string stroka;
	LEXEM_TYPE typeLex;

};
class  TArithmeticExpression
{
	string infix;
	vector<Lexema> postfix;
	vector<Lexema> lexems;
	map<string, int> priority =
	{
		{ "+",1}, {"-", 1}, {"*",2}, {"/", 2},{"(", 0}
	};
	map<char, Polinom> operands;

public:

	TArithmeticExpression(string stroka)
	{
		infix = stroka;
	}

	vector<Lexema> getLexems()
	{
		return lexems;
	}
	void Parse2()
	{
		int open = 0;
		int close = 0;
		int pos = 0;


		while (pos < infix.size()) {
			string x(1, infix[pos]);
			if (x.find_first_of("()") != -1)
			{
				Lexema tmp;
				tmp.stroka = x;
				if (tmp.stroka == "(")
				{
					open++;
				}
				else
				{
					close++;
				}
				tmp.typeLex = BRACKET;
				lexems.push_back(tmp);
				pos++;
			}

			else if (x.find_first_of("+*/-") != -1)// знак
			{
				Lexema tmp;
				tmp.stroka = x;
				tmp.typeLex = OPERATION;
				lexems.push_back(tmp);
				pos++;
			}
			else {

				// aa + bb
				if (isalpha(infix[pos])) {
					// копим букву
					Lexema tmp;
					tmp.stroka = x;
					tmp.typeLex = VARIABLE;
					lexems.push_back(tmp);
					pos++;
				}
				else if (isdigit(infix[pos])) {
					pos++;
					while (isdigit(infix[pos]) || (infix[pos] == ',') || (infix[pos] == '.'))
					{
						string next_element(1, infix[pos]);
						x += next_element;
						pos++;
					}
					// x = "123.45"
					Lexema tmp;
					tmp.stroka = x;
					tmp.typeLex = OPERAND;
					lexems.push_back(tmp);
				}
			}
		}
	}
	bool check()
	{
		int open = 0;
		int close = 0;
		for (int i = 0; i < lexems.size() - 1; i++)
		{
			if (lexems[i].typeLex == lexems[i + 1].typeLex && lexems[i].typeLex != BRACKET && lexems[i + 1].typeLex != BRACKET)
			{
				return false;
			}
			if (lexems[i].stroka == "(")
			{
				open++;
			}
			else if (lexems[i].stroka == ")")
			{
				close++;
			}

		}
		if (lexems[lexems.size() - 1].stroka == "(")
		{
			open++;
		}
		else if (lexems[lexems.size() - 1].stroka == ")")
		{
			close++;
		}
		if (close != open)
		{
			return false;
		}
		return true;
	}
	void ToPostfix( )//значение по умолчанию
	{
		int size = lexems.size(); // построение постфиксной записи
		Stack<Lexema> stack(size);
		for (int i = 0; i < size; i++)
		{
			if (lexems[i].typeLex == OPERAND || lexems[i].typeLex == VARIABLE)
			{
				postfix.push_back(lexems[i]);
			}
			else
			{
					if(lexems[i].typeLex == BRACKET)
					{
						if (lexems[i].stroka == "(")
						{
							stack.push(lexems[i]);
						}
						else
						{
							while (stack.top().stroka != "(")
							{
								Lexema tmp = stack.pop();
								postfix.push_back(tmp);
							}
							Lexema tmp = stack.pop();
						}
					}
					//case(OPERATION):
					else
					{
						int j = 0;
						int size_stack = stack.stack_real_size();
						int next_lexema_priority = 0;
						int lexema_priority = 0;
						auto it = priority.find(lexems[i].stroka);
						if (it != priority.end())
						{
							lexema_priority = it->second;
						}
						if (stack.emptiness_сheck())
						{
							stack.push(lexems[i]);/// исключение доступа пам€ти
						}
						else
						{
							auto it2 = priority.find(stack.top().stroka);
							if (it2 != priority.end())
							{
								next_lexema_priority = it2->second;
							}
							while (lexema_priority <= next_lexema_priority && size_stack != 0)
							{
								Lexema element = stack.pop();
								postfix.push_back(element);//искл
//								auto it2 = priority.find(stack.top().stroka);
								auto it2 = priority.find(element.stroka);
								next_lexema_priority = it2->second;//искл
								size_stack = stack.stack_real_size();
							}
							stack.push(lexems[i]);
						}
					}

				}
		}
		int stack_size_2 = stack.stack_real_size();
		for (int i = 0; i < stack_size_2 ; i++)
		{
			Lexema tmp = stack.pop();
			postfix.push_back(tmp);
		}
	}
	void Variable(map<char, Polinom>& values) // vmesto double polinom
	{
		for (int i = 0; i < lexems.size(); i++)
		{
			if (lexems[i].typeLex == VARIABLE)
			{
				map<char, Polinom>::iterator pos = values.find(lexems[i].stroka[0]);
				Polinom val;// vmesto double polinom
				if (pos == values.end())
				{
					string tmp;
					cout << "¬ведите значение" << endl << lexems[i].stroka << "=" << endl;
					cin >> tmp; // vmesto double polinom
					Polinom x(tmp);
					val = x;
				}
				else
				{
					val = pos->second;
				}
				operands.insert({ lexems[i].stroka[0], val });
			}
		}

	}
	Polinom Calculate()//
	{
		Stack<Polinom> stack(postfix.size());// vmesto double polinom
		for (int i = 0; i < postfix.size(); i++)
		{
			if (postfix[i].typeLex == OPERATION)
			{
				if (postfix[i].stroka == "+")
				{
					Polinom tmp = stack.pop(); //vmesto double polinom
					Polinom tmp2 = stack.pop();
					stack.push(tmp + tmp2);
				}
				if (postfix[i].stroka == "-")
				{
					Polinom tmp = stack.pop();
					Polinom tmp2 = stack.pop();
					stack.push(tmp2 - tmp);
				}
				if (postfix[i].stroka == "*")
				{
					Polinom tmp = stack.pop();
					Polinom tmp2 = stack.pop();
					stack.push(tmp * tmp2);
				}
				if (postfix[i].stroka == "/")
				{
					Polinom tmp = stack.pop();
					Polinom tmp2 = stack.pop();
					//stack.push(tmp2/tmp);
				}
			}
			else if(postfix[i].typeLex == OPERAND)
			{
				stack.push(Polinom(postfix[i].stroka));
			}
			else if (postfix[i].typeLex == VARIABLE)
			{
				Polinom value;
				auto it = operands.find(postfix[i].stroka[0]);
				if (it != operands.end())
				{
					 value = it->second;
				}
				stack.push(value);
			}
		}
		return stack.top();
	}
	string GetInfix() const 
	{
		return infix;
	}
	vector<Lexema> GetPostfix() const 
	{
		return postfix;
	}
	vector<Lexema> GetLexems() const
	{
		return lexems;
	}
	vector<char> GetOperands() const;
	~TArithmeticExpression()
	{

	}
};