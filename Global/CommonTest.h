#ifndef COMMON_TEST_H
#define COMMON_TEST_H

#include "VersionControl.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <iomanip>
#include <exception>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <complex>
#include <cstdio>
#include <cstdlib> 
#include "MyTools/MyUtilityTools.h"
#include "Random/Random.h"

using std::cin;
using std::cout;
using std::wcout;
using std::cerr;
using std::wcout;
using std::endl;
using std::ends;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::make_pair;
using std::exception;

#ifdef __OS_VERSION_WINDOWS__
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "IPHlpApi.lib")
#pragma comment (lib, "MyTools.lib")
#endif

#endif