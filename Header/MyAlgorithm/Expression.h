#ifndef MYALGORITHM_EXPRESSION_H
#define MYALGORITHM_EXPRESSION_H

#include "VersionControl.h"
#include <iostream>
#include <string>
#include "MyTools/MyUtilityTools.h"

namespace MyAlgorithm
{
	using std::ostream;
	using std::string;
	using Utility::exceptionx;
	using MyTools::Trim;

	class CExpression;
	//节点抽象基类
	class CExpressionNode
	{
		friend class CExpression;
		friend ostream& operator <<(ostream&, const CExpression&);
		friend ostream& operator <<(ostream& o, const CExpressionNode& e)
		{
			e.Print(o);
			return o;
		}

		int m_iCount;		//引用计数器

	protected:
		CExpressionNode(void) : m_iCount(1) {}
		virtual void Print(ostream&) const = 0;
		virtual double Eval(void) const = 0;
		virtual ~CExpressionNode(void) {};
	};

	//值节点
	template <typename T>
	class CValueNode : public CExpressionNode
	{
		friend class CExpression;
		CValueNode(T t) : m_t(t) {}
		void Print(ostream& o) const {o << this->m_t;}
		double Eval(void) const {return this->m_t;}

		T m_t;
	};

	class CExpression
	{
		friend ostream& operator <<(ostream&, const CExpression&);

	public:
		//创建一个值类型的节点
		template<typename T>
		CExpression(T t) : m_pNode(new CValueNode<T>(t)) {}

		CExpression(const CExpression&);
		CExpression& operator =(const CExpression&);
		~CExpression(void);

		//创建一个一元操作符节点
		CExpression(const string&, CExpression);
		//创建一个二元操作符节点
		CExpression(const string&, CExpression, CExpression);
		//创建一个三元操作符节点
		CExpression(const string&, CExpression, CExpression, CExpression);

		//计算表达式的值
		double Eval(void) const;

	private:
		CExpressionNode* m_pNode;
	};

	//一元操作符节点
	class CUnaryNode : public CExpressionNode
	{
		friend class CExpression;

		CUnaryNode(const string& strOperator, CExpression expr) : m_strOperator(strOperator), m_expr(expr) {}
		void Print(ostream& o) const {o << "(" << this->m_strOperator << this->m_expr << ")";}
		double Eval(void) const
		{
			if ("-" == Trim(this->m_strOperator))
			{
				return -this->m_expr.Eval();
			}else if ("+" == Trim(this->m_strOperator))
			{
				return this->m_expr.Eval();
			}
			else
			{
				throw exceptionx("错误的操作符（数）");
			}
		}

		string m_strOperator;
		CExpression m_expr;
	};

	//二元操作符节点
	class CBinaryNode : public CExpressionNode
	{
		friend class CExpression;

		CBinaryNode(const string& strOperator, CExpression expr1, CExpression expr2) : m_strOperator(strOperator), m_expr1(expr1), m_expr2(expr2) {}
		void Print(ostream& o) const {o << "(" << this->m_expr1 << this->m_strOperator << this->m_expr2 << ")";}
		double Eval(void) const
		{
			if ("+" == Trim(this->m_strOperator))
			{
				return this->m_expr1.Eval() + this->m_expr2.Eval();
			}else if ("-" == Trim(this->m_strOperator))
			{
				return this->m_expr1.Eval() - this->m_expr2.Eval();
			}else if ("*" == Trim(this->m_strOperator))
			{
				return this->m_expr1.Eval() * this->m_expr2.Eval();
			}else if ("/" == this->m_strOperator && 0 != this->m_expr2.Eval())
			{
				return this->m_expr1.Eval() / this->m_expr2.Eval();
			}
			else
			{
				throw exceptionx("非法的操作符（数）");
			}
		}

		string m_strOperator;
		CExpression m_expr1;
		CExpression m_expr2;
	};

	//三元操作符节点
	class CTernaryNode : public CExpressionNode
	{
		friend class CExpression;

		string m_strOperator;
		CExpression m_expr1;
		CExpression m_expr2;
		CExpression m_expr3;

		CTernaryNode(const string& strOperator, const CExpression& expr1, const CExpression& expr2, const CExpression& expr3) : m_strOperator(strOperator), m_expr1(expr1), m_expr2(expr2), m_expr3(expr3) {}
		void Print(ostream& o) const {o << "(" << this->m_expr1 << " ? " << this->m_expr2 << " : " << this->m_expr3 << ")";}
		double Eval(void) const {return 0 != this->m_expr1.Eval() ? this->m_expr2.Eval() : this->m_expr3.Eval();}
	};

	ostream& operator <<(ostream& o, const CExpression& e);
}

#endif