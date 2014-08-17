#ifndef MYALGORITHM_GRAPH_H
#define MYALGORITHM_GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <utility>

namespace MyAlgorithm
{
	using std::cout;
	using std::endl;
	using std::map;
	using std::set;
	using std::pair;
	using std::make_pair;

	template <typename TypeKey, typename TypeValue>
	class CGraph
	{
	public:
		struct GraphNode
		{
			GraphNode(void) :
			tValue(NULL),
			bVisit(false),
			pNext(NULL)
		{}
		TypeValue tValue;
		bool bVisit;
		GraphNode* pNext;
		};
		CGraph(const map<TypeKey, GraphNode*>&);
		//������ȱ���
		void DFS(void);

	protected:
		//�Խڵ�Ĵ�����
		//��һ��������Ҫ�����Ľڵ�
		virtual void WorkProcess(GraphNode*);

	private:
		//��ֹ���ƺ͸�ֵ
		CGraph(const CGraph&);
		CGraph& operator =(const CGraph&);

		map<TypeKey, GraphNode*> m_mapGraph;		//ͼ�����ӱ��ʾ��ʽ<�ڵ��ʶ���ڽӵ�>
		set<pair<unsigned short, unsigned short> > m_setExist;				//�Ѿ����ڵ������
	};

	template <typename TypeKey, typename TypeValue>
	CGraph<TypeKey, TypeValue>::CGraph(const map<TypeKey, GraphNode*>& mapGraph) :
		m_mapGraph(mapGraph)
	{}

	template <typename TypeKey, typename TypeValue>
	void CGraph<TypeKey, TypeValue>::WorkProcess(GraphNode* pCurNode)
	{
		cout << pCurNode->tValue << endl;
	}
}

#endif