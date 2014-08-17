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
		//深度优先遍历
		void DFS(void);

	protected:
		//对节点的处理函数
		//第一个参数是要遍历的节点
		virtual void WorkProcess(GraphNode*);

	private:
		//禁止复制和赋值
		CGraph(const CGraph&);
		CGraph& operator =(const CGraph&);

		map<TypeKey, GraphNode*> m_mapGraph;		//图的链接表表示形式<节点标识，邻接点>
		set<pair<unsigned short, unsigned short> > m_setExist;				//已经存在的坐标点
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