#include <bits/stdc++.h>

using namespace std;

int main() {
	fstream fin, fout;
	fin.open("merge.txt", ios::in); 
	fout.open("merge2.txt", ios::out);
	string *sarr = new string[10];
	int sidx = 0;
	bool lss = false;
	int lsn = 0, lastnn = -1, lastnn2 = -1;
	while (!fin.eof()) {
		getline(fin, sarr[sidx]);
		string& cnt = sarr[sidx];
		if (cnt.length() == 0) continue;
		if (cnt[0] == '{') {
			if (lastnn2 != -1) {
				cout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
				fout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
			}
			else if (lsn == 1) fout << sarr[lastnn+1] << endl << sarr[sidx-1] << endl;
			else if (lsn >= 2) fout << sarr[lastnn] << endl << sarr[sidx-1] << endl;
			else fout << sarr[0] << endl << sarr[sidx-1] << endl;
			sidx = 0;
			// lss = false;
			lsn = 0;
			lastnn = -1;
			lastnn2 = -1;
		}
		else {
			if ((cnt.find("[¡¡") != cnt.npos) || (cnt.find("¡¡]") != cnt.npos)) { lastnn2 = sidx; } //printf("fff\n"); }
			if (cnt[0] == '[') { lsn++; lastnn = sidx; }
			sidx++;
		}
	}
	fin.close(); fout.close();
	cout << "process merge2.txt done." << endl;
	fin.open("log2.txt", ios::in); 
	fout.open("rep2.txt", ios::out);
	string s;
	while (!fin.eof()) {
		getline(fin, s);
		int pos = s.find("000002");
		if (pos == s.npos) continue;
		string ln = s.substr(pos+15, 6);
		string last = s.substr(pos+27);
		fout << ln << endl << last << endl; 
	}
	fin.close(); fout.close();
	cout << "process log2.txt done." << endl;
}
