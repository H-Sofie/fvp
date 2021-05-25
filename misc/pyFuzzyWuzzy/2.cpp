#include <bits/stdc++.h>

using namespace std;

map<string, string> m;

int main() {
	fstream f1, f2;
	f1.open("merge2.txt", ios::in);
	f2.open("merge3.txt", ios::out);
	while (!f1.eof()) {
		string s1, s2;
		getline(f1, s1);
		getline(f1, s2);
		if (m.count(s1) == 1) {
			cout << "!dup " << s1 << " to " << s2 << endl;
		} else {
			m[s1] = s2;
			f2 << s1 << endl << s2 << endl;
		}
	}
	return 0;
}
