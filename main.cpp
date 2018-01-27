#include<bits/stdc++.h>
#include "solve_bf.h"
#include "module.h"

using namespace std;
const string AY="2017-2018";
const string sem="2";
const int maxlength_module=20;
int main()
{
 	string s1,s2,time_table;
	char ch;
	int num_modules,i;
	ifstream myfile;
	vector <module> modules;
	cout<<"Please type in how many modules do you have?";
	cin>>num_modules;
	for(i=0;i<num_modules;i++)
	{
		cout<<"Please type in the module code:";
		cin>>s1;
		s2=s1+".json";
		myfile.open(s2.c_str());
		if(myfile.is_open())
		{
			modules[i].code=s1;
			time_table="";
			while(myfile.eof()==0) 
			{
				myfile>>s2;
				time_table+=s2;
			}
			modules[i]=module(time_table);
			myfile.close();
		}
		else
		{
			cout<<"Please type in the correct the module code"<<endl;
			i--;
		}
		
	}
	

	
	solve(modules);
}
	//module m;
	//modules.push_back(m);
	//modules.pop_back();
