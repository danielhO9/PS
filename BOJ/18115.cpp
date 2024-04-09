#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	vector<int> A(N); for (int i = 0; i < N; ++i) cin >> A[i];
	deque<int> temp; for (int i = 0; i < N; ++i) temp.push_back(i);
	vector<int> ord;
	for (int i = 0; i < N; ++i) {
		if (A[i] == 1) {
			ord.push_back(temp.front());
			temp.pop_front();
		} else if (A[i] == 2) {
			ord.push_back(temp[1]);
			int x = temp.front();
			temp.pop_front();
			temp.pop_front();
			temp.push_front(x);
		} else {
			ord.push_back(temp.back());
			temp.pop_back();
		}
	}
	vector<int> ans(N);
	for (int i = 0; i < N; ++i) ans[ord[i]] = N - i;
	for (int i = 0; i < N; ++i) cout << ans[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}