#ifndef MYCLIB_MY_STRING_H
#define MYCLIB_MY_STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

//查找第二个字符串在第一个字符串中最后出现的位置
char* MyStrRStr(char*, const char*);

//查找第二个字符在第一个字符串中出现的位置
//返回NULL表示不存在
char* MyStrRChr(char*, const char);

//获取字符串的长度
//第一个参数的指向目标缓冲区的指针
//下一个参数是缓冲区的大小
size_t MyStrLen(const char*, size_t siz);

//拷贝字符串
char* MyStrCpy(char*, const char*, size_t);

//连接字符串
//第一个参数是目的缓冲区指针
//下一个参数是源缓冲区
//下一个是目的缓冲区的长度
char* MyStrNCat(char*, const char*, size_t);

//类似strcpy并返回一个指向目标字符串末尾的指针
//第一个参数是目标缓冲区首址
//下一个参数是源缓冲区首址
char* MyStrCpyEnd(char*, const char*);

//类似strchr函数
//第一个参数是源字符串
//下一个参数是需要超找的字符
//下一个参数是需要查找第几个出现的字符
char* MyStrNChr(char *, int, int);

//在第一个参数中进行查找，并返回匹配第二个参数所包含的字符的数量
int CountChr(const char*, const char*);

//反转字符串
char* ReverseStr(char*);

#ifdef __cplusplus
}
#endif

#endif