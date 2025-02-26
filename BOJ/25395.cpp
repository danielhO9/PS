#include <bits/stdc++.h>
using namespace std;

int N, S;
int x[1000000];
int h[1000000];
int l[1000000];
int r[1000000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> S;
	for (int i = 0; i < N; ++i) cin >> x[i];
	for (int i = 0; i < N; ++i) cin >> h[i];
	for (int i = 0; i < N; ++i) {
		l[i] = lower_bound(x, x + N, x[i] - h[i]) - x;
		r[i] = upper_bound(x, x + N, x[i] + h[i]) - x;
		--r[i];
	}
	queue<int> q; q.push(S - 1);
	int curl = S - 1, curr = S - 1;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (int i = l[here]; i < curl; ++i) {
			q.push(i);
		}
		for (int i = curr + 1; i <= r[here]; ++i) {
			q.push(i);
		}
		curl = min(curl, l[here]);
		curr = max(curr, r[here]);
	}
	for (int i = curl; i <= curr; ++i) cout << i + 1 << ' ';
}