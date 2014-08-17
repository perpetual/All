#ifndef CLIB_C_LIB_H
#define CLIB_C_LIB_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

//可移植的atol函数
long AToL(char *);

//可移植的ltoa函数
char* LToA(long, char*);

//可变参数
void VariableArg(int, ...);
int MyPrintf(const char*, ...);

//组合数
void Comb(int, int);

#ifdef __cplusplus
}
#endif

#endif