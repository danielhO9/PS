#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	vector<int> A(N); for (int i = 0; i < N; ++i) cin >> A[i];
	stack<int> S;
	vector<int> ans(N);
	for (int i = N - 1; i >= 0; --i) {
		while (!S.empty() && S.top() <= A[i]) S.pop();
		if (S.empty()) ans[i] = -1;
		else ans[i] = S.top();
		S.push(A[i]);
	}
	for (auto i: ans) cout << i << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}