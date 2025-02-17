#include <bits/stdc++.h>
using namespace std;

int N, T;
string X;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> T >> X;
	int len = (1 << (N - T));
	string ans = X.substr(0, len);
	for (int i = 0; i < (1 << N); i += len) {
		if (i + len > (1 << N)) break;
		ans = max(ans, X.substr(i, len));
	}
	cout << ans;
}