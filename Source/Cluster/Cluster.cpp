#include "Cluster/Cluster.h"

namespace Cluster
{
	CCluster* CCluster::pC = NULL;

	CCluster::CClusterItem::CClusterItem(void)
	{
		pC->m_list.push_back(this);
	}

	void* CCluster::CClusterItem::operator new(size_t sz, CCluster& c)
	{
		pC = &c;
		return ::operator new(sz);
	}

	void* CCluster::CClusterItem::operator new(size_t) {abort(); return NULL;}

	void CCluster::CClusterItem::operator delete(void* p, CCluster&)
	{
		//void* pp = &c;
		::operator delete(p);
	}

	void CCluster::CClusterItem::operator delete(void*)
	{
		cout << endl;
		return;
	}


	CCluster::~CCluster(void)
	{
		for (list<CCluster::CClusterItem*>::iterator it = this->m_list.begin(); it != this->m_list.end(); ++it)
		{
			delete *it;
		}
	}

	ostream& operator <<(ostream& o, const CCluster::CClusterItem&)
	{
		return o;
	}
}