#include <bits/stdc++.h>
using namespace std;

int N, K;
int A[500000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> A[i];
	unordered_map<int, int> idx;
	for (int i = 0; i < N; ++i) idx[A[i]] = i;
	vector<int> tmp; for (int i = 0; i < N; ++i) tmp.push_back(A[i]);
	sort(tmp.begin(), tmp.end());
	int cnt = 0;
	for (int i = N - 1; i >= 0; --i) {
		if (cnt == K) break;
		int j = idx[tmp[i]];
		if (i == j) continue;
		swap(A[i], A[j]);
		swap(idx[A[i]], idx[A[j]]);
		++cnt;
	}
	if (cnt != K) cout << -1;
	else {
		for (int i = 0; i < N; ++i) cout << A[i] << ' ';
	}
}