#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[50];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	bool pos = true;
	for (int i = 0; i < n; ++i) if (a[i] != 0) {
		pos = false;
		break;
	}
	if (pos) {
		cout << 0 << '\n';
		return;
	}
	deque<int> A;
	for (int i = 0; i < n; ++i) A.push_back(a[i]);
	while (!A.empty() && A.back() == 0) A.pop_back();
	while (!A.empty() && A.front() == 0) A.pop_front();
	pos = true;
	for (auto i: A) if (i == 0) {
		pos = false;
		break;
	}
	if (pos) {
		cout << 1 << '\n';
		return;
	}
	cout << 2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}