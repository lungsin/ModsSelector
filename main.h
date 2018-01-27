#ifndef MAIN_H
#define MAIN_H
#include <bits/stdc++.h>
using namespace std;

struct solution {
  bitset<120> bm;
  vector<int> mod;

  solution() {
    mod = vector<int>(120);
  }

  solution(bitset<120> bm, vector<int> mod):bm(bm),mod(mod){}

  void merge(bitset<120> bm2, int mod_no) {
    for (int i = 0; i < 120; i++) {
      if (bm2[i]) {
        mod[i] = mod_no;
        bm[i] = 1;
      }
    }
  }

  int max_consecutive() const {
    int res = 0;
    int last = -1;
    for (int i = 0; i < 120; i++) {
      if (bm[i]) {
        res = max(res, i - last);
      } else {
        last = i;
      }
    }
    return res;
  }

  int max_in_a_day() const {
    int res = 0;
    for (int day = 0; day < 4; day++) {
      int cur = 0;
      for (int hour = 0; hour < 24; hour++) {
        if (bm[day*24 + hour]) cur++;
      }
      res = max(res, cur);
    }
    return res;
  }

  int min_in_a_day() const {
    int res = 1000;
    for (int day = 0; day < 4; day++) {
      int cur = 0;
      for (int hour = 0; hour < 24; hour++) {
        if (bm[day*24 + hour]) cur++;
      }
      res = min(res, cur);
    }
    return res;
  }

  bool operator < (solution rhs) const{
    if (max_consecutive() != rhs.max_consecutive())
      return max_consecutive() < rhs.max_consecutive();
    if (max_in_a_day() != rhs.max_in_a_day())
      return max_in_a_day() < rhs.max_in_a_day();
    return min_in_a_day() > rhs.min_in_a_day();
  }

  void print() const {
    for (int day = 0; day < 5; day++) {
      for (int hour = 0; hour < 24; hour++) {
        if (bm[day*24 + hour]) {
          cout << mod[day*24 + hour];
        } else cout << '-';
      }
      cout << '\n';
    }
  }

};


#endif
