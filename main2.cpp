#include <bits/stdc++.h>
#include "solve_bf.h"
using namespace std;

bitset<120> input_session() {
  int day, hour;
  cin >> day >> hour;
  bitset<120> res;
  res[day * 24 + hour] = 1;
  return res;
}

bitset<120> input_choices() {
  bitset<120> res;
  int x;
  cin >> x;
  for (int i = 0; i < x; i++) {
    res |= input_session();
  }
  return res;
}

vector<bitset<120>> input_mod() {
  vector<bitset<120>> res;
  int x;
  cin >> x;
  for (int i = 0; i < x; i++) {
    res.push_back(input_choices());
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  vector<vector<bitset<120>>> res;
  for (int i = 0; i < n; i++) {
    res.push_back(input_mod());
  }
  build_bf(res);
  auto pq = optimal_solution(10);
  while (!pq.empty()) {
    pq.top().print();
    printf("\n");
    pq.pop();
  }
  return 0;
}
