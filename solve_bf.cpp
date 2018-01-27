#include<bits/stdc++.h>
#include "module.h"

#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pf push_front
#define pb2 pop_back
#define pf2 pop_front
#define line printf("\n")
#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define ll long long
#define ALL(a) a.begin(),a.end()
#define vi vector<int>

using namespace std;

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

clock_t first_attempt = clock();
inline void cek_time(){
  clock_t cur = clock()- first_attempt;
  cerr<<"TIME : "<<(double) cur/CLOCKS_PER_SEC<<endl;
}
inline void OPEN (string s) {
  freopen ((s + ".in").c_str (), "r", stdin);
  freopen ((s + ".out").c_str (), "w", stdout);
}

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> bbst;
//find_by_order(idx) : i-th index 
//order_of_key(val)  : val has which index

//end of template

#include "main.h"

typedef bitset<120> timeslot;
vector<vector<timeslot> > slot;
priority_queue<solution> ans;
solution sol;

int max_size = 1e6;
void bf(int pos) {
  if(pos==-1){
    ans.push(sol);
    if(ans.size() > max_size) ans.pop();
  }
  else{
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

string conv(solution s) {
  vector<pair<string, group> > used;
  for (int i = 0; i < 120; i++) {
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
  string res = "https://nusmods.com/timetable/sem-2/share?";
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
      else if (g.type == "Sectional Training") res += "SEC";
      else if (g.type == "Laboratory") res += "LAB";
      else cout << "Unkown type: " << g.type << '\n', assert(0);
      res += ':';
      res += g.code;
    }
  }
  return res;
}

vector<string> solve(vector<module> modules) {

  slot.clear();
  lvl.clear();

  for (int i = 0; i < modules.size(); i++) {
    if (modules[i].lec.size()) {
      lvl.emplace_back(modules[i], 0);
      vector<bitset<120>> cur;
      for (int j = 0; j < modules[i].lec.size(); j++) {
        cur.push_back(modules[i].lec[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].lab.size()) {
      lvl.emplace_back(modules[i], 1);
      vector<bitset<120>> cur;
      for (int j = 0; j < modules[i].lab.size(); j++) {
        cur.push_back(modules[i].lab[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].sec.size()) {
      lvl.emplace_back(modules[i], 2);
      vector<bitset<120>> cur;
      for (int j = 0; j < modules[i].sec.size(); j++) {
        cur.push_back(modules[i].sec[j].slots);
      }
      slot.push_back(cur);
    }
    if (modules[i].tut.size()) {
      lvl.emplace_back(modules[i], 3);
      vector<bitset<120>> cur;
      for (int j = 0; j < modules[i].tut.size(); j++) {
        cur.push_back(modules[i].tut[j].slots);
      }
      slot.push_back(cur);
    }
  }

  auto pq = optimal_solution(5);
  vector<string> ans;
  while (!pq.empty()) {
    ans.push_back(conv(pq.top()));
    pq.pop();
  }
  reverse(ans.begin(), ans.end());
  return ans;
}
