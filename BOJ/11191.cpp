#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void rref(vector<ll>& A) {
	if (A.empty()) return;
    const int m = A.size();
    int sz = 60;
    for (int j = sz - 1, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; ++i) {
            if ((A[i] >> j) & 1) {
                swap(A[r], A[i]);
                break;
            }
        }
        if ((A[r] >> j) & 1) {
            for (int i = 0; i < m; ++i) if (i != r) {
                if ((A[i] >> j) & 1) A[i] ^= A[r];
            }
            ++r;
        }
    }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<ll> A(n);
	for (int i = 0; i < n; ++i) cin >> A[i];
	rref(A);
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 3; j >= 0; --j) {
	// 		cout << A[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	ll ans = 0ll;
	for (int i = 0; i < n; ++i) {
		ans ^= A[i];
	}
	cout << ans;
}