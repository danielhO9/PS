#include <bits/stdc++.h>
using namespace std;

int N, M, A[100], B[100];
deque<int> acnt[101], bcnt[101];
vector<int> ans;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		acnt[A[i]].push_back(i);
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> B[i];
		bcnt[B[i]].push_back(i);
	}
	int apt = -1, bpt = -1;
	for (int i = 100; i >= 1; --i) {
		while (!acnt[i].empty() && acnt[i].front() <= apt) {
			acnt[i].pop_front();
		}
		while (!bcnt[i].empty() && bcnt[i].front() <= bpt) {
			bcnt[i].pop_front();
		}
		while (!acnt[i].empty() && !bcnt[i].empty()) {
			apt = acnt[i].front();
			bpt = bcnt[i].front();
			ans.push_back(i);
			acnt[i].pop_front();
			bcnt[i].pop_front();
		}
	}
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
	

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}