#include <bits/stdc++.h>
using namespace std;

void solve() {
	string S, T; cin >> S >> T;
	vector<char> arr(T.size());
	for (int i = 0; i < T.size(); ++i) arr[i] = T[i];
	int s = 0, e = (int)T.size() - 1;
	int rev = 0;
	while (e - s + 1 > S.size()) {
		char end;
		if (rev) end = arr[s];
		else end = arr[e];
		if (rev) ++s;
		else --e;
		if (end == 'B') rev ^= 1;
	}
	for (int i = 0; i < S.size(); ++i) {
		if ((rev && S[i] != arr[e - i]) || (!rev && S[i] != arr[s + i])) {
			cout << 0;
			return;
		}
	}
	cout << 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}