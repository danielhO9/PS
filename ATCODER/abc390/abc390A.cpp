#include <bits/stdc++.h>
using namespace std;

void solve() {
	int A[5]; for (int i = 0; i < 5; ++i) cin >> A[i];
	bool flag = true;
	for (int i = 0; i < 5; ++i) {
		if (A[i] != i + 1) {
			flag = false;
			if (i == 4) {
				cout << "No";
				return;
			}
			swap(A[i], A[i + 1]);
			break;
		}
	}
	if (flag) {
		cout << "No";
		return;
	}
	for (int i = 0; i < 5; ++i) if (A[i] != i + 1) {
		cout << "No";
		return;
	}
	cout << "Yes";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}