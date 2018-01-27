#ifndef MAIN_H
#define MAIN_H
#include <bits/stdc++.h>
using namespace std;

const int bitset_sz = 70*13;

struct solution {
  bitset<bitset_sz> bm;
  vector<pair<int, int> > mod;

  solution() {
    mod = vector<pair<int,int> >(bitset_sz);
  }

  solution(bitset<bitset_sz> bm, vector<pair<int,int> > mod):bm(bm),mod(mod){}

  void merge(bitset<bitset_sz> bm2, int mod_no, int class_no) {
    for (int i = 0; i < bitset_sz; i++) {
      if (bm2[i]) {
        mod[i] = {mod_no, class_no};
        bm[i] = 1;
      }
    } 
  }

  int calc() const {
    int res = 0;
    for (int week = 0; week < 13; week++) {
      for (int day = 0; day < 5; day++) {
        int cur = 0, cur2 = 0;
        for (int hour = 0; hour < 14; hour++) {
          int val_id = week*14*5 + day*14 + hour;
          cur += bm[val_id];
          if (hour && bm[val_id] && bm[val_id-1] && mod[val_id] != mod[val_id-1]) cur2++;
        }
        res += cur*cur + cur2*3;
      }
    }
    return res;
  }

  bool operator < (solution rhs) const{
    return calc() < rhs.calc();
  }
};
#endif
