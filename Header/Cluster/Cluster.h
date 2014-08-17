#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <iostream>
#include <list>
#include "MyAlgorithm/List.h"
#include "MyAlgorithm/Nodes.h"

namespace Cluster
{
	using MyAlgorithm::CSLList;
	using MyAlgorithm::CNode;
	using MyAlgorithm::CSLLNode;
	using std::ostream;
	using std::list;

	class CCluster
	{
		friend class CClusterItem;
	public:
		static CCluster* pC;
		class CClusterItem
		{
		public:
			friend class CCluster;
			friend ostream& operator <<(ostream&, const CCluster::CClusterItem&);
			CClusterItem(void);
			void* operator new(size_t, CCluster&);
			void* operator new (size_t);
			void operator delete(void*, CCluster&);
			void operator delete(void*);
		};
		CCluster(void) {}
		~CCluster(void);
		CCluster(const CCluster&);
		CCluster& operator =(const CCluster&);
	private:
		list<CClusterItem*> m_list;
	};

	ostream& operator <<(ostream&, const CCluster::CClusterItem&);
}

#endif