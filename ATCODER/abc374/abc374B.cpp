#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string S, T;

void solve() {
	cin >> S >> T;
	while (S.size() < T.size()) S.push_back('_');
	while (T.size() < S.size()) T.push_back('_');
	for (int i = 0; i < S.size(); ++i) {
		if (S[i] != T[i]) {
			cout << i + 1;
			return;
		}
	}
	cout << 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}