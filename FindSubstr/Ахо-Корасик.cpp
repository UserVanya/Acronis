#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
const int k = 26, NMAX = 10000;

struct bohrVrtx {
	int nextVrtx[k];
	int patNum;
	int suffLink;
	int autoMove[k];
	int par;
	int suffFlink;
	bool flag;
	char symb;
};

class BohrClass {
public:
	vector<bohrVrtx> bohr;
	vector<string> pattern;
	BohrClass();
	bohrVrtx makeBohrVrtx(int p, char c);
	void addStringToBohr(const string& s);
	bool isStringInBohr(const string& s);
	int getAutoMove(int v, char ch);
	int getSuffLink(int v);
	int getSuffFlink(int v);
	void check(int v, int i);
	void findAllPos();
};

bohrVrtx BohrClass::makeBohrVrtx(int p, char c) {
	bohrVrtx v;
	memset(v.nextVrtx, 255, sizeof(v.nextVrtx));
	memset(v.autoMove, 255, sizeof(v.autoMove));
	v.flag = false;
	v.suffLink = -1;
	v.par = p;
	v.symb = c;
	v.suffFlink = -1;
	return v;
}

BohrClass::BohrClass() {
	bohr.push_back(makeBohrVrtx(0, '$'));
}

void BohrClass::addStringToBohr(const string& s) {
	int num = 0;
	for (int i = 0; i < s.length(); i++) {
		char ch = s[i] - 'a';
		if (bohr[num].nextVrtx[ch] == -1) {
			bohr.push_back(makeBohrVrtx(num, ch));
			bohr[num].nextVrtx[ch] = (int)bohr.size() - 1;
		}
		num = bohr[num].nextVrtx[ch];
	}
	bohr[num].flag = true;
	pattern.push_back(s);
	bohr[num].patNum = (int)pattern.size() - 1;
}
bool BohrClass::isStringInBohr(const string& s) {
	int num = 0;
	for (int i = 0; i < s.length(); i++) {
		char ch = s[i] - 'a';
		if (bohr[num].nextVrtx[ch] == -1) {
			return false;
		}
		num = bohr[num].nextVrtx[ch];
	}
	return true;
}
int BohrClass::getSuffLink(int v) {
	if (bohr[v].suffLink == -1)
		if (v == 0 || bohr[v].par == 0)
			bohr[v].suffLink = 0;
		else
			bohr[v].suffLink = getAutoMove(getSuffLink(bohr[v].par), bohr[v].symb);
	return bohr[v].suffLink;
}
int BohrClass::getAutoMove(int v, char ch) {
	if (bohr[v].autoMove[ch] == -1)
		if (bohr[v].nextVrtx[ch] != -1)
			bohr[v].autoMove[ch] = bohr[v].nextVrtx[ch];
		else
			if (v == 0)
				bohr[v].autoMove[ch] = 0;
			else
				bohr[v].autoMove[ch] = getAutoMove(getSuffLink(v), ch);
	return bohr[v].autoMove[ch];
}
int BohrClass::getSuffFlink(int v) {
	if (bohr[v].suffFlink == -1) {
		int u = getSuffLink(v);
		if (u == 0)
			bohr[v].suffFlink = 0;
		else
			bohr[v].suffFlink = (bohr[u].flag) ? u : getSuffFlink(u);
	}
	return bohr[v].suffFlink;
}
void BohrClass::check(int v, int i) {
	for (int u = v; u != 0; u = getSuffFlink(u)) {
		if (bohr[u].flag) {
			cout << '*';
		}
	}
}

void BohrClass::findAllPos() {
	int u = 0;
	char c;
	int i = 0;
	do {
		c = getchar();
		cout << c;
		u = getAutoMove(u, c - 'a');
		check(u, i + 1);
		i++;
	} while (!feof(stdin));
}
int main() {
	BohrClass * b = new BohrClass();
	b->addStringToBohr("fff");
	b->findAllPos();
	system("pause");
}