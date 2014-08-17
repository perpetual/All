#ifndef CLIB_C_LIB_H
#define CLIB_C_LIB_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

//����ֲ��atol����
long AToL(char *);

//����ֲ��ltoa����
char* LToA(long, char*);

//�ɱ����
void VariableArg(int, ...);
int MyPrintf(const char*, ...);

//�����
void Comb(int, int);

#ifdef __cplusplus
}
#endif

#endif