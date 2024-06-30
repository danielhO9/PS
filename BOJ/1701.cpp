#include <bits/stdc++.h>
using namespace std;

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
	int ans = 0;
	for (int i = 0; i < S.size(); ++i) {
		vector<int> pi = getPartialMatch(S.substr(i));
		ans = max(ans, *max_element(pi.begin(), pi.end()));
	}
	cout << ans;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}