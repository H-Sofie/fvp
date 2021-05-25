#include <bits/stdc++.h>

using namespace std;

typedef unsigned char uchar;

const int MAX_FILENAME_LEN = 255;
const int MAX_FILE_LEN = 64*1024*1024;

uchar binOri[MAX_FILE_LEN];
uchar binCN[MAX_FILE_LEN];

int lenOri=0, lenCN=0;
int global_offset = 4;

int getPos2(int pos) {
	int b1 = binCN[pos];
	int b2 = binCN[pos + 1];
	int b3 = binCN[pos + 2];
	int b4 = binCN[pos + 3];
	return b1 + b2*0x100 + b3*0x10000 + b4*0x1000000;
}

int main(int argc, char *argv[]) {
	memset(binOri, 0, sizeof(binOri));
	memset(binCN, 0, sizeof(binCN));
	
	fstream fs;
	FILE *fp, *fp2, *lout=stderr;
	string oriFileName, cnFileName, oriResultFileName, cnResultFileName;
	if (argc >= 5) oriFileName=argv[1], cnFileName=argv[2], oriResultFileName=argv[3], cnResultFileName=argv[4];
	if (argc == 6) global_offset = atoi(argv[5]);
	
//	if (strlen(argv[1]) == 0) oriFileName = "jp.hcb"; else oriFileName = argv[1];
//	if (strlen(argv[2]) == 0) cnFileName = "cn.hcb"; else cnFileName = argv[2];
//	if (strlen(argv[3]) == 0) oriResultFileName = "output_jp.txt"; else oriResultFileName = argv[2];
//	if (strlen(argv[4]) == 0) cnResultFileName = "output_cn.txt"; else cnResultFileName = argv[3];

//	oriFileName = "Hoshimemo_EH.hcb";
//	cnFileName =  "Hoshimemo_EHchn.bch";
//	oriResultFileName = "jp.txt";
//	cnResultFileName = "cn.txt";
	
	fs.open(oriFileName, ios::in | ios::binary);
	while (!fs.eof()) {
		fs.read((char *)&binOri[lenOri], sizeof(char));
		lenOri++;
	}
	fs.close();
	fs.open(cnFileName, ios::in | ios::binary);
	while (!fs.eof()) {
		fs.read((char *)&binCN[lenCN], sizeof(char));
		lenCN++;
	}
	fs.close();
	
//	cout << "lenOri=" << lenOri << " lenCN=" << lenCN << endl;
	fprintf(lout, "lenOri=0x%X, lenCN=0x%X\n", lenOri, lenCN);
	
	fp = fopen(oriResultFileName.c_str(), "w");
	fp2 = fopen(cnResultFileName.c_str(), "w");
	int pos = global_offset, nextpos = global_offset;
	uchar c = 0;
	bool isPushStr = false;
	while (pos < lenOri) {
		c = binOri[pos];
		// if (pos >= 0x7B037) { fprintf(lout, "at pos 0x%02X opc 0x%02X\n", pos, c); }
		isPushStr = false;
		if (c > 0x27) {
			fprintf(lout, "W: unknown opcode 0x%02X at 0x%08X\n", c, pos);
		}
		switch(c) {
			case 0x0C:
			case 0x10:
			case 0x12:
			case 0x16:
			case 0x18:
				nextpos = pos + 2; break;
			case 0x01:
			case 0x03:
			case 0x0B:
			case 0x0F:
			case 0x11:
			case 0x15:
			case 0x17:
				nextpos = pos + 3; break;
			case 0x02:
			case 0x06:
			case 0x07:
			case 0x0A:
			case 0x0D:
				nextpos = pos + 5; break;
			case 0x0E:
				nextpos = pos + 1; isPushStr = true; break;
			default:
				nextpos = pos + 1; break;
		}
		if (isPushStr) {
			int len = binOri[nextpos];
			// if (pos >= 0x7B037) { fprintf(lout, "len = %02X\n", len); }
			fprintf(fp, "{0x%08X}\n", pos);
			int cntpos = nextpos + 1;
			for (int i = 0; i < len-1; i++) {
				// fputc(binOri[cntpos+i], fp);
				if (binOri[cntpos+i] == 0x00) break;
				else fputc(binOri[cntpos+i], fp);
			}
			fputc('\n', fp);
			
			if (binCN[pos] == 0x0E) {
				int len2 = binCN[nextpos];
				int cntpos = nextpos + 1;
				fprintf(fp2, "{0x%08X}\n", pos);
				for (int i = 0; i < len2-1; i++) {
					if (binCN[cntpos+i] == 0x00) break;
					else fputc(binCN[cntpos+i], fp2);
				}
				fputc('\n', fp2);
			} else if (binCN[pos] == 0x06) { // JMP u32
				int pos2 = getPos2(pos + 1);
				if (binCN[pos2] != 0x0E) {
					fprintf(lout, "W: jmp addr 0x%08X at 0x%08X does not contain 0x0E(pushstring) opcode\n", pos2, pos);
					// exit(0);
					goto SKIPCN;
				}
				int len2 = binCN[pos2 + 1];
				int cntpos = pos2 + 2;
				fprintf(fp2, "{0x%08X}\n", pos);
				// for (int i = 0; i < len2-1; i++)
				for (int i = 0; i < len2; i++) // not contain 0x00
					fputc(binCN[cntpos+i], fp2);
				fputc('\n', fp2);
			} else {
				fprintf(lout, "W: 0x%08X does not contain 0x06(jmp) or 0x0E(pushstring) opcode\n", pos);
				// exit(0);
				goto SKIPCN;
			}
			
			SKIPCN:
			nextpos = nextpos + len + 1;
		}
		pos = nextpos;
		// fprintf(lout, "nextpos = %08X\n", nextpos);
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}

