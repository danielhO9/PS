#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll l[200000], r[200000];

void solve() {
	cin >> N;
	ll minx = 0, maxx = 0;
	for (int i = 0; i < N; ++i) {
		cin >> l[i] >> r[i];
		minx += l[i];
		maxx += r[i];
	}
	if (minx <= 0 && 0 <= maxx) cout << "Yes\n";
	else {
		cout << "No";
		return;
	}
	for (int i = 0; i < N; ++i) {
		if (maxx) {
			int num = min(maxx, r[i] - l[i]);
			cout << r[i] - num << ' ';
			maxx -= num;
		} else {
			cout << r[i] << ' ';
		}
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}