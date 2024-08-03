#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<size_t n>
void rref(vector<bitset<n>>& A) {
    int m = (int)A.size();
    for (int j = 59, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; i++) {
            if (A[i][j]) {
                swap(A[r], A[i]);
                break;
            }
        }
        if (A[r][j]) {
            for (int i = 0; i < m; i++) if (i != r) {
                if (A[i][j]) {
                    A[i] ^= A[r];
                }
            }
            r++;
        }
    }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	ll a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	vector<bitset<60>> A(n);
	for (int i = 0; i < n; ++i) {
		A[i] = bitset<60>(a[i] ^ a[0]);
	}
	rref(A);
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 3; j >= 0; --j) {
	// 		cout << A[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	ll ans = 0ll;
	for (int i = 0; i < n; ++i) {
		ans ^= A[i].to_ulong();
	}
	cout << ans;
}