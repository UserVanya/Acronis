#include <iostream>
#include <map>
#include <vector>
using namespace std;

void function(vector<string> substrings) {
	multimap<string, int> tmp;
	char c;
	do {
		c = getchar();
		for (auto it = tmp.begin(); it != tmp.end(); it++) {
			if (it->second == it->first.size()) {
				cout << '*';
				tmp.erase(it);
				continue;
			}
			if (c == it->first[it->second]) 
				it->second++;
			else 
				tmp.erase(it);
		}
		cout << c;
		for (int i = 0; i < substrings.size(); i++) {
			if (c == substrings[i][0]) {
				tmp.insert(make_pair(substrings[i], 1));
			}
		}
	} while (!feof(stdin));
}
int main() {
	vector<string> tmp;
	tmp.push_back("ffff");
	function(tmp);
	system("pause");
}