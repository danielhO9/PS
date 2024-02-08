#include <bits/stdc++.h>
using namespace std;

string s;
vector<int> lb, ls;
bool remain[1000000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> s;
		for (int j = 0; j < s.length(); ++j) remain[j] = 1;
		lb.clear(); ls.clear();
		for (int j = 0; j < s.length(); ++j) {
			if (s[j] == 'B' && !lb.empty()) {
				remain[lb.back()] = 0;
				lb.pop_back();
			} else if (s[j] == 'b' && !ls.empty()) {
				remain[ls.back()] = 0;
				ls.pop_back();
			} else if (isupper(s[j])) lb.push_back(j);
			else if (islower(s[j])) ls.push_back(j);
		}
		for (int j = 0; j < s.length(); ++j) {
			if (s[j] != 'B' && s[j] != 'b' && remain[j]) cout << s[j];
		}
		cout << '\n';
	}
}