/*
 * data-download
 * This file is part of data-download
 *
 * Copyright (C) 2018 - Edgration
 *
 * data-download is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * data-download is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with data-download. If not, see <http://www.gnu.org/licenses/>.
 */

 
#include <bits/stdc++.h>
using namespace std;

#define IL inline 
IL int read() {
	char ch = getchar(); int u = 0, f = 1;
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { u = (u << 1) + (u << 3) + ch - 48; ch = getchar(); }
	return u * f; 
}

const int maxn = 1e5 + 10;
char name[maxn];
bool download[maxn];

string pre = "axel https://lydsy.download/archive/";
string suc = ".zip -a";

string turn(int i) {
	vector<int>temp;
	while (i) {
		temp.push_back(i % 10);
		i /= 10;
	}
	reverse(temp.begin(), temp.end());
	string rtn = "";
	for (int i = 0; i < temp.size(); ++i) rtn += char(temp[i] + '0');
	return rtn;
}

IL int READ(string &name) {
	int u = 0; int t = name.length();
	for (int i = 0; i < t; ++i) if (isdigit(name[i])) u = (u << 1) + (u << 3) + name[i] - '0';
	return u;
}

IL void make(int start, int end) {
	int cnt = 0;
	if (start >= 1000 && end <= 5000) {
		system("ls > list.txt");
		FILE *List = freopen("list.txt", "r", stdin);
		while (~fscanf(List, "%s", name)) {
			int len = strlen(name);
			int u = 0;
			for (int i = 0; i < len; ++i) if (isdigit(name[i])) u = (u << 1) + (u << 3) + name[i] - '0';
			download[u] = 1;
		}
		for (int i = start; i <= end; ++i) {
			if (download[i]) { 
				continue;
			}
			else {
				string mid = turn(i);
				string url = pre + mid + suc;
				system(url.c_str());
				cnt++;
			}
		}	
	}
	else { start = end = 0; }
}

int main(int argc, char *argv[]) {
	if (argc <= 1) { system("echo \"\\033[0;33muse -help to know how more information. \\033[0m\""); }
	else if (argc == 2) {
		string cur = argv[1];
		if (cur == "-help" || cur == "-h") {
			system("echo \"\\033[0;33m[commonds] \n-d -[start data number] -[end data number]  download\n-h                                          help \n-a                                          about\n \\033[0m\"");
		}
		else if (cur == "-about" || cur == "-a") {
			system("echo \"\\033[0;33m=============================================\\033[0m\"");
			system("echo \"\\033[0;33mThis program is made by Edgration on 2018.7\\033[0m\"");
			system("echo \"\\033[0;33mmore information on http://www.edgration.com\\033[0m\"");
			system("echo \"\\033[0;33m=============================================\\033[0m\"");
		}
		else {
			system("echo \"\\033[0;33muse -help to know how more information. \\033[0m\""); 
		}
	}
	else if (argc == 3) { system("echo \"\\033[0;33muse -help to know how more information. \\033[0m\""); }
	else if (argc == 4) {
		string cur = argv[1];
		if (cur == "-d" || cur == "-download") {
		int a = 0, b = 0;
		string A = argv[2]; string B = argv[3];
		a = READ(A); b = READ(B); make(a, b);
		}
		else {
			system("echo \"\\033[0;33muse -help to know how more information. \\033[0m\"");
		}
	}
	else if (argc > 4) { system("echo \"\\033[0;33muse -help to know how more information. \\033[0m\""); }
	return 0;
}		
