#include <bits/stdc++.h>
using namespace std;

string ambilstr(string s, string lbl) {
  int idx = s.find(lbl) + lbl.size() + 3;
  string res;
  while (1) {
    if (s[idx] == '"') break;
    res += s[idx++];
  }
  return res;
}
