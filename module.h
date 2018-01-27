#ifndef MODULE_H
#define MODULE_H
#include <bits/stdc++.h>
#include "main.h"
using namespace std;

string ambilstr(string s, string lbl);

struct group{
    string code;
    bitset<bitset_sz> slots;
    string type;

    group(string s) {
      string s2;
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '\n') {
        } else s2 += s[i];
      }
      s = s2;
      
      code = ambilstr(s, "ClassNo");
      type = ambilstr(s, "LessonType");
      string day = ambilstr(s, "DayText");
      string start = ambilstr(s, "StartTime");
      string end = ambilstr(s, "EndTime");
      
      int startint = stoi(start)/100;
      int endint = stoi(end)/100;
      int dayint;
      string weekText = ambilstr(s, "WeekText");
      vector<int> weekList = split(weekText);
      if (day == "Monday") dayint = 0;
      else if (day == "Tuesday") dayint = 1;
      else if (day == "Wednesday") dayint = 2;
      else if (day == "Thursday") dayint = 3;
      else if (day == "Friday") dayint = 4;
      else {cout << "Unknown day: " << day; assert(0);}
      for(int week : weekList){
          for (int i = startint; i < endint; i++) {
          slots[week*14*5 + dayint*14 + i - 8] = 1;
        }
      }
    }
    
    vector<int> split(string s){
      vector<int> ret; int num;
      if(s == "Every Week")for(int i = 1;i<=13 ; i++)ret.push_back(i-1);
      else if(s == "Even Week")for(int i = 2;i<=13 ; i+=2)ret.push_back(i-1);
      else if(s == "Odd Week")for(int i = 1;i<=13 ; i+=2)ret.push_back(i-1);
      else{
        char separator = ',';
        string token;
        stringstream ss(s);
        while(getline(ss, token, separator)) {
          ret.push_back(stoi(token)-1);
        }
      }
      return ret;
    }
    
    void merge(group g) {
      slots |= g.slots;
    }

    bool operator < (group rhs) const{
      if (code != rhs.code) return code < rhs.code;
      return type < rhs.type;
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

    void check(vector<group> &v) {
      for (int i = 0; i < v.size(); i++) {
        for (int j = i+1; j < v.size(); j++) {
          if (v[i].slots == v[j].slots) {
            swap(v[j], v.back());
            v.pop_back();
            j--;
          }
        }
      }
    }

    module(string s) {
      vector<string> v = split(s);
      for (string i : v) {
        group g = group(i);
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
      check(sec);
      check(tut);
      check(lec);
      check(lab);
    }
};


#endif
