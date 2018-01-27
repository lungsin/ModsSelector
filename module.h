#ifndef MODULE_H
#define MODULE_H
#include <bits/stdc++.h>
using namespace std;

struct timegroup{
    string code;
    bitset<120> bm;
};

struct module {
    string code;
    vector<timegroup> tg;
};


#endif
