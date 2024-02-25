#include <bits/stdc++.h>
using namespace std;

int N, M;

void cons(vector<int>& ans) {
	if (ans.size() == M) {
		for (auto i: ans) cout << i << ' ';
		cout << '\n';
		return;
	}
	if (ans.size() < M) {
		for (int i = 1; i <= N; ++i) {
			ans.push_back(i);
			cons(ans);
			ans.pop_back();
		}
	}
}

void solve() {
	cin >> N >> M;
	vector<int> ans;
	cons(ans);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}