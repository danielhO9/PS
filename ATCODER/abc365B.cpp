#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int N; cin >> N;
	int A[N];
	for (int i = 0; i < N; ++i) cin >> A[i];
	vector<pair<int, int>> V;
	for (int i = 0; i < N; ++i) {
		V.push_back({A[i], i});
	}
	sort(V.begin(), V.end());
	cout << V[N - 2].second + 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}