#include <bits/stdc++.h>

using namespace std;

vector<int> v;
map<int, int> m;

bool isrep(int idx) { //ÊÇ·ñÌæ»» 
	for (int i = 0; i < v.size(); i++) if (idx == v[i]) return false;
	return true;
}

int main() {
	fstream fin, fout, fout2;
	fin.open("merge.txt", ios::in); 
	fout.open("merge4.txt", ios::out);
//	fout2.open("merge4chn.txt", ios::out);
	string *sarr = new string[10];
	int sidx = 0;
	bool lss = false;
	int lsn = 0, lastnn = -1, lastnn2 = -1;
	int idx = 1; 
	while (!fin.eof()) {
		getline(fin, sarr[sidx]);
		string& cnt = sarr[sidx];
		if (cnt.length() == 0) continue;
		if (cnt[0] == '{') {
//			if (lastnn2 != -1) {
//				// cout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
//				fout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
//			}
//			else if (lsn == 1) fout << sarr[lastnn+1] << endl << sarr[sidx-1] << endl;
//			else if (lsn >= 2) fout << sarr[lastnn] << endl << sarr[sidx-1] << endl;
//			else fout << sarr[0] << endl << sarr[sidx-1] << endl;
			if (lastnn2 != -1) {
				// cout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
				fout << idx << endl << sarr[lastnn2+1] << endl;
			}
			else if (lsn == 1) fout << idx << endl << sarr[lastnn+1] << endl;
			else if (lsn >= 2) fout << idx << endl << sarr[lastnn] << endl;
			else fout << idx << endl << sarr[0] << endl;
//			if (lastnn2 != -1) {
//				// cout << sarr[lastnn2+1] << endl << sarr[sidx-1] << endl;
//				fout2 << idx << endl << '@' << sarr[sidx-1] << endl;
//			}
//			else if (lsn == 1) fout2 << idx << endl << '@' << sarr[sidx-1] << endl;
//			else if (lsn >= 2) fout2 << idx << endl << '@' << sarr[sidx-1] << endl;
//			else fout2 << idx << endl << '@' << sarr[sidx-1] << endl;
			sidx = 0;
			// lss = false;
			lsn = 0;
			lastnn = -1;
			lastnn2 = -1;
			idx++;
		}
		else {
			if ((cnt.find("[¡¡") != cnt.npos) || (cnt.find("¡¡]") != cnt.npos)) { lastnn2 = sidx; } //printf("fff\n"); }
			if (cnt[0] == '[') { lsn++; lastnn = sidx; }
			sidx++;
		}
	}
	fin.close(); fout.close(); //fout2.close();
	cout << "process merge4.txt done." << endl;
	fin.open("output2GBK.txt", ios::in);
	fout.open("output4.txt", ios::out);
	string tmp;
	int line = 1;
	idx = 1;
//	v.push_back(373);
//	v.push_back(3090);
//	v.push_back(3091);
//	v.push_back(11237);
//	v.push_back(11238);
//	v.push_back(18755);
//	v.push_back(18756);//7
//	v.push_back(25472);
//	v.push_back(25473);
//	v.push_back(26330);//10
//	v.push_back(26331);
//	v.push_back(275);
//	v.push_back(26331);
	v.push_back(373);
	v.push_back(38377);
	v.push_back(38378);
	int offset = 0;
	while(!fin.eof()) {
		getline(fin, tmp);
		int pos = tmp.find("pushstring");
		if (pos == tmp.npos) {
		} else {
			if (line > 263967) {
				if (!isrep(idx)) {
					offset++;
				} else if (tmp.substr(pos+11).length() == 0) {
					idx--;
				} else {
					fout << idx-offset << " " << line << endl << tmp.substr(pos+11) << endl;
					
				}
				idx++;
			}
			// cout << tmp.substr(0, pos+12) << reps << endl;
		}
		line++;
	}
	fin.close(); fout.close();
	cout << "process output4.txt done." << endl;
	return 0;
}
