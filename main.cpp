#include<bits/stdc++.h>
#include "solve_bf.h"
#include "module.h"


#include "HTTPDownloader.hpp"

using namespace std;
const string AY="2017-2018";
string sem;
const int maxlength_module=20;

int main()
{
 	string s1,s2,time_table;
	char ch;
	int num_modules,i;
	ifstream myfile;
	vector <module> modules;
	cout << "Please enter the semester\n>";
	cin >> sem;
	cout<<"Please type in how many modules do you have?\n>";
	cin>>num_modules;
	for(i=0;i<num_modules;i++)
	{
		cout<<"Please type in the module code\n>";
		cin>>s1;

	  string url = "https://nusmods.com/api/2017-2018/" + sem + "/modules/"+s1+"/timetable.json";

	  HTTPDownloader http;



		module m = module(http.download(url));
		m.code=s1;
		modules.push_back(m);
		// }
		// else
		// {
		// 	cout<<"Please type in the correct the module code"<<endl;
		// 	i--;
		// }
		
	}
	
	auto ans = solve(modules, sem);
	for (auto i : ans) {
		cout << i << '\n';
	}
}
