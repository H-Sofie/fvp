#include <bits/stdc++.h>

using namespace std;

vector<int> v;
map<int, int> m;
map<int, string> m2;

bool isrep(int idx) {
	for (int i = 0; i < v.size(); i++) if (idx == v[i]) return false;
	return true;
}

int main() {
	fstream fin, fout, fout2, fin2;
	fin.open("output2GBK.txt", ios::in);
	fin2.open("merge4chn.txt", ios::in);
	fout.open("output4GBK.txt", ios::out);
	string tmp;
	while(!fin2.eof()) {
		string s1, s2;
		getline(fin2, s1);
		getline(fin2, s2);
		stringstream ss(s1);
		int ln;
		ss >> ln;
		m2[ln] = s2;
	}
	int line=1, offset=0, idx=1;
	v.push_back(373);
	v.push_back(38377);
	v.push_back(38378);
	while(!fin.eof()) {
		getline(fin, tmp);
		int pos = tmp.find("pushstring");
		if (pos == tmp.npos) {
			fout << tmp << endl;
		} else {
			if (line > 263967) {
				if (!isrep(idx)) {
					offset++;
					fout << tmp << endl;
				} else if (tmp.substr(pos+11).length() == 0) {
					idx--;
					fout << tmp << endl;
				} else {
					// fout << idx-offset << " " << line << endl << tmp.substr(pos+11) << endl;
					fout << tmp.substr(0, pos+11);
					if (m2.count(idx-offset) == 0) { cout << "fff " << idx-offset << endl; }
					else fout << m2[idx-offset] << endl;
				}
				idx++;
			} else {
				fout << tmp << endl;
			}
			// cout << tmp.substr(0, pos+12) << reps << endl;
		}
		line++;
	}
	return 0;
}
