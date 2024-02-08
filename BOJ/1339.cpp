#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	vector<int> cnt(26);
	for (int i = 0; i < N; ++i) {
		string S; cin >> S;
		int n = S.size();
		for (int j = 0; j < n; ++j) {
			int temp = 1;
			for (int k = j; k < n - 1; ++k) temp *= 10;
			cnt[S[j] - 'A'] += temp;
		}
	}
	vector<pair<int, int>> V;
	for (int i = 0; i < 26; ++i) V.push_back({cnt[i], i});
	sort(V.begin(), V.end(), greater<>());
	int ans = 0, now = 9;
	for (auto i: V) {
		if (i.first == 0) break;
		ans += i.first * now;
		--now;
	}
	cout << ans;
}