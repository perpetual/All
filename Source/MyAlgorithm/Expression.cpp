#include <cstdlib>
#include "MyAlgorithm/Expression.h"

namespace MyAlgorithm
{
	CExpression::CExpression(const CExpression& expr)
	{
		this->m_pNode = expr.m_pNode;
		++this->m_pNode->m_iCount;
	}

	CExpression& CExpression::operator =(const CExpression& expr)
	{
		++expr.m_pNode->m_iCount;
		0 == --this->m_pNode->m_iCount ? delete this->m_pNode, NULL : NULL;
		this->m_pNode = expr.m_pNode;
		return *this;
	}

	CExpression::~CExpression(void)
	{
		0 == --this->m_pNode->m_iCount ? delete this->m_pNode, NULL : NULL;
	}

	ostream& operator <<(ostream& o, const CExpression& e)
	{
		e.m_pNode->Print(o);
		return o;
	}

	CExpression::CExpression(const string& strOperator, CExpression expr) : m_pNode(new CUnaryNode(strOperator, expr)) {}

	CExpression::CExpression(const string& strOperator, CExpression expr1, CExpression expr2) : m_pNode(new CBinaryNode(strOperator, expr1, expr2)) {}

	CExpression::CExpression(const string& strOperator, CExpression expr1, CExpression expr2, CExpression expr3) : m_pNode(new CTernaryNode(strOperator, expr1, expr2, expr3)) {}

	double CExpression::Eval() const
	{
		return this->m_pNode->Eval();
	}
}