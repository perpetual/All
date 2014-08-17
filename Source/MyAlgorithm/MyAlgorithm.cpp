#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "MyAlgorithm/MyAlgorithm.h"
#include "MyTools/MyUtilityTools.h"
#include "MyAlgorithm/Stack.h"

namespace MyAlgorithm
{
	using std::cout;
	using std::endl;
	using std::make_pair;
	using MyAlgorithm::CLinkStack;

	double SquareRoot(double dValue)
	{
		double dLast = 1.0;		//��һ�μ����ֵ
		double dNew = 0.0;
		double dTemp = 0.0;
		bool b = true;

		while (b)
		{
			dNew = (dLast + dValue / dLast) / 2;
			dTemp = dNew - dLast;
			if (dTemp < 0.000001 && dTemp > -0.000001)
			{
				break;
			}
			else
			{
				dLast = dNew;
			}
		}

		return dLast;
	}

	bool Prime(unsigned long long ullValue)
	{
		unsigned long long ullTemp = ullValue / 2;
		bool bRet = true;

		for (unsigned long long ull = 2; ull <= ullTemp; ++ull)
		{
			if (0 == ullValue % ull)
			{
				bRet = false;
			}
		}

		return bRet;
	}

	vector<unsigned int> FindPrime(unsigned int uiEnd, bool bDebug)
	{
		list<unsigned int> listTemp;
		vector<unsigned int> vecRet;

		//��ʼ��һ���б�
		for (unsigned int u = 2; u <= uiEnd; ++u)
		{
			listTemp.push_back(u);
			if (0 == u % 10000)
			{
				system("cls");
				cout << 100 * u / uiEnd << '%' << endl;
			}
		}

		list<unsigned int>::iterator ci;
		list<unsigned int>::iterator itTemp;
		list<unsigned int>::iterator itFirst;
		unsigned int uiCount = 1000;
		unsigned int uiLast = 0;

		//���������б�1֮�����������Ԫ�ض�������������ϵ��
		while (ci = listTemp.begin(), ci != listTemp.end())
		{
			itFirst = ci;
			for (list<unsigned int>::iterator i = ++ci; i != listTemp.end();)
			{
				itTemp = i++;
				if (0 == *itTemp % *itFirst)
				{
					listTemp.erase(itTemp);		//�����һ��Ԫ��֮���ĳ��Ԫ���ܱ���һ��Ԫ����������ɾ����Ԫ��
				}
			}

			if (*itFirst > uiCount)
			{
				uiCount += 1000;
				cout << '(' << vecRet.size() - uiLast << ')' << endl;
				uiLast = vecRet.size();
			}
			vecRet.push_back(*itFirst);
			bDebug ? (cout << *itFirst << ' ', 1) : 0;
			listTemp.erase(itFirst);
		}
		return vecRet;
	}

	unsigned long long Factorial1(char c)
	{
		if (c <= 1)
		{
			return 1;
		}
		else
		{
			return c * Factorial1(c - 1);
		}
	}

	unsigned long long Factorial2(char c)
	{
		unsigned long long ullRet = 1;

		while (c > 1)
		{
			ullRet *= c--;
		}

		return ullRet;
	}

	unsigned long long Fibonacci1(char c)
	{
		if (c <= 2)
		{
			return 1;
		}
		else
		{
			return Fibonacci1(c - 1) + Fibonacci1(c - 2);
		}
	}

	unsigned long long Fibonacci2(unsigned int ui)
	{
		unsigned long long ullRet = 1;
		unsigned long long ullPreVal = 1;
		unsigned long long ullPrePreVal = 1;

		while (ui-- > 2)
		{
			ullRet = ullPreVal + ullPrePreVal;
			ullPrePreVal = ullPreVal;
			ullPreVal = ullRet;
		}

		return ullRet;
	}

	unsigned long long Hermite(unsigned char n, int x)
	{
		if (n <= 0)
		{
			return 1;
		}
		else
		{
			if (1 == n)
			{
				return 2 * x;
			}
			else
			{
				return 2 * x * Hermite(n - 1, x) - 2 * (n - 1) * Hermite(n - 2, x);
			}
		}
	}

	//�ϴ�ĳ��Խ�С�����������϶������������Լ���ı������ϴ���ȡ���϶�����n�����Լ����ʣ��m�����Լ��
	unsigned long long GCD(unsigned long long a, unsigned long long b)
	{
		if (a > 0 && b > 0)
		{
			unsigned long long ull = a % b;		//���a<b����һ�������𵽵���a��bλ�õ�Ч������֤��һ���������ڵڶ�������

			if (0 == ull)
			{
				return b;
			}
			else
			{
				return GCD(b, ull);
			}
		}
		else
		{
			return 0;
		}
	}

	bool Palindrome(const string& str, bool bFlag)
	{
		unsigned int uiFront = 0;
		unsigned int uiRear = str.length() > 0 ? str.length() - 1 : 0;

		while (uiFront < uiRear)
		{
			if (bFlag ? str.at(uiFront++) != str.at(uiRear--) : tolower(str.at(uiFront++)) != tolower(str.at(uiRear--)))
			{
				break;
			}
		}

		return uiFront >= uiRear;
	}

	//m�൱�ڶ�̬�ı�����飬��Ϊ������ֵΪ���ݣ�����Ϊ1~r
	//ʵ��ȡֵ����nΪ������ֵ��rΪ��Ӧ�������������
	void Comb(unsigned int n, unsigned int r, map<unsigned int, unsigned int>& m, vector<string>& vecResult)
	{
		for (unsigned int ui = n; ui >= r; --ui)
		{
			m[r] = ui;
			if (r > 1)
			{
				Comb(ui - 1, r - 1, m, vecResult);
			}
			else
			{
				string str;
				for (int j = m[0]; j > 0; --j)
				{
					str += MyTools::NumberToDecString(m[j]);
				}
				vecResult.push_back(str);
			}
		}
	}

	vector<string> Comb(unsigned int n, unsigned int r)
	{
		vector<string> vec;
		if (r <= n && 0 != r)
		{
			map<unsigned int, unsigned int> m;
			m[0] = r;
			Comb(n, r, m, vec);
		}
		return vec;
	}

	static double Operation(char chOperator, double d1, double d2)
	{
		double dRet = 0;

		switch (chOperator)
		{
		case '+':
			dRet = d1 + d2;
			break;
		case '-':
			dRet = d1 - d2;
			break;
		case '*':
			dRet = d1 * d2;
			break;
		default:
			dRet = d1 / d2;
			break;
		}
		return dRet;
	}

	double RBN(const string& str)
	{
		CLinkStack<char> stkOperators;		//������ջ
		CLinkStack<double> stkOperands;	//������ջ

		for (string::size_type i = 0; i < str.length(); ++i)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				stkOperands.Push(str[i] - '0');
			} else if (')' == str[i] || str.length() == i)
			{
				double d2 = stkOperands.Top();
				stkOperands.Pop();
				double d1 = stkOperands.Top();
				stkOperands.Pop();
				char chOperator = stkOperators.Top();
				stkOperators.Pop();
				stkOperands.Push(Operation(chOperator, d1, d2));		//���м��������ջ
			} 
			else if (' ' != str[i] && '\t' != str[i] && '(' != str[i])
			{
				if (!stkOperators.IsEmpty() && ('*' == stkOperators.Top() || '/' == stkOperators.Top()))
				{
					double d2 = stkOperands.Top();
					stkOperands.Pop();
					double d1 = stkOperands.Top();
					stkOperands.Pop();
					char chOperator = stkOperators.Top();
					stkOperators.Pop();
					stkOperands.Push(Operation(chOperator, d1, d2));		//���м��������ջ
				}
				stkOperators.Push(str[i]);
			}
		}

		while (!stkOperators.IsEmpty())
		{
			double d2 = stkOperands.Top();
			stkOperands.Pop();
			double d1 = stkOperands.Top();
			stkOperands.Pop();
			char chOperator = stkOperators.Top();
			stkOperators.Pop();
			stkOperands.Push(Operation(chOperator, d1, d2));		//���м��������ջ
		}
		return stkOperands.Top();
	}

	string Conversion(unsigned int ui, unsigned char ucRadix)
	{
		CLinkStack<char> stk;
		string str;

		if (0 == ui)
		{
			str = "0";
		}
		else
		{
			while (ui > 0)
			{
				stk.Push('0' + ui % ucRadix);
				ui /= ucRadix;
			}

			while (!stk.IsEmpty())
			{
				str += stk.Pop();
			}
		}

		return str;
	}

	bool BracketMatch(const string& str)
	{
		CLinkStack<char> stk;

		for (string::const_iterator cit = str.begin(); cit != str.end(); ++cit)
		{
			switch (*cit)
			{
			case '(':
			case '[':
			case '{':
				stk.Push(*cit);
				break;
			case ')':
				if (stk.IsEmpty() || '(' != stk.Pop())
				{
					return false;
				}
				break;
			case ']':
				if (stk.IsEmpty() || '[' != stk.Pop())
				{
					return false;
				}
				break;
			case '}':
				if (stk.IsEmpty() || '{' != stk.Pop())
				{
					return false;
				}
				break;
			default:
				break;
			}
		}
		return stk.IsEmpty();
	}

	static pair<int, int> NextPos(vector<vector<int> >& vecvec, const pair<int, int>& prPos)
	{
		pair<int, int> prTemp(prPos);

		if (0 == vecvec[prPos.first][prPos.second])
		{
			prTemp.second -= 1;
		}else if (-1 == vecvec[prPos.first][prPos.second])
		{
			prTemp.first += 1;
		}else if (-2 == vecvec[prPos.first][prPos.second])
		{
			prTemp.second += 1;
		}else if (-3 == vecvec[prPos.first][prPos.second])
		{
			prTemp.first -= 1;
		}
		else
		{
			prTemp.first = 0;
			prTemp.second = 0;
		}

		--vecvec[prPos.first][prPos.second];
		return prTemp;
	}

	bool MazePath(const vector<vector<int> >& vecvecMaze, const pair<int, int>& prStart, const pair<int, int>& prEnd)
	{
		vector<vector<int> > vecvec(vecvecMaze);
		CLinkStack<pair<int, int> > stk;
		pair<int, int> prCurPos = prStart;

		do 
		{
			int iStatus = vecvec[prCurPos.first][prCurPos.second];
			if (0 == iStatus)		//�������ͨ��
			{
				--vecvec[prCurPos.first][prCurPos.second];
				stk.Push(prCurPos);
				if (prCurPos == prEnd)
				{
					while (!stk.IsEmpty())
					{
						pair<int, int> pr = stk.Pop();
						cout << pr.first << ' ' << pr.second << endl;
					}
					return true;
				}
				else
				{
					prCurPos = NextPos(vecvec, prCurPos);
				}
			}
			else
			{
				if (!stk.IsEmpty())
				{
					pair<int, int> prTemp = stk.Pop();

					while (vecvec[prTemp.first][prTemp.second] <= -4 && !stk.IsEmpty())
					{
						prTemp = stk.Pop();
					}

					if (vecvec[prTemp.first][prTemp.second] > -4 && vecvec[prTemp.first][prTemp.second] <= 0)		//���ܱߵĵ㻹û�б�����
					{
						stk.Push(prTemp);
						prCurPos = NextPos(vecvec, prTemp);
					}
				}
			}
		} while (!stk.IsEmpty());
		return false;
	}
	
	bool MazePath(void)
	{
		int a[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
			{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
			{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};

		vector<vector<int> > vecvec;

		for (int i = 0; i < 10; ++i)
		{
			vecvec.push_back(vector<int>());
			for (int j = 0; j < 10; ++j)
			{
				vecvec[i].push_back(a[i][j]);
			}
			MyTools::PrintContainer(vecvec[i]);
		}
		return MazePath(vecvec, make_pair(1, 1), make_pair(8, 8));
	}

	static void Hanoi(size_t szNum, char cha, char chb, char chc, vector<string>& vec)
	{
		if (1 == szNum)
		{
			vec.push_back(string(1, cha) + "->" + chc);
		}
		else
		{
			Hanoi(szNum - 1, cha, chc, chb, vec);
			vec.push_back(string(1, cha) + "->" + chc);
			Hanoi(szNum - 1, chb, cha, chc, vec);
		}
	}

	vector<string> Hanoi(size_t szNum)
	{
		vector<string> vec;
		Hanoi(szNum, 'a', 'b', 'c', vec);
		return vec;
	}
}