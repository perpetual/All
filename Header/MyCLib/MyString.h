#ifndef MYCLIB_MY_STRING_H
#define MYCLIB_MY_STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

//���ҵڶ����ַ����ڵ�һ���ַ����������ֵ�λ��
char* MyStrRStr(char*, const char*);

//���ҵڶ����ַ��ڵ�һ���ַ����г��ֵ�λ��
//����NULL��ʾ������
char* MyStrRChr(char*, const char);

//��ȡ�ַ����ĳ���
//��һ��������ָ��Ŀ�껺������ָ��
//��һ�������ǻ������Ĵ�С
size_t MyStrLen(const char*, size_t siz);

//�����ַ���
char* MyStrCpy(char*, const char*, size_t);

//�����ַ���
//��һ��������Ŀ�Ļ�����ָ��
//��һ��������Դ������
//��һ����Ŀ�Ļ������ĳ���
char* MyStrNCat(char*, const char*, size_t);

//����strcpy������һ��ָ��Ŀ���ַ���ĩβ��ָ��
//��һ��������Ŀ�껺������ַ
//��һ��������Դ��������ַ
char* MyStrCpyEnd(char*, const char*);

//����strchr����
//��һ��������Դ�ַ���
//��һ����������Ҫ���ҵ��ַ�
//��һ����������Ҫ���ҵڼ������ֵ��ַ�
char* MyStrNChr(char *, int, int);

//�ڵ�һ�������н��в��ң�������ƥ��ڶ����������������ַ�������
int CountChr(const char*, const char*);

//��ת�ַ���
char* ReverseStr(char*);

#ifdef __cplusplus
}
#endif

#endif