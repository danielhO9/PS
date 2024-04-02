#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void manacher(const string& S, vector<int>& A) {
	const int n = S.size();
	int r = -1, p = -1;
	for (int i = 0; i < n; ++i) {
		if (i < r) A[i] = min(A[2 * p - i], r - i);
		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n && S[i - A[i] - 1] == S[i + A[i] + 1]) ++A[i];
		if (r < i + A[i]) {
			r = i + A[i]; p = i;
		}
	}
}

vector<int> palindrome(const string& S) {
	string tS = "";
	for (auto i: S) {
		tS += '#';
		tS += i;
	}
	tS += '#';
	const int n = tS.size();
	vector<int> A(n, 0);
	manacher(tS, A);
	return A;
}

void solve() {
	string S; cin >> S;
	// #a#b#c#
	vector<int> res = palindrome(S);
	ll ans = 0;
	for (int i = 0; i < res.size(); ++i) {
		// cout << res[i] << ' ';
		ans += (res[i] + 1) / 2;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}