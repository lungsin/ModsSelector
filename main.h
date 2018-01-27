#ifndef MAIN_H
#define MAIN_H
#include <bits/stdc++.h>
using namespace std;

const int bitset_sz = 120*14;

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
    for (int week = 1; week <= 13; week++) {
      for (int day = 0; day < 5; day++) {
        int cur = 0, cur2 = 0;
        for (int hour = 0; hour < 24; hour++) {
          cur += bm[week*24*5 + day*24 + hour];
          if (hour && bm[week*24*5 + day*24 + hour] && bm[week*24*5 + day*24 + hour-1] && mod[week*24*5 + day*24+hour] != mod[week*24*5 + day*24+hour-1]) cur2++;
        }
        res += cur*cur + cur2*2;
      }
    }
    return res;
  }

  bool operator < (solution rhs) const{
    return calc() < rhs.calc();
  }

  // void print() const {
  //   for (int day = 0; day < 5; day++) {
  //     for (int hour = 0; hour < 24; hour++) {
  //       if (bm[day*24 + hour]) {
  //         cout << mod[day*24 + hour];
  //       } else cout << '-';
  //     }
  //     cout << '\n';
  //   }
  // }

};


#endif
