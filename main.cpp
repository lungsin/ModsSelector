#include<bits/stdc++.h>
#include "solve_bf.h"
#include "module.h"

#include "HTTPDownloader.hpp"

using namespace std;
const string AY="2017-2018";
string sem, dummy;

#define line puts("========================================")
#define cls for (int ___ = 0; ___ < 50; ___++) puts("");

vector<module> modules;


void print_modules() {
	for (int i = 0; i < modules.size(); i++) {
		cout << i+1 << ". " << modules[i].code << '\n';
	}
	if (!modules.size()) cout << "No modules selected\n";
}

module add_module(string code) {
	string url = "https://nusmods.com/api/2017-2018/" + sem + "/modules/"+code+"/timetable.json";
	HTTPDownloader http;
	module m = module(http.download(url));
	m.code = code;
	return m;
}

void add_module() {
	cls;
	line;
	print_modules();
	line;
	cout << "Add module code: ";
	string s;
	cin >> s;
	modules.push_back(add_module(s));
}

void delete_module() {
	cls;
	line;
	print_modules();
	line;
	cout << "Delete module number: ";
	int num;
	cin >> num;
	swap(modules[num-1], modules.back());
	modules.pop_back();
}

void set_semester() {
	cls;
	cout << "Set semester to: ";
	cin >> sem;
	vector<module> nm;
	for (int i = 0; i < modules.size(); i++) {
		nm.push_back(add_module(modules[i].code));
	}
	modules = nm;
}

void generate() {
	cls;
	cout << "Please wait a few moments...\n";
	auto ans = solve(modules, sem);
	cout << "Here are the top five timetables\n";
	for (auto i : ans) {
		cout << i << '\n';
	}
	cin.ignore();
	cout << "Press enter to return to main menu\n";
	getline(cin, dummy);
}


int main() {
	sem = "1";
	while (1) {
		cls;
		line;
		cout << "Current semester: " << sem << '\n';
		cout << "Currently selected " << modules.size() << (modules.size()==1?" module":" modules") << '\n';
		print_modules();
		line;
		cout << "1. Add module\n";
		cout << "2. Delete module\n";
		cout << "3. Set semester\n";
		cout << "4. Generate!\n";
		cout << "5. Quit\n> ";
		int cmd;
		cin >> cmd;
		switch(cmd) {
			case 1:
				add_module();
				break;
			case 2:
				delete_module();
				break;
			case 3:
				set_semester();
				break;
			case 4:
				generate();
				break;
			case 5:
				cout << "Goodbye!\n";
				return 0;
			default:
				cout << "Unkown command\n";
		}
	}
}
