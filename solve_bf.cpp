#include<bits/stdc++.h>


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

#include <main.h>
#include <solve_bf.h>

typedef bitset<100> timeslot;
typedef vector<int> module;
vector<vector<timeslot> > slot;
priority_queue<solution> ans;
solution sol;

int max_size = 1e6;
void bt(int pos) {
	if(pos==-1){
        ans.push(sol);
		if(ans.size() > max_size) ans.pop();
    }
    else{
		solution ori = sol;
		for(auto a : slot){
			if( (a & sol_time).none()){
				sol.merge(a, pos);
				bf(pos-1);
				sol = ori;
			}
		}
    }
}

void build_bf(vector<vector<timeslot> > tslot){
	slot = tslot;
}

priority_queue<solution> optimal_solution(int size){
	max_size = size;
	bf(0);
	return ans;
}