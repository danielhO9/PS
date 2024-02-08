#include <bits/stdc++.h>
using namespace std;

string s, c;
vector<char> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s >> c;
	for (auto i: s) {
		Q.push_back(i);
		if (Q.size() >= c.length()) {
			bool boom = true;
			for (int j = 0; j < c.length(); ++j) {
				if (c[j] != Q[((int) Q.size()) - c.length() + j]) {
					boom = false;
					break;
				}
			}
			if (boom) for (int i = 0; i < c.length(); ++i) Q.pop_back();
		}	
	}
	if (Q.empty()) cout << "FRULA";
	else {
		for (auto i: Q) cout << i;
	}
}