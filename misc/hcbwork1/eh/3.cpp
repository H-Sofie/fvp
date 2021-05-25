#include <bits/stdc++.h>

using namespace std;

map<int, string> m;
map<int, string>::iterator it;

int main(int argc, char *argv[]) {
	fstream fin, fout;
	fin.open(argv[1], ios::in);
	fout.open(argv[2], ios::out);
	while (!fin.eof()) {
		string s1, s2, s3;
		getline(fin, s1);
		getline(fin, s2);
		getline(fin, s3);
		stringstream ss(s1), ss2(s2);
		int ln1, ln2;
		ss >> hex >> ln1; ss2 >> hex >> ln2;
		if (ln2 != 0) {
			m[ln2] = s3;
		} else {
			m[ln1] = s3;
		}
	}
	for (it = m.begin(); it != m.end(); it++) {
		fout.setf(ios::uppercase);
		fout << "0x" << hex << setw(8) << setfill('0') << it->first << endl << it->second << endl;
	}
	fin.close(); fout.close();
	return 0;
}
