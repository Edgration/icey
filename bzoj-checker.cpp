/*
 * bzoj-checker
 * This file is part of bzoj-checker
 *
 * Copyright (C) 2018 - Edgration
 *
 * bzoj-checker is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * bzoj-checker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with bzoj-checker. If not, see <http://www.gnu.org/licenses/>.
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

IL void myexit() {
	system("echo \"\\033[0;33msomething wrong. use -help to know how more information. \\033[0m\"");
	exit(0);
}	

IL string turn(int i) {
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

char ttemp[1000]; char ttemp2[1000];
char data_num_char[1000];
char book[1000][1000];
bool cmps(string a, string b) { return READ(a) < READ(b); }
int work(int num, string num_string, string dir) {
	if (!(num >= 1000 && num <= 5000)) myexit();

	string dow = (string)"./download-data" + (string)" -d " + num_string + string(" ") + num_string;
	string exedir = num_string + (string)"/test";
	string com = (string)"g++ " + dir + (string)" -o " + exedir + (string)" -w -O2 -lm -DONLINE_JUDGE";
	
	/* download data and cd into it*/
	system(dow.c_str());  
	
	system("ls > list2.txt");
	FILE *fa = freopen("list2.txt", "r", stdin);
	
	bool al = 0, al2 = 0;
	while (~fscanf(fa, "%s", ttemp)) {
		string tt = ttemp;
		if (tt == num_string) al = 1; 
		if (tt == num_string + (string)(".zip")) al2 = 1;
	}
	if (al2 == 0) {
		printf("Download Failed");
		myexit();
	}
	else if (al == 0) {
		string unzip_pre = "unzip ";
		string unzip = unzip_pre + num_string;
		system(unzip.c_str());
	}
	system("rm list2.txt");
	
	system(com.c_str());
	bool CeFlag = 1;
	/* get list */
	string getlist = string("ls ") + num_string + string(" > list.txt");
	system(getlist.c_str());
	FILE *list = freopen("list.txt", "r", stdin);
	int ct = 1; int eded = 0;
	
	/* compile */
	vector<string>lli;
	while (~fscanf(list, "%s", book[ct])) {
		string temp = book[ct];
		if (temp == "test") CeFlag = 0, ct--;
		else eded = ct; lli.push_back(temp);
		ct++;
	}
	ct--; system("rm list.txt");
	sort(lli.begin(), lli.end(), cmps);
	/* test */
	map<string, bool>tested; tested.clear();
	
	printf("\n=========================================================\n");
	for (int cr = 1; cr <= ct; ++cr) {
		string data_num = lli[cr - 1];
		if (data_num == "list.txt" || data_num == "test") continue;
		string Fr = (string)"echo " + data_num + string(" | cut -d. -f1") + (string)" > Fr";
		string Su   = (string)"echo " + data_num + string(" | cut -d. -f2") + (string)" > Su"; 	
		system(Fr.c_str()); system(Su.c_str());
		FILE *sss = freopen("Fr", "r", stdin); 
		fscanf(sss, "%s", ttemp); string Front = ttemp;
		system("rm Fr");
		FILE *ccc = freopen("Su", "r", stdin); 
		fscanf(ccc, "%s", ttemp2); string Suf   = ttemp2;
		system("rm Su");
		if (tested[Front]) continue;
		else tested[Front] = 1;
		
		printf("|%5s    ", Front.c_str());
		fflush(stdout);
			
		if (CeFlag == 1) {
			printf("|         \033[3;43m CompileError \033[0m         |");
			fflush(stdout);
			printf("     --     |\n"); fflush(stdout);
			if (cr != ct - 1) printf("---------------------------------------------------------\n");
			continue;
		}
			
		string doit = (string)"{ time -p ./" + exedir + (string)" < " + num_string + string("/") + \
		Front + string(".in >") + "checker; } 2>time_cnt";
		
		//cerr << doit << endl;
		system(doit.c_str());
		string chk  = "diff -b -q checker " + num_string + string("/") + Front + string(".out >ans");  
		system(chk.c_str()); 
		FILE *cur = freopen("ans", "r", stdin);
		fscanf(cur, "%s", ttemp);
		string te = ttemp;
		bool Reflag = 0;
		FILE *cur2 = freopen("time_cnt", "r", stdin);
		scanf("%s", ttemp); string ReTest = ttemp;
		if (ReTest != "real") Reflag = 1; scanf("%s", ttemp);
		if (Reflag) {
			printf("|         \033[3;45m RuntimeError \033[0m         |");
			fflush(stdout);
			printf("     --     |\n"); fflush(stdout);
		}
		else if (te != Front) { 
			printf("|         \033[3;41m WrongAnswer! \033[0m         |");
			fflush(stdout);
			printf("%8ss   |\n", ttemp); fflush(stdout);
		} //WA
		else { 
			printf("|         \033[3;42m RightOutPut! \033[0m         |");
			fflush(stdout);
			printf("%8ss   |\n", ttemp); fflush(stdout);
		} //AC
		system("rm ans"); system("rm checker"); system("rm time_cnt");
		if (cr < eded - 1) printf("---------------------------------------------------------\n");
	};
	if (!CeFlag) {
		string des = (string)"rm " + exedir;
		system(des.c_str()); 
	}
	printf("=========================================================\n\n");
	
	/* end data */
}

IL string getSuf(string A) {
	int Len = A.size();
	int pos = 0;
	for (int i = 0; i < Len; ++i) if (A[i] == '.') pos = i;
	return A.substr(pos + 1, Len - pos + 1); 	
}	

int work2(int num, string num_string, string dir) {
	
	string dow = (string)"wget " + (string)" -d " + num_string + string(" ") + num_string;
	string exedir = num_string + (string)"/test";
	string com = (string)"g++ " + dir + (string)" -o " + exedir + (string)" -w -O2 -lm -DONLINE_JUDGE";
	
	/* download data and cd into it*/
	
	system("ls > list2.txt");
	FILE *fa = freopen("list2.txt", "r", stdin);
	
	bool al = 0, al2 = 0;
	
	system(com.c_str());
	bool CeFlag = 1;
	/* get list */
	string getlist = string("ls ") + num_string + string(" > list.txt");
	system(getlist.c_str());
	FILE *list = freopen("list.txt", "r", stdin);
	int ct = 1; int eded = 0;
	
	/* compile */
	vector<string>lli;
	string Ans_Or_Out;
	while (~fscanf(list, "%s", book[ct])) {
		string temp = book[ct]; 
		if (temp == "test") CeFlag = 0, ct--;
		else eded = ct; lli.push_back(temp);
		
		string t_t = getSuf(temp);
		if (t_t != "in" && t_t != "est") Ans_Or_Out = t_t;
		ct++;
	}
	
	ct--; system("rm list.txt");
	sort(lli.begin(), lli.end(), cmps);
	/* test */
	map<string, bool>tested; tested.clear();
	
	printf("\n================================================================\n");
	
	for (int cr = 1; cr <= ct; ++cr) {
		string data_num = lli[cr - 1];
		if (data_num == "list.txt" || data_num == "test") continue;
		string Fr = (string)"echo " + data_num + string(" | cut -d. -f1") + (string)" > Fr";
		string Su   = (string)"echo " + data_num + string(" | cut -d. -f2") + (string)" > Su"; 	
		system(Fr.c_str()); system(Su.c_str());
		FILE *sss = freopen("Fr", "r", stdin); 
		fscanf(sss, "%s", ttemp); string Front = ttemp;
		system("rm Fr");
		FILE *ccc = freopen("Su", "r", stdin); 
		fscanf(ccc, "%s", ttemp2); string Suf   = ttemp2;
		system("rm Su");
		if (tested[Front]) continue;
		else tested[Front] = 1;
		
		printf("|%12s    ", Front.c_str());
		fflush(stdout);
			
		if (CeFlag == 1) {
			printf("|         \033[3;43m CompileError \033[0m         |");
			fflush(stdout);
			printf("     --     |\n"); fflush(stdout);
			if (cr != ct - 1) printf("----------------------------------------------------------------\n");
			continue;
		}
			
		string doit = (string)"{ time -p ./" + exedir + (string)" < " + num_string + string("/") + \
		Front + string(".in >") + "checker; } 2>time_cnt";
		
		//cerr << doit << endl;
		system(doit.c_str());
		string chk  = "diff -b -q checker " + num_string + string("/") + Front + string(".")
		+ Ans_Or_Out + string(" >ans");  
		system(chk.c_str()); 
		FILE *cur = freopen("ans", "r", stdin);
		fscanf(cur, "%s", ttemp);
		string te = ttemp;
		bool Reflag = 0;
		FILE *cur2 = freopen("time_cnt", "r", stdin);
		scanf("%s", ttemp); string ReTest = ttemp;
		if (ReTest != "real") Reflag = 1; scanf("%s", ttemp);
		if (Reflag) {
			printf("|         \033[3;45m RuntimeError \033[0m         |");
			fflush(stdout);
			printf("     --     |\n"); fflush(stdout);
		}
		else if (te != Front) { 
			printf("|         \033[3;41m WrongAnswer! \033[0m         |");
			fflush(stdout);
			printf("%8ss   |\n", ttemp); fflush(stdout);
		} //WA
		else { 
			printf("|         \033[3;42m RightOutPut! \033[0m         |");
			fflush(stdout);
			printf("%8ss   |\n", ttemp); fflush(stdout);
		} //AC
		system("rm ans"); system("rm checker"); system("rm time_cnt");
		if (cr < eded - 1) printf("----------------------------------------------------------------\n");
	};
	if (!CeFlag) {
		string des = (string)"rm " + exedir;
		system(des.c_str()); 
	}
	printf("================================================================\n\n");
	system("rm list2.txt");
}

int main(int argc, char *argv[]) {
	if (argc == 4) {
		cout << endl;
		string pre = argv[1];
		if (pre == "-t" || pre == "--test") {
			string num = argv[2]; string dir = argv[3]; 
			work(READ(num), num, dir);
		} 
		else if (pre == "-l" || pre == "--local") {
			string num = argv[2]; string dir = argv[3]; 
			work2(0, num, dir);
		} 
		else {
			myexit(); return 0;
		} 
	}
	else if (argc == 2) {
		string temp = argv[1];
		if (temp == "-h" || temp == "--help") {
			printf("usage : [-t] [problem number]   [cpp location]  download BZOJ-data and Test\n"); 
			printf("        [-l] [data-floder address] [cpp location]  local-data checker\n");
			printf("        [-h] help\n");
			printf("        [-a] about\n"); 
		} else if (temp == "-about" || temp == "-a") {
			system("echo \"\\033[0;33m=============================================\\033[0m\"");
			system("echo \"\\033[0;33mThis program is made by Edgration on 2018.8\\033[0m\"");
			system("echo \"\\033[0;33mmore information on http://www.edgration.com\\033[0m\"");
			system("echo \"\\033[0;33m=============================================\\033[0m\"");
		}
	}
	else myexit();
	return 0;
}
