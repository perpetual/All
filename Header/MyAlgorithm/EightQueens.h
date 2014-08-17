#ifndef MYALGORITHM_EIGHT_QUEENS_H
#define MYALGORITHM_EIGHT_QUEENS_H

#include <map>

namespace MyAlgorithm
{
	using std::map;

	class CEightQueens
	{
	public:
		CEightQueens(unsigned short usDimension = 8);
	private:
		//��ֹ���ƺ͸�ֵ
		CEightQueens(const CEightQueens&);
		CEightQueens& operator =(const CEightQueens&);

		bool Attack(unsigned short);									//�ж�ĳ�еĻʺ��Ƿ��ܹ�������֮ǰ���еĻʺ�
		void Display(void);												//��ʾ����
		void PutChess(unsigned short usRow);					//��ĳ�з�������
		map<unsigned short, unsigned short> m_mapQueens;		//���ڻʺ��λ��<�У���>
		const unsigned short m_usDimension;						//ά��
		unsigned int m_uiCount;										//������
	};
}

#endif