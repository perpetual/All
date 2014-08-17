#ifndef MYALGORITHM_MY_ALGORITHM_H
#define MYALGORITHM_MY_ALGORITHM_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>

namespace MyAlgorithm
{
	using std::list;
	using std::vector;
	using std::string;
	using std::map;
	using std::pair;

	//开平方
	double SquareRoot(double);

	//质数
	bool Prime(unsigned long long);

	//寻找从2到值内的所有素数
	//第二个参数表示是否显示调试信息
	vector<unsigned int> FindPrime(unsigned int, bool = true);

	//递归阶乘
	unsigned long long Factorial1(char);
	//迭代阶乘
	unsigned long long Factorial2(char);

	//递归斐波那契数
	unsigned long long Fibonacci1(char);
	//迭代斐波那契数
	unsigned long long Fibonacci2(unsigned int);

	//厄密多项式
	//第一个参数是项数
	//第二个参数是参数值
	unsigned long long Hermite(unsigned char, int);

	//最大公约数
	unsigned long long GCD(unsigned long long, unsigned long long);

	//判断是否是回文
	//第一个参数是待判断的字符串
	//第二个参数表示是否区分大小写
	bool Palindrome(const string&, bool = false);

	//打印组合数
	vector<string> Comb(unsigned int, unsigned int);

	//逆波兰表达式（表达式求值）
	double RBN(const string&);

	//数制转换
	string Conversion(unsigned int, unsigned char);

	//括号匹配
	bool BracketMatch(const string&);

	//迷宫
	//第一个参数是迷宫矩阵（1代表不可走，0代表可走）
	//下一个参数表示起始点
	//下一个参数表示结束点
	bool MazePath(const vector<vector<int> >&, const pair<int, int>&, const pair<int, int>&);
	bool MazePath(void);

	//汉诺塔
	vector<string> Hanoi(size_t);
}

#endif