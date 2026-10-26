#include <bits/stdc++.h>
using namespace std;
vector<int> A(6), B(6);

bool check(int x, int y, int z) {
	if (A[0] < x && x < A[1] && A[2] < y && y < A[3] && A[4] < z && z < A[5]) return true;
	return false;
}

void solve() {
	cin >> A[0] >> A[2] >> A[4] >> A[1] >> A[3] >> A[5];
	cin >> B[0] >> B[2] >> B[4] >> B[1] >> B[3] >> B[5];
	if ((A[1] > B[0] && B[1] > A[0]) && (A[3] > B[2] && B[3] > A[2]) && (A[5] > B[4] && B[5] > A[4])) {
		cout << "Yes";
		return;
	}
	cout << "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}