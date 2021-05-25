#include <bits/stdc++.h>

using namespace std;

map<string, int> m;
map<string, int> m2;
typedef pair<string, int> ppp;

bool cmp(const ppp &a, const ppp &b) {
	return a.second > b.second;
}

int main() {
	fstream fin, fout;
	fin.open("result3manual.txt", ios::in);
	fout.open("result3pending.txt", ios::out);
	while (!fin.eof()) {
		string s1, s2;
		getline(fin, s1);
		getline(fin, s2);
		stringstream ss(s1);
		int line;
		ss >> line;
		if (m.count(s2) == 1) {
			if (m[s2] == 1) {
				fout << m2[s2] << endl << s2 << endl;
			}
			fout << line << endl << s2 << endl;
			m[s2] = m[s2]+1;
			m2[s2] = line;
			// cout << "fff";
		} else {
			m[s2] = 1;
			m2[s2] = line;
		}
	}
	vector<ppp> v(m.begin(), m.end());
	sort(v.begin(), v.end(), cmp); 
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second > 1) cout << v[i].second << " " << v[i].first << endl;
	}
	return 0;
}
