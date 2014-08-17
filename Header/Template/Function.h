#ifndef TEMPLATE_FUNCTION_H
#define TEMPLATE_FUNCTION_H

namespace Template
{
	//һԪ��������
	//��һ������ΪһԪ�����Ĳ���
	//��һ������Ϊ����ֵ
	template <typename X, typename Y>
	class CUnaryFunc
	{
	public:
		virtual Y operator ()(X) const = 0;
		virtual CUnaryFunc* Clone(void) const = 0;
		virtual ~CUnaryFunc(void) {}
	};

	//���ĺ���
	template <typename F, typename G, typename X, typename Y>
	class CCompositionCore : public CUnaryFunc<X, Y>
	{
	public:
		CCompositionCore(F f, G g) :
		  m_f(f),
		  m_g(g)
	  {}

	  Y operator ()(X x) const
	  {
		  return this->m_f(this->m_g(x));
	  }

	  CUnaryFunc<X, Y>* Clone(void) const
	  {
		  return new CCompositionCore(*this);
	  }
	private:
		F m_f;
		G m_g;
	};

	//��Ϻ���
	template <typename X, typename Y>
	class CComposition
	{
	public:
		template <typename F, typename G>
		CComposition(F f, G g) :
			m_pfunc(new CCompositionCore<F, G, X, Y>(f, g))
		{}
		CComposition(const CComposition& comp) :
			m_pfunc(comp.m_pfunc->Clone())
		{}
		CComposition& operator =(const CComposition& comp)
		{
			if (this != &comp)
			{
				delete this->m_pfunc;
				this->m_pfunc = comp.m_pfunc->Clone();
			}
			return *this;
		}
		~CComposition(void) {delete this->m_pfunc;}
		Y operator ()(X x) const
		{
			return (*this->m_pfunc)(x);
		}
	private:
		CUnaryFunc<X, Y>* m_pfunc;
	};

}

#endif