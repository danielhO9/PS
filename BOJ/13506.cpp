#include <bits/stdc++.h>
using namespace std;

bool pos[1000000];

// N[...i] 접두사와 접미사가 같은 최대 길이(본인 제외)
vector<int> getPartialMatch(const string& N) {
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
	string S; cin >> S;
	int n = S.size();
	vector<int> pi = getPartialMatch(S);
	vector<int> arr;
	arr.push_back(pi.back()); pos[pi.back()] = true;
	while (arr.back() != 0) {
		arr.push_back(pi[arr.back() - 1]);
		pos[arr.back()] = true;
	}
	int ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (pos[pi[i]]) ans = max(ans, pi[i]);
	}
	for (int i = 0; i < ans; ++i) cout << S[i];
	if (ans == 0) cout << -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}