#include <bits/stdc++.h>

using namespace std;

vector<int> v;
map<int, int> m;

bool isrep(int idx) { //ÊÇ·ñÌæ»» 
	for (int i = 0; i < v.size(); i++) if (idx == v[i]) return false;
	return true;
}

int main(int argc, char *argv[]) {
	fstream fin, fout;
	int idx;
	
	
	fin.open(argv[1], ios::in); 
	if (!fin) {
		cout << "skip jp" << endl;
	} else {
		fout.open(argv[2], ios::out); // numbered jp strings
		idx = 1; 
		while (!fin.eof()) {
			string s1, s2;
			getline(fin, s1);
			getline(fin, s2);
			if (s2.length() == 0) continue;
			fout << idx << endl << s2 << endl;
			idx++;
		}
		fin.close(); fout.close();
		cout << "process " << argv[1] << " done." << endl;
	}
	
	
	fin.open(argv[3], ios::in);
	if (!fin) {
		cout << "skip cn" << endl;
	} else {
		fout.open(argv[4], ios::out); // numbered cn strings
		idx = 1; 
		while (!fin.eof()) {
			string s1, s2;
			getline(fin, s1);
			getline(fin, s2);
			if (s2.length() == 0) continue;
			fout << idx << endl << "@" << s2 << endl;
			idx++;
		}
		fin.close(); fout.close();
		cout << "process " << argv[3] << " done." << endl;
	}
	
	
	fin.open(argv[5], ios::in); // origin decompiled script
	if (!fin) {
		cout << "skip script" << endl;
	} else {
		fout.open(argv[6], ios::out);
		string tmp;
		int line = 1;
		idx = 1;
//		// Hoshimemo_HD
//		v.push_back(373);
//		v.push_back(38377);
//		v.push_back(38378);
		// HoshimemoEH_HD
		int offset = 0;
		while(!fin.eof()) {
			getline(fin, tmp);
			int pos = tmp.find("pushstring");
			if (pos == tmp.npos) {
			} else {
				// if (line > 263967) { // Hoshimemo_HD
				if (line > 267556) { // HoshimemoEH_HD
					if (!isrep(idx)) {
						offset++;
					} else if (tmp.substr(pos+11).length() == 0) {
						idx--;
					} else {
						fout << idx-offset << endl << tmp.substr(pos+11) << endl;
						//fout << idx-offset << " " << line << endl << tmp.substr(pos+11) << endl;
					}
					idx++;
				}
				// cout << tmp.substr(0, pos+12) << reps << endl;
			}
			line++;
		}
		fin.close(); fout.close();
		cout << "process " << argv[5] << " done." << endl;
	}
	return 0;
}
