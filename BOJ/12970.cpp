#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, K; cin >> N >> K;
	if ((N / 2) * ((N + 1) / 2) < K) {
		cout << -1;
		return;
	}
	vector<int> ans;
	for (int i = 0; i < (N / 2); ++i) {
		ans.push_back((N + 1) / 2);
	}
	int index = (N / 2) - 1;
	int sum = (N / 2) * ((N + 1) / 2);
	while (sum > K) {
		if (ans[index]) {
			--ans[index];
			if (ans[index] == 0) --index;
		}
		--sum;
	}
	// for (auto i: ans) cout << i << ' ';
	string ret = "";
	int rem = (N + 1) / 2;
	for (auto i: ans) {
		while (rem > i) {
			ret += 'B';
			--rem;
		}
		ret += 'A';
	}
	while (rem) {
		ret += 'B';
		--rem;
	}
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}