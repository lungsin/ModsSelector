#include <bits/stdc++.h>
#include "solve_bf.h"
using namespace std;

struct solution {
  bitset<100> bm;
  vector<int> mod;

  solution() {
    mod = vector<int>(100);
  }

  solution(bitset<100> bm, vector<int> mod):bm(bm),mod(mod){}

  void merge(bitset<100> bm2, int mod_no) {
    for (int i = 0; i < 100; i++) {
      if (bm2[i]) {
        mod[i] = mod_no;
        bm[i] = 1;
      }
    }
  }

  int max_consecutive() {
    int res = 0;
    int last = -1;
    for (int i = 0; i < 100; i++) {
      if (bm[i]) {
        res = max(res, i - last);
      } else {
        last = i;
      }
    }
    return res;
  }

  bool operator < (solution &rhs) const{
    return max_consecutive() < rhs.max_consecutive();
  }

};

bitset<100> input_session() {
  int day, hour;
  cin >> day >> hour;
  bitset<100> res;
  res[day * 20 + hour] = 1;
  return res;
}

bitset<100> input_choices() {
  bitset<100> res;
  int x;
  cin >> x;
  for (int i = 0; i < x; i++) {
    res |= input_session();
  }
  return res;
}

vector<bitset<100>> input_mod() {
  vector<bitset<100>> res;
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
  vector<vector<bitset<100>>> res;
  for (int i = 0; i < n; i++) {
    res.push_back(input_mod());
  }
  build_bf(res);
  return 0;
}
