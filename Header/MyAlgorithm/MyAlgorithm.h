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

	//��ƽ��
	double SquareRoot(double);

	//����
	bool Prime(unsigned long long);

	//Ѱ�Ҵ�2��ֵ�ڵ���������
	//�ڶ���������ʾ�Ƿ���ʾ������Ϣ
	vector<unsigned int> FindPrime(unsigned int, bool = true);

	//�ݹ�׳�
	unsigned long long Factorial1(char);
	//�����׳�
	unsigned long long Factorial2(char);

	//�ݹ�쳲�������
	unsigned long long Fibonacci1(char);
	//����쳲�������
	unsigned long long Fibonacci2(unsigned int);

	//���ܶ���ʽ
	//��һ������������
	//�ڶ��������ǲ���ֵ
	unsigned long long Hermite(unsigned char, int);

	//���Լ��
	unsigned long long GCD(unsigned long long, unsigned long long);

	//�ж��Ƿ��ǻ���
	//��һ�������Ǵ��жϵ��ַ���
	//�ڶ���������ʾ�Ƿ����ִ�Сд
	bool Palindrome(const string&, bool = false);

	//��ӡ�����
	vector<string> Comb(unsigned int, unsigned int);

	//�沨�����ʽ�����ʽ��ֵ��
	double RBN(const string&);

	//����ת��
	string Conversion(unsigned int, unsigned char);

	//����ƥ��
	bool BracketMatch(const string&);

	//�Թ�
	//��һ���������Թ�����1�������ߣ�0������ߣ�
	//��һ��������ʾ��ʼ��
	//��һ��������ʾ������
	bool MazePath(const vector<vector<int> >&, const pair<int, int>&, const pair<int, int>&);
	bool MazePath(void);

	//��ŵ��
	vector<string> Hanoi(size_t);
}

#endif