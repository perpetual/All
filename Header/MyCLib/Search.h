#ifndef MYALGORITHM_SEARCH_H
#define MYALGORITHM_SEARCH_H


//模式匹配KMP
//第一个参数是主串
//下一个参数是模式串
//下一个参数是主串中的字符位置
//返回值是模式串在子串中第一次出现的位置
int KMP(const char*, const char*, int);

#endif