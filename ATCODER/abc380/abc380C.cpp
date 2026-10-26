#include <bits/stdc++.h>
using namespace std;

int N, K;
string S;

void solve() {
	cin >> N >> K;
	cin >> S;
	int cnt = 0;
	vector<pair<char, int>> ans;
	for (int i = 0; i < N; ++i) {
		if (i == 0 || S[i - 1] == S[i]) ++cnt;
		else {
			ans.push_back({S[i - 1], cnt});
			cnt = 1;
		}
	}
	ans.push_back({S[N - 1], cnt});
	cnt = 0;
	for (int i = 0; i < ans.size(); ++i) {
		if (ans[i].first == '1') ++cnt;
		if (cnt == K) {
			swap(ans[i -1], ans[i]);
		}
	}
	for (auto i: ans) {
		for (int j = 0; j < i.second; ++j)cout << i.first;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}