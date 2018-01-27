#ifndef SOLVE_BF_H
#define SOLVE_BF_H
#include<bits/stdc++.h>
#include "main.h"
#include "module.h"
using namespace std;

void build_bf(vector<vector<bitset<bitset_sz> > > slot);
priority_queue<solution> optimal_solution(int size);
vector<string> solve(vector<module> modules, string sem);

#endif
