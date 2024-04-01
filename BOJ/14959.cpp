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

void solve() {
	int n; cin >> n;
	vector<int> arr(n);
	for (int i = n - 1; i >= 0; --i) cin >> arr[i];
	vector<int> pi = getPartialMatch(arr);
	int k = 0, p = n;
	for (int i = 0; i < n; ++i) {
		int nk = n - (i + 1), np = (i + 1) - pi[i];
		if ((k + p == nk + np && np < p) || k + p > nk + np) {
			k = nk; p = np;
		}
	}
	cout << k << ' ' << p;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}