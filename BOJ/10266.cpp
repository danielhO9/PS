#include <bits/stdc++.h>
using namespace std;

vector<int> getPartialMatch(vector<int>& N) {
	int m = N.size(); 
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

vector<int> kmpSearch(vector<int>& H, vector<int>& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) ret.push_back(begin);
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a.begin(), a.end());
	vector<int> H;
	for (int i = 0; i < n; ++i) {
		int nxti = (i + 1) % n;
		H.push_back((a[nxti] + 360000 - a[i]) % 360000);
	}
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a.begin(), a.end());
	vector<int> N;
	for (int i = 0; i < n; ++i) {
		int nxti = (i + 1) % n;
		N.push_back((a[nxti] + 360000 - a[i]) % 360000);
	}
	for (int i = 0; i < n; ++i) H.push_back(H[i]);
	vector<int> res = kmpSearch(H, N);
	if (res.empty()) cout << "impossible";
	else cout << "possible";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}