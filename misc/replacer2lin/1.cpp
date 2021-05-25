#include <bits/stdc++.h>

using namespace std;

map<int, string> m;

int main() {
	fstream fr, fin, fout;
	fr.open("result3manual.txt", ios::in);
	while (!fr.eof()) {
		string s1, s2;
		getline(fr, s1);
		getline(fr, s2);
		stringstream ss(s1);
		int ln;
		ss >> ln;
		if (m.count(ln) == 1) {
			// cout << "!dup " << ln << endl;
		} else {
			m[ln] = s2;
			// cout << ln << ": " << s2 << endl;
		}
	}
	fin.open("output3GBK.txt", ios::in);
	fout.open("output3GBKfin.txt", ios::out);
	string tmp;
	int line = 1;
	while(!fin.eof()) {
		getline(fin, tmp);
		if (m.count(line) == 0) {
			fout << tmp << endl;
		} else {
			string reps = m[line];
			int pos = tmp.find("pushstring");
			if (pos == tmp.npos) {
				cout << "fff" << endl;
				break;
			}
			fout << tmp.substr(0, pos+12) << reps << endl;
			// cout << tmp.substr(0, pos+12) << reps << endl;
		}
		line++;
	}
	return 0;
}
