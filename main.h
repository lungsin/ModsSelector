#ifndef MAIN_H
#define MAIN_H

struct solution {
  bitset<100> bm;
  vector<int> mod;

  solution();

  solution(bitset<100> bm, vector<int> mod);

  void merge(bitset<100> bm2, int mod_no);

  int max_consecutive();

  bool operator < (solution &rhs) const;
}

#endif
