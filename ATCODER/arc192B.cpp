#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int A[200000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	if (N == 1) {
		cout << "Fennec";
		return;
	} else if (N == 2) {
		cout << "Snuke";
		return;
	}
	int ocnt = 0, ecnt = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i] % 2) ++ocnt;
		else ++ecnt;
	}
	if (N == 3) {
		if (ocnt == 0) cout << "Snuke";
		else cout << "Fennec";
		return;
	}
	++ecnt;
	if (N % 2) {
		if (ecnt % 2) cout << "Fennec";
		else cout << "Snuke";
	} else {
		if (ecnt % 2) cout << "Snuke";
		else cout << "Fennec";
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}