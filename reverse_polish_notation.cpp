#include <string>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <stack>
#include <cmath>

using namespace std;

int getPrior(char symb)
{
	switch (symb)
	{
	case '(':
		return 0;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	case '^':
		return 4;
	default:
		return -1;
	}
}

string calc(string a, string b, string oper)
{
	double res = 0;
	if (oper == "+") { res = stod(a) + stod(b); }
	if (oper == "-") { res = stod(a) - stod(b); }
	if (oper == "*") { res = stod(a) * stod(b); }
	if (oper == "/") { res = stod(a) / stod(b); }
	if (oper == "^") { res = pow(stod(a), stod(b)); }
	return to_string(res);
}

bool isOperation(string symb)
{
	if (symb == "+" || symb == "-" || symb == "*" || symb == "/" || symb == "^")  { return true; }
	return false;
}

string revPolishNotation(string expr)
{
	string res;
	stack<char> signs;
	for (char a : expr)
	{
		if (isdigit(a) || a == '.')
		{
			res += a;
		}
		else
		{
			if (a == '(')
			{
				signs.push(a);
			}
			else if (signs.empty())
			{
				signs.push(a);
				res += ' ';
			}
			else if (a == ')')
			{
				while (signs.top() != '(')
				{
					res += ' ';
					res += signs.top();
					signs.pop();
				}
				signs.pop();
			}
			else if (getPrior(signs.top()) >= getPrior(a))
			{
				while (!signs.empty() && getPrior(signs.top()) >= getPrior(a))
				{
					res += ' ';
					res += signs.top();
					signs.pop();
				}
				res += ' ';
				signs.push(a);
			}
			else
			{
				res += ' ';
				signs.push(a);
			}

		}

	}
	int range = signs.size();
	for (int i = 0; i < range; ++i)
	{
		res += ' ';
		res += signs.top();
		signs.pop();
	}
	return res;
}

string* splitNotation(string notation)
{
	int size = 0;
	for (char a : notation)
	{
		if (a == ' ') { ++size; }
	}
	string* splitedNot = new string[size + 2];
	int i = 0;
	for (char ch : notation)
	{
		if (ch == ' ') { ++i; }
		else { splitedNot[i] += ch; }
	}
	splitedNot[size + 1] = "end";
	return splitedNot;
}

void check(string str)
{
	bool isPrevDig = true;
	int parenthCounter = 0;
	for (char& ch : str)
	{
		if (isdigit(ch))
		{
			isPrevDig = true;
		}
		else if (ch == 40) { ++parenthCounter; }
		else if (ch == 41) { --parenthCounter; }
		else if ((ch >= 42 && ch <= 43) || (ch >= 45 && ch <= 47) || ch == 94)
		{
			if (!isPrevDig)
			{
				cerr << "ERROR : Multiple operators" << endl;
				exit(1);
			}
			isPrevDig = false;
		}
		else
		{
			cerr << "ERROR : Invalid character: " << ch << endl;
			exit(1);
		}
	}
	if (parenthCounter != 0)
	{
		cerr << "ERROR : Parentheses disbalance" << endl;
		exit(1);
	}
}

int main()
{
	string expr;
	cout << "Input expression: ";
	cin >> expr;
	check(expr);
	string revPolishExpr = revPolishNotation(expr);
	string* spA = splitNotation(revPolishExpr);
	string* navPtr = spA;


	stack<string> nums;
	while (*navPtr != "end")
	{
		if (!isOperation(*navPtr)) { nums.push(*navPtr); }
		else
		{
			string b = nums.top();
			nums.pop();
			string a = nums.top();
			nums.pop();
			string res = calc(a, b, *navPtr);
			nums.push(res);
		}
		++navPtr;
	}
	cout << "Answer: " << nums.top() << endl;
	delete[] spA;
	return 0;
}
