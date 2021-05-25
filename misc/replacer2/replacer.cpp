// replacer.cpp : 定义控制台应用程序的入口点。
//

// #include "stdafx.h"

//263901

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

map<string, string> m;
map<string, string>::iterator mit;

const int dummynum = 4;

int main(int argc, char* argv[])
{
	fstream fin, fout, lout, fout2;
	// fin.open(argv[1], ios::in);
	fin.open("merge3.txt", ios::in); 
	lout.open("log3.txt", ios::out);
	string *sarr = new string[10];
	int sidx = 0;
	while (!fin.eof()) {
		string s1, s2;
		getline(fin, s1);
		getline(fin, s2);
		m[s1] = s2;
	}
	fin.close();
	lout << "read done." << endl;
	cout << "read done." << endl;
	// fin.open(argv[2], ios::in);
	// fout.open(argv[3], ios::out);
	fin.open("output2GBK.txt", ios::in);
	fout.open("output3GBK.txt", ios::out);
	fout2.open("rep3.txt", ios::out);
	string tmp;
	int line = 1;
	int repnum = 0, repdnum = 0, nrepnum = 0;
	while (getline(fin, tmp)) {
		if (line < 263901) { fout << tmp << endl; line++; continue; }
		int pos = tmp.find("pushstring");
		if (pos != tmp.npos) {
			fout << tmp.substr(0, pos + 11);
			string last = tmp.substr(pos + 11);
			bool is_ascii_str = true;
			for (int i = 0; i < last.length(); i++)
				if (isascii(last[i]) == false) {
					is_ascii_str = false;
					break;
				}
			if (last.length() == 0) {
				fout << last;
			}
			else if (m.count(last) == 1  && line >= 263968) {
				fout << '@';
				fout << m[last];
				repnum++;
			}
			/*else if (last.length() >= 6 && m.count(last.substr(dummynum, last.length()-2*dummynum)) == 1  && line >= 263968) {
				fout << '@';
				fout << m[last.substr(dummynum, last.length()-2*dummynum)];
				repdnum++;
			}*/
			else if (is_ascii_str == false && line >= 263968) {
				fout << '@';
				fout << last;
				nrepnum++;
				// lout << last << " at line " << line << " added @ for not an ascii str." << endl;
				lout << "status 000002 at line " << line << " str: " << last << endl;
				// cout << "status 000002 at line " << line << " str: " << last << endl;
				fout2 << line << endl << last << endl;
			}
			else {
				fout << last;
				nrepnum++;
				// lout << last << " at line " << line << " not found." << endl;
				lout << "status 000001 at line " << line << " str: " << last << endl;
				cout << "status 000001 at line " << line << " str: " << last << endl;
			}
		}
		else {
			fout << tmp;
		}
		fout << endl;
		line++;
	}
	fin.close();
	fout.close();
	lout << "work done." << endl;
	lout << "replace " << repnum << " lines, dummy " << repdnum << " lines, not found " << nrepnum << " lines" << endl;
	cout << "work done." << endl;
	cout << "replace " << repnum << " lines, dummy " << repdnum << " lines, not found " << nrepnum << " lines" << endl;
	return 0;
}

