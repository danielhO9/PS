#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<size_t n>
void rref(vector<bitset<n>>& A) {
    int m = (int)A.size();
    for (int j = n - 1, r = 0; j >= 0 && r < m; --j) {
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
            ++r;
        }
    }
}

void solve() {
	int n; cin >> n;
	ll tot = 0ll;
	vector<bitset<60>> A(n);
	for (int i = 0; i < n; ++i) {
		ll tmp; cin >> tmp;
		A[i] = bitset<60>(tmp);
		tot ^= tmp;
	}
	
	bitset<60> B = bitset<60>(tot);
	for (int i = 0; i < n; ++i) {
		A[i] = A[i] & B;
	}
	rref(A);
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 5; j >= 0; --j) {
	// 		cout << A[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	ll ans = A[0].to_ulong();
	// for (int i = 1; i < n; ++i) {
	// 	ll tmp = ans ^ (A[i].to_ulong());
	// 	if (tmp < ans) ans = tmp;
	// }
	cout << abs(ans - (tot ^ ans)) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}