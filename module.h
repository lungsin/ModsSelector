#ifndef MODULE_H
#define MODULE_H
#include <bits/stdc++.h>
using namespace std;

string get_str(string s, string lbl) {
  int idx = s.find(lbl) + lbl.size() + 3;
  string res;
  while (1) {
    if (s[idx] == '"') break;
    res += s[idx++];
  }
  return res;
}

struct group{
    string code;
    bitset<120> slots;
    string type;

    group(string s) {
      code = get_str(s, "ClassNo");
      type = get_str(s, "LessonType");
      string day = get_str(s, "DayText");
      string start = get_str(s, "StartTime");
      string end = get_str(s, "EndTime");
      int startint = stoi(start)/100;
      int endint = stoi(end)/100;
      for (int i = start; i < end; i++) {
        slots[day*24 + i] = 1;
      }
    }

    void merge(group g) {
      slots |= g.slots;
    }

};

struct module {
    string code;
    vector<group> lec;
    vector<group> tut;
    vector<group> sec;
    vector<group> lab;


    vector<string> split(string s) {
      int last = -1;
      vector<string> res;
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '{') last = i;
        else if (s[i] == '}') {
          res.push_back(s.substr(last, i-last+1));
        }
      }
      return res;
    }

    void add(vector<group> &v, group &g) {
      if (!v.empty() && v.back().code == g.code && v.back().type == g.type) {
        v.back().merge(g);
      } else {
        v.push_back(g);
      }
    }

    module(string s) {
      vector<string> v = split(s);
      for (auto i : v) {
        group g = g(i);
        if (g.type == "Sectional Teaching") {
          add(sec, g);
        } else if (g.type == "Tutorial") {
          add(tut, g);
        } else if (g.type == "Lecture") {
          add(lec, g);
        } else if (g.type == "Laboratory") {
          add(lab, g);
        } else {
          cout << "Unkown mod type " << g.type << '\n';
          assert(0);
        }
      }
    }
};


#endif
