#include<bits/stdc++.h>
#include "module.h"
#include "main.h"

using namespace std;

vector<vector<bitset<bitset_sz> > > slot;
priority_queue<solution> ans;
solution sol;

int max_size = 1e6;
void bf(int pos) {
  if(pos==-1){
    ans.push(sol);
    if(ans.size() > max_size) ans.pop();
  }
  else{
    if (!ans.empty() && ans.top() < sol) return;
    solution ori = sol;
    for (int i = 0; i < slot[pos].size(); i++) {
      auto a = slot[pos][i];
      if( (a & sol.bm).none()){
        sol.merge(a, pos, i);
        bf(pos-1);
        sol = ori;
      }
    }
  }
}

priority_queue<solution> optimal_solution(int size){
  max_size = size;
  bf(slot.size()-1);
  return ans;
}

vector<pair<module, int> > lvl;

string conv(solution s, string sem) {
  cout << "sol: ";
  for (int i = 0; i < bitset_sz; i++) cout << s.bm[i];
  cout << '\n';
  vector<pair<string, group> > used;
  for (int i = 0; i < bitset_sz; i++) {
    if (s.bm[i]) {
      auto cur = s.mod[i];
      if (lvl[cur.first].second == 0) {
        used.emplace_back(lvl[cur.first].first.code, lvl[cur.first].first.lec[cur.second]);
      } else if (lvl[cur.first].second == 1) {
        used.emplace_back(lvl[cur.first].first.code, lvl[cur.first].first.lab[cur.second]);
      } else if (lvl[cur.first].second == 2) {
        used.emplace_back(lvl[cur.first].first.code, lvl[cur.first].first.sec[cur.second]);
      } else if (lvl[cur.first].second == 3) {
        used.emplace_back(lvl[cur.first].first.code, lvl[cur.first].first.tut[cur.second]);
      } else {
        assert(0);
      }
    }
  }
  map<string, set<group> > pt;
  for (auto i : used) {
    pt[i.first].insert(i.second);
  }
  string res = "https://nusmods.com/timetable/sem-"+sem+"/share?";
  bool first = true;
  for (auto it = pt.begin(); it != pt.end(); ++it) {
    if (first) {
      first = false;
    } else res += '&';
    res += it->first;
    res += '=';
    int i = 0;
    for (auto g : it->second) {
      if (i) res += ',';
      i++;
      if (g.type == "Lecture") res += "LEC";
      else if (g.type == "Tutorial") res += "TUT";
      else if (g.type == "Sectional Teaching") res += "SEC";
      else if (g.type == "Laboratory") res += "LAB";
      else cout << "Unkown type: " << g.type << '\n', assert(0);
      res += ':';
      res += g.code;
    }
  }
  return res;
}

vector<string> solve(vector<module> modules, string sem) {

  slot.clear();
  lvl.clear();
  while(!ans.empty()) ans.pop();

  for (int i = 0; i < modules.size(); i++) {
    if (modules[i].lec.size()) {
      lvl.emplace_back(modules[i], 0);
      vector<bitset<bitset_sz>> cur;
      for (int j = 0; j < modules[i].lec.size(); j++) {
        cur.push_back(modules[i].lec[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].lab.size()) {
      lvl.emplace_back(modules[i], 1);
      vector<bitset<bitset_sz>> cur;
      for (int j = 0; j < modules[i].lab.size(); j++) {
        cur.push_back(modules[i].lab[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].sec.size()) {
      lvl.emplace_back(modules[i], 2);
      vector<bitset<bitset_sz>> cur;
      for (int j = 0; j < modules[i].sec.size(); j++) {
        cur.push_back(modules[i].sec[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].tut.size()) {
      lvl.emplace_back(modules[i], 3);
      vector<bitset<bitset_sz>> cur;
      for (int j = 0; j < modules[i].tut.size(); j++) {
        cur.push_back(modules[i].tut[j].slots);
      }
      slot.push_back(cur);
    }
  }

  auto pq = optimal_solution(5);
  vector<string> ans;
  while (!pq.empty()) {
    ans.push_back(conv(pq.top(), sem));
    pq.pop();
  }
  reverse(ans.begin(), ans.end());
  return ans;
}
