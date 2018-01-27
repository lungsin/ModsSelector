#ifndef MAIN_H
#define MAIN_H
#include <bits/stdc++.h>
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

  int max_consecutive() const {
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

  bool operator < (solution rhs) const{
    return max_consecutive() < rhs.max_consecutive();
  }

  void print() const {
    for (int day = 0; day < 5; day++) {
      for (int hour = 8; hour < 22; hour++) {
        if (bm[day*20 + hour - 8]) {
          cout << mod[day*20 + hour - 8];
        } else cout << '-';
      }
      cout << '\n';
    }
  }

};


#endif
